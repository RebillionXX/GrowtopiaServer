#include <Manager/Database/Table/PlayerTable.hpp>
#include <fmt/core.h>
#include <Manager/Database/Interface/PlayerInterface.hpp>
#include <Utils/MiscUtils.hpp>

PlayerTable::PlayerTable(sqlpp::mysql::connection* pConnection) : m_pConnection(pConnection) {}

bool PlayerTable::IsAccountExist(const std::string& name) const {
    PlayerDB playerData{};
    for (const auto &row : (*m_pConnection)(select(all_of(playerData)).from(playerData).where(
        playerData.rawName == name && playerData.tankIdName != std::string{}
    ))) {
        if (row._is_valid)
            return true;
    }
    return false;
}

uint32_t PlayerTable::Insert(Player* pAvatar) {
    auto& det = pAvatar->GetDetail();

    if (this->IsAccountExist(det.GetTankIDName()))
        return 0;
    PlayerDB playerData{};
    return (uint32_t)((*m_pConnection)(insert_into(playerData).set(
        playerData.requestedName = /* TODO */"",
        playerData.tankIdName = det.GetTankIDName(),
        playerData.tankIdPass = det.GetTankIDPass()
        /*playerData.raw_name = player->GetRawName(),
        playerData.display_name = player->GetDisplayName(nullptr),
        playerData.relative_identifier = login->m_rid,
        playerData.machine_address = login->m_mac,
        playerData.role = player->GetRole(),
        playerData.inventory = player->Pack(PLAYER_DATA_INVENTORY),
        playerData.clothes = player->Pack(PLAYER_DATA_CLOTHES),
        playerData.gems = player->GetGems(),
        playerData.playmods = player->Pack(PLAYER_DATA_PLAYMODS),
        playerData.character_state = player->Pack(PLAYER_DATA_CHARACTER_STATE),
        playerData.country = player->GetLoginDetail()->m_country*/
    )));
}

PlayerRegistration PlayerTable::RegisterPlayer(const std::string& name, const std::string& password, const std::string& verifyPassword) {
    std::string lowerCase = name;

    if (password.length() < 8 || password.length() > 24)
        return PlayerRegistration { 
            .m_result   = PlayerRegistration::Result::INVALID_PASSWORD_LENGTH,
            .m_data     = "`4Oops!``  Your password must be between `$8`` and `$24`` characters long."
        };
    if (verifyPassword != password)
        return PlayerRegistration {
            .m_result   = PlayerRegistration::Result::MISMATCH_VERIFY_PASSWORD,
            .m_data     = "`4Oops!``  Passwords don't match.  Try again."
        };
    if (!Utils::ToLowerCase(lowerCase))
        return PlayerRegistration {
            .m_result   = PlayerRegistration::Result::INVALID_GROWID,
            .m_data     = "`4Oops!``  the name is includes invalid characters."
        };
    if (lowerCase.length() < 3 || lowerCase.length() > 18)
        return PlayerRegistration {
            .m_result   = PlayerRegistration::Result::INVALID_GROWID_LENGTH,
            .m_data     = "`4Oops!``  Your `wGrowID`` must be between `$3`` and `$18`` characters long."
        };
    if (this->IsAccountExist(lowerCase))
        return PlayerRegistration {
            .m_result   = PlayerRegistration::Result::EXIST_GROWID,
            .m_data     = fmt::format("`4Oops!``  The name `w{}`` is so cool someone else has already taken it.  Please choose a different name.", name)
        };
    if (!m_pConnection->is_valid()) {
        m_pConnection->reconnect();
        return PlayerRegistration {
            .m_result   = PlayerRegistration::Result::BAD_CONNECTION,
            .m_data     = "`4Oops!``  Server's database had bad connection, please try again."
        };
    }

    return PlayerRegistration {
        .m_result   = PlayerRegistration::Result::SUCCESS, 
        .m_data     = "" 
    };
}
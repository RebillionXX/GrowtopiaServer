#pragma once
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/mysql/mysql.h>
#include <Manager/Database/Interface/PlayerInterface.hpp>
#include <Player/Player.hpp>

struct PlayerRegistration {
public:
    enum class Result {
        SUCCESS,
        EXIST_GROWID,
        INVALID_GROWID,
        INVALID_PASSWORD, //
        INVALID_EMAIL_OR_DISCORD,
        INVALID_GROWID_LENGTH,
        INVALID_PASSWORD_LENGTH,
        MISMATCH_VERIFY_PASSWORD,
        BAD_CONNECTION
    };

public:
    PlayerRegistration::Result  m_result;
    std::string                 m_data;
};

class PlayerTable {
public:
    PlayerTable(sqlpp::mysql::connection* pConnection);
    ~PlayerTable() = default;

public:
    bool IsAccountExist(const std::string& name) const;

    uint32_t Insert(Player* pAvatar);

    PlayerRegistration RegisterPlayer(const std::string& name, const std::string& password, const std::string& verifyPassword);

private:
    sqlpp::mysql::connection* m_pConnection;
};
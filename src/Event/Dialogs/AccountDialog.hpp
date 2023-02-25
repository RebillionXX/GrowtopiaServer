#pragma once
#include <Logger/Logger.hpp>
#include <Event/EventType.hpp>
#include <Event/EventPool.hpp>
#include <Manager/Database/Database.hpp>
#include <Packet/TextFunction.hpp>

DIALOG_EVENT("growid_apply", OnDialogGrowIDApply) {
    if (!pAvatar->GetDetail().GetTankIDName().empty())
        return;
    
    PlayerTable* pTable = (PlayerTable*)GetDatabase()->GetTable(DATABASE_PLAYER_TABLE);
    if (!pTable)
        return;

    std::string 
        name            = eventParser.Get("logon", 1),
        password        = eventParser.Get("password", 1),
        verifyPassword  = eventParser.Get("verify_password", 1)
    ;
    auto lowerName = name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    auto playerAccount = pTable->RegisterPlayer(name, password, verifyPassword);
    if (playerAccount.m_result != PlayerRegistration::Result::SUCCESS) {
        pAvatar->PlayerDialog::Send(DIALOG_TYPE_REGISTRATION, TextParse({ 
            { "logon",              name                    }, 
            { "password",           password                },
            { "verify_password",    verifyPassword          },
            { "extra_message",      playerAccount.m_data    }
        }));
        return;
    }

    auto& det = pAvatar->GetDetail();
    det.SetTankIDName(lowerName);
    det.SetTankIDPass(password);
    pAvatar->SetRawName(name);
    // Unfinished //
}
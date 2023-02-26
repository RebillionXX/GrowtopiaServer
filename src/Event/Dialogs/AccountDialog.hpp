#pragma once
#include <config.hpp>
#include <Logger/Logger.hpp>
#include <Event/EventType.hpp>
#include <Event/EventPool.hpp>
#include <Manager/Database/Database.hpp>
#include <Manager/Item/ItemComponent.hpp>
#include <Packet/TextFunction.hpp>
#include <Packet/VariantFunction.hpp>

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

    TankInfo& det = pAvatar->GetDetail();
    PlayerItems* pItems = pAvatar->GetItems();

    det.SetTankIDName(lowerName);
    det.SetTankIDPass(password);

    pItems->AddItem(ITEM_MY_FIRST_WORLD_LOCK,   1);
    pItems->AddItem(ITEM_PICKAXE,               1);
    
    pAvatar->SetRawName(name);
    //pAvatar->SetUserId(pTable->Insert(pAvatar));

    CAction::PlaySFX((ENetPeer*)pAvatar, "success", 0);
    VarList::SetHasGrowID((ENetPeer*)pAvatar, true, name, det.GetTankIDPass());
    VarList::OnConsoleMessage((ENetPeer*)pAvatar, fmt::format("`oA `wGrowID`` with the logon of `w{}`` created. Write it and your password down as the will be required to logon!``", pAvatar->GetRawName()));
    VarList::OnConsoleMessage((ENetPeer*)pAvatar, fmt::format("`5Welcome to `w{}`5, press `wBack`` and then press `wConnect``, enjoy!", Configuration::GetName()));
    //pAvatar->RequestDisconnect();
    Logger::Print(INFO, "We got it?");
}
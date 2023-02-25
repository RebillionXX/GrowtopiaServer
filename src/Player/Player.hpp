#pragma once
#include <memory>
#include <enet/enet.h>
#include <ENetWrapper/Peer.hpp>
#include <Protocol/TankInfo.hpp>
#include <Player/PlayerDialog/PlayerDialog.hpp>
#include <Player/PlayerItems.hpp>
#include <Utils/TextParse.hpp>

class Player : public Peer,
    public PlayerDialog {
public:
    explicit Player(ENetPeer* pPeer);
    ~Player();
    
    operator ENetPeer*() { 
        return this->Get();
    }
public:
    bool IsFlagOn(ePlayerFlags flag) const;
    void SetFlag(ePlayerFlags flag);
    void RemoveFlag(ePlayerFlags flag);

    std::string GetRawName() const;
    void SetRawName(const std::string& name);

public:
    PlayerItems* GetItems();
    TankInfo& GetDetail();

public:
    void OnConnect();
    void OnDisconnect();

private:
    std::shared_ptr<PlayerItems> m_pItems;

private:
    uint32_t m_flags;
    TankInfo m_detail;

    std::string m_rawName;
    std::string m_displayName;

    std::string m_emailAddress;
    uint64_t m_discordClientId;
};
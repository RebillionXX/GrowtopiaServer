#include <Player/Player.hpp>
#include <ENetWrapper/ENetWrapper.hpp>
#include <Packet/PacketFactory.hpp>
#include <Logger/Logger.hpp>

Player::Player(ENetPeer* peer) : Peer(peer),
    PlayerDialog(peer),
    m_flags(0),
    m_detail(), m_items(peer) { 
}
Player::~Player() {
    // TODO
}

bool Player::IsFlagOn(ePlayerFlags flag) const {
    if (m_flags & flag)
        return true;
    return false;
}
void Player::SetFlag(ePlayerFlags flag) {
    m_flags |= flag;
}
void Player::RemoveFlag(ePlayerFlags flag) {
    m_flags &= ~flag;
}

uint32_t Player::GetUserId() const {
    return m_userId;
}
void Player::SetUserId(const uint32_t& userId) {
    m_userId = userId;
}

std::string Player::GetRawName() const {
    return m_rawName;
}
void Player::SetRawName(const std::string& name) {
    m_rawName = name;
}

TankInfo& Player::GetDetail() {
    return m_detail;
}
PlayerItems* Player::GetItems() {
    return &m_items;
}

void Player::OnConnect() {
    Logger::Print(INFO, "A player connected with IP {}, connectId {} and {} pings.", this->GetIp(), this->GetConnectId(), this->GetPing());
    
    auto packet = SLoginInformationRequestPacket();
    ENetWrapper::SendPacket(this->Get(), packet);
}
void Player::OnDisconnect() {
    Logger::Print(INFO, "A player disconnected with IP {}, connectId {} and {} pings.", this->GetIp(), this->GetConnectId(), this->GetPing());
}
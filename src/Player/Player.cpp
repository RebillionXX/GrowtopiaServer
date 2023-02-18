#include <Player/Player.hpp>
#include <ENetWrapper/ENetWrapper.hpp>
#include <Packet/PacketFactory.hpp>
#include <Logger/Logger.hpp>

Player::Player(ENetPeer* pPeer) : 
    Peer(pPeer), 
    m_flags(0), m_detail() {
    m_pItems = std::make_shared<PlayerItems>(pPeer);
}
Player::~Player() {
    if (m_pItems)
        m_pItems.reset();
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

std::string Player::GetRawName() const {
    return m_rawName;
}
void Player::SetRawName(const std::string& name) {
    m_rawName = name;
}

PlayerItems* Player::GetItems() {
    return m_pItems.get();
}
TankInfo& Player::GetDetail() {
    return m_detail;
}

template <Player::DialogType type>
void Player::SendDialog(TextParse parser) {
    
}

void Player::OnConnect() {
    Logger::Print(INFO, "A player connected with IP {}, connectId {} and {} pings.", this->GetIp(), this->GetConnectId(), this->GetPing());
    auto packet = SLoginInformationRequestPacket();
    ENetWrapper::SendPacket(this->Get(), packet);
}
void Player::OnDisconnect() {

}
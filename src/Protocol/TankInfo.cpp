#include <Protocol/TankInfo.hpp>
#include <fmt/core.h>

bool TankInfo::IsFlagOn(eClientFlags flag) const {
    if (m_flags & flag)
        return true;
    return false;
}
void TankInfo::SetFlag(eClientFlags flag) {
    m_flags |= flag;
}
void TankInfo::RemoveFlag(eClientFlags flag) {
    m_flags &= ~flag;
}
    
bool TankInfo::SetRequestedName(const std::string& data) {
    if (data.length() > 16 || data.length() < 1)
        return false;
    m_requestedName = data;
    return true;
}
std::string TankInfo::GetRequestedName() const {
    if (m_requestedName.empty())
        return std::string{};
    return m_requestedName;
}
bool TankInfo::SetTankIDName(const std::string& data) {
    if (data.length() > 24 || data.length() < 1)
        return false;
    m_tankIDName = data;
    return true;
}
std::string TankInfo::GetTankIDName() const {
    if (m_tankIDName.empty())
        return std::string{};
    return m_tankIDName;
}
bool TankInfo::SetTankIDPass(const std::string& data) {
    if (data.length() > 24 || data.length() < 1)
        return false;
    m_tankIDPass = data;
    return true;
}
std::string TankInfo::GetTankIDPass() const {
    if (m_tankIDPass.empty())
        return std::string{};
    return m_tankIDPass;
}

bool TankInfo::SetRelativeId(const std::string& data) {
    if (data.length() > 32 || data.length() < 1)
        return false;
    m_relativeId = data;
    return true;
}
std::string TankInfo::GetRelativeId() const {
    if (m_relativeId.empty())
        return std::string{};
    return m_relativeId;
}

bool TankInfo::SetCountryCode(const std::string& data) {
    if (data.length() > 3 || data.length() < 1)
        return false;
    m_countryCode = data;
    return true;
}
std::string TankInfo::GetCountryCode() const {
    if (m_countryCode.empty())
        return std::string{};
    return m_countryCode;
}

bool TankInfo::Serialize(TextParse parser) {
    if (!this->SetRequestedName(parser.Get("requestedName", 1)) ||
        !this->SetCountryCode(parser.Get("country", 1)) ||
        !this->SetRelativeId(parser.Get("rid", 1)))
        return false;

    this->m_gameVersion = std::stof(parser.Get("game_version", 1));
    auto platformID = parser.Get("platformID", 1);
    if (platformID.length() < 1)
        return false;
    this->m_platformID = static_cast<int32_t>(platformID[0]);
    if (this->m_platformID < 0)
        return false;
    return true;
}
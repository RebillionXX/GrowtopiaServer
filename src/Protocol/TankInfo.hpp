#pragma once
#include <array>
#include <string>
#include <Utils/TextParse.hpp>

enum ePlatformID {
    PLATFORM_ID_UNKNOWN = -1,
    PLATFORM_ID_WINDOWS,
    PLATFORM_ID_IOS,
    PLATFORM_ID_OSX,
    PLATFORM_ID_LINUX,
    PLATFORM_ID_ANDROID,
    PLATFORM_ID_WINDOWS_MOBILE,
    PLATFORM_ID_WEBOS,
    PLATFORM_ID_BBX,
    PLATFORM_ID_FLASH,
    PLATFORM_ID_HTML5,
    PLATFORM_ID_MAXVAL
};

enum eClientFlags {
    CLIENTFLAG_LOGGED_ON            = (1 << 0),
    CLIENTFLAG_IS_IN                = (1 << 1),
    CLIENTFLAG_UPDATING_ITEMS       = (1 << 2),
    CLIENTFLAG_UPDATING_TRIBUTE     = (1 << 3),
    CLIENTFLAG_IS_FACING_LEFT       = (1 << 4)
};
enum ePlayerFlags {
    PLAYERFLAG_IS_INVISIBLE         = (1 << 0),
    PLAYERFLAG_IS_MOD               = (1 << 1),
    PLAYERFLAG_IS_SUPER_MOD         = (1 << 2)
};

struct TankInfo {
public:
    bool IsFlagOn(eClientFlags flag) const;
    void SetFlag(eClientFlags flag);
    void RemoveFlag(eClientFlags flag);

    bool Serialize(TextParse parser);

    bool SetRequestedName(const std::string& data);
    std::string GetRequestedName() const;
    bool SetTankIDName(const std::string& data);
    std::string GetTankIDName() const;
    bool SetTankIDPass(const std::string& data);
    std::string GetTankIDPass() const;

    bool SetRelativeId(const std::string& data);
    std::string GetRelativeId() const;

    bool SetCountryCode(const std::string& data);
    std::string GetCountryCode() const;

private:
    std::string     m_requestedName; //16
    std::string     m_tankIDName; //24
    std::string     m_tankIDPass; //24

    std::string     m_relativeId; //32
    std::string     m_googleId,
                    m_securityId,
                    m_aid,
                    m_vid; //16

    std::string     m_countryCode; //3
    std::string     m_machineAddress;

    float           m_gameVersion = 0.0f;
    int32_t         m_platformID = PLATFORM_ID_UNKNOWN;
    std::string     m_meta = "";    

    uint32_t        m_flags = 0;
};
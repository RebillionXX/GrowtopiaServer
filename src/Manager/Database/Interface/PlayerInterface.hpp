#pragma once
#include <cstdint>
#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace PlayerInterface {
    struct ID {
        struct _alias_t {
            static constexpr const char _literal[] = "ID";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T Id;
                T& operator()() { return Id; }
                const T& operator()() const { return Id; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::integral, ::sqlpp::tag::must_not_insert, ::sqlpp::tag::must_not_update>;
    };
    struct RequestedName {
        struct _alias_t {
            static constexpr const char _literal[] = "RequestedName";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T requestedName;
                T& operator()() { return requestedName; }
                const T& operator()() const { return requestedName; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::varchar, ::sqlpp::tag::must_not_update>;
    };
    struct TankIDName {
        struct _alias_t {
            static constexpr const char _literal[] = "TankIDName";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T tankIdName;
                T& operator()() { return tankIdName; }
                const T& operator()() const { return tankIdName; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
    };
    struct TankIDPass {
        struct _alias_t {
            static constexpr const char _literal[] = "TankIDPass";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T tankIdPass;
                T& operator()() { return tankIdPass; }
                const T& operator()() const { return tankIdPass; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
    };
    struct RawName {
        struct _alias_t {
            static constexpr const char _literal[] = "RawName";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T rawName;
                T& operator()() { return rawName; }
                const T& operator()() const { return rawName; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
    };
    struct DisplayName {
        struct _alias_t {
            static constexpr const char _literal[] = "DisplayName";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T displayName;
                T& operator()() { return displayName; }
                const T& operator()() const { return displayName; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
    };
    struct EmailAddress {
        struct _alias_t {
            static constexpr const char _literal[] = "EmailAddress";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T emailAddress;
                T& operator()() { return emailAddress; }
                const T& operator()() const { return emailAddress; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
    };
    struct DiscordClientID {
        struct _alias_t {
            static constexpr const char _literal[] = "DiscordClientID";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T discordClientId;
                T& operator()() { return discordClientId; }
                const T& operator()() const { return discordClientId; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::bigint>;
    };
    struct Gems {
        struct _alias_t {
            static constexpr const char _literal[] = "Gems";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T gems;
                T& operator()() { return gems; }
                const T& operator()() const { return gems; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
    };  
    struct PlayerFlags {
        struct _alias_t {
            static constexpr const char _literal[] = "PlayerFlags";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T playerFlags;
                T& operator()() { return playerFlags; }
                const T& operator()() const { return playerFlags; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
    };
    struct PlayerItems {
        struct _alias_t {
            static constexpr const char _literal[] = "PlayerItems";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T playerItems;
                T& operator()() { return playerItems; }
                const T& operator()() const { return playerItems; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::blob>;
    };
    struct PlayerClothes {
        struct _alias_t {
            static constexpr const char _literal[] = "PlayerClothes";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T playerClothes;
                T& operator()() { return playerClothes; }
                const T& operator()() const { return playerClothes; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::blob>;
    };
    struct PlayMods {
        struct _alias_t {
            static constexpr const char _literal[] = "PlayMods";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T playMods;
                T& operator()() { return playMods; }
                const T& operator()() const { return playMods; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::blob>;
    };
    struct CharacterState {
        struct _alias_t {
            static constexpr const char _literal[] = "CharacterState";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T characterState;
                T& operator()() { return characterState; }
                const T& operator()() const { return characterState; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::blob>;
    };
}

struct PlayerDB 
: sqlpp::table_t<PlayerDB, 
    PlayerInterface::ID, 
    PlayerInterface::RequestedName, 
    PlayerInterface::TankIDName, 
    PlayerInterface::TankIDPass, 
    PlayerInterface::RawName,
    PlayerInterface::DisplayName, 
    PlayerInterface::EmailAddress, 
    PlayerInterface::DiscordClientID, 
    PlayerInterface::Gems,
    PlayerInterface::PlayerFlags,
    PlayerInterface::PlayerItems,
    PlayerInterface::PlayerClothes,
    PlayerInterface::PlayMods,
    PlayerInterface::CharacterState> {
    struct _alias_t {
        static constexpr const char _literal[] = "Players";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template <typename T>
        struct _member_t {
            T playerDB;
            T& operator()() { return playerDB; }
            const T& operator()() const { return playerDB; }
        };
    };
};
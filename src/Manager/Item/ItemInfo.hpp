#pragma once
#include <string>
#include <Manager/Item/ItemType.hpp>
#include <Manager/Item/ItemFlags.hpp>
#include <Utils/BinaryReader.hpp>
#include <Utils/BinaryWriter.hpp>
#include <Utils/Math.hpp>

struct ItemInfo {
    uint32_t m_Id;
    uint8_t m_editableType = 0;
    uint8_t m_itemCategory = 0;
    uint8_t m_itemType = 0;
    uint8_t m_material = 0;

    std::string m_name = "";
    std::string m_textureFile = "";

    uint32_t m_textureFileHash = 0;
    uint8_t m_visualEffect = 0;

    uint32_t m_flags1 = 0;
    uint32_t m_ingredient = 0;

    CL_Vec2<uint8_t> m_texture = CL_Vec2<uint8_t>{ 0, 0 };
    uint8_t m_spreadType = 0;
    uint8_t m_isStripeyWallpaper = 0;
    uint8_t m_collisionType = 0;
    uint8_t m_breakHits = 0;

    uint32_t m_resetTime = 0;
    uint32_t m_growTime = 0;
    uint32_t m_clothingType = 0;

    uint16_t m_rarity = 0;
    uint8_t m_maxAmount = 0;

    std::string m_extraFile = "";
    uint32_t m_extraFileHash = 0;

    union {
        uint32_t m_audioVolume = 0;
        uint32_t m_weatherId;
    };

    struct {
        std::string m_name = "";
        std::string m_prefix = "";
        std::string m_suffix = "";
        std::string m_ability = "";
    } m_pet;

    struct {
        uint8_t m_base = 0;
        uint8_t m_overlay = 0;
        uint32_t m_color = 0;
        uint32_t m_overlayColor = 0;
    } m_seed;

    struct {
        uint8_t m_base = 0;
        uint8_t m_leaves = 0;
    } m_tree;

    uint16_t m_flags2 = 0;
    uint16_t m_rayman = 0;

    std::string m_extraOptions1 = "";
    std::string m_textureFile2 = "";
    std::string m_extraOptions2 = "";
    std::string m_punchOptions = "";

    uint32_t m_unknownVal3 = 0;
    uint32_t m_unknownVal4 = 0;
    uint32_t m_unknownVal5 = 0;

    uint8_t m_bodypart[9] = { 0 };
    uint8_t m_reserved[80] = { 0 };

    bool m_hasExtra = false;
    CL_Vec2<uint8_t> m_defaultTexture = CL_Vec2<uint8_t>{ 0, 0 };
    uint32_t m_modsActive = 0;
    std::string m_description = "This is a seed.";

    std::string Cypher(const std::string& input) {
        constexpr std::string_view key{ "PBG892FXX982ABC*" };
        std::string ret(input.size(), 0);

        for (uint32_t index = 0; index < input.size(); index++)
            ret[index] = static_cast<char>(input[index] ^ key[(index + this->m_Id) % key.size()]);
        return ret;
    }
    bool IsBackground() const {
        return m_itemType == ITEMTYPE_BACKGROUND ||
            m_itemType == ITEMTYPE_BACK_BOOMBOX ||
            m_itemType == ITEMTYPE_MUSIC_NOTE;
    }

    std::size_t GetMemoryUsage() const {
        std::size_t ret{ 8 };
        ret += sizeof(uint16_t) + m_name.size();
        ret += sizeof(uint16_t) + m_textureFile.size();
        ret += 34;
        ret += sizeof(uint16_t) + m_extraFile.size();
        ret += 12;
        ret += sizeof(uint16_t) + m_pet.m_name.size();
        ret += sizeof(uint16_t) + m_pet.m_prefix.size();
        ret += sizeof(uint16_t) + m_pet.m_suffix.size();
        ret += sizeof(uint16_t) + m_pet.m_ability.size();
        ret += 16;
        ret += sizeof(uint16_t) + m_extraOptions1.size();
        ret += sizeof(uint16_t) + m_textureFile2.size();
        ret += sizeof(uint16_t) + m_extraOptions2.size();
        ret += 80;
        ret += sizeof(uint16_t) + m_punchOptions.size();
        ret += 21;
        return ret;
    }
    void Pack(BinaryWriter& buffer) {
        buffer.Write<uint32_t>(m_Id);
        buffer.Write<uint8_t>(m_editableType);
        buffer.Write<uint8_t>(m_itemCategory);
        buffer.Write<uint8_t>(m_itemType);
        buffer.Write<uint8_t>(m_material);

        buffer.Write(this->Cypher(m_name));
        buffer.Write(m_textureFile, sizeof(uint16_t));
        buffer.Write<uint32_t>(m_textureFileHash);

        buffer.Write<uint8_t>(m_visualEffect);
        buffer.Write<uint32_t>(m_flags1);
        buffer.Write<uint8_t>(m_texture.X);
        buffer.Write<uint8_t>(m_texture.Y);

        buffer.Write<uint8_t>(m_spreadType);
        buffer.Write<uint8_t>(m_isStripeyWallpaper);
        buffer.Write<uint8_t>(m_collisionType);
        buffer.Write<uint8_t>(m_breakHits);
        buffer.Write<uint32_t>(m_resetTime);
        buffer.Write<uint8_t>(m_clothingType);
        buffer.Write<uint16_t>(m_rarity);
        buffer.Write<uint8_t>(m_maxAmount);

        buffer.Write(m_extraFile);
        buffer.Write<uint32_t>(m_extraFileHash);
        buffer.Write<uint32_t>(m_audioVolume);

        buffer.Write(m_pet.m_name);
        buffer.Write(m_pet.m_prefix);
        buffer.Write(m_pet.m_suffix);
        buffer.Write(m_pet.m_ability);
        
        buffer.Write<uint8_t>(m_seed.m_base);
        buffer.Write<uint8_t>(m_seed.m_overlay);
        buffer.Write<uint8_t>(m_tree.m_base);
        buffer.Write<uint8_t>(m_tree.m_leaves);
        buffer.Write<uint32_t>(m_seed.m_color);
        buffer.Write<uint32_t>(m_seed.m_overlayColor);
        buffer.Write<uint32_t>(m_ingredient);
        buffer.Write<uint32_t>(m_growTime);
        buffer.Write<uint16_t>(m_flags2);
        buffer.Write<uint16_t>(m_rayman);

        buffer.Write(m_extraOptions1);
        buffer.Write(m_textureFile2, sizeof(uint16_t));
        buffer.Write(m_extraOptions2);

        for (auto index = 0; index < 80; index++)
            buffer.Write<uint8_t>(m_reserved[index]);

        buffer.Write(m_punchOptions);
        buffer.Write<uint32_t>(m_unknownVal3);

        for (auto index = 0; index < 9; index++)
            buffer.Write<uint8_t>(m_bodypart[index]);
        buffer.Write<uint32_t>(m_unknownVal4);
        buffer.Write<uint32_t>(m_unknownVal5);
    }
    void Serialize(BinaryReader& br) {
        m_Id = br.Read<uint32_t>();
        m_editableType = br.Read<uint8_t>();
        m_itemCategory = br.Read<uint8_t>();
        m_itemType = br.Read<uint8_t>();
        m_material = br.Read<uint8_t>();

        m_name = this->Cypher(br.ReadStringU16());
        m_textureFile = br.ReadStringU16();

        m_textureFileHash = br.Read<uint32_t>();
        m_visualEffect = br.Read<uint8_t>();
        m_flags1 = br.Read<uint32_t>();
        m_texture = CL_Vec2<uint8_t>{ br.Read<uint8_t>(), br.Read<uint8_t>() };
        m_spreadType = br.Read<uint8_t>();
        m_isStripeyWallpaper = br.Read<uint8_t>();
        m_collisionType = br.Read<uint8_t>();
        m_breakHits = br.Read<uint8_t>();
        m_resetTime = br.Read<uint32_t>();
        m_clothingType = br.Read<uint8_t>();
        m_rarity = br.Read<uint16_t>();
        m_maxAmount = br.Read<uint8_t>();

        m_extraFile = br.ReadStringU16();

        m_extraFileHash = br.Read<uint32_t>();
        m_audioVolume = br.Read<uint32_t>();

        m_pet.m_name = br.ReadStringU16();
        m_pet.m_prefix = br.ReadStringU16();
        m_pet.m_suffix = br.ReadStringU16();
        m_pet.m_ability = br.ReadStringU16();

        m_seed.m_base = br.Read<uint8_t>();
        m_seed.m_overlay = br.Read<uint8_t>();
        m_tree.m_base = br.Read<uint8_t>();
        m_tree.m_leaves = br.Read<uint8_t>();
        m_seed.m_color = br.Read<uint32_t>();
        m_seed.m_overlayColor = br.Read<uint32_t>();

        m_ingredient = br.Read<uint32_t>();
        m_growTime = br.Read<uint32_t>();
        m_flags2 = br.Read<uint16_t>();
        m_rayman = br.Read<uint16_t>();

        m_extraOptions1 = br.ReadStringU16();
        m_textureFile2 = br.ReadStringU16();
        m_extraOptions2 = br.ReadStringU16();
        for (auto index = 0; index < 80; index++)
            m_reserved[index] = br.Read<uint8_t>();
        
        m_punchOptions = br.ReadStringU16();
        m_unknownVal3 = br.Read<uint32_t>();
        for (auto index = 0; index < 9; index++)
            m_bodypart[index] = br.Read<uint8_t>();
        m_unknownVal4 = br.Read<uint32_t>();
        m_unknownVal5 = br.Read<uint32_t>();

        switch (m_spreadType) {
            case TILESPREAD_DIRECT8:
            case TILESPREAD_DIRECT4: {
                m_defaultTexture = CL_Vec2<uint8_t>(m_texture.X + 4, m_texture.Y + 1);
            } break;
            case TILESPREAD_HORIZONTAL:
            case TILESPREAD_VERTICAL: {
                m_defaultTexture = CL_Vec2<uint8_t>(m_texture.X + 3, m_texture.Y);
            } break;
            default: {
                m_defaultTexture = CL_Vec2<uint8_t>(m_texture.X, m_texture.Y);
            } break;
        }

        switch (m_itemType) {
        case ITEMTYPE_DOOR:
        case ITEMTYPE_LOCK:
        case ITEMTYPE_SIGN:
        case ITEMTYPE_MAIN_DOOR:
        case ITEMTYPE_SEED:
        case ITEMTYPE_PORTAL:
        case ITEMTYPE_MAILBOX:
        case ITEMTYPE_BULLETIN:
        case ITEMTYPE_DICE:
        case ITEMTYPE_PROVIDER:
        case ITEMTYPE_ACHIEVEMENT:
        case ITEMTYPE_SUNGATE:
        case ITEMTYPE_HEART_MONITOR:
        case ITEMTYPE_DONATION_BOX:
        case ITEMTYPE_TOYBOX:
        case ITEMTYPE_MANNEQUIN:
        case ITEMTYPE_SECURITY_CAMERA:
        case ITEMTYPE_MAGIC_EGG:
        case ITEMTYPE_GAME_RESOURCES:
        case ITEMTYPE_GAME_GENERATOR:
        case ITEMTYPE_XENONITE:
        case ITEMTYPE_DRESSUP:
        case ITEMTYPE_CRYSTAL:
        case ITEMTYPE_BURGLAR:
        case ITEMTYPE_SPOTLIGHT:
        case ITEMTYPE_DISPLAY_BLOCK:
        case ITEMTYPE_VENDING_MACHINE:
        case ITEMTYPE_FISHTANK:
        case ITEMTYPE_SOLAR:
        case ITEMTYPE_FORGE:
        case ITEMTYPE_GIVING_TREE:
        case ITEMTYPE_GIVING_TREE_STUMP:
        case ITEMTYPE_STEAM_ORGAN:
        case ITEMTYPE_TAMAGOTCHI:
        case ITEMTYPE_SWING:
        case ITEMTYPE_FLAG:
        case ITEMTYPE_LOBSTER_TRAP:
        case ITEMTYPE_ART_CANVAS:
        case ITEMTYPE_BATTLE_CAGE:
        case ITEMTYPE_PET_TRAINER:
        case ITEMTYPE_STEAM_ENGINE:
        case ITEMTYPE_LOCKBOT:
        case ITEMTYPE_WEATHER_SPECIAL:
        case ITEMTYPE_SPIRIT_STORAGE:
        case ITEMTYPE_DISPLAY_SHELF:
        case ITEMTYPE_VIP_ENTRANCE:
        case ITEMTYPE_CHALLENGE_TIMER:
        case ITEMTYPE_CHALLENGE_FLAG:
        case ITEMTYPE_FISH_MOUNT:
        case ITEMTYPE_PORTRAIT:
        case ITEMTYPE_WEATHER_SPECIAL2:
        case ITEMTYPE_FOSSIL_PREP:
        case ITEMTYPE_DNA_MACHINE:
        case ITEMTYPE_BLASTER:
        case ITEMTYPE_CHEMTANK:
        case ITEMTYPE_STORAGE:
        case ITEMTYPE_OVEN:
        case ITEMTYPE_SUPER_MUSIC:
        case ITEMTYPE_GEIGER_CHARGER:
        case ITEMTYPE_ADVENTURE_RESET:
        case ITEMTYPE_TOMB_ROBBER:
        case ITEMTYPE_FACTION:
        case ITEMTYPE_RED_FACTION:
        case ITEMTYPE_GREEN_FACTION:
        case ITEMTYPE_BLUE_FACTION:
        case ITEMTYPE_FISHGOTCHI_TANK:
        case ITEMTYPE_ITEM_SUCKER:
        case ITEMTYPE_ROBOT:
        case ITEMTYPE_TICKET:
        case ITEMTYPE_STATS_BLOCK:
        case ITEMTYPE_FIELD_NODE:
        case ITEMTYPE_OUIJA_BOARD:
        case ITEMTYPE_AUTO_ACTION_BREAK:
        case ITEMTYPE_AUTO_ACTION_HARVEST:
        case ITEMTYPE_AUTO_ACTION_HARVEST_SUCK:
        case ITEMTYPE_LIGHTNING_IF_ON:
        case ITEMTYPE_PHASED_BLOCK:
        case ITEMTYPE_PASSWORD_STORAGE:
        case ITEMTYPE_PHASED_BLOCK_2:
        case ITEMTYPE_WEATHER_INFINITY:
        case ITEMTYPE_KRANKENS_BLOCK:
        case ITEMTYPE_FRIENDS_ENTRANCE:
        case 30:
        case 133: {
            m_hasExtra = true;
            break;
        }
        }
    }
};
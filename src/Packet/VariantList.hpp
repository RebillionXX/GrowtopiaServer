#pragma once
#include <memory>
#include <variant>
#include <enet/enet.h>
#include <Packet/GameUpdatePacket.hpp>
#include <Utils/Math.hpp>
#include <Utils/BinaryReader.hpp>
#include <Utils/BinaryWriter.hpp>

enum class VariantType : uint8_t {
    NONE,
    FLOAT,
    STRING,
    VECTOR_2,
    VECTOR_3,
    UNSIGNED_INT,
    INT = 9,
};

class Variant {
public:
    using DataType = std::variant<float, std::string, CL_Vec2<float>, CL_Vec3<float>, uint32_t, int32_t>;
    Variant();
    Variant(const DataType& var);

    template <typename T>
    T Get() const;
    VariantType GetType() const;
    std::size_t GetMemoryUsage() const;

    void Serialize(BinaryReader& br);
    void Pack(BinaryWriter& buffer);

private:
    DataType mObject;
};

class VariantList {
public:
    VariantList();
    VariantList(uint8_t* pData);
    ~VariantList();

    std::vector<Variant> GetObjects() const;
    std::size_t GetTotalObjects() const;

    std::size_t GetMemoryUsage() const;

    void Insert(Variant::DataType data);
    uint8_t* Pack();

public:
    static VariantList Create(std::string vType, int32_t executionDelay = -1, int32_t netId = -1);

    int32_t executionDelay;
    int32_t netId;   

private:
    std::vector<Variant> mObjects;
};
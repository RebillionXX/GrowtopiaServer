#include <Packet/VariantList.hpp>
#include <fmt/core.h>
#include <ENetWrapper/Peer.hpp>

Variant::Variant() : mObject() {}
Variant::Variant(const DataType& var) : mObject({ var }) {}

template<typename T>
T Variant::Get() const {
    return std::get<T>(mObject);
}
VariantType Variant::GetType() const {
    switch (mObject.index())
    {
    case 0: return VariantType::FLOAT;
    case 1: return VariantType::STRING;
    case 2: return VariantType::VECTOR_2;
    case 3: return VariantType::VECTOR_3;
    case 4: return VariantType::UNSIGNED_INT;
    case 5: return VariantType::INT;
    default: return VariantType::NONE;
    }
}
std::size_t Variant::GetMemoryUsage() const {
    std::size_t memoryAlloc = 1;
    switch(this->GetType()) {
    case VariantType::STRING: { memoryAlloc += sizeof(int32_t) + this->Get<std::string>().size(); } break;
    case VariantType::VECTOR_2: { memoryAlloc += sizeof(CL_Vec2<float>); } break;
    case VariantType::VECTOR_3: { memoryAlloc += sizeof(CL_Vec3<float>); } break;
    default: { memoryAlloc += sizeof(int32_t); } break;
    }
    return memoryAlloc;
}

void Variant::Serialize(BinaryReader& br) {
    VariantType objType = static_cast<VariantType>(br.Read<uint8_t>());

    switch (objType) {
    case VariantType::FLOAT: { mObject = DataType({ br.Read<float>() }); } break;
    case VariantType::STRING: { mObject = DataType({ br.ReadStringU32() }); } break;
    case VariantType::VECTOR_2: { mObject = DataType({ br.Read<CL_Vec2<float>>() }); } break;
    case VariantType::VECTOR_3: { mObject = DataType({ br.Read<CL_Vec3<float>>() }); } break;
    case VariantType::UNSIGNED_INT: { mObject = DataType({ br.Read<uint32_t>() }); } break;
    case VariantType::INT: { mObject = DataType({ br.Read<int32_t>() }); } break;
    default:
        break;
    }
}
void Variant::Pack(BinaryWriter& buffer) {
    buffer.Write<uint8_t>(static_cast<uint8_t>(this->GetType()));

    switch (this->GetType()) {
    case VariantType::FLOAT: { buffer.Write<float>(this->Get<float>()); } break;
    case VariantType::STRING: { buffer.Write(this->Get<std::string>(), sizeof(uint32_t)); } break;
    case VariantType::VECTOR_2: {
        auto value = this->Get<CL_Vec2<float>>();
        buffer.Write<float>(value.X);
        buffer.Write<float>(value.Y);
    } break;
    case VariantType::VECTOR_3: {
        auto value = this->Get<CL_Vec3<float>>();
        buffer.Write<float>(value.X);
        buffer.Write<float>(value.Y);
        buffer.Write<float>(value.Z);
    } break;
    case VariantType::UNSIGNED_INT: { buffer.Write<uint32_t>(this->Get<uint32_t>()); } break;
    case VariantType::INT: { buffer.Write<int>(this->Get<int32_t>()); } break;
    default:
        break;
    }
}

VariantList::VariantList() : mObjects{}, executionDelay{ 0 }, netId{ -1 } {}
VariantList::VariantList(uint8_t* pData) {
    BinaryReader br(pData);
    auto objectCount = br.Read<uint8_t>();
    fmt::print("Serializing VariantList...\n");
    fmt::print("vList -> Loading {} Objects.\n", objectCount);
    
    mObjects.reserve(objectCount);
    for (auto index = 0; index < objectCount; index++) {
        br.Skip(sizeof(uint8_t));
        auto& vObject = mObjects.emplace_back();
        vObject.Serialize(br);
        fmt::print("vList::Object[{}] -> {}\n", index, vObject.Get<std::string>());
    }
}
VariantList::~VariantList() { mObjects.clear(); }

std::vector<Variant> VariantList::GetObjects() const {
    return mObjects;
}
std::size_t VariantList::GetTotalObjects() const {
    return mObjects.size();
}

std::size_t VariantList::GetMemoryUsage() const {
    std::size_t memoryAlloc = 1;
    for (auto obj : this->GetObjects())
        memoryAlloc += obj.GetMemoryUsage() + sizeof(uint8_t);
    return memoryAlloc;
}

void VariantList::Insert(Variant::DataType data) {
    mObjects.push_back({ data });
}
uint8_t* VariantList::Pack() {
    auto memoryAlloc = this->GetMemoryUsage();

    BinaryWriter buffer(memoryAlloc);
    buffer.Write<uint8_t>(mObjects.size());
    for (auto index = 0; index < mObjects.size(); index++) {
        buffer.Write<uint8_t>(index);
        mObjects[index].Pack(buffer);
    }

    uint8_t* pData = (uint8_t*)std::malloc(memoryAlloc);
    std::memcpy(pData, buffer.Get(), memoryAlloc);
    return pData;
}

VariantList VariantList::Create(std::string vType, int32_t executionDelay, int32_t netId) {
    VariantList vList;
    vList.executionDelay = executionDelay;
    vList.netId = netId;
    vList.Insert(vType);
    return vList;
}
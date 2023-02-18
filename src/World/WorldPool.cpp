#include <World/WorldPool.hpp>

WorldPool::~WorldPool() {
    /*for (auto& [name, world] : this->m_worlds)
        this->RemoveWorld(name);*/
    m_worlds.clear();
}

std::unordered_map<std::string, std::shared_ptr<World>> WorldPool::GetWorlds() {
    return this->m_worlds;
}
size_t WorldPool::GetActiveWorlds() const {
    return m_worlds.size();
}
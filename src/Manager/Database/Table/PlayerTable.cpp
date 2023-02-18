#include <Manager/Database/Table/PlayerTable.hpp>

PlayerTable::PlayerTable(sqlpp::mysql::connection* pConnection) : m_pConnection(pConnection) {}
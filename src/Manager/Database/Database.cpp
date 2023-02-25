#include <Manager/Database/Database.hpp>
#include <config.hpp>
#include <sqlpp11/mysql/connection.h>
#include <Logger/Logger.hpp>

Database g_database;
Database* GetDatabase() {
    return &g_database;
}

bool Database::Connect() {
    try {

/*        m_pConnection = new sqlpp::mysql::connection{ Configuration::GetMySQL() };
        Logger::Print(INFO, "Initializing {}", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Database"));
        Logger::Print(" - Connection Configuration\n"
        "  | {}: {}\n"
        "  | {}: {}\n"
        "  | {}: {}\n", 
        fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Host"), m_pConnection->get_config()->host, 
        fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "User"), m_pConnection->get_config()->user,
        fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Database"), m_pConnection->get_config()->database);
*/
        m_pPlayerTable = new PlayerTable(m_pConnection);
    }
    catch (const sqlpp::exception &e) {
        return false;
    }
    return true;
}

sqlpp::mysql::connection* Database::GetConnection() {
    return this->m_pConnection;
}
void* Database::GetTable(eDatabaseTable table) {
    switch (table) {
        case DATABASE_PLAYER_TABLE: return m_pPlayerTable;
        default:
            return nullptr;
    }
    return nullptr;
}
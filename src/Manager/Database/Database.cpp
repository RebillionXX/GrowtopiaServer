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
        sqlpp::mysql::global_library_init();
        m_pConnection = new sqlpp::mysql::connection{ Configuration::GetMySQL() };
        Logger::Print(INFO, "Initializing {}, connecting to the server. [{} | {}]", 
            fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Database"),
            fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "{}", m_pConnection->get_config()->user),
        fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "{}", m_pConnection->get_config()->database));
        
        m_pPlayerTable = new PlayerTable(m_pConnection);
        return true;
    }
    catch (const sqlpp::exception &e)   { return false; }
    catch (...)                         { return false; }
    return false;
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
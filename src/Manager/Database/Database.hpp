#pragma once
#include <algorithm>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/mysql/mysql.h>
#include <Manager/Database/Table/PlayerTable.hpp>

enum eDatabaseTable {
    DATABASE_PLAYER_TABLE
};

class Database {
public:
    bool Connect();

    sqlpp::mysql::connection* GetConnection();
    void* GetTable(eDatabaseTable table);

public:
    Database() = default;
    ~Database() = default;

private:
    sqlpp::mysql::connection* m_pConnection     {   nullptr   };
    PlayerTable* m_pPlayerTable                 {   nullptr   };
};

Database* GetDatabase();
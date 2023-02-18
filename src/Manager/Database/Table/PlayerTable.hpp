#pragma once
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/mysql/mysql.h>
#include <Manager/Database/Interface/PlayerInterface.hpp>
#include <Player/Player.hpp>

enum class RegistrationResult {
    SUCCESS,
    EXIST_GROWID,
    INVALID_GROWID,
    INVALID_PASSWORD, //
    INVALID_EMAIL_OR_DISCORD,
    INVALID_GROWID_LENGTH,
    INVALID_PASSWORD_LENGTH,
    MISMATCH_VERIFY_PASSWORD,
    BAD_CONNECTION
};

class PlayerTable {
public:
    PlayerTable(sqlpp::mysql::connection* pConnection);
    ~PlayerTable() = default;

private:
    sqlpp::mysql::connection* m_pConnection;
};
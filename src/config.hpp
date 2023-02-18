#pragma once
#include <string>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/mysql/mysql.h>

class Configuration {
public:
    static std::string GetName()     {   return "Growtopia Server";     }
    static std::string GetVersion()  {   return "0.0.1";                }

    static std::string GetBaseHost() {   return "127.0.0.1";            }
    static uint16_t GetBasePort()    {   return 16000;                  }

public:
    static std::shared_ptr<sqlpp::mysql::connection_config> GetMySQL() {
        auto pConfig = std::make_shared<sqlpp::mysql::connection_config>();
        pConfig->host                = "127.0.0.1";
        pConfig->port                = 3306;
        pConfig->user                = "root";
        pConfig->password            = "";
        pConfig->database            = "growtopia_server";
        pConfig->auto_reconnect      = true;
        pConfig->debug               = false;
        return pConfig;
    }
};
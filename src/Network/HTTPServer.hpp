#pragma once
#include <string>
#include <thread>
#include <httplib.h>

class HTTPServer {
public:
    bool Listen();
    void Stop();
    
    std::thread& GetThread();
    void ServicePoll();
    
public:
    HTTPServer() = default;
    ~HTTPServer() = default;

private:
    std::unique_ptr<httplib::SSLServer> m_pServer;
    std::thread m_serviceThread;
};

HTTPServer* GetHTTP();
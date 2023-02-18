#include <Network/HTTPServer.hpp>
#include <config.hpp>
#include <Logger/Logger.hpp>
#include <Utils/TextParse.hpp>

HTTPServer g_httpServer;
HTTPServer* GetHTTP() {
    return &g_httpServer;
}

bool HTTPServer::Listen() {
    Logger::Print(INFO, "Starting {}, binding port to server", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "HTTP Server")); 
    m_pServer = std::make_unique<httplib::SSLServer>("./cache/cert.pem", "./cache/key.pem");

    if (!m_pServer->bind_to_port("0.0.0.0", 443)) {
        Logger::Print(EXCEPTION, "Failed to bind port 443 to HTTP Server.");
        return false;
    }  
	std::thread t(&HTTPServer::ServicePoll, this);
	this->m_serviceThread = std::move(t);

    Logger::Print("{} Initialized, Listening to {}", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "HTTP Server"), fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "https://0.0.0.0:443"));
    return true;
}
void HTTPServer::Stop() {
    m_pServer->stop();
    m_pServer.release();
}

std::thread& HTTPServer::GetThread() {
    return this->m_serviceThread;
}
void HTTPServer::ServicePoll() {
    m_pServer->Post("/growtopia/server_data.php", [&](const httplib::Request& request, httplib::Response& response) {
        /*if (request.params.empty() || request.get_header_value("User-Agent").find("UbiServices_SDK") == std::string::npos) {
            response.status = 403;
            return;
        }*/
        Logger::Print(INFO, "A request from {} | {}", request.remote_addr, request.path);
        
        TextParse parser{};
        parser.Add("server", Configuration::GetBaseHost());
        parser.Add<uint16_t>("port", Configuration::GetBasePort());
        parser.Add<bool>("type", true);
        parser.Add("#maint", "Server is under maintenance. We will be back online shortly. Thank you for your patience!");
        parser.Add("meta", "0DA34F801AE23F00");
        parser.Add("RTENDMARKERBS1001", "", "");
        response.set_content(parser.GetAsString(), "text/html");
    });
    m_pServer->listen_after_bind();
}

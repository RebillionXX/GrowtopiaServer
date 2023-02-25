#include <thread>
#include <config.hpp>
#include <fmt/color.h>
#include <Logger/Logger.hpp>
#include <Manager/Item/ItemManager.hpp>
#include <Manager/Database/Database.hpp>
#include <Network/HTTPServer.hpp>
#include <Event/EventPool.hpp>
#include <Server/ServerPool.hpp>
#include <Utils/Utils.hpp>

int main(int argc, char* argv[]) {
    std::string commandArguments{};
    for (int i = 1; i < argc; i++) commandArguments.append(std::string(argv[i]).append(" "));

    Logger::Init();
    Logger::Print(INFO, fmt::format(fmt::emphasis::bold, "Starting {} {}", 
        fmt::format(fg(fmt::color::gold), Configuration::GetName()), 
        fmt::format(fmt::emphasis::bold, "V{}", Configuration::GetVersion())
    ));

    if (commandArguments.find("--nohttp") == std::string::npos) {
        if (!GetHTTP()->Listen())
            Logger::Print(WARNING, "Failed to starting {}, please run an external service.", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "HTTP Server"));
    }
    
    if (!GetDatabase()->Connect()) {
        Logger::Print(WARNING, "Failed to connect {}, please check server configuration.", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "MySQL Server"));
        return EXIT_FAILURE;
    }
    if (!GetItemManager()->Serialize()) {
        Logger::Print(EXCEPTION, "{} >> failed to load items.dat, please make sure the file is on /cache", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "ItemManager"));
        return EXIT_FAILURE;
    }  

    Logger::Print(INFO, "Initializing {} and registering events...", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Event Pool"));
    GetEventPool()->RegisterEvents();

    Logger::Print(INFO, "Initializing {} and starting up {}...", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Server Pool"), fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Master Server"));
    if (enet_initialize() != 0) {
        Logger::Print(EXCEPTION, fmt::format(fmt::emphasis::bold, "Failed to Initialize ENet, Terminating the Server..."));
        return EXIT_FAILURE;
    };
    if (!GetServerPool()->StartInstance()) {
        Logger::Print(EXCEPTION, "Couldn't Startup {} Correctly, Terminating the Server...", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Master Server"));
        return EXIT_FAILURE;
    };
    GetServerPool()->Start();

    std::vector<std::thread> workerThread{};
    workerThread.push_back(
    std::thread([&]() {
        std::string consoleCommand{};
        while (std::cin >> consoleCommand) {
        switch (Hash::Fnv1A(consoleCommand)) {
        case "shutdown"_fnv: {
            for (auto [instanceId, server] : GetServerPool()->GetServers()) {
                if (!GetServerPool()->StopInstance(instanceId))
                    Logger::Print(WARNING, "Failed to shutdown InstanceId {}, this instance doesn't found on {}", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "{}", instanceId), fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Server Pool"));
            }
        } break;
        case "svinfo"_fnv: {
            std::string data{};
            data.append(fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Server Information\n"))
                .append(fmt::format("{}: {}\n", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Active Servers"), fmt::format("{}/4", GetServerPool()->GetActiveServers())))
                .append(fmt::format("{}: {}\n", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Active Players (All Servers)"), GetServerPool()->GetActivePlayers()))
                .append(fmt::format("{}: {}\n", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Active Worlds (All Servers)"), GetServerPool()->GetActiveWorlds()));
            data.append(fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Servers Stats\n"));
            for (auto [instanceId, server] : GetServerPool()->GetServers())
                data.append(fmt::format("{} | Uptime: {} [Players: {}, Worlds: {}] | In/Out PPS: {}/{}\n", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "S{}", instanceId), server->GetUptime(), server->GetActivePlayers(), server->GetActiveWorlds(), server->GetHost()->incomingBandwidth, server->GetHost()->outgoingBandwidth));
            
            data.resize(data.length() - 1);
            Logger::Print(INFO, data);
        } break;
        case "hwinfo"_fnv: {
            std::string 
                username = Console::Execute("whoami"),
                threadsUsage = Console::Execute(fmt::format("ps huH p {} | wc -l", ::getpid()));
            username.resize(username.length() - 1);
            threadsUsage.resize(threadsUsage.length() - 1);

            std::string data{ fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Hardware Information\n") };
            data.append(fmt::format("{}: {}\n", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Hostname"), Console::GetHostname()))
                .append(fmt::format("{}: {}\n", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Username"), username))
                .append(fmt::format("{}: {}\n", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Process Id"), ::getpid()))
                .append(fmt::format("{}: {}\n", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Thread Concurrency"), std::thread::hardware_concurrency()))
                .append(fmt::format("{}: {}\n", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Threads Used"), threadsUsage))
                .append(fmt::format("{}: {}\n", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "CPU Load"), Console::GetLoadAverage()));
            data.resize(data.length() - 1);
            Logger::Print(INFO, data);
        } break;
        default:
            break;
        }
        }
    }));
    for (auto& thread : workerThread)
        thread.detach();
    while (GetServerPool()->IsRunning()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

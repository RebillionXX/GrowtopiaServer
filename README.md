# GrowtopiaServer
 Growtopia Private Server made in C++, well-structured and reliable code.
### This server has Linux and Windowns compatibility.
This code has been tested to compile under Ubuntu 20.04 with Visual Studio Code 1.75.1 and for Windows it has been tested in Windows 11.

## Features
- [x] In-Built Web Server
- [x] Events Handler and Event Pool (easy to support more events using [sigslot](https://github.com/palacaze/sigslot) to deal with it)
- [ ] Database (almost finished and planning to change it to PostgreSQL)
- [x] Item Manager, decoding and encoding are very simple same as adding/editing items which is coming in near future.
- [x] Easy packet management and as well as adding new packets for easier usage.
- [ ] Account Login & Registration
- [ ] Player's Data are well-structured and easy to understand.
- [ ] Load Balancer and Server Gateway for sub-servers (currently we only have Server Pool for holding servers)
- [x] Server Pool for servers management
- [x] World Pool for worlds management
- [ ] Tile, TileExtra and World
- [ ] Players and Worlds caching

# Dependencies
you could install these by ``vcpkg`` on Windows or ``apt-get`` on Linux
 - [fmtlib - fmt](https://github.com/fmtlib/fmt)
 - [gabime - spdlog](https://github.com/gabime/spdlog) 
 - [yhirose - cpp-httplib](https://github.com/yhirose/cpp-httplib)
 - [openssl - openssl](https://github.com/openssl/openssl)
 - [Neargye magic_enum](https://github.com/Neargye/magic_enum)
 - [lsalzman - enet](https://github.com/lsalzman/enet)
 - [rbock - sqlpp11](https://github.com/rbock/sqlpp11)
 - [palacaze - sigslot](https://github.com/palacaze/sigslot)
 - [SethRobinson - proton](https://github.com/SethRobinson/proton)

# Contributing
Feedback and pull requests are very welcome!

### Contact
Rebillion#1015 on Discord

project(server LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB INCLUDE_FILES
    *.h
    **/*.h
    **/**/*.h
    **/**/**/*.h
    **/**/**/**/*.h
)
file(GLOB SOURCE_FILES
    *.cpp
    **/*.cpp
    **/**/*.cpp
    **/**/**/*.cpp
    **/**/**/**/*.cpp
)
add_executable(${PROJECT_NAME}
    ${INCLUDE_FILES}
    ${SOURCE_FILES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 11
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    NOMINMAX
    WIN32_LEAN_AND_MEAN 
    CPPHTTPLIB_OPENSSL_SUPPORT
)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(magic_enum REQUIRED)
find_package(unofficial-enet REQUIRED)
find_package(Sqlpp11 REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SIGSLOT_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../libraries/cpp-httplib
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt::fmt
    spdlog::spdlog
    OpenSSL::SSL
    magic_enum::magic_enum
    unofficial::enet::enet
    sqlpp11::sqlpp11
    Pal::Sigslot
)
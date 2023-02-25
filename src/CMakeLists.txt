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

set(USE_SYSTEM_DATE ON)
set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 11
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    NOMINMAX
    WIN32_LEAN_AND_MEAN 
    SPDLOG_FMT_EXTERNAL
    CPPHTTPLIB_OPENSSL_SUPPORT
)

if (CONAN_EXPORTED)
    include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else ()
    include(${CMAKE_CURRENT_SOURCE_DIR}/conan.cmake)

    conan_cmake_configure(REQUIRES 
        fmt/9.1.0
        cpp-httplib/0.12.0
        magic_enum/0.8.2
        spdlog/1.11.0 
        openssl/1.0.2s
        sigslot/1.2.1
        sqlpp11/0.61
        mariadb-connector-c/3.3.3

    GENERATORS cmake_find_package
    IMPORTS "bin, * -> ./bin"
    IMPORTS "lib, * -> ./lib"
    OPTIONS OPTIONS fmt:shared=True spdlog:shared=True)

    conan_cmake_autodetect(settings)
    conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/conan")

find_package(fmt REQUIRED)
find_package(httplib REQUIRED)
find_package(magic_enum REQUIRED)
find_package(spdlog REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PalSigslot REQUIRED)
find_package(Sqlpp11 REQUIRED)
find_package(mariadb-connector-c REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt::fmt
    httplib::httplib
    magic_enum::magic_enum
    spdlog::spdlog
    OpenSSL::SSL
    Pal::Sigslot
    sqlpp11::sqlpp11
    mariadb-connector-c::mariadb-connector-c
    enet
)
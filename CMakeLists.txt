cmake_minimum_required(VERSION 3.28)
project(Arcadia2D CXX)

set(SFML_BUILD_NETWORK OFF)
set(SPDLOG_USE_STD_FORMAT ON)

include(FetchContent)
FetchContent_Declare(sfml URL https://github.com/SFML/SFML/archive/refs/tags/3.0.2.tar.gz)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_Declare(logs URL https://github.com/gabime/spdlog/archive/refs/tags/v1.17.0.tar.gz)
FetchContent_MakeAvailable(sfml json logs)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS Engine/Source/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS Engine/Include/*.h)


add_executable(Arcadia2D)
target_sources(Arcadia2D PRIVATE ${SOURCES} ${HEADERS})

target_include_directories(Arcadia2D PRIVATE Engine/Include)
target_compile_features(Arcadia2D PRIVATE cxx_std_20)
target_compile_options(Arcadia2D PRIVATE $<IF:$<CXX_COMPILER_ID:MSVC>, /W4, -Wall -Wextra>)
target_link_libraries(Arcadia2D PRIVATE SFML::Graphics SFML::Audio nlohmann_json::nlohmann_json spdlog::spdlog)

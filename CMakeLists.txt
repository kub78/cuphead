cmake_minimum_required(VERSION 3.22.1)
project(cuphead)

file(GLOB SRCS src/*.cpp)
file(GLOB HDRS src/*.h src/bullet.hpp)

if(WIN32)
	include_directories(vcpkg_installed/x64-windows-release/include)
	link_directories(vcpkg_installed/x64-windows-release/lib)
elseif(UNIX)
	find_package(Boost 1.65 COMPONENTS filesystem REQUIRED)
	find_package(SFML 2.5 COMPONENTS system audio window graphics REQUIRED)
	find_package(nlohmann_json 3.2.0 REQUIRED)
endif()

add_executable(cuphead ${SRCS} ${HDRS})

if(WIN32)
	target_link_libraries(cuphead sfml-window.lib sfml-graphics.lib sfml-system.lib sfml-audio.lib boost_filesystem-vc140-mt.lib)
elseif(UNIX)
	target_link_libraries(cuphead sfml-graphics sfml-window sfml-audio sfml-system ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)
endif()
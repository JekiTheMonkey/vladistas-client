cmake_minimum_required(VERSION 3.16)
project(vladistas-client)
set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS window network REQUIRED)

set(FLAGS
    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

set(SRC
    src/Main.cpp
	src/Client.cpp
	src/Application.cpp
	src/Config.cpp
)

add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE include/)
target_link_libraries(${PROJECT_NAME} sfml-window sfml-network)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})

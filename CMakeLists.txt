cmake_minimum_required(VERSION 3.15)
project(gpio_scanner CXX)

find_package(spdlog REQUIRED)
find_package(libgpiod REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} spdlog::spdlog libgpiod::libgpiod -static)

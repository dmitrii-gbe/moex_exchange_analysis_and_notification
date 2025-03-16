cmake_minimum_required(VERSION 3.14)
project(UserverJsonServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE /usr/include/userver/third_party)
target_include_directories(${PROJECT_NAME} PRIVATE /usr/include/userver)
target_include_directories(${PROJECT_NAME} PRIVATE /usr/include)
# Find userver
find_package(userver REQUIRED)

# Create an executable

# Link userver to the executable
# target_link_libraries(json_server PRIVATE userver-core)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)
target_link_libraries(${PROJECT_NAME} PRIVATE
    userver::core
    # userver::http-server
    # userver::formats-json
    # userver::logging
    # OpenSSL::SSL
    # OpenSSL::Crypto
    # pthread
)

# Userver automatically provides include directories when linked, so no need for manual includes

cmake_minimum_required(VERSION 3.26)

project(simulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable( ${CMAKE_PROJECT_NAME} 

    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/input_waves.cpp
    ${CMAKE_SOURCE_DIR}/src/simulate.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/includes
)



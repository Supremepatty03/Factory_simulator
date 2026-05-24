cmake_minimum_required(VERSION 3.20)

project(FactorySimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(factory_sim
    src/main.cpp
    src/app/App.cpp
    src/infrastructure/InputFileParser.cpp
    src/infrastructure/TokenReader.cpp
    src/infrastructure/ValidationError.cpp
    src/domain/Event.cpp
    src/application/SimulationEngine.cpp
    src/application/MachineSelector.cpp
    src/application/EventDispatcher.cpp
    src/application/OutputFormatter.cpp
)

target_include_directories(factory_sim PRIVATE include)
target_include_directories(factory_sim PRIVATE ${CMAKE_SOURCE_DIR}/include)
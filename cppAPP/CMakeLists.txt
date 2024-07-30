cmake_minimum_required(VERSION 3.16)

project(Device-Controller)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(
    SRC_FILES
    src/clientHandler/clientHandler.cpp
    src/clientHandler/httpGetHandle.cpp
    src/parser/parser.cpp
    src/deviceManager/deviceManager.cpp
    src/deviceManager/led.cpp
    src/deviceManager/airConditioner.cpp
    src/serviceManager/serviceManager.cpp
    main.cpp    
)

include_directories(
    src/
    src/clientHandler
    src/deviceManger
    src/parser
    src/serviceManger
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
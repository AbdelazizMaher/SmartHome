cmake_minimum_required(VERSION 3.16)

project(Device-Controller)

set(
    SRC_FILES
    src/clientHandler/clientHandler.cpp
    src/clientHandler/httpGetHandle.cpp
    src/parser/parser.cpp
    main.cpp    
)

include_directories(
    src/
    src/clientHandler
    src/deviceManger
    src/parser
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
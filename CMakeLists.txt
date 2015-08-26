cmake_minimum_required(VERSION 3.3)
project(Deluge)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static")

set(LIBS
        glew32s
        opengl32
        freetype
        ssl
        crypto
        ws2_32
        lua
)

add_definitions(-DGLEW_STATIC)
add_definitions(-D_WIN32)

link_directories("C:/Users/Mark/.clion10/system/cmake/generated/586cc0cb/586cc0cb/Debug")
include_directories(C:/Users/Mark/Documents/Github/zeno/include)
include_directories(${CMAKE_SOURCE_DIR})

set(SOURCE_FILES
    App.cpp
    Console.cpp
    DelugeLua.cpp
    PersistantSettings.cpp
    Sprite.cpp
)


add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC   zeno-window-s-d
                                                    zeno-network-s-d
                                                    zeno-gui-s-d
                                                    zeno-graphics-s-d
                                                    zeno-system-s-d
                                                    zeno-utility-s-d
                                                    ${LIBS}
)

add_custom_target(CopyResources ALL
        COMMAND ${CMAKE_COMMAND} -E remove_directory "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Resources"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Resources" "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Resources"
        COMMENT "Copying ${PROJECT_NAME} Resources to build tree"
        VERBATIM)

cmake_minimum_required(VERSION 3.7)
project(bulanci C)

set(CMAKE_C_STANDARD 99)
link_libraries(ws2_32 wsock32)

set(SDL2_INCLUDE_DIR SDL/include)
set(SDL2_LIB_DIR SDL/lib/x64)
set(SDL2ttf_INCLUDE_DIR SDL2_ttf/include)
set(SDL2ttf_LIB_DIR SDL2_ttf/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

include_directories(${SDL2ttf_INCLUDE_DIR})
link_directories(${SDL2ttf_LIB_DIR})

add_executable(bulanci main.c Client.c Client.h Server.c Server.h Player.c Player.h Weapon.c Weapon.h Enums.c Enums.h Bullet.c Bullet.h Common.c Common.h Map.c Map.h GUI.c GUI.h)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread" )
target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_ttf)
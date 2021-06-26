cmake_minimum_required(VERSION 3.19)
project(client)

cmake_minimum_required(VERSION 3.7)


set(CMAKE_C_STANDARD 11)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
set(CMAKE_C_FLAGS "-pthread")


add_executable(client main.c Game/game.c Game/game.h constants.h Game/gameObjets/ship.h Game/gameObjets/ship.c Game/render.h
 Game/render.c Game/gameObjets/bullet.h Game/gameObjets/bullet.c Game/gameObjets/bunker.h Game/gameObjets/bunker.c Game/collisions.h
 Game/collisions.c Game/gameObjets/enemy.c Game/gameObjets/enemy.h Game/util.h Game/util.c Game/gameObjets/spacecraft.h Game/gameObjets/spacecraft.c)
target_link_libraries(client ${SDL2_LIBRARIES} SDL2_image SDL2_ttf)
cmake_minimum_required(VERSION 3.19)
project(client)

cmake_minimum_required(VERSION 3.7)


set(CMAKE_C_STANDARD 11)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
set(CMAKE_C_FLAGS "-pthread")


add_executable(client main.c game/game.c game/game.h constants.h game/gameObjets/ship.h game/gameObjets/ship.c game/render.h
 game/render.c game/gameObjets/bullet.h game/gameObjets/bullet.c game/gameObjets/bunker.h game/gameObjets/bunker.c game/gameObjets/enemy.c game/gameObjets/enemy.h game/util.h game/util.c game/gameObjets/spacecraft.h game/gameObjets/spacecraft.c
 socket/cJson.h socket/cJson.c socket/socketClient.h socket/socketClient.c socket/serializer.h socket/serializer.c)
target_link_libraries(client ${SDL2_LIBRARIES} SDL2_image SDL2_ttf)
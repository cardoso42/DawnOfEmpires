set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(GameController STATIC GameController.cpp)

target_include_directories(GameController
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(GameController PUBLIC AssetManager)
target_link_libraries(GameController PUBLIC Animator)
target_link_libraries(GameController PUBLIC AnimatedAsset)
target_link_libraries(GameController PUBLIC TilePiece)
target_link_libraries(GameController PUBLIC Empire)
target_link_libraries(GameController PUBLIC TileMap)
target_link_libraries(GameController PUBLIC Window)
target_link_libraries(GameController PUBLIC ActionMenu)

target_include_directories(GameController PUBLIC
                           "${PROJECT_BINARY_DIR}/src/GameController"
                           )

install(TARGETS GameController
        EXPORT GameControllerTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/GameController/GameController.hpp" DESTINATION include)

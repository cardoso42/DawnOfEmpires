set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(GameController STATIC GameController.cpp)

target_include_directories(GameController
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(GameController PRIVATE AssetManager)
target_link_libraries(GameController PRIVATE Animator)
target_link_libraries(GameController PRIVATE AnimatedAsset)
target_link_libraries(GameController PRIVATE TilePiece)
target_link_libraries(GameController PRIVATE TileMap)
target_link_libraries(GameController PRIVATE Window)

target_include_directories(GameController PUBLIC
                           "${PROJECT_BINARY_DIR}/src/GameController"
                           )

install(TARGETS GameController
        EXPORT GameControllerTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/GameController/GameController.hpp" DESTINATION include)

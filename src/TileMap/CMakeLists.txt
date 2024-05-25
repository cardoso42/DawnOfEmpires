set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(TileMap STATIC TileMap.cpp)

target_include_directories(TileMap
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(TileMap PRIVATE AssetManager)
target_link_libraries(TileMap PRIVATE Animator)
target_link_libraries(TileMap PRIVATE AnimatedAsset)
target_link_libraries(TileMap PRIVATE TilePiece)

target_include_directories(TileMap PUBLIC
                           "${PROJECT_BINARY_DIR}/src/TileMap"
                           )

install(TARGETS TileMap
        EXPORT TileMapTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/TileMap/TileMap.hpp" DESTINATION include)

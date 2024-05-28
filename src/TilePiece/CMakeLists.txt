set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(TilePiece STATIC TilePiece.cpp)

target_include_directories(TilePiece
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(TilePiece PUBLIC IdGenerator)
target_link_libraries(TilePiece PUBLIC AssetManager)
target_link_libraries(TilePiece PUBLIC Animator)
target_link_libraries(TilePiece PUBLIC AnimatedAsset)
target_link_libraries(TilePiece PUBLIC GameContext)
target_link_libraries(TilePiece PUBLIC Resource)

target_include_directories(TilePiece PUBLIC
                           "${PROJECT_BINARY_DIR}/src/TilePiece"
                           )

install(TARGETS TilePiece
        EXPORT   TilePieceTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/TilePiece/TilePiece.hpp" DESTINATION include)

set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(GameContext STATIC GameContext.cpp)

target_include_directories(GameContext
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(GameContext PUBLIC AssetManager)
target_link_libraries(GameContext PUBLIC Animator)
target_link_libraries(GameContext PUBLIC Empire)
target_link_libraries(GameContext PUBLIC TilePiece)
target_link_libraries(GameContext PUBLIC WindowManager)

target_include_directories(GameContext PUBLIC
                           "${PROJECT_BINARY_DIR}/src/GameContext"
                           )

install(TARGETS GameContext
        EXPORT GameContextTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/GameContext/GameContext.hpp" DESTINATION include)

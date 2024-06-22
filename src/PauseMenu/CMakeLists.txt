set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(PauseMenu STATIC PauseMenu.cpp)

target_include_directories(PauseMenu
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(PauseMenu PUBLIC AssetManager)
target_link_libraries(PauseMenu PUBLIC Animator)
target_link_libraries(PauseMenu PUBLIC GenericMenu)
target_link_libraries(PauseMenu PUBLIC GameContext)

target_include_directories(PauseMenu PUBLIC
                           "${PROJECT_BINARY_DIR}/src/PauseMenu"
                           )

install(TARGETS PauseMenu
        EXPORT PauseMenuTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/PauseMenu/PauseMenu.hpp" DESTINATION include)

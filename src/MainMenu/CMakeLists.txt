set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(MainMenu STATIC MainMenu.cpp)

target_include_directories(MainMenu
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(MainMenu PUBLIC AssetManager)
target_link_libraries(MainMenu PUBLIC Animator)
target_link_libraries(MainMenu PUBLIC GenericMenu)
target_link_libraries(MainMenu PUBLIC GameContext)

target_include_directories(MainMenu PUBLIC
                           "${PROJECT_BINARY_DIR}/src/MainMenu"
                           )

install(TARGETS MainMenu
        EXPORT MainMenuTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/MainMenu/MainMenu.hpp" DESTINATION include)

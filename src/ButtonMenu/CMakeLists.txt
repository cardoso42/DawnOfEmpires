set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(ButtonMenu STATIC ButtonMenu.cpp)

target_include_directories(ButtonMenu
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(ButtonMenu PRIVATE AssetManager)
target_link_libraries(ButtonMenu PRIVATE Animator)
target_link_libraries(ButtonMenu PRIVATE GameContext)
target_link_libraries(ButtonMenu PUBLIC MenuElement)

target_include_directories(ButtonMenu PUBLIC
                           "${PROJECT_BINARY_DIR}/src/ButtonMenu"
                           )

install(TARGETS ButtonMenu
        EXPORT ButtonMenuTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/ButtonMenu/ButtonMenu.hpp" DESTINATION include)

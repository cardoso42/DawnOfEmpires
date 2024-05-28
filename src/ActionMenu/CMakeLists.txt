set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(ActionMenu STATIC ActionMenu.cpp)

target_include_directories(ActionMenu
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(ActionMenu PUBLIC AssetManager)
target_link_libraries(ActionMenu PUBLIC Animator)
target_link_libraries(ActionMenu PUBLIC ButtonMenu)
target_link_libraries(ActionMenu PUBLIC GenericMenu)
target_link_libraries(ActionMenu PUBLIC Empire)
target_link_libraries(ActionMenu PUBLIC TilePiece)

target_include_directories(ActionMenu PUBLIC
                           "${PROJECT_BINARY_DIR}/src/ActionMenu"
                           )

install(TARGETS ActionMenu
        EXPORT ActionMenuTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/ActionMenu/ActionMenu.hpp" DESTINATION include)

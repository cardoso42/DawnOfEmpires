set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(ContextMenu STATIC ContextMenu.cpp)

target_include_directories(ContextMenu
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(ContextMenu PUBLIC AssetManager)
target_link_libraries(ContextMenu PUBLIC Animator)
target_link_libraries(ContextMenu PUBLIC GenericMenu)

target_include_directories(ContextMenu PUBLIC
                           "${PROJECT_BINARY_DIR}/src/ContextMenu"
                           )

install(TARGETS ContextMenu
        EXPORT ContextMenuTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/ContextMenu/ContextMenu.hpp" DESTINATION include)

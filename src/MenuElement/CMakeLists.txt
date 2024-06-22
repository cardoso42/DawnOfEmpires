set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(MenuElement STATIC MenuElement.cpp)

target_include_directories(MenuElement
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(MenuElement PUBLIC AssetManager)
target_link_libraries(MenuElement PUBLIC Animator)
target_link_libraries(MenuElement PUBLIC BaseComponent)

target_include_directories(MenuElement PUBLIC
                           "${PROJECT_BINARY_DIR}/src/MenuElement"
                           )

install(TARGETS MenuElement
        EXPORT MenuElementTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/MenuElement/MenuElement.hpp" DESTINATION include)

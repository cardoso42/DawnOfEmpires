set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(Window STATIC Window.cpp)

target_include_directories(Window
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(Window PRIVATE AssetManager)
target_link_libraries(Window PRIVATE Animator)

target_include_directories(Window PUBLIC
                           "${PROJECT_BINARY_DIR}/src/Window"
                           )

install(TARGETS Window
        EXPORT WindowTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/Window/Window.hpp" DESTINATION include)

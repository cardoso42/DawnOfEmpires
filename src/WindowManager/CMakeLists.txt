set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(WindowManager STATIC WindowManager.cpp)

target_include_directories(WindowManager
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(WindowManager PRIVATE AssetManager)
target_link_libraries(WindowManager PRIVATE Animator)
target_link_libraries(WindowManager PRIVATE GameContext)

target_include_directories(WindowManager PUBLIC
                           "${PROJECT_BINARY_DIR}/src/WindowManager"
                           )

install(TARGETS WindowManager
        EXPORT WindowManagerTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/WindowManager/WindowManager.hpp" DESTINATION include)

set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(StackMenu STATIC StackMenu.cpp)

target_include_directories(StackMenu
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(StackMenu PUBLIC AssetManager)
target_link_libraries(StackMenu PUBLIC Animator)
target_link_libraries(StackMenu PUBLIC BaseComponent)
target_link_libraries(StackMenu PUBLIC GenericMenu)

target_include_directories(StackMenu PUBLIC
                           "${PROJECT_BINARY_DIR}/src/StackMenu"
                           )

install(TARGETS StackMenu
        EXPORT StackMenuTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/StackMenu/StackMenu.hpp" DESTINATION include)

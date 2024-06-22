set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(GenericMenu STATIC GenericMenu.cpp)

target_include_directories(GenericMenu
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(GenericMenu PUBLIC AssetManager)
target_link_libraries(GenericMenu PUBLIC Animator)
target_link_libraries(GenericMenu PUBLIC ButtonMenu)
target_link_libraries(GenericMenu PUBLIC BaseComponent)
target_link_libraries(GenericMenu PUBLIC GameContext)
target_link_libraries(GenericMenu PUBLIC MenuElement)
target_link_libraries(GenericMenu PUBLIC IncrementDecrementControl)

target_include_directories(GenericMenu PUBLIC
                           "${PROJECT_BINARY_DIR}/src/GenericMenu"
                           )

install(TARGETS GenericMenu
        EXPORT GenericMenuTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/GenericMenu/GenericMenu.hpp" DESTINATION include)

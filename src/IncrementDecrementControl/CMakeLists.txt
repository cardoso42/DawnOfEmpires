set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(IncrementDecrementControl STATIC IncrementDecrementControl.cpp)

target_include_directories(IncrementDecrementControl
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(IncrementDecrementControl PUBLIC AssetManager)
target_link_libraries(IncrementDecrementControl PUBLIC Animator)
target_link_libraries(IncrementDecrementControl PUBLIC BaseComponent)
target_link_libraries(IncrementDecrementControl PUBLIC ButtonMenu)
target_link_libraries(IncrementDecrementControl PUBLIC GameContext)
target_link_libraries(IncrementDecrementControl PUBLIC MenuElement)

target_include_directories(IncrementDecrementControl PUBLIC
                           "${PROJECT_BINARY_DIR}/src/IncrementDecrementControl"
                           )

install(TARGETS IncrementDecrementControl
        EXPORT IncrementDecrementControlTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/IncrementDecrementControl/IncrementDecrementControl.hpp" DESTINATION include)

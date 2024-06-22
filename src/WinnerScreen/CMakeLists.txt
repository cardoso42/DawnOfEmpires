set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(WinnerScreen STATIC WinnerScreen.cpp)

target_include_directories(WinnerScreen
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(WinnerScreen PUBLIC AssetManager)
target_link_libraries(WinnerScreen PUBLIC Animator)
target_link_libraries(WinnerScreen PUBLIC BaseComponent)
target_link_libraries(WinnerScreen PUBLIC ButtonMenu)
target_link_libraries(WinnerScreen PUBLIC Empire)

target_include_directories(WinnerScreen PUBLIC
                           "${PROJECT_BINARY_DIR}/src/WinnerScreen"
                           )

install(TARGETS WinnerScreen
        EXPORT WinnerScreenTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/WinnerScreen/WinnerScreen.hpp" DESTINATION include)

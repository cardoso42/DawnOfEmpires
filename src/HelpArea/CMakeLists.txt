set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(HelpArea STATIC HelpArea.cpp)

target_include_directories(HelpArea
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(HelpArea PUBLIC AssetManager)
target_link_libraries(HelpArea PUBLIC Animator)
target_link_libraries(HelpArea PUBLIC Empire)
target_link_libraries(HelpArea PUBLIC TilePiece)

target_include_directories(HelpArea PUBLIC
                           "${PROJECT_BINARY_DIR}/src/HelpArea"
                           )

install(TARGETS HelpArea
        EXPORT HelpAreaTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/HelpArea/HelpArea.hpp" DESTINATION include)

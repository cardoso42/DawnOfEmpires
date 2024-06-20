set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(ResourceBar STATIC ResourceBar.cpp)

target_include_directories(ResourceBar
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(ResourceBar PUBLIC AssetManager)
target_link_libraries(ResourceBar PUBLIC Animator)
target_link_libraries(ResourceBar PUBLIC Resource)
target_link_libraries(ResourceBar PUBLIC Empire)
target_link_libraries(ResourceBar PUBLIC BaseComponent)

target_include_directories(ResourceBar PUBLIC
                           "${PROJECT_BINARY_DIR}/src/ResourceBar"
                           )

install(TARGETS ResourceBar
        EXPORT ResourceBarTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/ResourceBar/ResourceBar.hpp" DESTINATION include)

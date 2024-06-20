set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(BaseComponent STATIC BaseComponent.cpp)

target_include_directories(BaseComponent
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(BaseComponent PUBLIC AssetManager)
target_link_libraries(BaseComponent PUBLIC Animator)

target_include_directories(BaseComponent PUBLIC
                           "${PROJECT_BINARY_DIR}/src/BaseComponent"
                           )

install(TARGETS BaseComponent
        EXPORT BaseComponentTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/BaseComponent/BaseComponent.hpp" DESTINATION include)

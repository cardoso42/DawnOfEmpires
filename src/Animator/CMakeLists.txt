set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(Animator STATIC Animator.cpp)

target_include_directories(Animator
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(Animator PUBLIC
                           "${PROJECT_BINARY_DIR}/src/Animator"
                           )

target_link_libraries(Animator PRIVATE AssetManager)

install(TARGETS Animator
        EXPORT AnimatorTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/Animator/Animator.hpp" DESTINATION include)

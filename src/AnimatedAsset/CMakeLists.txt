set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(AnimatedAsset STATIC AnimatedAsset.cpp)

target_include_directories(AnimatedAsset
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(AnimatedAsset PRIVATE AssetManager)
target_link_libraries(AnimatedAsset PRIVATE Animator)

target_include_directories(AnimatedAsset PUBLIC
                           "${PROJECT_BINARY_DIR}/src/AnimatedAsset"
                           )

install(TARGETS AnimatedAsset
        EXPORT AnimatedAssetTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/AnimatedAsset/AnimatedAsset.hpp" DESTINATION include)

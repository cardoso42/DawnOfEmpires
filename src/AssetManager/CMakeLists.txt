set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

configure_file(AssetManager.hpp.in AssetManager.hpp)

add_library(AssetManager STATIC AssetManager.cpp)

target_include_directories(AssetManager
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(AssetManager PUBLIC
                           "${PROJECT_BINARY_DIR}/src/AssetManager"
                           )

install(TARGETS AssetManager
        EXPORT AssetManagerTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/AssetManager/AssetManager.hpp" DESTINATION include)

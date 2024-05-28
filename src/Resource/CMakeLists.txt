set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(Resource STATIC ResourceBase.cpp)

target_include_directories(Resource
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(Resource PUBLIC
                           "${PROJECT_BINARY_DIR}/src/Resource"
                           )

install(TARGETS Resource
        EXPORT ResourceTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/Resource/Resource.hpp" DESTINATION include)

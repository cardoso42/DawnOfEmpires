set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(IdGenerator STATIC IdGenerator.cpp)

target_include_directories(IdGenerator
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(IdGenerator PRIVATE AssetManager)
target_link_libraries(IdGenerator PRIVATE Animator)

target_include_directories(IdGenerator PUBLIC
                           "${PROJECT_BINARY_DIR}/src/IdGenerator"
                           )

install(TARGETS IdGenerator
        EXPORT IdGeneratorTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/IdGenerator/IdGenerator.hpp" DESTINATION include)

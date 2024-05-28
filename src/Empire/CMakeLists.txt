set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

add_library(Empire STATIC Empire.cpp)

target_include_directories(Empire
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(Empire PUBLIC TilePiece)
target_link_libraries(Empire PUBLIC GameContext)

target_include_directories(Empire PUBLIC
                           "${PROJECT_BINARY_DIR}/src/Empire"
                           )

install(TARGETS Empire
        EXPORT EmpireTargets
        DESTINATION lib)

install(FILES "${PROJECT_BINARY_DIR}/src/Empire/Empire.hpp" DESTINATION include)

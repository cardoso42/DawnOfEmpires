cmake_minimum_required(VERSION 3.16)
project(DawnOfEmpires VERSION 1.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(RESOURCES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)
set(RESOURCES_DEST_DIR ${CMAKE_BINARY_DIR}/resources)
set(FILES_BASE_PATH ${CMAKE_BINARY_DIR})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build: Debug, Release" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(X11 REQUIRED)

add_subdirectory(src/IdGenerator)
add_subdirectory(src/AssetManager)
add_subdirectory(src/Animator)
add_subdirectory(src/AnimatedAsset)
add_subdirectory(src/GameController)
add_subdirectory(src/TilePiece)
add_subdirectory(src/Empire)
add_subdirectory(src/TileMap)
add_subdirectory(src/Window)
add_subdirectory(src/GenericMenu)
add_subdirectory(src/ActionMenu)
add_subdirectory(src/ButtonMenu)
add_subdirectory(src/ContextMenu)
add_subdirectory(src/GameContext)

add_executable(DawnOfEmpires src/main.cpp)
target_link_libraries(DawnOfEmpires PRIVATE sfml-graphics)
target_link_libraries(DawnOfEmpires PRIVATE sfml-audio)
target_link_libraries(DawnOfEmpires PUBLIC IdGenerator)
target_link_libraries(DawnOfEmpires PUBLIC AssetManager)
target_link_libraries(DawnOfEmpires PUBLIC Animator)
target_link_libraries(DawnOfEmpires PUBLIC AnimatedAsset)
target_link_libraries(DawnOfEmpires PUBLIC GameController)
target_link_libraries(DawnOfEmpires PUBLIC TilePiece)
target_link_libraries(DawnOfEmpires PUBLIC Empire)
target_link_libraries(DawnOfEmpires PUBLIC TileMap)
target_link_libraries(DawnOfEmpires PUBLIC WindowManager)
target_link_libraries(DawnOfEmpires PUBLIC GenericMenu)
target_link_libraries(DawnOfEmpires PUBLIC ActionMenu)
target_link_libraries(DawnOfEmpires PUBLIC ButtonMenu)
target_link_libraries(DawnOfEmpires PUBLIC ContextMenu)
target_link_libraries(DawnOfEmpires PUBLIC GameContext)
target_link_libraries(DawnOfEmpires PUBLIC ${X11_LIBRARIES})
target_compile_features(DawnOfEmpires PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET DawnOfEmpires
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:DawnOfEmpires>
        VERBATIM)
endif()

target_include_directories(DawnOfEmpires PUBLIC
                           "${PROJECT_BINARY_DIR}/src"
                           )

file(MAKE_DIRECTORY ${RESOURCES_DEST_DIR})
file(COPY ${RESOURCES_SOURCE_DIR} DESTINATION ${CMAKE_BINARY_DIR})
message(STATUS "Resources copied to ${RESOURCES_DEST_DIR}")

install(TARGETS DawnOfEmpires)

cmake_minimum_required(VERSION 3.16)
project(DawnOfEmpires VERSION 1.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(RESOURCES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)
set(RESOURCES_DEST_DIR ${CMAKE_BINARY_DIR}/resources)
# option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(DawnOfEmpires src/main.cpp)
target_link_libraries(DawnOfEmpires PRIVATE sfml-graphics)
target_link_libraries(DawnOfEmpires PRIVATE sfml-audio)
target_compile_features(DawnOfEmpires PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET DawnOfEmpires
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:DawnOfEmpires>
        VERBATIM)
endif()

file(MAKE_DIRECTORY ${RESOURCES_DEST_DIR})
file(COPY ${RESOURCES_SOURCE_DIR} DESTINATION ${CMAKE_BINARY_DIR})
message(STATUS "Resources copied to ${RESOURCES_DEST_DIR}")

install(TARGETS DawnOfEmpires)
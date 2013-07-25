cmake_minimum_required(VERSION 2.6)

# Nom du projet
project(UltraShooter)

set(EXECUTABLE_NAME ultrashooter)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(SFML 2 COMPONENTS system graphics window audio REQUIRED)

include_directories(${SFML_INCLUDE_DIR}/.. include include/tinyxml)


if ( NOT SFML_FOUND )
message(FATAL_ERROR "SFML not found !")
endif ( NOT SFML_FOUND )

file(
GLOB_RECURSE
source_files
src/*
)


# Déclaration de l'exécutable
add_executable(
../${EXECUTABLE_NAME}
${source_files}
)


target_link_libraries(
../${EXECUTABLE_NAME}
${SFML_LIBRARIES}
)





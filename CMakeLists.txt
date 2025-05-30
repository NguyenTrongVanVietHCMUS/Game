# CMakeList.txt : CMake project for Game, include source and define
# project specific logic here.
#

# Add source to this project's executable.


cmake_minimum_required (VERSION 3.10)
project ("Game")

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/SourceCode")

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")  # Recursive glob

add_executable(Game ${SOURCES})
# set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/SourceCode")
# file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")
# add_executable (Game ${SOURCES})

target_link_libraries(Game ${CMAKE_CURRENT_SOURCE_DIR}/lib/sfml-audio.lib)
target_link_libraries(Game ${CMAKE_CURRENT_SOURCE_DIR}/lib/sfml-graphics.lib)
target_link_libraries(Game ${CMAKE_CURRENT_SOURCE_DIR}/lib/sfml-network.lib)
target_link_libraries(Game ${CMAKE_CURRENT_SOURCE_DIR}/lib/sfml-system.lib)
target_link_libraries(Game ${CMAKE_CURRENT_SOURCE_DIR}/lib/sfml-window.lib)

# target_link_libraries(Game ${CMAKE_CURRENT_SOURCE_DIR}/lib/raylib.lib)
# target_link_libraries(Game ${CMAKE_CURRENT_SOURCE_DIR}/lib/raylibdll.lib)


set(FILES_TO_COPY
	${CMAKE_CURRENT_SOURCE_DIR}/bin/openal32.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/sfml-audio-2.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/sfml-graphics-2.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/sfml-network-2.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/sfml-system-2.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/sfml-window-2.dll 
	# ${CMAKE_CURRENT_SOURCE_DIR}/bin/raylib.dll
)

foreach(file ${FILES_TO_COPY}) 
    add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${file}  
        $<TARGET_FILE_DIR:Game>  
    )
endforeach()

add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_CURRENT_SOURCE_DIR}/Media
        $<TARGET_FILE_DIR:Game>/Media  
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Game PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

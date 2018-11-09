# At LEAST 2.8 but newer is better
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(hangman VERSION 0.1 LANGUAGES CXX)

set (SOURCE_FILES main.cpp ${CMAKE_CURRENT_LIST_DIR}/Hangman.cpp 
						   ${CMAKE_CURRENT_LIST_DIR}/Hangman.h
						   ${CMAKE_CURRENT_LIST_DIR}/Window.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/Window.h)

SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/Debug)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT hangman)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_executable(hangman ${SOURCE_FILES})

target_include_directories (hangman PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL/include)
target_include_directories (hangman PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL2_ttf-2.0.14/include)

target_link_libraries(hangman ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL/lib/win32/SDL2.lib)
target_link_libraries(hangman ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL/lib/win32/SDL2main.lib)
target_link_libraries(hangman ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib)

add_custom_command(TARGET hangman POST_BUILD  COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/Roboto-Black.ttf" ${PROJECT_SOURCE_DIR}/build
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/SDL2.dll" $<TARGET_FILE_DIR:hangman>
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/SDL2_ttf.dll" $<TARGET_FILE_DIR:hangman>
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/libfreetype-6.dll" $<TARGET_FILE_DIR:hangman>
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/Roboto-Black.ttf" $<TARGET_FILE_DIR:hangman>
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/zlib1.dll" $<TARGET_FILE_DIR:hangman>
				   )
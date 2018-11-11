# At LEAST 2.8 but newer is better
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(hangman VERSION 0.1 LANGUAGES CXX)

set (SOURCE_FILES main.cpp ${CMAKE_CURRENT_LIST_DIR}/Hangman.cpp 
						   ${CMAKE_CURRENT_LIST_DIR}/Hangman.h
						   ${CMAKE_CURRENT_LIST_DIR}/GameManager.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/GameManager.h
						   ${CMAKE_CURRENT_LIST_DIR}/Graphics.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/Graphics.h
						   ${CMAKE_CURRENT_LIST_DIR}/Timer.h
						   ${CMAKE_CURRENT_LIST_DIR}/Timer.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/Window.h
						   ${CMAKE_CURRENT_LIST_DIR}/Window.h
						   ${CMAKE_CURRENT_LIST_DIR}/MathHelper.h
						   ${CMAKE_CURRENT_LIST_DIR}/Entities/GameEntity.h
						   ${CMAKE_CURRENT_LIST_DIR}/Entities/GameEntity.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/Entities/Texture.h
						   ${CMAKE_CURRENT_LIST_DIR}/Entities/Texture.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/Entities/AnimatedTexture.h
						   ${CMAKE_CURRENT_LIST_DIR}/Entities/AnimatedTexture.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/AssetManager.h
						   ${CMAKE_CURRENT_LIST_DIR}/AssetManager.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/InputManager.h
						   ${CMAKE_CURRENT_LIST_DIR}/InputManager.cpp)

file(GLOB_RECURSE TMP_FILES
    ${CMAKE_CURRENT_LIST_DIR}/Entities/*.h
	${CMAKE_CURRENT_LIST_DIR}/Entities/*.cpp
	)

foreach(f ${TMP_FILES})
    # Get the path of the file relative to ${DIRECTORY},
    # then alter it (not compulsory)

    file(RELATIVE_PATH SRCGR ${CMAKE_CURRENT_LIST_DIR} ${f})
	if (${f} MATCHES ".*cpp")
		set(SRCGR "Source Files/${SRCGR}")
	elseif (${f} MATCHES ".*h")
	    set(SRCGR "Header Files/${SRCGR}")
	endif()

    # Extract the folder, ie remove the filename part
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    # Source_group expects \\ (double antislash), not / (slash)
    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
endforeach()

SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/Debug)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT hangman)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_executable(hangman ${SOURCE_FILES})

set(VARIABLE_NAME ${CMAKE_CURRENT_LIST_DIR}/GameEntity.cpp ${CMAKE_CURRENT_LIST_DIR}/GemeEntity.h)
source_group("Entities\\module" FILES ${VARIABLE_NAME})
set(SOURCE_FILES ${VARIABLE_NAME})

target_include_directories (hangman PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL/include)
target_include_directories (hangman PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL2_ttf-2.0.14/include)
target_include_directories (hangman PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL2_image-2.0.4/include)

target_link_libraries(hangman ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL/lib/win32/SDL2.lib)
target_link_libraries(hangman ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL/lib/win32/SDL2main.lib)
target_link_libraries(hangman ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib)
target_link_libraries(hangman ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL2_image-2.0.4/lib/x86/SDL2_image.lib)

add_custom_command(TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/Roboto-Black.ttf" ${PROJECT_SOURCE_DIR}/build
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/SDL2.dll" $<TARGET_FILE_DIR:hangman>
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/SDL2_ttf.dll" $<TARGET_FILE_DIR:hangman>
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libfreetype-6.dll" $<TARGET_FILE_DIR:hangman>
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/Roboto-Black.ttf" $<TARGET_FILE_DIR:hangman>
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libjpeg-9.dll" $<TARGET_FILE_DIR:hangman>
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libpng16-16.dll" $<TARGET_FILE_DIR:hangman>
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libwebp-7.dll" $<TARGET_FILE_DIR:hangman>
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/SDL2_image.dll" $<TARGET_FILE_DIR:hangman>
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libtiff-5.dll" $<TARGET_FILE_DIR:hangman>
				   TARGET hangman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/zlib1.dll" $<TARGET_FILE_DIR:hangman>
				   )
# At LEAST 2.8 but newer is better
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(Galaga VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCE_FILES     ${CMAKE_CURRENT_LIST_DIR}/*.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/*.h
						   ${CMAKE_CURRENT_LIST_DIR}/Entities/*.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/Entities/*.h
						   ${CMAKE_CURRENT_LIST_DIR}/Managers/*.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/Managers/*.h
						   ${CMAKE_CURRENT_LIST_DIR}/Galaga/*.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/Galaga/*.h
						   ${CMAKE_CURRENT_LIST_DIR}/Galaga/Enemies/*.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/Galaga/Enemies/*.h
						   ${CMAKE_CURRENT_LIST_DIR}/Levels/*.xml
						   ${CMAKE_CURRENT_LIST_DIR}/Physics/*.cpp
						   ${CMAKE_CURRENT_LIST_DIR}/Physics/*.h
						   )

file(GLOB_RECURSE TMP_FILES
    ${CMAKE_CURRENT_LIST_DIR}/Physics/*.h
	${CMAKE_CURRENT_LIST_DIR}/Physics/*.cpp
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

file(GLOB_RECURSE TMP_FILES
    ${CMAKE_CURRENT_LIST_DIR}/Levels/*.xml
	)

foreach(f ${TMP_FILES})
    # Get the path of the file relative to ${DIRECTORY},
    # then alter it (not compulsory)

    file(RELATIVE_PATH SRCGR ${CMAKE_CURRENT_LIST_DIR} ${f})
	if (${f} MATCHES ".*cpp")
		set(SRCGR "Source Files/${SRCGR}")
	elseif (${f} MATCHES ".*h")
	    set(SRCGR "Source Files/${SRCGR}")
	endif()

    # Extract the folder, ie remove the filename part
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    # Source_group expects \\ (double antislash), not / (slash)
    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
endforeach()

file(GLOB_RECURSE TMP_FILES
    ${CMAKE_CURRENT_LIST_DIR}/Managers/*.h
	${CMAKE_CURRENT_LIST_DIR}/Managers/*.cpp
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

file(GLOB_RECURSE TMP_FILES
    ${CMAKE_CURRENT_LIST_DIR}/Galaga/*.h
	${CMAKE_CURRENT_LIST_DIR}/Galaga/*.cpp
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

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Galaga)

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_executable(Galaga ${SOURCE_FILES})

target_include_directories (Galaga PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL/include)
target_include_directories (Galaga PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL2_ttf-2.0.14/include)
target_include_directories (Galaga PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL2_image-2.0.4/include)
target_include_directories (Galaga PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL2_mixer-2.0.4/include)

target_link_libraries(Galaga ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL/lib/win32/SDL2.lib)
target_link_libraries(Galaga ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL/lib/win32/SDL2main.lib)
target_link_libraries(Galaga ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib)
target_link_libraries(Galaga ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL2_image-2.0.4/lib/x86/SDL2_image.lib)
target_link_libraries(Galaga ${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/SDL2_mixer-2.0.4/lib/x86/SDL2_mixer.lib)

add_custom_command(TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/SDL2.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/SDL2_ttf.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libfreetype-6.dll" $<TARGET_FILE_DIR:Galaga>			   
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libpng16-16.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libwebp-7.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libjpeg-9.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/SDL2_image.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libtiff-5.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/zlib1.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libFLAC-8.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libmodplug-1.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libmpg123-0.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libogg-0.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libopus-0.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libopusfile-0.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libvorbis-0.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/libvorbisfile-3.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ExternalDependencies/dlls/SDL2_mixer.dll" $<TARGET_FILE_DIR:Galaga>
				   TARGET Galaga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/Levels/Level1.xml" "${CMAKE_BINARY_DIR}/Debug/Levels/Level1.xml"
				   )
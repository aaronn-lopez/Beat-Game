cmake_minimum_required(VERSION 3.5.0)

project(Game)

add_definitions(-DSFML_STATIC)

include_directories(${PROJECT_SOURCE_DIR}/include)
if(WIN32)
    link_directories(${PROJECT_SOURCE_DIR}/lib/windows)
elseif(APPLE)
endif()


file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c)
add_executable(${PROJECT_NAME} ${SOURCES})



add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/src/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/src/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)

if(WIN32)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        # SFML Libraries for Release
        $<$<CONFIG:Release>:sfml-system-s.lib sfml-graphics-s.lib sfml-window-s.lib sfml-audio-s.lib sfml-network-s.lib>

        # SFML Libraries for Debug
        $<$<CONFIG:Debug>:sfml-system-s-d.lib sfml-graphics-s-d.lib sfml-window-s-d.lib sfml-audio-s-d.lib sfml-network-s-d.lib>

        # Additional dependencies required by SFML
        opengl32.lib
        freetype.lib
        winmm.lib
        gdi32.lib
        ws2_32.lib
        flac.lib
        vorbis.lib
        vorbisenc.lib
        vorbisfile.lib
        ogg.lib
    )
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        # SFML Libraries for Release
        $<$<CONFIG:Release>:sfml-system-s.lib sfml-graphics-s.lib sfml-window-s.lib sfml-audio-s.lib sfml-network-s.lib>

        # SFML Libraries for Debug
        $<$<CONFIG:Debug>:sfml-system-s-d.lib sfml-graphics-s-d.lib sfml-window-s-d.lib sfml-audio-s-d.lib sfml-network-s-d.lib>

        # Additional dependencies required by SFML
        opengl32.lib
        freetype.lib
        winmm.lib
        gdi32.lib
        ws2_32.lib
        flac.lib
        vorbis.lib
        vorbisenc.lib
        vorbisfile.lib
        ogg.lib
    )
endif()


    
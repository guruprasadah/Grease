project( "Grease Engine Core" )

file( GLOB_RECURSE EngineSrcs Source/*.cpp )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_library( GreaseCore STATIC ${EngineSrcs} )
target_include_directories( GreaseCore PUBLIC Include )

# Vendor libraries
add_subdirectory( Vendor )
# Tools
add_subdirectory( Tools )

target_link_libraries( GreaseCore ${GREASE_CORE_VENDOR_LIBS} )

######## Function for adding project ###############
function( add_grease_project NAME PATH )

file( GLOB_RECURSE ${NAME}srcs ${PATH}/Source/*.cpp )

add_executable( ${NAME} ${${NAME}srcs} )

target_link_libraries( ${NAME} GreaseCore )
target_include_directories( ${NAME} PUBLIC ${PATH}/Include )

add_custom_command( TARGET ${NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${PATH}/Assets ${CMAKE_BINARY_DIR}/Assets )
endfunction()
######## Function for adding project end ###########
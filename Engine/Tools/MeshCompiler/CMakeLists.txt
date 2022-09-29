project( ModelCompiler )

file( GLOB_RECURSE ModelCompilerSrcs Source/*.cpp )

add_subdirectory( Vendor )

add_executable( MeshCompiler ${ModelCompilerSrcs} )
target_link_libraries( MeshCompiler ${VENDOR_LIBS} )

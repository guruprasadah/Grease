add_subdirectory( GLAD )
add_subdirectory( GLFW )
add_subdirectory( GLM )

set( GREASE_CORE_VENDOR_LIBS "GLAD" "glfw" "glm" PARENT_SCOPE )
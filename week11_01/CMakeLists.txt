# week11_01: copied from week10_01
add_executable(week11_01 main.cpp)

target_link_libraries(week11_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

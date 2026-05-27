# week10_01: copied from week09_02
add_executable(week10_01 main.cpp)

target_link_libraries(week10_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

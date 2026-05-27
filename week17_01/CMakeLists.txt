add_executable(week17_01 main.cpp)

target_link_libraries(week17_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

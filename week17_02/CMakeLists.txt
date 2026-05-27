add_executable(week17_02 main.cpp)

target_link_libraries(week17_02
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

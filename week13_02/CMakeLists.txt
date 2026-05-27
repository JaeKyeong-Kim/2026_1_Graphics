add_executable(week13_02 main.cpp)

target_link_libraries(week13_02
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

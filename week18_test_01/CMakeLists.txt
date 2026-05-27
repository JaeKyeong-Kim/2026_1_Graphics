add_executable(week18_test_01 main.cpp)

target_link_libraries(week18_test_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

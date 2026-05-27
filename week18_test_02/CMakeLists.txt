add_executable(week18_test_02 main.cpp)

target_link_libraries(week18_test_02
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

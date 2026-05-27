# week11_test_02: test variant
add_executable(week11_test_02 main.cpp)

target_link_libraries(week11_test_02
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

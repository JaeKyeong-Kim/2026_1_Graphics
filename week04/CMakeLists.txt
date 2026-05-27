# week04: week03_test_01 기반 기본 셋업
add_executable(week04 main.cpp)

target_link_libraries(week04
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

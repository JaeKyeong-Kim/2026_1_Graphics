# week02: 기본 셋업
add_executable(week02 main.cpp)

target_link_libraries(week02
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

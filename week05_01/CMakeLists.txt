# week05_01: week04 기반, matrix mode 설정을 RenderScene으로 이동
add_executable(week05_01 main.cpp)

target_link_libraries(week05_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

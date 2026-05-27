# week06_01: week05_01 기반, RenderScene에서 viewport/projection을 매번 재설정
add_executable(week06_01 main.cpp)

target_link_libraries(week06_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

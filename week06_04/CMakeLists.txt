# week06_04: week06_03 기반, 삼각함수로 원형 점열 렌더링
add_executable(week06_04 main.cpp)

target_link_libraries(week06_04
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

# week06_03: week06_02 기반, (0,0,0)~(50,50,50) 점열 추가
add_executable(week06_03 main.cpp)

target_link_libraries(week06_03
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

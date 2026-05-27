# week06_02: week05_02 환경 + week06_01 점 렌더링 내용
add_executable(week06_02 main.cpp)

target_link_libraries(week06_02
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

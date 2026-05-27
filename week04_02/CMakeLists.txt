# week04_02: week04 기반 설명 보강 버전
add_executable(week04_02 main.cpp)

target_link_libraries(week04_02
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

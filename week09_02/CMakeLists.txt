# week09_02: week09_01 기반
add_executable(week09_02 main.cpp)

target_link_libraries(week09_02
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

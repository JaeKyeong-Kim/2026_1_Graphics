# week09_01: week08_05 기반
add_executable(week09_01 main.cpp)

target_link_libraries(week09_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

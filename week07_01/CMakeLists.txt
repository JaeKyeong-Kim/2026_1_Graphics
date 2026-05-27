# week07_01: week06_04 기반
add_executable(week07_01 main.cpp)

target_link_libraries(week07_01
    OpenGL::GL
    "-framework GLUT"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

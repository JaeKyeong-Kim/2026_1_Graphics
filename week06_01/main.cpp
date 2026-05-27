#if defined(__APPLE__)                              // macOS 환경이면 Apple GLUT 헤더를 사용한다.
#include <GLUT/glut.h>                              // macOS 기본 GLUT 프레임워크 헤더를 포함한다.
#else                                               // macOS가 아닌 환경 분기다.
#include <GL/glut.h>                                // 일반 GLUT 헤더를 포함한다.
#endif

#include <iostream>                                 // 콘솔 로그 출력에 사용한다.
#include <stdio.h>                                  // 기존 코드 흐름을 유지하기 위한 C 표준 헤더다.

void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, 500, 500);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(50.0f, 50.0f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

/* [week06_01 시험 요약]
 * - glBegin(GL_POINTS) + glVertex3f로 3D 점을 찍는 기본 구조다.
 * - glPointSize로 점 크기 상태를 지정한 뒤 정점을 제출한다.
 */

void SetupRC(void)
{
    std::cout << "SetupRC" << std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("week06_01");

    SetupRC();
    glutDisplayFunc(RenderScene);

    glutMainLoop();
}

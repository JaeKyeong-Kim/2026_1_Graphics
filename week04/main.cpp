#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>

void RenderScene(void)
{
    std::cout << "RenderScene" <<std::endl;
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 640, 480);

    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(0, 240, 320, 0);

    glutSwapBuffers();
}

/* [week04 시험 요약]
 * - glOrtho(0,640,0,480)로 좌하단 원점 기반 좌표계를 사용한다.
 * - 동일 도형 코드라도 투영 좌표계가 바뀌면 위치 해석이 달라진다.
 * - projection 설정은 보통 SetupRC/reshape에서 관리한다.
 */

void SetupRC(void)
{
    std::cout << "SetupRC" <<std::endl;
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    // glOrtho(-320, 320, -240, 240, -1, 1); // 이전 것
    glOrtho(0, 640, 0, 480, -1, 1); // ortho만 변경하여서 좌하단에 그려지는 형태로 바뀜. 

    glMatrixMode(GL_MODELVIEW); // 투영 설정이 끝났으니 모델뷰 모드로 원복하고 이거 renderscence에 넣을 경우 이 아래에 glrect등을 사용
    glLoadIdentity();  
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("week04");

    SetupRC();
    glutDisplayFunc(RenderScene);

    glutMainLoop();

}

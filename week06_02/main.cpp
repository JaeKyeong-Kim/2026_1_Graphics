#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>

void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

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

void ChangeSize(GLsizei w, GLsizei h)
{
    GLint wSize = 250;
    GLfloat aspectRatio;

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h)
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -1.0, 1.0);
    else
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();
}

void SetupRC(void)
{
    std::cout << "SetupRC" << std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // 현재 시스템(드라이버/하드웨어)에서 지원하는 점 크기 속성을 조회한다.
    GLfloat sizes[2];
    GLfloat step;
    glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);

    std::cout << "GL_POINT_SIZE_RANGE: min=" << sizes[0]
              << ", max=" << sizes[1] << std::endl;
    std::cout << "GL_POINT_SIZE_GRANULARITY: " << step << std::endl;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("week06_02");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}

/*
===============================================================================
[week06_02 보충 정리 - glPointSize와 glGetFloatv]
===============================================================================

1) 점 크기 지정 함수
- void glPointSize(GLfloat size);
- 현재 코드의 glPointSize(10.0f)는 "점의 요청 크기"를 지정한다.

2) 왜 시스템 조회가 필요한가?
- 요청한 점 크기가 항상 그대로 적용되는 것은 아니다.
- GPU/드라이버가 허용하는 최소/최대 범위와 증분 단위(granularity)에 맞춰
    실제 점 크기가 적용된다.

3) 지원 범위 조회 방법
- GLfloat sizes[2];
- GLfloat step;
- glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
- glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);

4) 조회 결과 의미
- sizes[0]: 지원 최소 점 크기
- sizes[1]: 지원 최대 점 크기
- step: 점 크기가 증가/감소 가능한 단위

5) 이 파일에서의 동작
- SetupRC()에서 위 값을 조회해 콘솔에 출력한다.
- 실행 시 로그를 보면 "이 시스템에서 가능한 점 크기 범위"를 바로 확인할 수 있다.
===============================================================================
*/

/* [week06_02 Notes 보강]
 * - 시험 포인트: 요청 점 크기(glPointSize)와 실제 지원 가능한 크기 범위는 다를 수 있다.
 */

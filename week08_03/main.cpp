#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include <stdio.h>

GLfloat gPointSizeRange[2] = {1.0f, 64.0f};
GLfloat gPointSizeStep = 1.0f;

void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

    const GLfloat pi = 3.1415926535f;
    const GLfloat maxAngle = 2.0f * pi * 3.0f;

    GLfloat x, y, z, angle;
    GLfloat curSize = gPointSizeRange[0];

    // 1) 원본 정답 스타일: 점을 찍으면서 z를 증가시키고 점 크기(step)도 증가
    z = -50.0f;
    for (angle = 0.0f; angle <= maxAngle; angle += 0.1f)
    {
        x = 50.0f * std::cos(angle);
        y = 50.0f * std::sin(angle);

        glPointSize(curSize);
        glColor3f(1.0f, 0.0f, 0.0f);

        glBegin(GL_POINTS);
        glVertex3f(x, y, z);
        glEnd();

        z += 0.5f;
        curSize += gPointSizeStep;
        if (curSize > gPointSizeRange[1])
            curSize = gPointSizeRange[1];
    }

    // 2) 추가 요구: 같은 점들을 GL_LINE_STRIP으로 이어서 궤적 표시
    GLfloat zLine = -50.0f;
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for (angle = 0.0f; angle <= maxAngle; angle += 0.1f)
    {
        x = 50.0f * std::cos(angle);
        y = 50.0f * std::sin(angle);
        glVertex3f(x, y, zLine);
        zLine += 0.5f;
    }
    glEnd();

    glPopMatrix();
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
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -300.0, 300.0);
    else
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, -300.0, 300.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();
}

void SetupRC(void)
{
    std::cout << "SetupRC" << std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glGetFloatv(GL_POINT_SIZE_RANGE, gPointSizeRange);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &gPointSizeStep);

    std::cout << "GL_POINT_SIZE_RANGE: [" << gPointSizeRange[0] << ", " << gPointSizeRange[1] << "]" << std::endl;
    std::cout << "GL_POINT_SIZE_GRANULARITY: " << gPointSizeStep << std::endl;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("week08_03");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}

/*
===============================================================================
[week08_03 정리]
===============================================================================
1) glGetFloatv(GL_POINT_SIZE_RANGE, sizes)
- 하드웨어가 지원하는 점 크기 최소/최대 범위를 조회한다.

2) glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step)
- 점 크기가 실제로 변할 수 있는 최소 단위를 조회한다.

3) 원본 정답 스타일 반영
- angle: 0 -> 2*pi*3 (3회전)
- x=50*cos(angle), y=50*sin(angle)
- z는 -50부터 0.5씩 증가
- curSize는 step 단위로 증가

4) 추가한 부분
- 같은 좌표를 GL_LINE_STRIP으로 다시 한 번 그려 점들을 선으로 연결했다.
- 결과적으로 "점 나선 + 연결된 궤적 선"이 함께 보인다.
===============================================================================
*/

/* [week08_03 Notes 보강]
 * - GL_LINE_STRIP은 연속 연결, GL_LINES는 2점 단위 독립 선분이라는 차이를 구분한다.
 */

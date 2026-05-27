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
    const GLfloat angleStep = 0.1f;
    const int total = static_cast<int>(maxAngle / angleStep) + 1;

    GLfloat x, y, z, angle;

    // week08_01과 동일하게 지원 범위 내에서 점 크기를 점진적으로 키운다.
    GLfloat visualMinSize = gPointSizeRange[0];
    GLfloat visualMaxSize = gPointSizeRange[1];
    if (visualMaxSize < visualMinSize)
        visualMaxSize = visualMinSize;
    // 점이 과도하게 커지지 않도록 상한과 증가 곡선을 완만하게 조정
    const GLfloat softMaxSize = 18.0f;
    if (visualMaxSize > softMaxSize)
        visualMaxSize = softMaxSize;
    const GLfloat growthPower = 1.8f;

    z = -50.0f;
    for (int i = 0; i < total; ++i)
    {
        angle = i * angleStep;
        x = 50.0f * std::cos(angle);
        y = 50.0f * std::sin(angle);

        const GLfloat t = static_cast<GLfloat>(i) / static_cast<GLfloat>(total - 1);
        GLfloat size = visualMinSize + (visualMaxSize - visualMinSize) * std::pow(t, growthPower);

        if (gPointSizeStep > 0.0f)
            size = visualMinSize + std::floor((size - visualMinSize) / gPointSizeStep) * gPointSizeStep;
        if (size > visualMaxSize)
            size = visualMaxSize;

        glPointSize(size);
        glColor3f(1.0f, 0.0f, 0.0f);

        glBegin(GL_POINTS);
        glVertex3f(x, y, z);
        glEnd();

        z += 0.5f;
    }

    glPopMatrix();
    glutSwapBuffers();
}

/* [week08_02 시험 요약]
 * - week08_01의 점 나선 로직을 기반으로, 선 연결 없이 점 렌더링만 수행한다.
 * - angle/z 증가 규칙을 유지하면서 점 크기 증가를 완만하게 튜닝한 연습 버전이다.
 */

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
    glutCreateWindow("week08_02");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}

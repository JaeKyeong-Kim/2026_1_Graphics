#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>
#include <cmath>

int gWindow = 0;
int gWindowA = 0;

void DrawAxisArrow(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat x1, GLfloat y1, GLfloat z1)
{
    const GLfloat dx = x1 - x0;
    const GLfloat dy = y1 - y0;
    const GLfloat dz = z1 - z0;
    const GLfloat headScale = 0.12f;

    const GLfloat len = std::sqrt(dx*dx + dy*dy + dz*dz);
    if (len < 1e-6f)
        return;

    const GLfloat vx = dx / len;
    const GLfloat vy = dy / len;
    const GLfloat vz = dz / len;


    GLfloat ux = 0.0f, uy = 1.0f, uz = 0.0f;
    if (std::fabs(vx*ux + vy*uy + vz*uz) > 0.999f) { ux = 1.0f; uy = 0.0f; uz = 0.0f; }

    GLfloat px = vy*uz - vz*uy;
    GLfloat py = vz*ux - vx*uz;
    GLfloat pz = vx*uy - vy*ux;
    const GLfloat plen = std::sqrt(px*px + py*py + pz*pz);
    if (plen < 1e-6f) { px = 1.0f; py = 0.0f; pz = 0.0f; }
    else { px /= plen; py /= plen; pz /= plen; }

    const GLfloat headLen = headScale * len;
    const GLfloat bx = x1 - vx * headLen;
    const GLfloat by = y1 - vy * headLen;
    const GLfloat bz = z1 - vz * headLen;

    glBegin(GL_LINES);
    // shaft
    glVertex3f(x0, y0, z0);
    glVertex3f(x1, y1, z1);
    // head sides
    glVertex3f(x1, y1, z1);
    glVertex3f(bx + px * headLen, by + py * headLen, bz + pz * headLen);
    glVertex3f(x1, y1, z1);
    glVertex3f(bx - px * headLen, by - py * headLen, bz - pz * headLen);
    glEnd();
}

void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

    glLineWidth(2.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    DrawAxisArrow(0.0f, 0.0f, 0.0f, 1.2f, 0.0f, 0.0f); 
    glColor3f(0.0f, 1.0f, 0.0f);
    DrawAxisArrow(0.0f, 0.0f, 0.0f, 0.0f, 1.2f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    DrawAxisArrow(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.2f);

    glutSwapBuffers();
}

void DrawCubeEdge(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat x1, GLfloat y1, GLfloat z1, bool dashed)
{
    if (dashed)
    {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
    }
    else
    {
        glDisable(GL_LINE_STIPPLE);
    }

    glBegin(GL_LINES);
    glVertex3f(x0, y0, z0);
    glVertex3f(x1, y1, z1);
    glEnd();
}

void RenderSceneA(void)
{
    std::cout << "RenderSceneA" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);
    
    glVertex3f(0.8f, 0.8f, -0.8f); glVertex3f(-0.8f, 0.8f, -0.8f);
    glVertex3f(-0.8f, 0.8f, -0.8f); glVertex3f(-0.8f, -0.8f, -0.8f);

    glVertex3f(-0.8f, -0.8f, 0.8f); glVertex3f(0.8f, -0.8f, 0.8f);
    glVertex3f(0.8f, -0.8f, 0.8f); glVertex3f(0.8f, 0.8f, 0.8f);
    glVertex3f(0.8f, 0.8f, 0.8f); glVertex3f(-0.8f, 0.8f, 0.8f);
    glVertex3f(-0.8f, 0.8f, 0.8f); glVertex3f(-0.8f, -0.8f, 0.8f);

    glVertex3f(-0.8f, 0.8f, 0.8f); glVertex3f(-0.8f, 0.8f, -0.8f);
    glVertex3f(-0.8f, -0.8f, -0.8f); glVertex3f(-0.8f, -0.8f, 0.8f);
    glVertex3f(0.8f, 0.8f, -0.8f); glVertex3f(0.8f, 0.8f, 0.8f);   
    
    glEnd();

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    glBegin(GL_LINES);
    
    glVertex3f(0.8f, -0.8f, -0.8f); glVertex3f(0.8f, -0.8f, 0.8f);   
    glVertex3f(0.8f, -0.8f, -0.8f); glVertex3f(0.8f, 0.8f, -0.8f);
    glVertex3f(-0.8f, -0.8f, -0.8f); glVertex3f(0.8f, -0.8f, -0.8f);
    
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

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
    glutInitWindowPosition(400, 400);
    gWindow = glutCreateWindow("simple");
    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(950, 400);
    gWindowA = glutCreateWindow("simpleA");
    SetupRC();
    glutDisplayFunc(RenderSceneA);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}

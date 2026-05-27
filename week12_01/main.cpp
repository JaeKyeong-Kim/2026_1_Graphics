#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>
#include <cmath>

// Global window handles for GLUT multi-window setup
int gWindow = 0;   // Left window - RGB coordinate axes
int gWindowA = 0;  // Right window - 3D cube with hidden-edge stipple

// DrawAxisArrow: Renders an arrow from (x0,y0,z0) to (x1,y1,z1) with triangular arrowhead.
// Uses cross product to compute perpendicular vectors for proper arrowhead orientation.
void DrawAxisArrow(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat x1, GLfloat y1, GLfloat z1)
{
    // Direction vector from start to end
    const GLfloat dx = x1 - x0;
    const GLfloat dy = y1 - y0;
    const GLfloat dz = z1 - z0;
    const GLfloat headScale = 0.12f;

    // Compute normalized direction vector (arrow shaft direction)
    const GLfloat len = std::sqrt(dx*dx + dy*dy + dz*dz);
    if (len < 1e-6f)
        return;

    const GLfloat vx = dx / len;
    const GLfloat vy = dy / len;
    const GLfloat vz = dz / len; 

    // Find a perpendicular vector using cross product.
    // Start with an arbitrary reference vector that's not parallel to direction.
    GLfloat ux = 0.0f, uy = 1.0f, uz = 0.0f;
    if (std::fabs(vx*ux + vy*uy + vz*uz) > 0.999f) { ux = 1.0f; uy = 0.0f; uz = 0.0f; }

    // Cross product: direction × reference = perpendicular vector
    GLfloat px = vy*uz - vz*uy;
    GLfloat py = vz*ux - vx*uz;
    GLfloat pz = vx*uy - vy*ux;
    const GLfloat plen = std::sqrt(px*px + py*py + pz*pz);
    if (plen < 1e-6f) { px = 1.0f; py = 0.0f; pz = 0.0f; }
    else { px /= plen; py /= plen; pz /= plen; }

    // Compute arrowhead base position (moved back from endpoint along direction)
    const GLfloat headLen = headScale * len;
    const GLfloat bx = x1 - vx * headLen;
    const GLfloat by = y1 - vy * headLen;
    const GLfloat bz = z1 - vz * headLen;

    glBegin(GL_LINES);
    // shaft: from start to end
    glVertex3f(x0, y0, z0);
    glVertex3f(x1, y1, z1);
    // head side 1: endpoint to perpendicular offset
    glVertex3f(x1, y1, z1);
    glVertex3f(bx + px * headLen, by + py * headLen, bz + pz * headLen);
    // head side 2: endpoint to opposite perpendicular offset
    glVertex3f(x1, y1, z1);
    glVertex3f(bx - px * headLen, by - py * headLen, bz - pz * headLen);
    glEnd();
}

// RenderScene: First window callback - draws RGB coordinate axes with arrows.
// Each axis is a 1.2-unit arrow in its corresponding color.
void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Apply 45° rotation around X-axis, then 45° around Y-axis for isometric-like view
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

    glLineWidth(2.0f);

    // X-axis (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    DrawAxisArrow(0.0f, 0.0f, 0.0f, 1.2f, 0.0f, 0.0f); 
    // Y-axis (green)
    glColor3f(0.0f, 1.0f, 0.0f);
    DrawAxisArrow(0.0f, 0.0f, 0.0f, 0.0f, 1.2f, 0.0f);
    // Z-axis (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    DrawAxisArrow(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.2f);

    glutSwapBuffers();
}

// DrawCubeEdge: Helper to draw a single edge with optional dashing via GL_LINE_STIPPLE.
// (Currently unused but kept for reference structure.)
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

// RenderSceneA: Second window callback - draws a 3D wireframe cube.
// 9 edges shown solid (front-facing), 3 edges at far corner shown dashed (hidden).
void RenderSceneA(void)
{
    std::cout << "RenderSceneA" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Same 45°/45° isometric rotation as first window
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    // Draw 9 solid edges (visible front faces of the cube)
    glBegin(GL_LINES);
    
    // Top front edge
    glVertex3f(0.8f, 0.8f, -0.8f); glVertex3f(-0.8f, 0.8f, -0.8f);
    // Left front edge
    glVertex3f(-0.8f, 0.8f, -0.8f); glVertex3f(-0.8f, -0.8f, -0.8f);

    // Bottom back edge
    glVertex3f(-0.8f, -0.8f, 0.8f); glVertex3f(0.8f, -0.8f, 0.8f);
    // Right back bottom edge
    glVertex3f(0.8f, -0.8f, 0.8f); glVertex3f(0.8f, 0.8f, 0.8f);
    // Right back top edge
    glVertex3f(0.8f, 0.8f, 0.8f); glVertex3f(-0.8f, 0.8f, 0.8f);
    // Left back top edge
    glVertex3f(-0.8f, 0.8f, 0.8f); glVertex3f(-0.8f, -0.8f, 0.8f);

    // Left connecting edges (front-to-back)
    glVertex3f(-0.8f, 0.8f, 0.8f); glVertex3f(-0.8f, 0.8f, -0.8f);
    glVertex3f(-0.8f, -0.8f, -0.8f); glVertex3f(-0.8f, -0.8f, 0.8f);
    // Right front top edge
    glVertex3f(0.8f, 0.8f, -0.8f); glVertex3f(0.8f, 0.8f, 0.8f);   
    
    glEnd();

    // Draw 3 dashed edges (hidden behind, at far corner)
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);  // Pattern: 0x00FF = 0000000011111111 (4 off, 4 on)
    glBegin(GL_LINES);
    
    // Right back bottom edge (hidden)
    glVertex3f(0.8f, -0.8f, -0.8f); glVertex3f(0.8f, -0.8f, 0.8f);   
    // Right front bottom edge (hidden)
    glVertex3f(0.8f, -0.8f, -0.8f); glVertex3f(0.8f, 0.8f, -0.8f);
    // Bottom front edge (hidden)
    glVertex3f(-0.8f, -0.8f, -0.8f); glVertex3f(0.8f, -0.8f, -0.8f);
    
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    glutSwapBuffers();
}

// ChangeSize: Reshape callback - called when window is resized.
void ChangeSize(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

// SetupRC: Initialize OpenGL rendering context (called once per window).
void SetupRC(void)
{
    std::cout << "SetupRC" << std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    // Create first window: RGB axes
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);
    gWindow = glutCreateWindow("simple");
    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    // Create second window: 3D cube
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(950, 400);
    gWindowA = glutCreateWindow("simpleA");
    SetupRC();
    glutDisplayFunc(RenderSceneA);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}

/* [week12_01 - copied from week11_test_01 with exam-prep comments]
 * - Multi-window demo with dual 3D coordinate systems.
 * - Left window: RGB coordinate axes with arrow markers (45°/45° isometric projection).
 * - Right window: 3D wireframe cube with hidden-edge stipple (9 solid front, 3 dashed back).
 * - Uses glLineStipple(1, 0x00FF) for dashed pattern on rear cube edges.
 * - Cross-product based arrowhead computation ensures perpendicular orientation.
 */

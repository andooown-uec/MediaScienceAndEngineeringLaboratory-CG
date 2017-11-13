#include <GL/glut.h>
#include "draw.h"

GLdouble plateVertex[][3] = {
    { 0.0, 0.0, 0.0 },
    { 1.0, 0.0, 0.0 },
    { 1.0, 0.0, 1.0 },
    { 0.0, 0.0, 1.0 }
};  // 頂点

GLdouble plateNormal[3] = { 0.0, 1.0, 0.0 };   // 法線

// 板を描画する関数
void plate(void) {
    int i;

    // 図形を描画
    glBegin(GL_QUADS);
    glNormal3dv(plateNormal);
    for (i = 0; i < 4; ++i) {
        glVertex3dv(plateVertex[i]);
    }
    glEnd();
}
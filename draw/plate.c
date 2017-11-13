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

// XZ 平面に板を描画する関数
void plateXZ(GLdouble x, GLdouble y, GLdouble z, GLdouble sizeX, GLdouble sizeZ) {
    // 座標系を保存
    glPushMatrix();
    // 座標系を変換
    glTranslated(x, y, z);
    glScaled(sizeX, 1.0, sizeZ);
    // 板を描画
    plate();
    // 座標系を復元
    glPopMatrix();
}
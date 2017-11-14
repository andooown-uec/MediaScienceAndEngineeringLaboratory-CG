#include <GL/glut.h>
#include "draw.h"

GLdouble plateVertex[][3] = {
    { 0.0, 0.0, 0.0 },
    { 1.0, 0.0, 0.0 },
    { 1.0, 0.0, 1.0 },
    { 0.0, 0.0, 1.0 }
};  // 頂点

GLdouble plateNormalXY[3] = { 0.0, 0.0, 1.0 };   // 法線
GLdouble plateNormalXZ[3] = { 0.0, 1.0, 0.0 };   // 法線
GLdouble plateNormalYZ[3] = { 1.0, 0.0, 0.0 };   // 法線

// 板を描画する関数
void plate(GLdouble normal[]) {
    int i;

    // 図形を描画
    glBegin(GL_QUADS);
    glNormal3dv(normal);
    for (i = 0; i < 4; ++i) {
        glVertex3dv(plateVertex[i]);
    }
    glEnd();
}

// XZ 平面に板を描画する関数
void plateXY(GLdouble x, GLdouble y, GLdouble z, GLdouble sizeX, GLdouble sizeY) {
    // 座標系を保存
    glPushMatrix();
    // 座標系を変換
    glTranslated(x, y, z);
    glScaled(sizeX, sizeY, 1.0);
    glRotated(270.0, 1.0, 0.0, 0.0);
    // 板を描画
    plate(plateNormalXY);
    // 座標系を復元
    glPopMatrix();
}
// XZ 平面に板を描画する関数
void plateXZ(GLdouble x, GLdouble y, GLdouble z, GLdouble sizeX, GLdouble sizeZ) {
    // 座標系を保存
    glPushMatrix();
    // 座標系を変換
    glTranslated(x, y, z);
    glScaled(sizeX, 1.0, sizeZ);
    // 板を描画
    plate(plateNormalXZ);
    // 座標系を復元
    glPopMatrix();
}
// YZ 平面に板を描画する関数
void plateYZ(GLdouble x, GLdouble y, GLdouble z, GLdouble sizeY, GLdouble sizeZ) {
    // 座標系を保存
    glPushMatrix();
    // 座標系を変換
    glTranslated(x, y, z);
    glScaled(1.0, sizeY, sizeZ);
    glRotated(90.0, 0.0, 0.0, 1.0);
    // 板を描画
    plate(plateNormalYZ);
    // 座標系を復元
    glPopMatrix();
}
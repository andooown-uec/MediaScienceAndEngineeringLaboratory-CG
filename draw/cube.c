#include <GL/glut.h>
#include "draw.h"

GLdouble cubeVertex[][3] = {
    { 0.0, 0.0, 0.0 },
    { 1.0, 0.0, 0.0 },
    { 1.0, 1.0, 0.0 },
    { 0.0, 1.0, 0.0 },
    { 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 1.0 },
    { 1.0, 1.0, 1.0 },
    { 0.0, 1.0, 1.0 }
};  // 頂点
  
int cubeFace[][4] = {
    { 0, 1, 2, 3 },
    { 1, 5, 6, 2 },
    { 5, 4, 7, 6 },
    { 4, 0, 3, 7 },
    { 4, 5, 1, 0 },
    { 3, 2, 6, 7 }
};  // 面

GLdouble cubeNormal[][3] = {
    { 0.0, 0.0,-1.0 },
    { 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0 },
    {-1.0, 0.0, 0.0 },
    { 0.0,-1.0, 0.0 },
    { 0.0, 1.0, 0.0 }
};  // 法線

// 立方体を描画する関数
void cube(GLdouble x, GLdouble y, GLdouble z, GLdouble sizeX, GLdouble sizeY, GLdouble sizeZ) {
    int i, j;

    // 座標系を保存
    glPushMatrix();
    // 座標系を変換
    glTranslated(x, y, z);
    glScaled(sizeX, sizeY, sizeZ);    
    // 図形を描画
    glBegin(GL_QUADS);
    for (j = 0; j < 6; ++j) {
        glNormal3dv(cubeNormal[j]);
        for (i = 0; i < 4; ++i) {
            glVertex3dv(cubeVertex[cubeFace[j][i]]);
        }
    }
    glEnd();
    // 座標系を復元
    glPopMatrix();
}
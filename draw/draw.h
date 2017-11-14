// 立方体を描画する関数
void cube(GLdouble x, GLdouble y, GLdouble z, GLdouble sizeX, GLdouble sizeY, GLdouble sizeZ);

// 板を描画する関数
void plate(GLdouble normal[]);
// XZ 平面に板を描画する関数
void plateXY(GLdouble x, GLdouble y, GLdouble z, GLdouble sizeX, GLdouble sizeY);
// XZ 平面に板を描画する関数
void plateXZ(GLdouble x, GLdouble y, GLdouble z, GLdouble sizeX, GLdouble sizeZ);
// YZ 平面に板を描画する関数
void plateYZ(GLdouble x, GLdouble y, GLdouble z, GLdouble sizeY, GLdouble sizeZ);
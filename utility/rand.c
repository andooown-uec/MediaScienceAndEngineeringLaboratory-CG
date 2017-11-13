#include <stdlib.h>
#include <time.h>
#include "utility.h"

// 乱数を初期化する関数
void initRand(void) {
    srand((unsigned)time(NULL));
}

// 0 〜 max - 1 の 乱数を返す関数
int randRange(int max) {
    return (int)(((double)rand() / ((double)RAND_MAX + 1)) * max);
}
// 0 〜 1 の 乱数を返す関数
float randf() {
    return (float)rand() / ((float)RAND_MAX + 1);
}
// min 〜 max の乱数を返す関数
float randRangef(float min, float max) {
    return min + randf() * (max - min);
}
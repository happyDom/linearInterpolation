#include "linearInterpolation.h"

/* =====================================================================
 * x 方向一维插值核心：给定一行 y 数据（pyValues），由 x 查插值结果
 * 前置条件：pTable 及其 pxValues/pyValues 已由调用方校验非空
 * ===================================================================== */
static float _interpolateX(const linearInterpolation_t *pTable, const float *pyValues, float x){
    uint8_t i;

    /* 边界钳制 */
    if (x <= pTable->pxValues[0]) { return pyValues[0]; }
    if (x >= pTable->pxValues[pTable->sizeOfX - 1]) { return pyValues[pTable->sizeOfX - 1]; }

    for (i = 0; i < pTable->sizeOfX - 1; i++) {
        if (x <= pTable->pxValues[i + 1]) {
            /* 精确命中采样点 */
            if (pTable->pxValues[i] == x) { return pyValues[i]; }
            if (x == pTable->pxValues[i + 1]) { return pyValues[i + 1]; }

            /* x 方向除零保护（相邻 x 重复时退回左端点） */
            if (0.0f == pTable->pxValues[i + 1] - pTable->pxValues[i]) { return pyValues[i]; }
            
            /* 线性插值 */
            return pyValues[i] + (pyValues[i + 1] - pyValues[i]) * (x - pTable->pxValues[i]) / (pTable->pxValues[i + 1] - pTable->pxValues[i]);
        }
    }
    return 0.0f;
}

/* =====================================================================
 * 一维表初始化
 * ===================================================================== */
void tableInitXY(linearInterpolation_t *pTable, uint8_t sizeOfX, const float *pxValues, const float *pyValues){
    if (NULL == pTable) {
        return;
    }
    if (sizeOfX < 1) {
        sizeOfX = 1;
    }
    pTable->sizeOfX      = sizeOfX;
    pTable->sizeOfY      = sizeOfX;
    pTable->pxValues     = pxValues;
    pTable->pyValues     = pyValues;
    pTable->pzValuesOfY  = NULL;
}

/* =====================================================================
 * 二维表初始化（z 按行优先扁平存储）
 * ===================================================================== */
void tableInitXYZ(linearInterpolation_t *pTable, uint8_t sizeOfX, uint8_t sizeOfY, const float *pxValues, const float *pyValues, const float *pzValuesByY){
    if (NULL == pTable) { return; }

    if (sizeOfX < 1) { sizeOfX = 1; }
    if (sizeOfY < 1) { sizeOfY = 1; }

    pTable->sizeOfX      = sizeOfX;
    pTable->sizeOfY      = sizeOfY;
    pTable->pxValues     = pxValues;
    pTable->pyValues     = pyValues;
    pTable->pzValuesOfY  = pzValuesByY;
}

/* =====================================================================
 * 一维查表：由 x 查 y
 * ===================================================================== */
float getY(const linearInterpolation_t *pTable, float x)
{
    if (NULL == pTable || pTable->sizeOfX < 1) { return 0.0f; }
    if (NULL == pTable->pxValues || NULL == pTable->pyValues) { return 0.0f; }

    return _interpolateX(pTable, pTable->pyValues, x);
}

/* =====================================================================
 * 二维查表：由 (x, y) 双线性插值查 z
 * 算法：先对上下两条 y 边界行做 x 插值得到 z0/z1，再沿 y 方向线性插值
 * ===================================================================== */
float getZ(const linearInterpolation_t *pTable, float x, float y){
    uint8_t i;
    float z0, z1;

    if (NULL == pTable || pTable->sizeOfX < 1 || pTable->sizeOfY < 1) { return 0.0f; }
    if (NULL == pTable->pxValues || NULL == pTable->pyValues || NULL == pTable->pzValuesOfY) { return 0.0f; }

    /* y 低于/高于表范围：钳制到首/末行 */
    if (y <= pTable->pyValues[0]) { return _interpolateX(pTable, pTable->pzValuesOfY, x); }
    if (y >= pTable->pyValues[pTable->sizeOfY - 1]) { return _interpolateX(pTable, pTable->pzValuesOfY + (pTable->sizeOfY - 1) * pTable->sizeOfX, x); }

    /* 定位 y 所在区间 [i, i+1] */
    for (i = 0; i < pTable->sizeOfY - 1; i++) {
        /* 精确命中 y 采样点 */
        if (y == pTable->pyValues[i + 1]) { return _interpolateX(pTable, pTable->pzValuesOfY + (i + 1) * pTable->sizeOfX, x); }

        if (y < pTable->pyValues[i + 1]) {
            if (y == pTable->pyValues[i]) {
                return _interpolateX(pTable, pTable->pzValuesOfY + i * pTable->sizeOfX, x);
            }

            /* 上下两行的 x 插值 */
            z0 = _interpolateX(pTable, pTable->pzValuesOfY + i * pTable->sizeOfX, x);
            z1 = _interpolateX(pTable, pTable->pzValuesOfY + (i + 1) * pTable->sizeOfX, x);

            /* y 方向除零保护（相邻 y 重复时退回下边界行） */
            if (0.0f == pTable->pyValues[i + 1] - pTable->pyValues[i]) { return z0; }
            
            /* y 方向线性插值 */
            return z0 + (z1 - z0) * (y - pTable->pyValues[i]) / (pTable->pyValues[i + 1] - pTable->pyValues[i]);
        }
    }
    return 0.0f;
}

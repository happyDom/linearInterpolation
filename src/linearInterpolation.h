#ifndef LINEARINTERPOLATION_H
#define LINEARINTERPOLATION_H

#include <stdint.h>

/* =====================================================================
 * 线性插值查表模块
 * ---------------------------------------------------------------------
  * 数据指针改为 const，标定表可声明为 const 数组放 Flash / ROM。
 *
 * 前提约定：
 *   - pxValues 必须从小到大单调递增
 *   - 二维表的 pyValues 必须从小到大单调递增
 *   - 表中任意相邻点 x 值（二维时还有 y 值）不允许重复
 * ===================================================================== */

typedef struct{
    uint8_t     sizeOfX;          /* x 序列长度（一维/二维的 x 维）          */
    uint8_t     sizeOfY;          /* y 序列长度（一维表时等于 sizeOfX）      */
    const float *pxValues;        /* x 值序列，从小到大                      */
    const float *pyValues;        /* y 值序列；二维表时作为 y 轴，从小到大   */
    const float *pzValuesOfY;     /* 二维表 z 值，扁平连续存储，行优先
                                     （第 i 行第 j 列 = pz[i*sizeOfX + j]） */
} linearInterpolation_t;

/* 一维表初始化：绑定外部 x/y 数组（不拥有内存，无需释放） */
void  tableInitXY(linearInterpolation_t *pTable, uint8_t sizeOfX, const float *pxValues, const float *pyValues);

/* 二维表初始化：绑定外部 x/y/z 数组，z 按行优先传入（不拥有内存） */
void  tableInitXYZ(linearInterpolation_t *pTable, uint8_t sizeOfX, uint8_t sizeOfY, const float *pxValues, const float *pyValues, const float *pzValuesByY);

/* 一维查表：由 x 线性插值查 y */
float getY(const linearInterpolation_t *pTable, float x);

/* 二维查表：由 (x, y) 双线性插值查 z */
float getZ(const linearInterpolation_t *pTable, float x, float y);

#endif /* LINEARINTERPOLATION_H */

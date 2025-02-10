#ifndef e3273d88a856189f8cf94e4e3e8d69ee6
#define e3273d88a856189f8cf94e4e3e8d69ee6
#include <stdint.h>

typedef struct
{
    uint8_t sizeOfX;
    uint8_t sizeOfY;
    float *pxValues;        //这是x值序列，要求x值序列从小到大变化
    float *pyValues;        //这是y值序列，如果是二维查表，则要求y值从小到大变化
    float *pzValuesOfY;       //这是z值序列，这是一个二级数组指针，第一层映射y值，第二层映射x值
} linearInterpolation_t;

void tableInitXY(linearInterpolation_t *pTable, uint8_t sizeOfX);                           //初始化一维表结构
void tableInitXYZ(linearInterpolation_t *pTable, uint8_t sizeOfX, uint8_t sizeOfY);         //初始化二维表结构
void tableInitXY_withValues(linearInterpolation_t *pTable, uint8_t sizeOfX, float *pxValues, float *pyValues);
void tableInitXYZ_withValues(linearInterpolation_t *pTable, uint8_t sizeOfX, uint8_t sizeOfY, float *pxValues, float *pyValues, float (*pzValuesByY)[sizeOfX]);
float getY(linearInterpolation_t *pTable, float x);                                         //根据指定的 x 查 y，一维线性插值查表
float getZ(linearInterpolation_t *pTable, float x, float y);                                //根据指定的 x，y 查 z，二维线性插值查表
#endif

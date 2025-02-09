#include "linearInterpolation.h"
#include <stdio.h>

void tableInitXY(linearInterpolation_t *pTable, uint8_t sizeOfX){//表格初始化为一维表，由x查y值
  if(NULL == pTable){return;}
  if(sizeOfX < 1){sizeOfX=1;}
  
  pTable->sizeOfX = sizeOfX;
  pTable->sizeOfY = sizeOfX;
}

void tableInitXY_withValues(linearInterpolation_t *pTable, uint8_t sizeOfX, float *pxValues, float *pyValues){//表格初始化为一维表，并将指定的值填充到表格中
  //初始化表格
  tableInitXY(pTable, sizeOfX);

  pTable.pxValues = pxValues;
  pTable.pyValues = pyValues;
}

void tableInitXYZ(linearInterpolation_t *pTable, uint8_t sizeOfX, uint8_t sizeOfY){//表格初始化为二维表，由(x,y)查z值
  if(NULL == pTable){return;}
  if(sizeOfX < 1){sizeOfX=1;}
  if(sizeOfY < 1){sizeOfY=1;}

  pTable->sizeOfX = sizeOfX;
  pTable->sizeOfY = sizeOfY;
}

//表格初始化为二维表，并将指定的值填充到表格中
void tableInitXYZ_withValues(linearInterpolation_t *pTable, uint8_t sizeOfX, uint8_t sizeOfY, float *pxValues, float *pyValues, float (*pzValuesByY)[sizeOfX]){
  //初始化表格
  tableInitXYZ(pTable, sizeOfX, sizeOfY);

  pTable->pxValues = pxValues;
  pTable->pyValues = pyValues;
  pTable->pzValuesOfY = pzValuesByY;
}

float getY(linearInterpolation_t *pTable, float x){//一维查表，由(x)坐标查y值
  if(pTable->sizeOfX < 1){return 0;}
  if(NULL == pTable->pxValues){return 0;}
  if(NULL == pTable->pyValues){return 0;}
  
  if(x <= pTable->pxValues[0]){return pTable->pyValues[0];}
  if(x >= pTable->pxValues[pTable->sizeOfX -1]){return pTable->pyValues[pTable->sizeOfX-1];}

  for(uint8_t i=0; i < pTable->sizeOfX-1; i++){
    if(x <= pTable->pxValues[i+1]){
      if(pTable->pxValues[i] == x){return pTable->pyValues[i];}
      if(x == pTable->pxValues[i+1]){return pTable->pyValues[i+1];}
      
      if(0 == pTable->pxValues[i+1]-pTable->pxValues[i]){return pTable->pyValues[i];}

      return pTable->pyValues[i]+(pTable->pyValues[i+1]-pTable->pyValues[i])*(x-pTable->pxValues[i])/(pTable->pxValues[i+1]-pTable->pxValues[i]);
    }
  }
	return 0;
}

float getZ(linearInterpolation_t *pTable, float x, float y){//二维查表，由(x,y)坐标，查z值
  linearInterpolation_t zTableY0;
  zTableY0.sizeOfX = pTable->sizeOfX;
  zTableY0.pxValues = pTable->pxValues;

  if(y <= pTable->pyValues[0]){
    zTableY0.pyValues = pTable->pzValuesOfY[0];
    return getY(&zTableY0, x);
  }
  if(y >= pTable->pyValues[pTable->sizeOfY-1]){
    zTableY0.pyValues = pTable->pzValuesOfY[pTable->sizeOfY-1];
    return getY(&zTableY0, x);
  }

  //根据给定的y值，找到y所在位置的上界和下界
  for(unsigned int i=0; i<pTable->sizeOfY-1; i++){
    if(y == pTable->pyValues[i+1]){
      zTableY0.pyValues = pTable->pzValuesOfY[i+1];
      return getY(&zTableY0, x);
    }

    if(y < pTable->pyValues[i+1]){
      if(y == pTable->pyValues[i]){
        zTableY0.pyValues = pTable->pzValuesOfY[i];
        return getY(&zTableY0, x);
      }

      linearInterpolation_t zTableY1;
      float z0,z1;
      
      zTableY1.sizeOfX = pTable->sizeOfX;
      zTableY1.pxValues = pTable->pxValues;

      zTableY0.pyValues = pTable->pzValuesOfY[i];
      zTableY1.pyValues = pTable->pzValuesOfY[i+1];
      z0 = getY(&zTableY0, x);
      z1 = getY(&zTableY1, x);

      return z0 + (z1 - z0) * (y - pTable->pyValues[i]) / (pTable->pyValues[i+1] - pTable->pyValues[i]);
    }
  }

  //default
  return 0;
}

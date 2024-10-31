#include "linearInterpolation.h"

void tableInitXY(linearInterpolation_t *pTable, uint8_t sizeOfX){//表格初始化为一维表，由x查y值
  if(NULL == pTable){return;}
  if(sizeOfX < 1){sizeOfX=1;}

  pTable->pxValues = (float *)malloc(sizeof(float) * pTable->sizeOfX);
  pTable->pyValues = (float *)malloc(sizeof(float) * pTable->sizeOfX);
}

void tableInitXYZ(linearInterpolation_t *pTable, uint8_t sizeOfX, uint8_t sizeOfY){//表格初始化为二维表，由(x,y)查z值
  if(NULL == pTable){return;}
  if(sizeOfX < 1){sizeOfX=1;}
  if(sizeOfY < 1){sizeOfY=1;}
  if(sizeOfY < sizeOfX){sizeOfY = sizeOfX;}

  pTable->pxValues = (float *)malloc(sizeof(float) * pTable->sizeOfX);
  pTable->pyValues = (float *)malloc(sizeof(float) * pTable->sizeOfY);
  pTable->pzValues = (float **)malloc(sizeof(float) * pTable->sizeOfY);
  for(uint8_t i = 0;i < pTable->sizeOfY; i++){
    pTable->pzValues[i] = (float *)malloc(sizeof(float) * pTable->sizeOfX);
  }
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
  return 0; //todo
}

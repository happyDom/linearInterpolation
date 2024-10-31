#include "linearInterpolation.h"

void tableInitXY(linearInterpolation_t *pTable, uint8_t sizeOfX){//表格初始化为一维表，由x查y值
  if(NULL == pTable){return;}
  if(sizeOfX < 1){sizeOfX=1;}

  pTable->pxIndexs = (float *)malloc(sizeof(float) * pTable->sizeOfX);
  pTable->pyIndexs = (float *)malloc(sizeof(float) * pTable->sizeOfX);
}

void tableInitXYZ(linearInterpolation_t *pTable, uint8_t sizeOfX, uint8_t sizeOfY){//表格初始化为二维表，由(x,y)查z值
  if(NULL == pTable){return;}
  if(sizeOfX < 1){sizeOfX=1;}
  if(sizeOfY < 1){sizeOfY=1;}
  if(sizeOfY < sizeOfX){sizeOfY = sizeOfX;}

  pTable->pxIndexs = (float *)malloc(sizeof(float) * pTable->sizeOfX);
  pTable->pyIndexs = (float *)malloc(sizeof(float) * pTable->sizeOfY);
  pTable->pzIndexs = (float **)malloc(sizeof(float) * pTable->sizeOfY);
  for(uint8_t i = 0;i < pTable->sizeOfY; i++){
    pTable->pzIndexs[i] = (float *)malloc(sizeof(float) * pTable->sizeOfX);
  }
}

float getY(linearInterpolation_t *pTable, float x){//一维查表，由(x)坐标查y值
  if(pTable->sizeOfX < 1){return 0;}
  if(NULL == pTable->pxIndexs){return 0;}
  if(NULL == pTable->pyIndexs){return 0;}
  
  if(x <= pTable->pxIndexs[0]){return pTable->pyIndexs[0];}
  if(x >= pTable->pxIndexs[pTable->sizeOfX -1]){return pTable->pyIndexs[pTable->sizeOfX-1];}

  for(uint8_t i=0; i < pTable->sizeOfX-1; i++){
    if(x <= pTable->pxIndexs[i+1]){
      if(pTable->pxIndexs[i] == x){return pTable->pyIndexs[i];}
      if(x == pTable->pxIndexs[i+1]){return pTable->pyIndexs[i+1];}
      
      if(0 == pTable->pxIndexs[i+1]-pTable->pxIndexs[i]){return pTable->pyIndexs[i];}

      return pTable->pyIndexs[i]+(pTable->pyIndexs[i+1]-pTable->pyIndexs[i])*(x-pTable->pxIndexs[i])/(pTable->pxIndexs[i+1]-pTable->pxIndexs[i]);
    }
  }
}

float getZ(linearInterpolation_t *pTable, float x, float y){//二维查表，由(x,y)坐标，查z值
  return 0; //todo
}

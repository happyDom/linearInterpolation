#include <stdio.h>
#include "linearInterpolation.h"

linearInterpolation_t demoTable;

int main(int argc, char const *argv[])
{
    if(false){
        //使用 init 方法配置表参数
        tableInitXY(&demoTable, 3);
        demoTable.pxValues[0] = 0;
        demoTable.pxValues[1] = 2;
        demoTable.pxValues[2] = 4;

        free(demoTable.pyValues);
        static float yValues[] = {10.0f, 15.0f, 20.0f};
        demoTable.pyValues = yValues;

        float userX=0;
        while (true)
        {
            printf("please input X value:"); scanf("%f", &userX);
            printf("the x is: %f, then the y should be: %f\n", userX, getY(&demoTable, userX));
        }
    }

    if(true){
        //自定义表参数
        demoTable.sizeOfX = 2;
        demoTable.sizeOfY = 3;

        //static的约束保障了这些变量的空间不会被收回
        static float xValues[] = {1,2};
        static float yValues[] = {1,2,3};

        demoTable.pxValues = xValues;
        demoTable.pyValues = yValues;
        demoTable.pzValuesOfY = (float **)malloc(sizeof(float) * demoTable.sizeOfY);

        static float pzValuesOfY_0[] = {2,3};
        static float pzValuesOfY_1[] = {3,4};
        static float pzValuesOfY_2[] = {4,5};
        demoTable.pzValuesOfY[0] = pzValuesOfY_0;   //把每一个y对应一行z值配置到表中
        demoTable.pzValuesOfY[1] = pzValuesOfY_1;
        demoTable.pzValuesOfY[2] = pzValuesOfY_2;

        float userX=0, userY=0;
        while (true)
        {
            printf("please input X value:"); scanf("%f", &userX);
            printf("please input Y value:"); scanf("%f", &userY);
            printf("the coord is: (%f, %f), then the z should be: %f\n", userX, userY, getZ(&demoTable, userX, userY));
        }
    }
    
    return 0;
}

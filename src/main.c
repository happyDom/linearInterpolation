#include <stdio.h>
#include "linearInterpolation.h"

linearInterpolation_t demoTable;

#define A 0
int main(int argc, char const *argv[])
{
    if(A){
        /*
        * Y
        * ↑
        * | 
        * 20-------------*
        * ｜
        * 15--------*
        * ｜
        * 10---* 
        * ｜
        * *----2----4----8-------------> X
        */
        //static的约束保障了这些变量的空间不会被收回
        static float xValues[] = {2, 4, 8};
        static float yValues[] = {10.0f, 15.0f, 20.0f};
        tableInitXY(&demoTable, 3, xValues,yValues);
        
        float userX=0;
        while (1)
        {
            printf("please input X value:"); scanf("%f", &userX);
            printf("the x is: %f, then the y should be: %f\n", userX, demoTable.getY(&demoTable, userX));
        }
    }

    if(!A){
        /*
        * *----1----2-----------------> X
        * ｜
        * 1    2    3
        * ｜
        * 2    3    4
        * ｜
        * 3    4    8
        * ｜
        * ↓
        * Y
        */
        //static的约束保障了这些变量的空间不会被收回
        static float xValues[] = {1,2};
        static float yValues[] = {1,2,3};

        static float zValues[][2] = {   {2,3},
                                        {3,4},
                                        {4,8}};
        tableInitXYZ(&demoTable, 2, 3, xValues, yValues, zValues);
        
        float userX=0, userY=0;
        while (1)
        {
            printf("please input X value:"); scanf("%f", &userX);
            printf("please input Y value:"); scanf("%f", &userY);
            printf("the coord is: (%f, %f), then the z should be: %f\n", userX, userY, demoTable.getZ(&demoTable, userX, userY));
        }
    }
    
    return 0;
}

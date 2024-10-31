#include <stdio.h>
#include "linearInterpolation.h"

linearInterpolation_t demoTable;

int main(int argc, char const *argv[])
{   
    tableInitXY(&demoTable, 3);
    demoTable.pxValues[0] = 0;
    demoTable.pxValues[1] = 2;
    demoTable.pxValues[2] = 4;
    demoTable.pyValues[0] = 10;
    demoTable.pyValues[1] = 15;
    demoTable.pyValues[2] = 20;

    float userNumber=0;
    while (true)
    {
        printf("please input a number:"); scanf("%f", &userNumber);
        printf("the x is: %f, then the y should be: %f\n", userNumber, getY(&demoTable, userNumber));
    }
    

    return 0;
}

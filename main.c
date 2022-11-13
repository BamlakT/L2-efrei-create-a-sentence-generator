#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "cmake-build-debug/tst node.h"
#include "cmake-build-debug/parser.h"
// Driver program to test above functions
int main()
{
    int a= File_parser();
    printf("%d",a);
    // Use current time as
    // seed for random generator
    srand(time(0));
    //printf("Print random sentence\n");
    //modelone();
    printf("\n             -Hello-\n         ---This is Group INT2-9 !---");
    menu_real();

    return 0;
}

#include <stdio.h>

int swap_add(int *px, int *py)
{
    int t = *px;
    *px = *py;
    *py = t;
    return *px + *py;
}

int caller()
{
    int x = 100;
    int y = 200;
    int z = 300;
    int w = 400;
    return 0;
}

int main()
{
    caller();
}
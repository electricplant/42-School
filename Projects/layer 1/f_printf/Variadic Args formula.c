#include <stdio.h>
#include <stdarg.h>

int max(int num_args, ...);

int main(void)
{
    max(6, 10, 9, 8, 2, 7, 9);
    return (0);
}

int max(int num_args, ...)
{
    va_list args;

    va_start(args, num_args);
    
    for (int i = 0; i < num_args; i++)
    {
        int x = va_arg(args, int);
        printf("x: %d\n", x);
    }
    va_end(args);
    return (0);
}
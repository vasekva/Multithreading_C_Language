#include "header.h"

int ft_check_params(int argc, char *argv[])
{
    int i;

    i = 0;
    if (argc != 5 && argc != 6)
    {
        if (argc < 5)
            printf("Error: %s\n", ONE);
        else
            printf("Error: %s\n", TWO);
        return (-1);
    }
    while (i < argc)
    {
        printf("Parameter N%d - |%s|\n", i, argv[i]);
        i++;
    }
    return (0);
}

int main(int argc, char *argv[])
{
    (void)argv;

    ft_check_params(argc, argv);
//    if (args == 4)
//    {
//        wait_eat();
//    }
//    if (args == 5)
//    {
//        wait_die();
//    }
    return (0);
}
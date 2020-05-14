#include "lem_in.h"

void    error_msg()
{
    ft_putstr(RED);
    ft_putstr("ERROR");
    ft_putendl(RESET);
    exit(EXIT_FAILURE);
}

void    print_lines(char *str)
{
    // ft_putendl_fd(RED, 1);
    ft_putstr("helloeee");
    ft_putstr(str);
    // ft_putendl(RESET);
}
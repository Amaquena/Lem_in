#include "lem-in.h"

int main(void)
{
    char line[] = "1 2 3";
    char line1[] = "1 2 3";
    // char **room;

    // room = ft_strsplit(line, ' ');
    if (ft_strequ(line, line1))
        ft_putstr(line);
    // free(room[0]);
    // free(room[1]);
    // free(room[2]);
    // free(room);
    return (0);
}
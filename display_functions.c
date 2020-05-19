#include "lem_in.h"

void error_msg(char *str)
{
    ft_putstr(RED);
    ft_putstr(str);
    ft_putendl(RESET);
    exit(EXIT_FAILURE);
}

void print_lines(t_farm *farm)
{
    t_room *rooms = farm->rooms;
    t_link *links = farm->links;

    printf("\nNumber of ants: %d\n", farm->ants);
    printf("Number of rooms: %d\n", farm->nbr_rooms);

    while (rooms)
    {
        printf("\nRoom name:\t%s\nRoom type:\t%d\nRoom x:\t%d\nRoom y:\t%d\nRoom h:\t%d\nRoom f:\t%d\n",
        rooms->name, rooms->type, rooms->x, rooms->y, rooms->h, rooms->f);
        rooms = rooms->next;
    }
    while (links)
    {
        printf("\nLink room1:\t%s\nlink room2:\t%s\nlink g:\t%d\n",
        links->room1, links->room2, links->g);
        links = links->next;
    }
}
#include "lem-in.h"

void error_msg(char *str, t_farm *farm)
{
    ft_putstr(RED);
    ft_putstr(str);
    ft_putendl(RESET);
    free_farm(farm);
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

void free_farm(t_farm *farm)
{
    t_room *rooms;
    t_room *nextroom;
    t_link *links;
    t_link *nextlink;

    rooms = farm->rooms;
    links = farm->links;

    if (rooms)
    {
        while (rooms)
        {
            // free(rooms->name);
            ft_strdel(&rooms->name);
            nextroom = rooms->next;
            free(rooms);
            rooms = nextroom;
        }
    }

    if (links)
    {
        while (links)
        {
            // free(links->room1);
            // free(links->room2);
            ft_strdel(&links->room1);
            ft_strdel(&links->room2);
            nextlink = links->next;
            free(links);
            links = nextlink;
        }
    }
    free(rooms);
    free(links);
    if (farm->line)
        ft_strdel(&farm->line);
}

void free_room(char **room)
{
    if (room[0])
    {
        free(room[0]);
        room[0] = NULL;
    }
    if (room[1])
    {
        free(room[1]);
        room[1] = NULL;
    }
    if (room[2])
    {
        free(room[2]);
        room[2] = NULL;
    }
    if (room)
    {
        free(room);
        room = NULL;
    }
}

void free_link(char **link)
{
    if (link[0])
    {
        free(link[0]);
        link[0] = NULL;
    }
    if (link[1])
    {
        free(link[1]);
        link[1] = NULL;
    }
    if (link)
    {
        free(link);
        link = NULL;
    }
}
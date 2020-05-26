#include "lem-in.h"

void error_msg(char *str, t_farm *farm)
{
    ft_putstr(RED);
    ft_putstr(str);
    ft_putendl(RESET);
    free_farm(farm);
    exit(EXIT_FAILURE);
}

void print_a_line(int ant, char *room)
{
    ft_putchar('L');
    ft_putnbr(ant);
    ft_putchar('-');
    ft_putstr(room);
}

t_ants convert_path(t_farm *farm)
{
    t_queue *path;
    t_ants ants;
    int i = 0;
    int count;

    count = 0;
    path = farm->paths[0];
    while (path)
    {
        count++;
        path = path->next;
    }

    path = farm->paths[0];
    ants.rooms = malloc(sizeof(char *) * (count + 1));
    ants.length = count;
    while (path)
    {
        ants.rooms[i] = ft_strdup(path->name);
        i++;
        path = path->next;
    }
    ants.rooms[i] = NULL;
    return (ants);
}

int print_cycle(int cycle, int ants, int paths_count, t_ants paths)
{
    int keep;
    int space;
    int ant;
    int i;
    int j;

    keep = 0;
    space = 0;
    i = -1;
    while (++i < paths_count)
    {
        j = 0;
        while (++j < paths.length)
        {
            ant = (cycle - j) * paths_count + i + 1;
            if (ant <= ants && ant > 0)
            {
                keep = 1;
                if (space || (space++ && !space))
                    ft_putchar(' ');
                print_a_line(ant, paths.rooms[j]);
            }
        }
    }
    return (keep);
}

void output_farm(t_farm *farm)
{
    int path_count;
    int keep;
    int cycles;
    t_ants path;

    path = convert_path(farm);
    path_count = 1;
    keep = 1;
    cycles = 1;
    while (keep)
    {
        keep = 0;
        ft_putchar('\n');
        keep = print_cycle(cycles, farm->ants, path_count, path);
        cycles++;
    }
}

void free_farm(t_farm *farm)
{

    t_room *rooms;
    t_room *nextroom;
    t_link *links;
    t_link *nextlink;
    t_queue **paths;
    t_queue *nextpath;
    size_t i;

    rooms = farm->rooms;
    links = farm->links;
    paths = farm->paths;
    i = 0;

    if (paths && paths[i])
    {
        while (paths && paths[i])
        {
            nextpath = paths[i]->next;
            ft_strdel(&paths[i]->name);
            ft_memdel((void **)&paths[i]);
            paths[i] = nextpath;
            // i++;
        }
    }

    if (rooms)
    {
        while (rooms)
        {
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
            ft_strdel(&links->room1);
            ft_strdel(&links->room2);
            nextlink = links->next;
            free(links);
            links = nextlink;
        }
    }
    free(rooms);
    free(links);
    free(paths);
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

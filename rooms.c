#include "lem_in.h"

static void    create_room(t_farm *farm, int type)
{
    t_room *new_room;
    t_room *head;

    if (!(new_room = (t_room *)malloc(sizeof(t_room))))
        error_msg("Error: Failed malloc when creating room.", farm);
    new_room->name = ft_strdup(farm->room[0]);
    new_room->x = ft_atoi(farm->room[1]);
    new_room->y = ft_atoi(farm->room[2]);
    new_room->f = 0;
    new_room->type = type;
    new_room->next = NULL;
    new_room->h = ++farm->nbr_rooms;

    head = farm->rooms;
    if(head)
    {
        while (head->next)
            head = head->next; 
        head->next = new_room;
    }
    else
        farm->rooms = new_room;
}

int    verify_start_end(t_farm *farm)
{
    t_room *head;
    int flag;

    head = farm->rooms;
    flag = 0;
    while (head)
    {
        if (head->type == START)
            flag++;
        if (head->type == END)
            flag++;
        head = head->next;
    }
    if (flag != 2)
        return (0);
    return (1);
}

int     verify_start_not_end(t_farm *farm)
{
    t_room *head;

    head = farm->rooms;
    while (head)
    {
        if (ft_strequ(head->name, farm->room[0]))
        {
            if (head->type == START)
                return (0);
            else if (head->type == END)
                return (0);
        }
        head = head->next;
    }
    return (1);
}

void     verify_room(t_farm *farm, int type)
{
    int count;
    
    count = 0;
    farm->room = ft_strsplit(farm->line, ' ');
    while (farm->room[count])
        count++;
    if (count != 3)
    {
        free_room(farm->room);
        free(farm->line);
        error_msg("Error: Incorrect format for declaring room.", farm);
    }
    if (!ft_strisdigit(farm->room[1]) || !ft_strisdigit(farm->room[2]))
        error_msg("Error: Room coordinates must be of integer type.", farm);
    create_room(farm, type);
    free_room(farm->room);
}
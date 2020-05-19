#include "lem_in.h"

static void    create_room(t_farm **farm, char **room, int type)
{
    t_room *new_room;
    t_room *head;

    if (!(new_room = (t_room *)malloc(sizeof(t_room))))
        error_msg("Error: Failed malloc when creating room.");
    new_room->name = room[0];
    new_room->x = ft_atoi(room[1]);
    new_room->y = ft_atoi(room[2]);
    new_room->f = 0;
    new_room->type = type;
    new_room->next = NULL;
    new_room->h = ++(*farm)->nbr_rooms;

    head = (*farm)->rooms;
    if(head)
    {
        while (head->next)
            head = head->next; 
        head->next = new_room;
    }
    else
        (*farm)->rooms = new_room;
}

int    verify_start_end(t_farm **farm)
{
    t_room *head;
    int flag;

    head = (*farm)->rooms;
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

void     verify_room(t_farm **farm, char *line, int type)
{
    char **room;
    int count;
    t_room *room_list;

    count = 0;
    room_list = (*farm)->rooms;
    room = ft_strsplit(line, ' ');    
    while (room[count])
        count++;
    if (count != 3)
        error_msg("Error: Incorrect format for declaring room.");
    if (!ft_strisdigit(room[1]) || !ft_strisdigit(room[2]))
        error_msg("Error: Room coordinates must be of integer type.");
    while (room_list)
    {
        if (ft_strequ(room_list->name, room[0]))
        {
            if (room_list->type == START)
                error_msg("Error: Room alredy set as Start");
            else if (room_list->type == END)
                error_msg("Error: Room alredy set as End");
        }
        room_list = room_list->next;
    }
    if (!room_list)
        create_room(farm, room, type);
}
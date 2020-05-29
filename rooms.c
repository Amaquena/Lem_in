/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kris <kris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 10:00:50 by kris              #+#    #+#             */
/*   Updated: 2020/05/29 10:00:53 by kris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*
    create_room() mallocs space in memory for a new room,
    this new room is given the inputs from farm->room and
    sets all the other values too NULL or zero.
    farm->nbr_room also increments to keep count of the total
    amount of rooms on the map.

    farm->rooms holds a list of all the rooms that are on the map.
*/

static void     create_room(t_farm *farm, int type)
{
    t_room  *new_room;
    t_room  *head;

    if (!(new_room = (t_room *)malloc(sizeof(t_room))))
        error_msg("Error: Failed malloc when creating room.", farm);
    new_room->name = ft_strdup(farm->room[0]);
    new_room->x = ft_atoi(farm->room[1]);
    new_room->y = ft_atoi(farm->room[2]);
    new_room->visited = 0;
    new_room->lock = 0;
    new_room->depth = 0;
    new_room->type = type;
    new_room->next = NULL;
    if (type == START)
        farm->start = ft_strdup(farm->room[0]);
    if (type == END)
        farm->end = ft_strdup(farm->room[0]);

    head = farm->rooms;
    if (head)
    {
        while (head->next)
            head = head->next;
        head->next = new_room;
    }
    else
        farm->rooms = new_room;
}

/*
    This function checks that there are both a valid start
    and a valid end in the map;
*/

int             verify_start_end(t_farm *farm)
{
    t_room  *head;
    int     flag;

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

/*
    This funtion is used to check that a room is
    not deined as a start room and an end room.
*/

static int      verify_start_not_end(t_farm *farm)
{
    t_room  *head;

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

/*
    Verify funtions takes the farm->line and splits it into farm->room
    farm->room is the check if it is a valid room before storing it.
    If all tests passes the create_room() is called.
*/

void            verify_room(t_farm *farm, int type)
{
    int     count;

    count = 0;
    farm->room = ft_strsplit(farm->line, ' ');
    while (farm->room[count])
        count++;
    if (count != 3)
    {
        free_room(farm->room);
        error_msg("Error: Incorrect format for declaring room.", farm);
    }
    if (!ft_strisdigit(farm->room[1]) || !ft_strisdigit(farm->room[2]))
    {
        free_room(farm->room);
        error_msg("Error: Room coordinates must be of integer type.", farm);
    }
    if (!verify_start_not_end(farm))
    {
        free_room(farm->room);
        error_msg("Error: Room set as Start and End", farm);
    }
    create_room(farm, type);
    free_room(farm->room);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_assist2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kris <kris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 20:39:10 by krissyleemc       #+#    #+#             */
/*   Updated: 2020/05/29 09:59:50 by kris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_room      *find_room(char *name, t_room *room)
{
    t_room  *tmp;

    tmp = room;
    while (tmp)
    {
        if (!ft_strcmp(tmp->name, name))
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

void        add_to_open_queue(char *room, t_queue **open, t_room *rooms)
{
    t_queue *new_open;
    t_queue *last;
    t_room  *tmp_room;

    tmp_room = find_room(room, rooms);
    if (tmp_room->visited == 0 && tmp_room->lock == 0)
    {
        tmp_room->visited = 1;
        new_open = (t_queue *)ft_memalloc(sizeof(t_queue));
        new_open->name = ft_strdup(room);
        new_open->next = NULL;

        last = (*open);
        if ((*open) == NULL)
        {
            new_open->prev = NULL;
            (*open) = new_open;
            return;
        }
        while (last->next)
            last = last->next;
        last->next = new_open;
        new_open->prev = last;
    }
}

void        find_linking_room(t_link *links, t_queue *open, t_farm *farm)
{
    t_queue *tmp_open;
    int flag = 0;

    tmp_open = open;
    while (links)
    {
        if (ft_strequ(links->room1, open->name))
        {
            flag = 1;
            add_to_open_queue(links->room2, &open, farm->rooms);
        }
        else if (ft_strequ(links->room2, open->name))
        {
            flag = 1;
            add_to_open_queue(links->room1, &open, farm->rooms);
        }
        open = tmp_open;
        links = links->next;
    }
    if (!flag)
        error_msg("Error: Start or end Dont link to any rooms", farm);
}

void        set_depth(t_queue *open, t_room *rooms, int depth)
{
    t_room *tmp_room;

    while (open)
    {
        tmp_room = find_room(open->name, rooms);
        if (tmp_room->type != START && tmp_room->depth == 0)
        {
            tmp_room->depth = depth;
        }
        open = open->next;
    }
}

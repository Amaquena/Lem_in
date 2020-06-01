/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_assist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kris <kris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 20:30:54 by krissyleemc       #+#    #+#             */
/*   Updated: 2020/05/29 09:59:16 by kris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void        add_to_closed_queue(t_queue **open, t_queue **closed)
{
    t_queue *tmp;
    t_queue *curr_closed;

    tmp = (*open);
    if ((*open) && (*open)->next)
    {
        (*open)->next->prev = NULL;
        (*open) = (*open)->next;
    }
    else if ((*open) && !(*open)->next)
    {
        tmp->next = NULL;
        (*open) = NULL;
    }

    tmp->next = NULL;
    if ((*closed) == NULL)
    {
        tmp->prev = NULL;
        (*closed) = tmp;
    }
    else
    {
        curr_closed = (*closed);
        while (curr_closed->next)
            curr_closed = curr_closed->next;
        curr_closed->next = tmp;
        tmp->prev = curr_closed;
    }
}

int         adjust_depth(t_room *rooms)
{
    while (rooms)
    {
        rooms->depth -= 1;
        if (rooms->type == END && rooms->depth < 0)
            return (0);
        rooms = rooms->next;
    }
    return (1);
}

int         check_if_end_found(t_queue *closed, t_room *rooms)
{
    t_room *tmp_room;

    while (closed->next)
        closed = closed->next;
    tmp_room = find_room(closed->name, rooms);
    if (tmp_room->type == END)
        return (1);
    return (0);
}

void        add_to_path_queue(t_room *room, t_queue **path, t_farm *farm)
{
    t_queue *new_path;
    t_queue *tmp_path;
    int     flag;

    room->lock = farm->lock;
    tmp_path = path[0];
    flag = 0;

    while (tmp_path)
    {
        if (ft_strequ(room->name, tmp_path->name))
        {
            flag = 1;
            break;
        }
        tmp_path = tmp_path->next;
    }
    if (flag == 0)
    {
        new_path = (t_queue *)ft_memalloc(sizeof(t_queue));
        new_path->name = ft_strdup(room->name);
        new_path->next = path[0];
        new_path->prev = NULL;

        if (path[0] != NULL)
            path[0]->prev = new_path;

        path[0] = new_path;
    }
}

int         find_on_closed(t_queue *closed, char *name)
{
    while (closed)
    {
        if (ft_strequ(closed->name, name))
            return (1);
        closed = closed->next;
    }
    return (0);
}

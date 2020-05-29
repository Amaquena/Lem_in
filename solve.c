/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kris <kris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 10:01:37 by kris              #+#    #+#             */
/*   Updated: 2020/05/29 10:01:39 by kris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void     find_linking_room2(char *name, t_farm *farm, int depth, t_queue **path, t_queue *closed)
{
    t_room  *tmp_room;
    t_link  *links;

    links = farm->links;
    while (links)
    {
        if (ft_strequ(links->room1, name))
        {
            tmp_room = find_room(links->room2, farm->rooms);
            if (tmp_room->depth == (depth - 1) && find_on_closed(closed, tmp_room->name))
            {
                add_to_path_queue(tmp_room, &path[0], farm);
                break;
            }
        }
        else if (ft_strequ(links->room2, name))
        {
            tmp_room = find_room(links->room1, farm->rooms);
            if (tmp_room->depth == (depth - 1) && find_on_closed(closed, tmp_room->name))
            {
                add_to_path_queue(tmp_room, &path[0], farm);
                break;
            }
        }
        links = links->next;
    }
}

static void     find_path(t_farm *farm, t_queue **path, t_queue *closed)
{
    t_queue     *tmp_closed;
    t_room      *tmp_room;

    tmp_closed = closed;
    while (tmp_closed->next)
        tmp_closed = tmp_closed->next;

    tmp_room = find_room(tmp_closed->name, farm->rooms);
    add_to_path_queue(tmp_room, &path[0], farm);
    while (tmp_closed)
    {
        tmp_room = find_room(path[0]->name, farm->rooms);
        find_linking_room2(path[0]->name, farm, tmp_room->depth, &path[0], closed);
        tmp_closed = tmp_closed->prev;
    }
}

static void     reset_rooms(t_farm *farm, t_queue **open, t_queue **closed)
{
    t_room *rooms;
    t_queue *tmp;
    t_queue *pop;

    rooms = farm->rooms;
    while (rooms)
    {
        if (rooms->type == START || rooms->type == END)
            rooms->lock = 0;
        if (rooms->lock == 0)
            rooms->depth = 0;
        rooms->visited = 0;
        rooms = rooms->next;
    }
    if ((*open))
    {
        tmp = (*open);
        while (tmp)
        {
            pop = tmp;
            tmp = tmp->next;
            ft_strdel(&pop->name);
            ft_memdel((void **)&pop);
        }
    }
    (*open) = NULL;
    if ((*closed))
    {
        tmp = (*closed);
        while (tmp)
        {
            pop = tmp;
            tmp = tmp->next;
            ft_strdel(&pop->name);
            ft_memdel((void **)&pop);
        }
    }
    (*closed) = NULL;
}

static int      count_paths(t_link *links, char *start)
{
    int count;

    count = 0;
    while (links)
    {
        if (ft_strequ(links->room1, start))
            count++;
        else if (ft_strequ(links->room2, start))
            count++;
        links = links->next;
    }
    return (count);
}

void            solve(t_farm *farm)
{
    t_queue *open;
    t_queue *closed;
    t_queue **path;
    t_room  *tmp_room;

    open = NULL;
    closed = NULL;
    farm->path_count = count_paths(farm->links, farm->start);
    farm->paths = (t_queue **)ft_memalloc(sizeof(t_queue *) * (farm->path_count + 1));
    path = farm->paths;

    int current_path = 0;
    while (current_path < farm->path_count)
    {
        add_to_open_queue(farm->start, &open, farm->rooms);
        while (open)
        {
            find_linking_room(farm->links, open, farm);
            tmp_room = find_room(open->name, farm->rooms);
            set_depth(open, farm->rooms, ++tmp_room->depth);
            add_to_closed_queue(&open, &closed);
            if (check_if_end_found(closed, farm->rooms))
                break;
        }
        if (adjust_depth(farm->rooms))
            find_path(farm, &path[current_path], closed);
        reset_rooms(farm, &open, &closed);
        current_path++;
    }
    path[current_path] = NULL;
}

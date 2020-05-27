/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krissyleemc <krissyleemc@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 20:14:35 by krissyleemc       #+#    #+#             */
/*   Updated: 2020/05/27 20:15:10 by krissyleemc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krissyleemc <krissyleemc@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 10:01:43 by kris              #+#    #+#             */
/*   Updated: 2020/06/01 20:19:24 by krissyleemc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_ants *convert_path(t_farm *farm)
{
    t_queue *path;
    t_ants *ants;
    int i;
    int count;
    int path_count;
    int current_path;

    path_count = 0;
    while (farm->paths[path_count])
        path_count++;

    farm->path_count = path_count;
    ants = (t_ants *)ft_memalloc(sizeof(t_ants) * (path_count));
    current_path = 0;
    while (current_path < path_count)
    {
        path = farm->paths[current_path];
        count = 0;
        while (path)
        {
            count++;
            path = path->next;
        }

        path = farm->paths[current_path];
        ants[current_path].rooms = malloc(sizeof(char *) * (count + 1));
        ants[current_path].length = count;
        i = 0;
        while (path)
        {
            ants[current_path].rooms[i] = ft_strdup(path->name);
            i++;
            path = path->next;
        }
        ants[current_path].rooms[i] = NULL;
        current_path++;
    }
    // ants[current_path] = NULL;
    return (ants);
}

int print_cycle(int cycle, int ants, int paths_count, t_ants *paths)
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
        while (++j < paths[i].length)
        {
            ant = (cycle - j) * paths_count + i + 1;
            if (ant <= ants && ant > 0)
            {
                keep = 1;
                if (space || (space++ && !space))
                    ft_putchar(' ');
                print_a_line(ant, paths[i].rooms[j]);
            }
        }
    }
    return (keep);
}

void free_ants(t_ants **ants, int path_count)
{
    int i;
    int j;
    t_ants *a;
    t_ants *head;

    a = *ants;
    head = *ants;
    i = 0;
    while (i < (path_count))
    {
        j = 0;
        while (a->rooms[j])
        {
            ft_strdel(&a->rooms[j]);
            j++;
        }
        ft_memdel((void **)&a->rooms);
        a = ++(*ants);
        i++;
    }
    free(head);
}

static t_content *create_node(char *line)
{
    t_content *node;

    node = (t_content *)malloc(sizeof(t_content));
    if (node)
    {
        node->content = ft_strdup(line);
        node->next = NULL;
    }
    return (node);
}

static void add_tail(t_content **head, t_content *node)
{
    t_content *tmp;

    if (!(head) || (!(node)))
        return;
    tmp = *head;
    if (tmp)
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = node;
    }
}

t_content *init_content(t_content **file, char *line)
{
    t_content *node;
    t_content *head;

    head = *file;
    if (head)
    {
        node = create_node(line);
        add_tail(&head, node);
    }
    else
        head = create_node(line);
    return (head);
}

void print_file(t_content **head)
{
    t_content *node;
    t_content *tmp;

    node = *head;
    if (node)
    {
        while (node)
        {
            ft_putendl(node->content);
            tmp = node;
            node = node->next;
            ft_strdel(&tmp->content);
            ft_memdel((void **)&tmp);
        }
    }
}

void output_farm(t_farm *farm, t_content *file)
{
    int path_count;
    int keep;
    int cycles;
    t_ants *path;

    path = convert_path(farm);
    path_count = 0;
    while (farm->paths[path_count])
        path_count++;
    keep = 1;
    cycles = 1;
    print_file(&file);
    while (keep)
    {
        keep = 0;
        ft_putchar('\n');
        keep = print_cycle(cycles, farm->ants, path_count, path);
        cycles++;
    }
    free_ants(&path, farm->path_count);
}

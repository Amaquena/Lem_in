/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krissyleemc <krissyleemc@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 10:01:06 by kris              #+#    #+#             */
/*   Updated: 2020/05/31 10:53:15 by krissyleemc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
#define LEM_IN_H

#include "libft/libft.h"
#include <stdio.h>

/*
** DEFINE COLOR
*/

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

/*
** Room types
*/

#define REG 0
#define START 1
#define END 2

typedef struct s_farm t_farm;
typedef struct s_room t_room;
typedef struct s_link t_link;
typedef struct s_queue t_queue;
typedef struct s_ants t_ants;

struct s_queue
{
    char *name;
    t_queue *next;
    t_queue *prev;
};

struct s_link
{
    t_room *start;
    t_room *end;
    char *room1;
    char *room2;
    t_link *next;
};

struct s_room
{
    char *name;
    int type;
    int x;
    int y;
    int depth;
    int visited;
    int lock;
    t_room *next;
};

typedef struct s_path
{
    t_link *head;
    int length;
    struct s_path *next;
} t_path;

struct s_farm
{
    int ants;
    int nbr_rooms;
    int current_depth;
    int lock;
    int path_count;
    char **room;
    char **link;
    char *line;
    char *start;
    char *end;
    t_room *rooms;
    t_link *links;
    t_queue **paths;
};

struct s_ants
{
    int length;
    char **rooms;
};

typedef enum
{
    false,
    true
} t_bool;

/*
** Util funtions
*/

void error_msg(char *str, t_farm *farm);
void free_farm(t_farm *farm);
void free_room(char **room);
void free_link(char **link);
void output_farm(t_farm *farm);
t_room *find_room(char *name, t_room *room);

/*
** assist funtions
*/

void add_to_open_queue(char *room, t_queue **open, t_room *rooms);
void add_to_closed_queue(t_queue **open, t_queue **closed);
void add_to_path_queue(t_room *room, t_queue **path, t_farm *farm);
void set_depth(t_queue *open, t_room *rooms, int depth);
int adjust_depth(t_room *rooms);
void find_linking_room(t_link *links, t_queue *open, t_farm *farm);
int find_on_closed(t_queue *closed, char *name);
int check_if_end_found(t_queue *closed, t_room *rooms);

/*
** initialize funtions
*/

void verify_room(t_farm *farm, int type);
int verify_start_end(t_farm *farm);
void verify_links(t_farm *farm);
void solve(t_farm *farm);

#endif

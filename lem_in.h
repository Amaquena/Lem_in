#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft/libft.h"
#include "stdio.h"

/*
** DEFINE COLOR
*/

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

/*
** Room types
*/

# define REG 0
# define START 1
# define END 2

typedef struct s_farm t_farm;
typedef struct s_room t_room;

struct      s_room
{
    char    *name;
    int     type;
    int     x;
    int     y;
    t_room  *next;
};

struct      s_farm
{
    int     ants;
    int     nbr_rooms;
    t_room  *rooms;
};

/*
** print funtions
*/

void        error_msg();
void        print_lines(char *str);

/*
** intitilizse funtions
*/

void        verify_room(t_farm **farm, char *line, int type);
void        create_room(t_farm **farm, char **room, int type);

#endif
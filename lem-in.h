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
typedef struct s_link t_link;
typedef struct s_queue t_queue;

struct          s_queue
{
    char        *name;
    t_queue     *next;
};

struct          s_link
{
    char        *room1;
    char        *room2;
    int         g;
    t_link      *next;
};

struct      s_room
{
    char            *name;
    int             type;
    int             x;
    int             y;
    // int             weight;
    int             depth;
    int             visited;
    int             h;
    int             f;
    t_room          *next;
    // t_link          *links;
};

struct      s_farm
{
    int     ants;
    int     nbr_rooms;
    int     current_depth;
    char    **room;
    char    **link;
    char    *line;
    char    *start;
    char    *end;
    t_room  *rooms;
    t_link  *links;
};

/*
** Util funtions
*/

void        error_msg(char *str, t_farm *farm);
void        print_lines(t_farm *farm);
void        free_farm(t_farm *farm);
void        free_room(char **room);
void        free_link(char **link);

/*
** intitilize funtions
*/

void        verify_room(t_farm *farm, int type);
int         verify_start_end(t_farm *farm);
void        verify_links(t_farm *farm);
void        find_path(t_farm *farm);

#endif
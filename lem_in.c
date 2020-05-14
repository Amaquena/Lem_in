#include "lem_in.h"

static void intitailze_values(t_farm **farm)
{
    (*farm)->rooms->name = NULL;
    (*farm)->rooms->type = REG;
    (*farm)->rooms->x = 0;
    (*farm)->rooms->y = 0;
    (*farm)->rooms = NULL;
}

static void count_ants(t_farm **farm)
{
    char *line;

    line = NULL;
    if (get_next_line(0, &line) < 1)
        error_msg();
    if (!ft_strisdigit(line))
        error_msg();
    if (atoi(line) < 1)
        error_msg();
    (*farm)->ants = atoi(line);
    ft_putendl(line);
    free(line);
}

static void initialize_map(t_farm **farm)
{
    char *line;
    int type;

    line = NULL;
    while (get_next_line(0, &line))
    {
        if (ft_strequ(line, "##start"))
            type = START;
        if (ft_strequ(line, "##end"))
            type = END;
        if (line[0] == '#')
            continue;
        if (ft_strchr(line, ' '))
        {
            verify_room(farm, line, type);
            type = REG;
        }
    }    
}

int main(void)
{
    t_farm *farm;

    count_ants(&farm);
    intitailze_values(&farm);
    initialize_map(&farm);
    // printf("%s\n%d\n%d\n%d\n", farm.rooms->name, farm.rooms->type, farm.rooms->x, farm.rooms->y);
    while(farm->rooms)
    {
    printf("\n\nants:\t%d\nnbr_rooms:\t%d\nroom name:\t%s\ntype:\t%d\nx:\t%d\ny:\t%d\n",
    farm->ants, farm->nbr_rooms, farm->rooms->name, farm->rooms->type, farm->rooms->x, farm->rooms->y);
        farm->rooms = farm->rooms->next;
    }
    return (0);
}
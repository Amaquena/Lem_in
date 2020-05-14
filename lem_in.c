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
        if (ft_strchr(line, ' ') && line[0] != '#')
        {
            verify_room(farm, line, type);
            type = REG;
        }
        if (ft_strchr(line, '-') && line[0] != '#')
            verify_links(farm, line);
        ft_putendl(line);
    }
    if (!verify_start_end(farm))
        error_msg();
}

int main(void)
{
    t_farm *farm;

    count_ants(&farm);
    intitailze_values(&farm);
    initialize_map(&farm);
    return (0);
}
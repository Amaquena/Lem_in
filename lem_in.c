#include "lem_in.h"

static void intitailze_values(t_farm **farm)
{
    (*farm)->rooms = NULL;
    (*farm)->links = NULL;
    (*farm)->nbr_rooms = 0;
    (*farm)->ants = 0;
}

static void count_ants(t_farm **farm, char *line)
{
    if (ft_atoi(line) < 1)
        error_msg("Error: Number of ant must be absolute.");
    (*farm)->ants = ft_atoi(line);
}

static void initialize_map(t_farm **farm)
{
    char *line;
    int type;
    int ret;

    line = NULL;
    while ((ret = get_next_line(0, &line)) > 0)
    {
        if (ft_strisdigit(line))
            count_ants(farm, line);
        else if (ft_strequ(line, "##start"))
            type = START;
        else if (ft_strequ(line, "##end"))
            type = END;
        else if (ft_strchr(line, ' ') && line[0] != '#')
        {
            verify_room(farm, line, type);
            type = REG;
        }
        else if (ft_strchr(line, '-') && line[0] != '#')
            verify_links(farm, line);
        else if (line[0] != '#')
            error_msg("Error: Input not recognized.");
        ft_putendl(line);
    }
    if (ret < 0)
        error_msg("Error: Failed to read file.");
    if (!verify_start_end(farm))
        error_msg("Error: No start or end declared.");
    if ((*farm)->ants < 1)
        error_msg("Error: No ants on map.");
    free(line);
}

int main(void)
{
    t_farm *farm;

    intitailze_values(&farm);
    initialize_map(&farm);
    print_lines(farm);
    // find_paths(&farm);

    return (0);
}
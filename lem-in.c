#include "lem-in.h"

/*
    All the values of the struct of the main farm struct are initialized
    to zero or NUNLL.
*/
static void intitailze_values(t_farm *farm)
{
    farm->rooms = NULL;
    farm->paths = NULL;
    farm->line = NULL;
    farm->room = NULL;
    farm->link = NULL;
    farm->links = NULL;
    farm->lock = 1;
    farm->path_count = 0;
    farm->nbr_rooms = 0;
    farm->ants = 0;
    farm->current_depth = 0;
}

/*
    This function takes the number of ants and stores it as
    an integer in the struct farm.
*/

static void count_ants(t_farm *farm)
{
    if (ft_atoi(farm->line) < 1)
        error_msg("Error: Number of ant must be absolute.", farm);
    farm->ants = ft_atoi(farm->line);
}

/*
    This is the main initializion functions which uses gnl to read
    a file from STDIN and verify that the contents of the file is
    valid and calls the appropriate functions to store ants, rooms
    and links in the farm struct.
*/

static void initialize_map(t_farm *farm)
{
    int type;
    int ret;

    type = REG;
    ret = 0;
    while ((ret = get_next_line(0, &farm->line)) > 0)
    {
        if (ft_strisdigit(farm->line))
            count_ants(farm);
        else if (ft_strequ(farm->line, "##start"))
            type = START;
        else if (ft_strequ(farm->line, "##end"))
            type = END;
        else if (ft_strchr(farm->line, ' ') && farm->line[0] != '#')
        {
            verify_room(farm, type);
            type = REG;
        }
        else if (ft_strchr(farm->line, '-') && farm->line[0] != '#')
            verify_links(farm);
        else if (farm->line[0] != '#')
            error_msg("Error: Input not recognized.", farm);
        ft_putendl(farm->line);
        ft_strdel(&farm->line);
    }
    if (ret < 0)
        error_msg("Error: Failed to read file.", farm);
    if (!verify_start_end(farm))
        error_msg("Error: No start or end declared.", farm);
    if (farm->ants < 1)
        error_msg("Error: No ants on map.", farm);
}

int verify_paths(t_farm *farm)
{
    t_queue *path;
    t_room *room;
    int current_path;
    int path_count;
    int flag;

    path_count = 0;
    while (farm->paths[path_count])
        path_count++;

    current_path = 0;
    while (current_path < path_count)
    {
        path = farm->paths[current_path];
        flag = 0;
        while (path)
        {
            room = find_room(path->name, farm->rooms);
            if (room->type == START)
                flag++;
            if (room->type == END)
                flag++;
            path = path->next;
        }
        if (flag != 2)
            return (0);
        current_path++;
    }
    if (!path_count)
        return (0);
    return (1);
}

int main(void)
{
    t_farm farm;

    intitailze_values(&farm);
    initialize_map(&farm);
    solve(&farm);
    if (verify_paths(&farm))
        output_farm(&farm);
    else
        error_msg("Error: Start room doesn't link to End.", &farm);
    free_farm(&farm);
    return (0);
}

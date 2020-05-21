#include "lem-in.h"

/*
    All the values of the struct of the main farm struct are initialized
    to zero or NUNLL.
*/
static void intitailze_values(t_farm *farm)
{
    // printf("links: %ld\trooms: %ld\tfarm: %ld\n", sizeof(t_link), sizeof(t_room), sizeof(t_farm));
    // (*farm)->rooms->name = NULL;
    // (*farm)->rooms->type = 0;
    // (*farm)->rooms->x = 0;
    // (*farm)->rooms->y = 0;
    // (*farm)->rooms->h = 0;
    // (*farm)->rooms->f = 0;
    farm->rooms = NULL;
    farm->line = NULL;
    farm->room = NULL;
    farm->link = NULL;
    farm->links = NULL;
    // (*farm)->links->room1 = NULL;
    // (*farm)->links->room2 = NULL;
    // (*farm)->links->g = 0;
    farm->nbr_rooms = 0;
    farm->ants = 0;
    farm->current_depth = 0;
    // (*farm) = NULL;
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
    This is the main initializion funtions which uses gnl to read
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
        // ft_putendl(farm->line);
        ft_strdel(&farm->line);
    }
    if (ret < 0)
        error_msg("Error: Failed to read file.", farm);
    if (!verify_start_end(farm))
        error_msg("Error: No start or end declared.", farm);
    if (farm->ants < 1)
        error_msg("Error: No ants on map.", farm);
}

int main(void)
{
    t_farm farm;

    intitailze_values(&farm);
    initialize_map(&farm);
    // print_lines(&farm);
    find_path(&farm);

    free_farm(&farm);
    return (0);
}
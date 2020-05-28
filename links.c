#include "lem-in.h"

/*
    create_link() mallocs space in memory for a new link,
    this new link is given the inputs from farm->link and
    sets all the other values as well.

    farm->links holds a list of all the links that joins
    rooms together.
*/

static void create_link(t_farm *farm)
{
    t_link *head;
    t_link *new_link;

    head = farm->links;
    if (!(new_link = (t_link *)malloc(sizeof(t_link))))
        error_msg("Error: Failed malloc when creating link.", farm);
    new_link->room1 = ft_strdup(farm->link[0]);
    new_link->room2 = ft_strdup(farm->link[1]);
    new_link->next = NULL;

    if (head)
    {
        while (head->next)
            head = head->next;
        head->next = new_link;
    }
    else
        farm->links = new_link;
}

/*
    This funtion validates that the links given are valid
    names on the map.
*/

static int validate_links(t_farm *farm)
{
    t_room *head;

    head = farm->rooms;
    while (head && !ft_strequ(head->name, farm->link[0]))
        head = head->next;
    if (!head)
        return (0);

    head = farm->rooms;
    while (head && !ft_strequ(head->name, farm->link[1]))
        head = head->next;
    if (!head)
        return (0);
    return (1);
}

/*
    Verify functions takes the farm->line and splits it into farm->link
    farm->link is the check if it is a valid link that joins each room
    together before storing it.
    If all tests passes create_links() is then called.
*/

void verify_links(t_farm *farm)
{
    int counter;

    counter = 0;
    farm->link = ft_strsplit(farm->line, '-');
    while (farm->link[counter])
        counter++;
    if (counter != 2)
    {
        free_link(farm->link);
        error_msg("Error: Incorrect format for declaring link.", farm);
    }
    if (!validate_links(farm))
    {
        free_link(farm->link);
        error_msg("Error: Invalid link, doesn't match any room.", farm);
    }
    create_link(farm);
    free_link(farm->link);
}

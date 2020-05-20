#include "lem_in.h"

static int set_link_weight(t_farm *farm)
{
    int     g;
    int     room1;
    int     room2;
    t_room *head;

    head = farm->rooms;

    while (!ft_strequ(head->name, farm->link[0]))
        head = head->next;
    if(!head)
        error_msg("Error: No room matching 1st link.", farm);
    else
        room1 = head->h;

    head = farm->rooms;
    while (!ft_strequ(head->name, farm->link[1]))
        head = head->next;
    if(!head)
        error_msg("Error: No room matching 2nd link.", farm);
    else
        room2 = head->h;

    if (farm->nbr_rooms > (room1 * room2))
        g = (farm->nbr_rooms / (room1 * room2));
    else
        g = ((room1 * room2) / farm->nbr_rooms);
    return (g);
}

static void    create_links(t_farm *farm)
{
    t_link  *head;
    t_link  *new_link;

    head = farm->links;
    if (!(new_link = (t_link *)malloc(sizeof(t_link))))
        error_msg("Error: Failed malloc when creating link.", farm);
    new_link->room1 = ft_strdup(farm->link[0]);
    new_link->room2 = ft_strdup(farm->link[1]);
    new_link->g = set_link_weight(farm);
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

static int validate_links(t_farm *farm)
{
    t_room *head;

    head = farm->rooms;
    while (head && !ft_strequ(head->name, farm->link[0]))
        head = head->next;
    if (!head)
        return (0);

    head = farm->rooms;
    while (head && !ft_strequ(head->name,farm->link[1]))
        head = head->next;
    if (!head)
        return (0);
    return (1);
}

void verify_links(t_farm *farm)
{
    int counter;

    counter = 0;
    farm->link = ft_strsplit(farm->line, '-');
    while (farm->link[counter])
        counter++;
    if (counter != 2)
    {
        ft_strdel(&farm->line);
        free_link(farm->link);
        error_msg("Error: Incorrect format for declaring link.", farm);
    }
    if (!validate_links(farm))
    {
        ft_strdel(&farm->line);
        free_link(farm->link);
        error_msg("Error: Invalid link, doesn't match any room.", farm);
    }
    create_links(farm);
    free_link(farm->link);
}
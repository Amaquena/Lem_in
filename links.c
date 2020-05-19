#include "lem_in.h"

static int set_link_weight(t_farm **farm, char **link)
{
    int     g;
    int     room1;
    int     room2;
    t_room *head;

    head = (*farm)->rooms;

    while (!ft_strequ(head->name, link[0]))
        head = head->next;
    if(!head)
        error_msg("Error: No room matching link.");
    room1 = head->h;

    head = (*farm)->rooms;
    while (!ft_strequ(head->name, link[1]))
        head = head->next;
    if(!head)
        error_msg("Error: No room matching link.");
    room2 = head->h;

    if ((*farm)->nbr_rooms > (room1 * room2))
        g = ((*farm)->nbr_rooms / (room1 * room2));
    else
        g = ((room1 * room2) / (*farm)->nbr_rooms);
    return (g);
}

static void    create_links(t_farm **farm, char **link)
{
    t_link  *head;
    t_link  *new_link;

    head = (*farm)->links;
    if (!(new_link = (t_link *)malloc(sizeof(t_link))))
        error_msg("Error: Failed malloc when creating link.");
    new_link->room1 = link[0];
    new_link->room2 = link[1];
    new_link->g = set_link_weight(farm, link);
    new_link->next = NULL;

    if (head)
    {
        while (head->next)
            head = head->next;
        head->next = new_link;
    }
    else
        (*farm)->links = new_link;
}

static int validate_links(t_farm **farm, char **link)
{
    t_room *head;

    head = (*farm)->rooms;
    while (head && !ft_strequ(head->name, link[0]))
        head = head->next;
    if (!head)
        return (0);

    head = (*farm)->rooms;
    while (head && !ft_strequ(head->name, link[1]))
        head = head->next;
    if (!head)
        return (0);
    return (1);
}

void verify_links(t_farm **farm, char *line)
{
    char **link;
    int counter;

    counter = 0;
    link = ft_strsplit(line, '-');
    while (link[counter])
        counter++;
    if (counter != 2)
        error_msg("Error: Incorrect format for declaring link.");
    if (!validate_links(farm, link))
        error_msg("Error: Invalid link, doesn't match any room.");
    create_links(farm, link);
}
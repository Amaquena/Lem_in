#include "lem-in.h"

/*
    Sets weights for each of the links for the rooms
    to be used in path finding algorithm.
*/

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

// static t_room	*find_room(char *name, t_room *room)
// {
// 	t_room	*tmp;

// 	tmp = room;
// 	while (tmp)
// 	{
// 		if (!ft_strcmp(tmp->name, name))
// 			return (tmp);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

/*
    The commented funtion below was intended to add a list of all the rooms
    in the link member of the struct as a list, that way each room could
    have a list of all the rooms its connected too. Function works,
    but was unable to free successfully .


static void add_links(t_farm *farm, char *link1, char *link2)
{
    t_room *room1;
    t_room *room2;
    t_link *new_link;
    t_link *room2_link;

    room1 = find_room(link1, farm->rooms);
    room2 = find_room(link2, farm->rooms);

    new_link = (t_link *)malloc(sizeof(t_link));
    new_link->room = room1;
    new_link->next = NULL;

    if (room2->links)
    {
        room2_link = room2->links;
		while (room2_link->next)
			room2_link = room2_link->next;
		room2_link->next = new_link;
    }
    else
    {
        room2->links = new_link;
    }
}

*/

/*
    create_link() mallocs space in memory for a new link,
    this new link is given the inputs from farm->link and
    sets all the other values as well.

    farm->links holds a list of all the links that joins
    rooms together.
*/

static void    create_link(t_farm *farm)
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
    while (head && !ft_strequ(head->name,farm->link[1]))
        head = head->next;
    if (!head)
        return (0);
    return (1);
}

/*
    Verify funtions takes the farm->line and splits it into farm->link
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

/*
    Used instead of the create_links funtion, but cant free without segfault.
  
    add_links(farm, farm->link[0], farm->link[1]);
    add_links(farm, farm->link[1], farm->link[0]);
*/
}
#include "lem-in.h"

static t_room	*find_room(char *name, t_room *room)
{
	t_room	*tmp;

	tmp = room;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void add_to_open_queue(char *room, t_queue **open, t_room *rooms)
{
    t_queue *new_open;
    t_room *tmp_room;

    tmp_room = find_room(room, rooms);
    if (tmp_room->visited == 0)
    {
        tmp_room->visited = 1;
        new_open = (t_queue *)malloc(sizeof(t_queue));
        new_open->name = ft_strdup(room);
        new_open->next = NULL;

        if ((*open))
        {
            while ((*open)->next)
                (*open) = (*open)->next;
            (*open)->next = new_open;
        }
        else
            (*open) = new_open;
    }
}

static void	find_linking_room(t_link *links, t_queue *open, t_room *rooms)
{
    t_queue *tmp_open;

    tmp_open = open;
	while (links)
	{
		if (ft_strequ(links->room1, open->name))
            add_to_open_queue(links->room2, &open, rooms);
		else if (ft_strequ(links->room2, open->name))
            add_to_open_queue(links->room1, &open, rooms);
        open = tmp_open;
		links = links->next;
	}
}

static void set_depth(t_queue *open, t_room *rooms, int depth)
{
    t_room *tmp_room;

    while (open)
    {
        tmp_room = find_room(open->name, rooms);
        if (tmp_room->type == REG && tmp_room->depth == 0)
        {
            tmp_room->depth = depth;
        }
        open = open->next;
    }
}

static void add_to_closed_queue(t_queue **open, t_queue **closed)
{
    t_queue *tmp;
    t_queue *curr_closed;

    if((*open))
    {
        tmp = (*open);
        (*open) = (*open)->next;
        // tmp->next = (*closed);
        // (*closed) = tmp;
    }

    tmp->next = NULL;
    if ((*closed) == NULL)
        (*closed) = tmp;
    else
    {
        curr_closed = (*closed);
        while (curr_closed ->next)
            curr_closed = curr_closed->next;
        curr_closed->next = tmp;
    }
}

void find_path(t_farm *farm)
{
    t_queue *open;
    t_queue *closed;
    t_room *rooms;
    // t_queue *head_open;

    open = NULL;
    closed = NULL;
    rooms = farm->rooms;
    
    add_to_open_queue(farm->start, &open, farm->rooms);
    // head_open = open;
    // while (farm->nbr_rooms-- != 0)
    while (open)
    {
        find_linking_room(farm->links, open, farm->rooms);
        set_depth(open, farm->rooms, ++farm->current_depth);
        add_to_closed_queue(&open, &closed);
        // open = open->next;
    }

    while (open)
    {
        printf("open->name: %s\n", open->name);
        open = open->next;
    }
    ft_putchar('\n');
    while (closed)
    {
        printf("closed->name: %s\n", closed->name);
        closed = closed->next;
    }
    ft_putchar('\n');
    while (rooms)
    {
        printf("room: %s;\troom->depth: %d\tvisited: %d\n", rooms->name, rooms->depth, rooms->visited);
        rooms = rooms->next;
    }
    exit(1);


    find_linking_room(farm->links, open, farm->rooms);
    set_depth(open, farm->rooms, ++farm->current_depth);
    add_to_closed_queue(&open, &closed);
}

// static void set_start_end_weight(t_room *rooms, int nbr_rooms)
// {
//     while (rooms)
//     {
//         if (rooms->type == END)
//             rooms->weight = nbr_rooms;
//         if (rooms->type == START)
//             rooms->weight = 0;
//         rooms = rooms->next;
//     }
// }

// void set_room_weights(t_farm *farm)
// {
//     t_room *rooms;
//     t_link *links;
//     t_room *tmp_link_room1;
//     t_room *tmp_link_room2;
//     int set_depth;

//     rooms = farm->room;
//     links = farm->links;

//     set_depth = 1;
//     set_start_end_weight(farm->rooms, farm->nbr_rooms);

//     t_room *start = find_room(farm->start, farm->room);
//     while (links)
//     {
//         tmp_link_room1 = find_room(links->room1, farm->rooms);
//         tmp_link_room2 = find_room(links->room2, farm->rooms);
//         if (tmp_link_room1->type == START)
//             tmp_link_room2->depth = set_depth;
//         if (tmp_link_room2->type == START)
//             tmp_link_room1->depth = set_depth;
//         links = links->next;
//     }

// }
#include "lem-in.h"

void output(t_queue *open, t_queue *closed, t_queue **path, t_room *rooms);

static t_room *find_room(char *name, t_room *room)
{
    t_room *tmp;

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
    t_queue *last;
    t_room *tmp_room;

    tmp_room = find_room(room, rooms);
    if (tmp_room->visited == 0)
    {
        tmp_room->visited = 1;
        new_open = (t_queue *)ft_memalloc(sizeof(t_queue));
        new_open->name = ft_strdup(room);
        new_open->next = NULL;

        last = (*open);
        if ((*open) == NULL)
        {
            new_open->prev = NULL;
            (*open) = new_open;
            return;
        }
        while (last->next)
            last = last->next;
        last->next = new_open;
        new_open->prev = last;
    }
}

static void find_linking_room(t_link *links, t_queue *open, t_farm *farm)
{
    t_queue *tmp_open;
    int flag = 0;

    tmp_open = open;
    while (links)
    {
        if (ft_strequ(links->room1, open->name))
        {
            flag = 1;
            add_to_open_queue(links->room2, &open, farm->rooms);
        }
        else if (ft_strequ(links->room2, open->name))
        {
            flag = 1;
            add_to_open_queue(links->room1, &open, farm->rooms);
        }
        open = tmp_open;
        links = links->next;
    }
    if (!flag)
        error_msg("Error: Start or end Dont link to any rooms", farm);
}

static void set_depth(t_queue *open, t_room *rooms, int depth)
{
    t_room *tmp_room;

    while (open)
    {
        tmp_room = find_room(open->name, rooms);
        if (tmp_room->type != START && tmp_room->depth == 0)
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

    if ((*open) && (*open)->next)
    {
        tmp = (*open);
        (*open)->next->prev = NULL;
        (*open) = (*open)->next;
    }
    else if ((*open) && !(*open)->next)
    {
        tmp = (*open);
        tmp->next = NULL;
        (*open) = NULL;
    }

    tmp->next = NULL;
    if ((*closed) == NULL)
    {
        tmp->prev = NULL;
        (*closed) = tmp;
    }
    else
    {
        curr_closed = (*closed);
        while (curr_closed->next)
            curr_closed = curr_closed->next;
        curr_closed->next = tmp;
        tmp->prev = curr_closed;
    }
}

static int adjust_depth(t_room *rooms)
{
    while (rooms)
    {
        rooms->depth -= 1;
        if (rooms->type == END && rooms->depth < 0)
            return (0);
        rooms = rooms->next;
    }
    return (1);
}

static int check_if_end_found(t_queue *closed, t_room *rooms)
{
    t_room *tmp_room;

    while (closed->next)
        closed = closed->next;
    tmp_room = find_room(closed->name, rooms);
    if (tmp_room->type == END)
        return (1);
    return (0);
}

static void add_to_path_queue(t_room *room, t_queue **path, t_farm *farm)
{
    t_queue *new_path;
    t_queue *tmp_path;
    int flag;

    room->lock = farm->lock;
    tmp_path = path[0];
    flag = 0;
    while (tmp_path)
    {
        if (ft_strequ(room->name, tmp_path->name))
        {
            flag = 1;
            break;
        }
        tmp_path = tmp_path->next;
    }
    if (flag == 0)
    {
        new_path = (t_queue *)ft_memalloc(sizeof(t_queue));
        new_path->name = ft_strdup(room->name);
        new_path->next = path[0];
        new_path->prev = NULL;

        if (path[0] != NULL)
            path[0]->prev = new_path;

        path[0] = new_path;
    }
}

static int find_on_closed(t_queue *closed, char *name)
{
    while (closed)
    {
        if (ft_strequ(closed->name, name))
            return (1);
        closed = closed->next;
    }
    return (0);
}

static void find_linking_room2(char *name, t_farm *farm, int depth, t_queue **path, t_queue *closed)
{
    t_room *tmp_room;
    t_link *links;

    links = farm->links;
    while (links)
    {
        if (ft_strequ(links->room1, name))
        {
            tmp_room = find_room(links->room2, farm->rooms);
            if (tmp_room->depth == (depth - 1) && find_on_closed(closed, tmp_room->name))
            {
                add_to_path_queue(tmp_room, &path[0], farm);
                break;
            }
        }
        else if (ft_strequ(links->room2, name))
        {
            tmp_room = find_room(links->room1, farm->rooms);
            if (tmp_room->depth == (depth - 1) && find_on_closed(closed, tmp_room->name))
            {
                add_to_path_queue(tmp_room, &path[0], farm);
                break;
            }
        }
        links = links->next;
    }
}

static void find_path(t_farm *farm, t_queue **path, t_queue *closed)
{
    t_queue *tmp_closed;
    t_room *tmp_room;

    tmp_closed = closed;
    while (tmp_closed->next)
        tmp_closed = tmp_closed->next;

    tmp_room = find_room(tmp_closed->name, farm->rooms);
    add_to_path_queue(tmp_room, &path[0], farm);
    while (tmp_closed)
    {
        tmp_room = find_room(path[0]->name, farm->rooms);
        find_linking_room2(path[0]->name, farm, tmp_room->depth, &path[0], closed);
        tmp_closed = tmp_closed->prev;
    }
}

static void reset_rooms(t_farm *farm, t_queue **open, t_queue **closed)
{
    t_room *rooms;
    t_queue *tmp;
    t_queue *pop;

    rooms = farm->rooms;
    while (rooms)
    {
        if (rooms->type == START || rooms->type == END)
            rooms->lock = 0;
        if (rooms->lock == 0)
            rooms->depth = 0;
        rooms->visited = 0;
        rooms = rooms->next;
    }
    if ((*open))
    {
        tmp = (*open);
        while (tmp)
        {
            pop = tmp;
            tmp = tmp->next;
            ft_strdel(&pop->name);
            ft_memdel((void **)&pop);
        }
    }
    if ((*closed))
    {
        tmp = (*closed);
        while (tmp)
        {
            pop = tmp;
            tmp = tmp->next;
            ft_strdel(&pop->name);
            ft_memdel((void **)&pop);
        }
    }
}

static int count_paths(t_link *links, char *start)
{
    int count;

    count = 0;
    while (links)
    {
        if (ft_strequ(links->room1, start))
            count++;
        else if (ft_strequ(links->room2, start))
            count++;
        links = links->next;
    }
    return (count);
}

void solve(t_farm *farm)
{
    t_queue *open;
    t_queue *closed;
    t_queue **path;
    t_room *tmp_room;
    int path_count;

    open = NULL;
    closed = NULL;
    path_count = count_paths(farm->links, farm->start);
    farm->paths = (t_queue **)ft_memalloc(sizeof(t_queue *) * path_count + 1);
    path = farm->paths;

    add_to_open_queue(farm->start, &open, farm->rooms);
    while (open)
    {
        find_linking_room(farm->links, open, farm);
        tmp_room = find_room(open->name, farm->rooms);
        set_depth(open, farm->rooms, ++tmp_room->depth);
        add_to_closed_queue(&open, &closed);
        if (check_if_end_found(closed, farm->rooms))
            break;
    }
    if (!adjust_depth(farm->rooms))
        error_msg("Error: Start room doesn't link to End.", farm);
    find_path(farm, &path[0], closed);
    reset_rooms(farm, &open, &closed);
    // output(open, closed, path, farm->rooms);
}

// void output(t_queue *open, t_queue *closed, t_queue **path, t_room *rooms)
// {
//     int i = 0;
//     while (open)
//     {
//         printf("open->name: %s\n", open->name);
//         open = open->next;
//     }
//     ft_putchar('\n');
//     while (closed)
//     {
//         printf("closed->name: %s\n", closed->name);
//         closed = closed->next;
//     }
//     ft_putchar('\n');
//     while (path[i])
//     {
//         printf("path->name: %s\n", path[i]->name);
//         path[i] = path[i]->next;
//     }
//     ft_putchar('\n');
//     while (rooms)
//     {
//         printf("room: %s;\tdepth: %d\tvisited: %d\tlock: %d\n", rooms->name, rooms->depth, rooms->visited, rooms->lock);
//         rooms = rooms->next;
//     }
// }

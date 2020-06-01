/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krissyleemc <krissyleemc@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:00:44 by amaquena          #+#    #+#             */
/*   Updated: 2020/06/01 16:38:44 by krissyleemc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char *ft_strsubchr(char **line, char *temp, char c)
{
	size_t count;
	char *str;

	count = 0;
	while (temp[count] != '\0')
	{
		if (temp[count] == c)
			break;
		count++;
	}
	if (temp[count] == '\n')
	{
		*line = ft_strsub(temp, 0, count);
		str = ft_strdup(&temp[count + 1]);
	}
	if (temp[count] == '\0')
	{
		*line = ft_strsub(temp, 0, count);
		str = ft_strnew(0);
	}
	return (str);
}

static int readfile(int fd, t_list **curr_list)
{
	int ret;
	char *temp;
	char buff[BUFF_SIZE + 1];

	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		temp = ft_strjoin((*curr_list)->content, buff);
		free((*curr_list)->content);
		(*curr_list)->content = temp;
		if (ft_strchr(buff, '\n'))
			break;
	}
	return (ret);
}

static t_list *ft_getfile(t_list **file, int fd)
{
	t_list *temp;

	temp = *file;
	while (temp)
	{
		if ((int)temp->content_size == fd)
			return (temp);
		temp = temp->next;
	}
	temp = ft_lstnew("\0", fd);
	ft_lstadd(file, temp);
	temp = NULL;
	return (*file);
}

int get_next_line(const int fd, char **line)
{
	int ret;
	char *temp;
	char buff[BUFF_SIZE + 1];
	static t_list *fd_list;
	t_list *curr_file;

	if (read(fd, buff, 0) < 0 || fd < 0 || fd <= -2147483648 ||
		fd >= 2147483647 || !line || BUFF_SIZE <= 0)
		return (-1);
	curr_file = ft_getfile(&fd_list, fd);
	if ((ret = readfile(fd, &curr_file)) < 0)
		return (-1);
	if (!ret && !(ft_strlen(curr_file->content)))
	{
		return (0);
	}
	temp = ft_strsubchr(line, (char *)curr_file->content, '\n');
	free(curr_file->content);
	curr_file->content = temp;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:27:41 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/15 16:39:59 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*find_node(t_node **head, int fd)
{
	t_node	*temp;
	t_node	*new;

	temp = *head;
	while (temp != NULL)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	new = malloc(sizeof(t_node));
	if (!new)
		return (0);
	new->fd = fd;
	new->save[0] = 0;
	new->next = *head;
	*head = new;
	return (new);
}

char	*clear(t_node **lst, t_node *node, int fd, char *line)
{
	t_node	*temp;

	temp = *lst;
	if (!(temp->fd == fd))
	{
		while (temp->next != 0)
		{
			if (temp->next->fd == fd)
			{
				temp->next = temp->next->next;
				break ;
			}
			temp = temp->next;
		}
	}
	else
		*lst = (*lst)->next;
	free(node);
	node = 0;
	return (line);
}

int	read_line(t_node **node, int fd)
{
	int	i;

	i = 0;
	if (read(fd, 0, 0) == -1)
		return (1);
	if ((*node)->save[0] == 0)
	{
		(*node)->size = read(fd, (*node)->buf, BUFFER_SIZE);
		(*node)->buf[(*node)->size] = 0;
		if ((*node)->size <= 0)
			return (1);
	}
	else
	{
		while ((*node)->save[i])
		{
			(*node)->buf[i] = (*node)->save[i];
			i++;
		}
		(*node)->buf[i] = '\0';
	}
	(*node)->buf[BUFFER_SIZE] = '\0';
	(*node)->save[0] = 0;
	return (0);
}

char	*make_line(t_node *node, char *line, int size)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(line);
	if (!line)
		len = 0;
	str = malloc(size + len + 1);
	if (!str)
	{
		free(line);
		return (0);
	}
	while (i < size + len)
	{
		if (i < len)
			str[i] = line[i];
		else
			str[i] = node->buf[i - len];
		i++;
	}
	str[i] = '\0';
	free(line);
	return (str);
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	t_node			*node;
	char			*line;

	line = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	node = find_node(&head, fd);
	if (!node)
		return (0);
	while (1)
	{
		if (read_line(&node, fd))
			return (clear(&head, node, fd, line));
		line = make_line(node, line, find_line(node));
		if (line == 0)
			return (clear(&head, node, fd, line));
		make_save(node, find_line(node));
		node->buf[0] = 0;
		if (ft_strchr(line, '\n') != 0 || node->size < BUFFER_SIZE)
			break ;
	}
	if (node->save[0] == 0)
		clear(&head, node, fd, line);
	return (line);
}

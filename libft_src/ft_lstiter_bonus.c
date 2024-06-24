/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bosnus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:37:30 by jimchoi           #+#    #+#             */
/*   Updated: 2023/10/23 13:15:59 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*iter;

	if (lst == 0 || f == 0)
		return ;
	iter = lst;
	while (iter != 0)
	{
		f(iter->content);
		iter = iter->next;
	}
}

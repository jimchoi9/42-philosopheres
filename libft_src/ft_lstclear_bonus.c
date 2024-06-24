/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:27:18 by jimchoi           #+#    #+#             */
/*   Updated: 2023/10/23 16:51:25 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*clear;

	if (lst == 0)
		return ;
	clear = *lst;
	while (*lst != 0)
	{
		clear = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = clear;
	}
}

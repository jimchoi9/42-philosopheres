/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:38:54 by jimchoi           #+#    #+#             */
/*   Updated: 2023/10/23 15:51:33 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (lst == 0 || new == 0)
		return ;
	if (*lst != 0)
	{
		ptr = ft_lstlast(*lst);
		if (ptr == 0)
			return ;
		ptr->next = new;
	}
	else
		*lst = new;
}

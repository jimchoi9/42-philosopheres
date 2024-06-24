/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:18:19 by jimchoi           #+#    #+#             */
/*   Updated: 2023/10/23 15:26:14 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*nextlst;
	void	*con;

	if (lst == 0 || f == 0)
		return (0);
	newlst = 0;
	while (lst != 0)
	{
		con = f(lst->content);
		nextlst = ft_lstnew(con);
		if (nextlst == 0)
		{
			ft_lstclear(&newlst, del);
			free(con);
			return (0);
		}
		ft_lstadd_back(&newlst, nextlst);
		lst = lst->next;
	}
	return (newlst);
}

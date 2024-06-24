/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:53:02 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/15 16:14:02 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t			len;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return ;
	len = ft_strlen(s);
	if (!len)
		len = 1;
	while (i < len)
	{
		f(i, s + i);
		i++;
	}
	return ;
}

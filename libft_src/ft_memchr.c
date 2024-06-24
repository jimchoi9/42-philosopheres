/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:19:39 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/15 16:11:51 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s1;

	if (s == NULL)
		return (0);
	s1 = (unsigned char *)s;
	while (n--)
	{
		if (*s1 == (unsigned char)c)
			return ((void *) s1);
		s1++;
	}
	return (0);
}

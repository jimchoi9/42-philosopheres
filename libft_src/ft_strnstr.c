/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:52:53 by jimchoi           #+#    #+#             */
/*   Updated: 2023/10/24 11:28:48 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_word(const char *s1, const char *s2, size_t len)
{
	while (*s2)
	{
		if (*s1 != *s2 || len < 1)
			return (1);
		s1++;
		s2++;
		len--;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (*needle == '\0')
		return ((char *) haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == *needle)
		{
			if (find_word(haystack + i, needle, len - i) == 0)
				return ((char *) haystack + i);
		}
		i ++;
	}
	return (0);
}

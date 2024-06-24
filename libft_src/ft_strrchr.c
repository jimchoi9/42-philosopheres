/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:03:34 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/15 16:17:49 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;

	result = (char *)s;
	if (s == NULL)
		return (0);
	while (*s)
		s++;
	while (s != result && *s != (char)c)
		s--;
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:52:35 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/21 13:13:34 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (n--)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		if (*str1 == '\0')
			break ;
		str1++;
		str2++;
	}
	return (0);
}

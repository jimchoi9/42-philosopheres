/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:52:52 by jimchoi           #+#    #+#             */
/*   Updated: 2023/10/23 16:41:25 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		start;
	int		end;

	start = -1;
	end = ft_strlen(s1);
	while (s1[++start] != '\0')
	{
		if (!ft_strchr(set, s1[start]) || *set == 0)
			break ;
	}
	while (end--)
	{
		if (!ft_strchr(set, s1[end]) || *set == 0)
			break ;
	}
	if (end == -1)
	{
		result = ft_calloc(1, 1);
		return (result);
	}
	result = ft_substr(s1, start, end - start + 1);
	if (result == 0)
		return (0);
	return (result);
}

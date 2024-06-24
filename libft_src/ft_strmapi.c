/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:52:55 by jimchoi           #+#    #+#             */
/*   Updated: 2023/10/20 21:55:45 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	char			*result;
	unsigned int	i;

	i = 0;
	len = ft_strlen(s);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (0);
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	return (result);
}

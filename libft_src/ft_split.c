/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:53:06 by jimchoi           #+#    #+#             */
/*   Updated: 2023/10/23 16:38:34 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**clean(char **result, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		free(result[i]);
		result[i] = 0;
		i++;
	}
	free (result);
	result = 0;
	return (0);
}

static int	count(char const *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	if (str[i] == sep)
		count = 0;
	while (str[i])
	{
		if (str[i] == sep && str[i + 1] != sep)
			if (str[i + 1] != 0)
				count++;
		i++;
	}
	return (count);
}

static char	*put_words(char sep, char const *str)
{
	size_t	len;
	size_t	i;
	char	*str2;

	len = 0;
	i = 0;
	while (str[len] && str[len] != sep)
		++len;
	str2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!str2)
		return (0);
	while (i < len)
	{
		str2[i] = str[i];
		++i;
	}
	str2[i] = '\0';
	return (str2);
}

static char	**make_result(char **result, char *s, char c)
{
	int	i;
	int	idx;

	i = 0;
	idx = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			result[idx] = put_words(c, s + i);
			if (result[idx] == 0)
				return (clean(result, idx));
			++idx;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		size;

	size = count(s, c);
	if (s[0] == 0)
		size = 0;
	result = (char **)ft_calloc(sizeof(char *), (size + 1));
	if (result == 0)
		return (clean(result, -1));
	result = make_result(result, (char *)s, c);
	if (result == 0)
		return (0);
	return (result);
}

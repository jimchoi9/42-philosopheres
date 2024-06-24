/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:15:33 by jimchoi           #+#    #+#             */
/*   Updated: 2023/10/24 11:53:03 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*make_str(char *str, int len, int n, int sign)
{
	int	num;
	int	i;

	num = 1;
	i = 0;
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		num = n % 10;
		str[len - 1 - i] = '0' + num;
		n = n / 10;
		i++;
	}
	if (sign)
		str[0] = '-';
	str[len] = 0;
	return (str);
}

static int	count_digits(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		sign;

	sign = 0;
	if (n == -2147483648)
	{
		str = ft_strdup("-2147483648");
		return (str);
	}
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	len = count_digits(n);
	str = malloc((len + sign + 1) * sizeof(char));
	if (str == 0)
		return (0);
	str = make_str(str, len + sign, n, sign);
	return (str);
}

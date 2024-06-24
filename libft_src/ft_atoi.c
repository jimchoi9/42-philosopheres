/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:53:10 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/21 16:06:19 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	long long	neg;
	long long	num;
	int			cnt;

	cnt = 0;
	num = 0;
	neg = 1;
	while (*str == '\n' || *str == '\t' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		cnt++;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
	}
	if (cnt > 1)
		num = 0;
	return (num * neg);
}

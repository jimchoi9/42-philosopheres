/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:53:13 by jimchoi           #+#    #+#             */
/*   Updated: 2023/10/23 16:38:17 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_nbr(int fd, int n)
{
	char	num;

	if (n < 0)
	{
		n *= -1;
		write (fd, "-", 1);
	}
	if (n < 10)
	{
		num = n + '0';
		write (fd, &num, 1);
		return ;
	}
	print_nbr(fd, n / 10);
	print_nbr(fd, n % 10);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write (fd, "-2147483648", 11);
	else if (n == 0)
		write (fd, "0", 1);
	else
		print_nbr(fd, n);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_libft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:28:42 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/15 15:30:21 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd_p(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstr_fd_p(char *s, int fd)
{
	size_t	len;

	if (!s)
		return (ft_putstr_fd_p("(null)", fd));
	len = ft_strlen(s);
	if (write(fd, s, len) == -1)
		return (-1);
	return (len);
}

int	ft_putnbr_fd_p(long n, int fd)
{
	int	num1;
	int	num2;

	if (n == -2147483648)
		return (ft_putstr_fd_p("-2147483648", fd));
	else if (n < 0)
	{
		num1 = ft_putchar_fd_p('-', fd);
		if (num1 == -1)
			return (-1);
		n *= -1;
		num2 = ft_putnbr_fd_p(n, fd);
	}
	else if (n > 9)
	{
		num1 = ft_putnbr_fd_p(n / 10, fd);
		if (num1 == -1)
			return (-1);
		num2 = ft_putnbr_fd_p(n % 10, fd);
	}
	else
		return (ft_putchar_fd_p(n + '0', fd));
	if (num2 == -1)
		return (-1);
	return (num1 + num2);
}

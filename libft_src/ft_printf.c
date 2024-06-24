/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:21:41 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/15 15:30:53 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_logic(const char *format, va_list ap)
{
	if (*format == 'c')
		return (ft_putchar_fd_p(va_arg(ap, int), 1));
	else if (*format == 's')
		return (ft_putstr_fd_p(va_arg(ap, char *), 1));
	else if (*format == 'p')
		return (ft_putstr_fd_hex(va_arg(ap, void *), 1));
	else if (*format == 'd')
		return (ft_putnbr_fd_p(va_arg(ap, int), 1));
	else if (*format == 'i')
		return (ft_putnbr_fd_p(va_arg(ap, int), 1));
	else if (*format == 'u')
		return (ft_putnbr_fd_u (va_arg(ap, int), 1));
	else if (*format == 'x')
		return (ft_putnbr_fd_hex(va_arg(ap, int), 1, 0));
	else if (*format == 'X')
		return (ft_putnbr_fd_hex(va_arg(ap, int), 1, 1));
	else if (*format == '%')
		return (ft_putchar_fd_p('%', 1));
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	num;
	int		res;

	num = 0;
	va_start (ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			res = ft_printf_logic(++format, ap);
			if (res == -1)
				return (-1);
			num += res;
		}
		else
		{
			if (write(1, format, 1) == -1)
				return (-1);
			num++;
		}
		format++;
	}
	va_end(ap);
	return (num);
}

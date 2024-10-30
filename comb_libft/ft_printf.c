/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:35:16 by danevans          #+#    #+#             */
/*   Updated: 2023/06/29 19:11:13 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_types(va_list args, char type)
{
	if (type == 'c')
		return (ft_char_fmt(va_arg(args, int)));
	else if (type == 's')
		return (ft_str_fmt(va_arg(args, char *)));
	else if (type == 'p')
		return (ft_pointer_fmt(va_arg(args, void *)));
	else if (type == 'x')
		return (ft_low_hexa_fmt(va_arg(args, unsigned int)));
	else if (type == 'X')
		return (ft_up_hexa_fmt(va_arg(args, unsigned int)));
	else if (type == 'd' || type == 'i')
		return (ft_decimal_fmt(va_arg(args, int)));
	else if (type == 'u')
		return (ft_un_decimal_fmt(va_arg(args, unsigned int)));
	else if (type == '%')
		return (ft_percent_fmt());
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	args;

	if (!format)
		return (0);
	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			len = len + ft_types(args, format[i]);
		}
		else
			len = len + write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}

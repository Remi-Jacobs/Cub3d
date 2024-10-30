/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_fmt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:55:13 by danevans          #+#    #+#             */
/*   Updated: 2023/06/29 19:05:21 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_char_fmt(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_str_fmt(char *str)
{
	if (!str)
		str = "(null)";
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_percent_fmt(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimals_fmt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:14:48 by danevans          #+#    #+#             */
/*   Updated: 2023/07/27 22:45:15 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	is_negative(long int value)
{
	char	*str;
	int		len;

	if (value < 0)
	{
		str = ft_itoa_base(value, "0123456789");
		ft_str_fmt(str);
		len = ft_strlen(str);
		free (str);
		return (len);
	}
	return (0);
}

int	ft_decimal_fmt(int value)
{
	int			len;
	char		*str;
	char		*min;
	long int	values;

	values = (long int) value;
	if (values == INT_MIN)
	{
		min = "-2147483648";
		ft_str_fmt(min);
		return (ft_strlen(min));
	}
	else if (values < 0)
	{
		len = is_negative(values);
		return (len);
	}
	else
	{
		str = ft_itoa_base(values, "0123456789");
		ft_str_fmt(str);
		len = ft_strlen(str);
		free (str);
		return (len);
	}
}

int	ft_un_decimal_fmt(unsigned int value)
{
	char	*str;
	int		len;

	str = ft_itoa_base(value, "0123456789");
	ft_str_fmt(str);
	len = ft_strlen(str);
	free (str);
	return (len);
}

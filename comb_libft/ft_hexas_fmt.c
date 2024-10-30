/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexas_fmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:47:28 by danevans          #+#    #+#             */
/*   Updated: 2023/06/26 08:14:22 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_low_hexa_fmt(unsigned int value)
{
	char	*str;
	int		len;

	str = ft_itoa_base(value, "0123456789abcdef");
	ft_str_fmt(str);
	len = ft_strlen(str);
	free (str);
	return (len);
}

int	ft_up_hexa_fmt(unsigned int value)
{
	char	*str;
	int		len;

	str = ft_itoa_base(value, "0123456789ABCDEF");
	ft_str_fmt(str);
	len = ft_strlen(str);
	free (str);
	return (len);
}

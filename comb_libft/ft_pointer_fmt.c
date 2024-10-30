/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_fmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:14:58 by danevans          #+#    #+#             */
/*   Updated: 2023/07/29 13:55:34 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	cal_len(unsigned long value, char *str)
{
	int	len;
	int	base;

	base = ft_strlen(str);
	len = 0;
	if (value == 0)
	{
		len = 1;
		return (len);
	}
	while (value)
	{
		value = value / base;
		len++;
	}
	return (len);
}

static char	*ft_itoa_based(unsigned long value, char *str)
{
	char	*result;
	int		len;
	int		base;

	base = ft_strlen(str);
	len = cal_len(value, str);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (result == NULL)
		return (NULL);
	result[len] = '\0';
	if (value == 0)
	{
		result[0] = '0';
		return (result);
	}
	len = len - 1;
	while (value)
	{
		result[len--] = str[value % base];
		value = value / base;
	}
	return (result);
}

int	ft_pointer_fmt(void *ptr)
{
	int					len;
	unsigned long		address;
	char				*str;
	char				*temp;

	if (ptr == NULL)
	{
		ft_str_fmt("0x0");
		return (3);
	}
	address = (unsigned long)ptr;
	str = ft_itoa_based(address, "0123456789abcdef");
	if (str == NULL)
		return (0);
	temp = str;
	str = ft_strjoin("0x", temp);
	ft_str_fmt(str);
	len = ft_strlen(str);
	free (str);
	free (temp);
	return (len);
}

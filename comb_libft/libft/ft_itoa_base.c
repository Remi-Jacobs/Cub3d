/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:41:17 by danevans          #+#    #+#             */
/*   Updated: 2023/07/27 14:22:40 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cal_len(long int value, char *str)
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
	else if (value < 0)
	{
		value = -(value);
		len++;
	}
	while (value)
	{
		value = value / base;
		len++;
	}
	return (len);
}

static char	*create_res(int len)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * len + 1);
	if (result == NULL)
		return (NULL);
	return (result);
}

static void	check_value(char *result, long int *value)
{
	if (*value == 0)
		result[0] = '0';
	else if (*value < 0)
	{
		*value = -*value;
		result[0] = '-';
	}
}

char	*ft_itoa_base(long int value, char *str)
{
	char	*result;
	int		len;
	int		base;

	base = ft_strlen(str);
	len = cal_len(value, str);
	result = create_res(len);
	if (result == NULL)
		return (NULL);
	result[len] = '\0';
	check_value(result, &value);
	if (value == 0)
		return (result);
	len = len - 1;
	while (value)
	{
		result[len--] = str[value % base];
		value = value / base;
	}
	return (result);
}

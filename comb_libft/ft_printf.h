/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:31:37 by danevans          #+#    #+#             */
/*   Updated: 2023/06/29 19:11:33 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include "./libft/libft.h"

int		ft_decimal_fmt(int value);
int		ft_un_decimal_fmt(unsigned int value);
int		ft_char_fmt(char c);
int		ft_str_fmt(char *str);
int		ft_percent_fmt(void);
int		ft_pointer_fmt(void *ptr);
int		ft_low_hexa_fmt(unsigned int value);
int		ft_up_hexa_fmt(unsigned int value);
int		ft_printf(const char *format, ...);
int		ft_types(va_list args, char type);

#endif 

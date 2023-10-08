/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 07:21:34 by dylan             #+#    #+#             */
/*   Updated: 2023/09/20 09:58:13 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	processtype(char c, va_list a_list, int *count, int type)
{
	int	io;

	io = 0;
	if (c == 'c')
		ft_putchar((char)va_arg(a_list, int), count, type);
	else if (c == 's')
		ft_putstrmod((const char *)va_arg(a_list, char *), count, type);
	else if (c == 'p')
		ft_putptr((uintptr_t)va_arg(a_list, void *), count, io, type);
	else if (c == 'i' || c == 'd')
		ft_putnbr((int)va_arg(a_list, int), count, type);
	else if (c == 'u')
		ft_putnbru((unsigned int)va_arg(a_list, unsigned int), count, type);
	else if (c == 'x' || c == 'X')
		ft_hex((unsigned int)va_arg(a_list, unsigned int), count, c, type);
	else if (c == '%')
		ft_putchar('%', count, type);
}

int	ft_printf(int type, const char *str, ...)
{
	va_list	ag_list;
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	va_start(ag_list, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			processtype(str[i], ag_list, &count, type);
		}
		else
			ft_putchar(str[i], &count, type);
		i++;
	}
	va_end(ag_list);
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlehex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:58:49 by dylan             #+#    #+#             */
/*   Updated: 2023/09/20 09:55:30 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_hex(unsigned int nb, int *count, char c, int type)
{
	if (nb >= 16)
	{
		ft_hex(nb / 16, count, c, type);
		ft_hex(nb % 16, count, c, type);
	}
	else
	{
		if (nb <= 9)
			ft_putchar((nb + '0'), count, type);
		else
		{
			if (c == 'x')
				ft_putchar((nb - 10 + 'a'), count, type);
			if (c == 'X')
				ft_putchar((nb - 10 + 'A'), count, type);
		}
	}
}

void	ft_putptr(uintptr_t nb, int *count, int io, int type)
{
	if (nb != 0)
	{
		if (io == 0)
		{
			io = 1;
			ft_putstrmod(("0x"), count, type);
		}
	}
	if (nb == 0 && io == 0)
	{
		ft_putstrmod(("(nil)"), count, type);
		return ;
	}
	if (nb >= 16)
	{
		ft_putptr(nb / 16, count, io, type);
		ft_putptr(nb % 16, count, io, type);
	}
	else
	{
		if (nb <= 9)
			ft_putchar((nb + '0'), count, type);
		else
			ft_putchar((nb - 10 + 'a'), count, type);
	}
}

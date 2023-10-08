/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlei.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:59:34 by dylan             #+#    #+#             */
/*   Updated: 2023/09/20 10:01:37 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ismin(int nb, int *count, int type)
{
	ft_putstrmod("-2", count, type);
	nb = 147483648;
	return (nb);
}

int	isnegmod(int nb, int *count, int type)
{
	ft_putchar('-', count, type);
	return (-nb);
}

void	ft_putnbr(int nb, int *count, int type)
{
	if (nb == -2147483648)
		nb = ismin(nb, count, type);
	if (nb < 0)
		nb = isnegmod(nb, count, type);
	if (nb >= 10)
	{
		ft_putnbr(nb / 10, count, type);
		ft_putnbr(nb % 10, count, type);
	}
	else
		ft_putchar((nb + '0'), count, type);
}

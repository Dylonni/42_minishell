/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handleu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:00:31 by dylan             #+#    #+#             */
/*   Updated: 2023/09/20 09:57:12 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_putnbru(unsigned int nb, int *count, int type)
{
	if (nb >= 10)
	{
		ft_putnbru(nb / 10, count, type);
		ft_putnbru(nb % 10, count, type);
	}
	else
		ft_putchar((nb + '0'), count, type);
}

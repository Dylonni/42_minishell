/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:07:10 by dylan             #+#    #+#             */
/*   Updated: 2023/09/20 09:58:57 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_putstrmod(const char *src, int *count, int type)
{
	int	i;

	i = 0;
	if (!src)
	{
		ft_putstrmod("(null)", count, type);
		return ;
	}
	while (src[i])
	{
		ft_putchar(src[i], count, type);
		i++;
	}
}

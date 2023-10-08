/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psan <psan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:52:03 by daumis            #+#    #+#             */
/*   Updated: 2023/09/27 14:38:56 by psan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo_check(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		while (str[i])
		{
			if (i != 0 && str[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	else
		return (1);
}

void	ft_echo(char **args)
{
	int	i;
	int	check;
	int	newline;

	i = -1;
	check = 0;
	newline = 1;
	if (!args)
		return (write(1, "\n", 1), (void)0);
	while (args[++i])
	{
		if (check == 0 && ft_echo_check(args[i]) == 0)
			newline = 0;
		else
		{
			check = 1;
			ft_putstr(args[i]);
			if (*(args + i + 1))
				write(1, " ", 1);
		}
	}
	if (newline == 1)
		write(1, "\n", 1);
	g_error = 0;
}

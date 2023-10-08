/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psan <psan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:52:17 by daumis            #+#    #+#             */
/*   Updated: 2023/09/27 15:48:10 by psan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(char **args)
{
	char	buf[PATH_MAX];
	int		i;

	if (!args)
		return (g_error = 0, (void)0);
	i = 0;
	if (*args && **args == '-')
	{
		while (*(*args + ++i))
			if (*(*args + i) != '-')
				return (g_error = 2,
					write(2, "pwd: invalid option\n", 21), (void)0);
	}
	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		ft_putstr(buf);
		write(1, "\n", 1);
		g_error = 0;
	}
	else
	{
		g_error = 1;
		perror("pwd");
	}
}

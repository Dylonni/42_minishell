/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:52:00 by daumis            #+#    #+#             */
/*   Updated: 2023/09/19 15:36:46 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cd(char **args, t_sh *shell)
{
	int			i;
	int			check;
	char		buf[PATH_MAX];

	i = 0;
	check = 0;
	if (!args || !*args)
		return (g_error = 1, write(2, "cd: requires a path\n", 21), (void)0);
	while (*(args + i))
		i++;
	if (*args && **args == '-' && (*(*args + 1)))
		return (g_error = 2, write(2, "cd: invalid option\n", 20), (void)0);
	if (i > 1)
		return (g_error = 1, write(2, "cd: too many arguments\n", 24), (void)0);
	if (chdir((const char *)*args) == -1)
	{
		check = 1;
		perror("cd");
	}
	if (getcwd(buf, sizeof(buf)) != NULL)
		(ft_cd_bis(buf, shell->env_cpy), ft_cd_bis(buf, shell->exp_cpy));
	if (check)
		g_error = 1;
	else
		g_error = 0;
}

// faut free avant d'assigner
void	ft_cd_bis(char *buf, t_var **env)
{
	t_var		*cpy;
	char		*value;

	cpy = ft_findkey("PWD", env);
	if (!cpy)
	{
		ft_varadd_back(env, ft_varnew(ft_strndup("PWD", 3),
				ft_strndup(buf, ft_strlen(buf))));
		value = ft_strndup("", 1);
	}
	else
	{
		value = ft_strndup(cpy->value, ft_strlen(cpy->value));
		(free(cpy->value), cpy->value = ft_strndup(buf, ft_strlen(buf)));
	}
	cpy = ft_findkey("OLDPWD", env);
	if (!cpy)
		ft_varadd_back(env, ft_varnew(ft_strndup("OLDPWD", 6),
				ft_strndup(value, ft_strlen(value))));
	else
		(free(cpy->value), cpy->value = ft_strndup(value, ft_strlen(value)));
	free(value);
}

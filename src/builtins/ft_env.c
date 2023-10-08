/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:53:51 by daumis            #+#    #+#             */
/*   Updated: 2023/09/19 15:52:24 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(char **args, t_sh *shell)
{
	if (!args || !(*args))
	{
		g_error = 0;
		ft_varprint(shell->env_cpy, 1);
	}
	else if (*args && **args == '-' && (*(*args + 1)))
		return (g_error = 2, write(2, "env: invalid option\n", 21), (void)0);
	else
	{
		g_error = 1;
		write(2, "env: too many arguments\n", 25);
	}
}

int	ft_env_child(t_sh *shell)
{
	int		size;
	t_var	*tmp_var;

	size = 0;
	if (!shell->env_cpy)
		return (-1);
	tmp_var = *(shell->env_cpy);
	while (tmp_var)
	{
		tmp_var = tmp_var->next;
		size++;
	}
	return (ft_env_child_bis(shell, size));
}

int	ft_env_child_bis(t_sh *shell, int size)
{
	t_var	*tmp_var;
	int		i;

	i = 0;
	shell->env = malloc(sizeof(char *) * (size + 1));
	if (!shell->env)
		return (-1);
	tmp_var = *(shell->env_cpy);
	while (tmp_var)
	{
		*(shell->env + i) = ft_strjoin(ft_strndup
				(tmp_var->key, ft_strlen(tmp_var->key)), "=");
		*(shell->env + i) = ft_strjoin(*(shell->env + i), tmp_var->value);
		i++;
		tmp_var = tmp_var->next;
	}
	*(shell->env + i) = NULL;
	return (0);
}

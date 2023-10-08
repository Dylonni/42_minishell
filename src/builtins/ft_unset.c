/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:14:12 by daumis            #+#    #+#             */
/*   Updated: 2023/09/18 15:37:33 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export_apnd(char **args, t_sh *shell, int i)
{
	t_var	*key;
	char	*cpy;

	cpy = ft_strndup(*args, i);
	key = ft_findkey(cpy, shell->exp_cpy);
	free(cpy);
	if (key && ft_strncmp("UID", key->key, 3) == 0 && ft_strlen(key->key) == 3)
		return ;
	if (key)
	{
		key->value = ft_strjoin(key->value, *args + i + 2);
		key = ft_findkey(key->key, shell->env_cpy);
		key->value = ft_strjoin(key->value, *args + i + 2);
	}
	else
	{
		if (!*(*args + i + 2))
			(ft_export_addexp(args, shell, i, ft_strndup("", 1)),
				ft_export_rmvenv(args, shell, i + 1));
		else
			(ft_export_addexp(args, shell, i,
					ft_strndup(*args + i + 2, ft_strlen(*args + i + 2))),
				ft_export_addenv(args, shell, i,
					ft_strndup(*args + i + 2, ft_strlen(*args + i + 2))));
	}
}

int	ft_unset_rmvexp(char **args, t_sh *shell)
{
	t_var	*tmp;

	if ((ft_strncmp(*args, "_", 1) == 0)
		&& ft_strlen(*args) == 1)
		return (-1);
	if (!shell || !shell->exp_cpy)
		return (-1);
	tmp = *(shell->exp_cpy);
	while (tmp)
	{
		if ((ft_strncmp(tmp->key, *args, ft_strlen(tmp->key)) == 0)
			&& ft_strlen(tmp->key) == ft_strlen(*args))
		{
			ft_varremove(shell->exp_cpy, tmp);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unset_rmvenv(char **args, t_sh *shell)
{
	t_var	*tmp;

	if ((ft_strncmp(*args, "_", 1) == 0) && ft_strlen(*args) == 1)
		return (-1);
	if (!shell || !shell->env_cpy)
		return (-1);
	tmp = *(shell->env_cpy);
	while (tmp)
	{
		if (!(ft_strncmp("UID", *args, 3) == 0 && ft_strlen(*args) == 3)
			&& ((ft_strncmp(tmp->key, *args, ft_strlen(tmp->key)) == 0)
				&& ft_strlen(tmp->key) == ft_strlen(*args)))
		{
			ft_varremove(shell->env_cpy, tmp);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unset_check(char **args, t_sh *shell)
{
	int		i;

	i = 0;
	while ((*(*args + i)) && (*(*args + i) != '='))
	{
		if (i == 0 && ft_isdigit(**args))
			return (-1);
		if (!ft_isalnum(*(*args + i)) && *(*args + i) != '_')
			return (-1);
		i++;
	}
	ft_unset_rmvexp(args, shell);
	ft_unset_rmvenv(args, shell);
	return (0);
}

void	ft_unset(char **args, t_sh *shell)
{
	if (!args || !(*args))
		return (g_error = 0, (void)0);
	else if (*args && **args == '-' && (*(*args + 1)))
		return (g_error = 2, ft_throw_err(*args, 5), (void)0);
	else if (ft_strncmp("UID", *args, 3) == 0 && ft_strlen(*args) == 3)
		return (g_error = 0, (void)0);
	else
	{
		while (*args)
		{
			if (!**args || **args == '=' || **args == '\0'
				|| ft_unset_check(args, shell) == -1)
			{
				g_error = -1;
				ft_throw_err(*args, 6);
			}
			args++;
		}
		if (g_error == -1)
			g_error = 1;
		else
			g_error = 0;
	}
}

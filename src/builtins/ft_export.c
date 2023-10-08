/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:58:55 by daumis            #+#    #+#             */
/*   Updated: 2023/09/18 15:34:41 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export_addexp(char **args, t_sh *shell, int i, char *value)
{
	t_var	*tmp;
	char	*cpy;

	if (!shell || !shell->exp_cpy)
		return (-1);
	tmp = *(shell->exp_cpy);
	cpy = ft_strndup(*args, i);
	if ((ft_strncmp(cpy, "_", 1) == 0) && ft_strlen(cpy) == 1)
		return (free(cpy), -1);
	while (tmp)
	{
		if ((ft_strncmp("UID", cpy, 3) == 0) && ft_strlen(cpy) == 3)
			break ;
		if ((ft_strncmp(tmp->key, cpy, ft_strlen(tmp->key)) == 0)
			&& ft_strlen(tmp->key) == ft_strlen(cpy))
			return (free(tmp->value), tmp->value = value, free(cpy), 0);
		tmp = tmp->next;
	}
	ft_varadd_back(shell->exp_cpy, ft_varnew(ft_strndup(*args, i), value));
	return (free(cpy), 0);
}

int	ft_export_addenv(char **args, t_sh *shell, int i, char *value)
{
	t_var	*tmp;
	char	*cpy;

	if (!shell || !shell->env_cpy)
		return (-1);
	tmp = *(shell->env_cpy);
	cpy = ft_strndup(*args, i);
	if ((ft_strncmp(cpy, "_", 1) == 0) && ft_strlen(cpy) == 1)
		return (free(cpy), -1);
	while (tmp)
	{
		if ((ft_strncmp("UID", cpy, 3) == 0) && ft_strlen(cpy) == 3)
			break ;
		if ((ft_strncmp(tmp->key, cpy, ft_strlen(tmp->key)) == 0)
			&& ft_strlen(tmp->key) == ft_strlen(cpy))
			return (free(tmp->value), tmp->value = value, free(cpy), 0);
		tmp = tmp->next;
	}
	ft_varadd_back(shell->env_cpy, ft_varnew(ft_strndup(*args, i), value));
	return (free(cpy), 0);
}

int	ft_export_rmvenv(char **args, t_sh *shell, int i)
{
	t_var	*tmp;
	char	*cpy;

	if (!shell || !shell->env_cpy)
		return (-1);
	tmp = *(shell->env_cpy);
	cpy = ft_strndup(*args, i);
	if ((ft_strncmp(cpy, "_", 1) == 0) && ft_strlen(cpy) == 1)
		return (free(cpy), -1);
	while (tmp)
	{
		if ((ft_strncmp(tmp->key, cpy, ft_strlen(tmp->key)) == 0)
			&& ft_strlen(tmp->key) == ft_strlen(cpy))
		{
			ft_varremove(shell->env_cpy, tmp);
			return (free(cpy), 0);
		}
		tmp = tmp->next;
	}
	return (free(cpy), 0);
}

int	ft_export_check(char **args, t_sh *shell)
{
	int		i;

	i = 0;
	while ((*(*args + i)) && (*(*args + i) != '='))
	{
		if (i == 0 && ft_isdigit(**args))
			return (-1);
		if (*(*args + i) == '+' && *(*args + i + 1) && *(*args + i + 1) == '=')
			break ;
		if (!ft_isalnum(*(*args + i)) && *(*args + i) != '_')
			return (-1);
		i++;
	}
	if (*(*args) != '+' && *(*args + i) == '+'
		&& *(*args + i + 1) && *(*args + i + 1) == '=')
		ft_export_apnd(args, shell, i);
	if ((*(*args + i)) == '=')
		(ft_export_addenv(args, shell, i,
				ft_strndup(*args + i + 1, ft_strlen(*args + i + 1))),
			ft_export_addexp(args, shell, i,
				ft_strndup(*args + i + 1, ft_strlen(*args + i + 1))));
	if (!*(*args + i))
		(ft_export_addexp(args, shell, i, NULL),
			ft_export_rmvenv(args, shell, i));
	return (0);
}

void	ft_export(char **args, t_sh *shell)
{
	if (!args || !(*args))
		(ft_varprint(shell->exp_cpy, 0), g_error = 0);
	else if (*args && **args == '-' && (*(*args + 1)))
		return (g_error = 2, write(2, "export: invalid option\n", 24), (void)0);
	else if (ft_strncmp("UID", *args, 3) == 0 && ft_strlen(*args) == 3)
		return (g_error = 0, (void)0);
	else
	{
		while (*args)
		{
			if (!**args || **args == '=' || **args == '\0'
				|| ft_export_check(args, shell) == -1)
				(ft_throw_err(*args, 4), g_error = -1);
			args++;
		}
		if (g_error == -1)
			g_error = 1;
		else
			g_error = 0;
	}
}

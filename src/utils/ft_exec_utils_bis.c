/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:36:20 by dylan             #+#    #+#             */
/*   Updated: 2023/09/19 16:14:53 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_absolute_path(char **final, t_exec *exec)
{
	if (ft_check_stat(*final) == 1)
		return (g_error = 126, ft_throw_err(*final, 8), 1);
	if (access(*final, F_OK) == 0)
	{
		exec->pathname = ft_strndup(*final, ft_strlen(*final));
		exec->command_found = 1;
		return (0);
	}
	return (g_error = 127, ft_throw_err(*final, 2), 1);
}

int	ft_relative_path(char **final, t_sh *shell, t_exec *exec)
{
	char	*cpy;

	if (!final || !*final || !**final)
		return (0);
	cpy = ft_strndup("PATH", 4);
	exec->paths = ft_split(ft_findvalue(cpy, shell->env_cpy), ':');
	free(cpy);
	if (!exec->paths)
		return (1);
	exec->pathname = NULL;
	while (exec->paths[exec->i])
	{
		if (ft_strjoin_pathname(final, exec->paths, exec->i, &(exec->pathname)))
			return (0);
		if (access(exec->pathname, F_OK) == 0)
		{
			exec->command_found = 1;
			break ;
		}
		exec->i++;
	}
	return (0);
}

int	ft_exec_cd(t_cmd **cmds, int count)
{
	t_cmd	*tmp_cmd;
	int		i;

	i = 0;
	if (!cmds)
		return (-1);
	tmp_cmd = *cmds;
	while (i < count - 1)
	{
		if (!tmp_cmd)
			return (-1);
		tmp_cmd = tmp_cmd->next;
		i++;
	}
	if (tmp_cmd && tmp_cmd->final && ft_strncmp(
			*(tmp_cmd->final), "cd", ft_strlen(*(tmp_cmd->final))) == 0
		&& ft_strlen(*(tmp_cmd->final)) == 2)
		return (0);
	return (1);
}

int	ft_exec_name(t_cmd **cmds, int count, char *name)
{
	t_cmd	*tmp_cmd;

	if (!cmds)
		return (-1);
	tmp_cmd = *cmds;
	if (count == 1 && tmp_cmd && tmp_cmd->final && ft_strncmp(
			*(tmp_cmd->final), name, ft_strlen(*(tmp_cmd->final))) == 0
		&& ft_strlen(*(tmp_cmd->final)) == ft_strlen(name))
		return (0);
	return (1);
}

int	ft_execute_check(t_cmd **cmds, t_sh *shell, int count)
{
	t_cmd	*tcmd;

	tcmd = *cmds;
	while (tcmd)
	{
		if ((!tcmd->rdrct_lst || !*(tcmd->rdrct_lst))
			&& (!(tcmd->final) || !*(tcmd->final)))
			return (g_error = 2, ft_throw_err("|", 9), 0);
		tcmd = tcmd->next;
	}
	if ((ft_exec_cd(cmds, count)) == 0)
		return (ft_cd((*cmds)->final + 1, shell), 0);
	if ((ft_exec_name(cmds, count, "exit")) == 0)
	{
		ft_exit((*cmds)->final + 1);
		if (g_error == 1)
			return (0);
		return (shell->status = 1, 0);
	}
	if ((ft_exec_name(cmds, count, "export")) == 0)
		return (ft_export((*cmds)->final + 1, shell), 0);
	if ((ft_exec_name(cmds, count, "unset")) == 0)
		return (ft_unset((*cmds)->final + 1, shell), 0);
	return (1);
}

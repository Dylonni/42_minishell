/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:49:22 by daumis            #+#    #+#             */
/*   Updated: 2023/09/27 18:47:00 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_execute_command(char **final, t_sh *shell)
{
	t_exec	exec;

	ft_memset(&exec, 0, sizeof(t_exec));
	if (ft_execute_builtin(final, shell) == 0)
		return (0);
	if (final && *final && (**final == '/' || **final == '.'))
	{
		if (ft_absolute_path(final, &exec))
			return (1);
	}
	else
	{
		if (!final || !*final || !**final)
			return (g_error = 0, ft_free_exec(&exec), 1);
		if (ft_relative_path(final, shell, &exec) == 1)
			return (g_error = 127, ft_throw_err(*final, 1), ft_free_exec(&exec)
				, 1);
	}
	if (!exec.command_found)
		return (g_error = 127, ft_throw_err(*final, 1), ft_free_exec(&exec), 1);
	if (execve(exec.pathname, final, shell->env) == -1)
		return (ft_exec_error(), perror("execve"), ft_free_exec(&exec), 1);
	return (ft_free_exec(&exec), 0);
}

int	ft_process_prnt(t_pipe *pipes)
{
	if (pipes->index > 0)
	{
		if (pipes->old_fd[0] > 2 && close(pipes->old_fd[0]) == -1)
			return (g_error = 1, perror("close"), 1);
		if (pipes->old_fd[1] > 2 && close(pipes->old_fd[1]) == -1)
			return (g_error = 1, perror("close"), 1);
	}
	if (pipes->index < pipes->count)
	{
		pipes->old_fd[0] = pipes->new_fd[0];
		pipes->old_fd[1] = pipes->new_fd[1];
	}
	return (0);
}

int	ft_process_chld(t_cmd *cmd, t_sh *shell, t_pipe *pipes)
{
	t_var	*cpy;
	int		shlvl;
	char	*str;

	ft_free_env(shell->env);
	cpy = ft_findkey("SHLVL", shell->env_cpy);
	if (cpy)
	{
		shlvl = (int)ft_atoll(cpy->value);
		free(cpy->value);
		if (shlvl <= 0 || shlvl > 1000)
			cpy->value = ft_strndup("1", 1);
		else
		{
			str = ft_itoa(shlvl + 1);
			cpy->value = ft_strndup(str, ft_strlen(str));
			free(str);
		}
	}
	(ft_env_child(shell), ft_signal_hrdc());
	if (ft_redirect_files(cmd, pipes, shell))
		return (ft_free_shell(shell), exit(g_error), 1);
	signal(SIGQUIT, ft_signal_backslash);
	ft_execute_command(cmd->final, shell);
	return (ft_free_shell(shell), exit(g_error), 1);
}

int	ft_execute_each(t_cmd *cmd, t_sh *shell, t_pipe *pipes)
{
	if (pipe(pipes->new_fd) == -1)
		return (g_error = 1, perror("pipe"), 1);
	shell->pid = fork();
	if (shell->pid == -1)
		return (g_error = 1, perror("fork"), 1);
	if (shell->pid == 0)
		return (ft_process_chld(cmd, shell, pipes));
	else
	{
		signal(SIGINT, ft_signal_c_prnt);
		signal(SIGQUIT, ft_signal_backslash);
		ft_hrdc_wait(cmd);
		return (ft_process_prnt(pipes));
	}
	return (0);
}

int	ft_execute(t_cmd **cmds, t_sh *shell)
{
	t_cmd	*tmp_cmd;
	t_pipe	pipes;

	(ft_memset(&pipes, 0, sizeof(t_pipe)), pipes.old_fd[1] = 1);
	if (!cmds)
		return (-1);
	tmp_cmd = *cmds;
	pipes.count = ft_cmdcount(cmds);
	if (pipes.count == -1)
		return (-1);
	if (ft_execute_check(cmds, shell, pipes.count) == 0)
		return (-1);
	while (tmp_cmd)
	{
		(ft_signal_exec(), ft_execute_each(tmp_cmd, shell, &pipes));
		tmp_cmd = tmp_cmd->next;
		pipes.index++;
	}
	while (wait(&pipes.status) > 0)
		if (WIFEXITED(pipes.status))
			g_error = WEXITSTATUS(pipes.status);
	if (g_error == 130)
		write(1, "\n", 1);
	return (unlink(".heredoc"), ft_close_pipes(&pipes), 0);
}

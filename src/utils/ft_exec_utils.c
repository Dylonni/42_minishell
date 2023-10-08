/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:56:29 by dylan             #+#    #+#             */
/*   Updated: 2023/09/27 18:39:26 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Function called to join a pathname with a command
(Ex ls will become /usr/bin/ls)*/
int	ft_strjoin_pathname(char **cmd, char **paths, int i, char **pathname)
{
	char	*tmp;

	if (!pathname)
		return (1);
	free(*pathname);
	*pathname = NULL;
	tmp = ft_strjoin(ft_strndup(paths[i], ft_strlen(paths[i])), "/");
	if (!tmp)
		return (1);
	*pathname = ft_strjoin(tmp, cmd[0]);
	if (!*pathname)
		return (free(tmp), 1);
	return (0);
}

void	ft_exec_error(void)
{
	if (errno == 13)
		g_error = 126;
}

/*Function called by ft_execute , closes pipes after finishing all
of the commands execution*/
void	ft_close_pipes(t_pipe *pipes)
{
	if (pipes->new_fd[0] > 2 && close(pipes->new_fd[0]) == -1)
		return (g_error = 1, perror("close"));
	if (pipes->new_fd[1] > 2 && close(pipes->new_fd[1]) == -1)
		return (g_error = 1, perror("close"));
}

/*Function called in ft_execute_command in case of if the user
asked for a builtin execution */
int	ft_execute_builtin(char **final, t_sh *shell)
{
	if (ft_strncmp(*final, "exit", ft_strlen(*final)) == 0
		&& ft_strlen(*final) == 4)
		return (ft_exit(final + 1), ft_free_shell(shell), exit(g_error), 0);
	if (ft_strncmp(*final, "cd", ft_strlen(*final)) == 0
		&& ft_strlen(*final) == 2)
		return (ft_cd(final + 1, shell), ft_free_shell(shell), exit(0), 0);
	if (ft_strncmp(*final, "echo", ft_strlen(*final)) == 0
		&& ft_strlen(*final) == 4)
		return (ft_echo(final + 1), ft_free_shell(shell), exit(g_error), 0);
	if (ft_strncmp(*final, "pwd", ft_strlen(*final)) == 0
		&& ft_strlen(*final) == 3)
		return (ft_pwd(final + 1), ft_free_shell(shell), exit(0), 0);
	if (ft_strncmp(*final, "export", ft_strlen(*final)) == 0
		&& ft_strlen(*final) == 6)
		return (ft_export(final + 1, shell), ft_free_shell(shell), exit(0), 0);
	if (ft_strncmp(*final, "unset", ft_strlen(*final)) == 0
		&& ft_strlen(*final) == 5)
		return (ft_unset(final + 1, shell), ft_free_shell(shell), exit(0), 0);
	if (ft_strncmp(*final, "env", ft_strlen(*final)) == 0
		&& ft_strlen(*final) == 3)
		return (ft_env(final + 1, shell), ft_free_shell(shell), exit(0), 0);
	return (1);
}

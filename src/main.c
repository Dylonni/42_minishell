/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psan <psan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:15:33 by daumis            #+#    #+#             */
/*   Updated: 2023/09/26 15:47:54 by psan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error = 0;

int	ft_redirect_files(t_cmd *cmd, t_pipe *pipes, t_sh *shell)
{
	if (!ft_rdrct_checkin(cmd) && dup2(pipes->old_fd[0], STDIN_FILENO) == -1)
		return (g_error = 1, perror("dup2"), 1);
	if (pipes->old_fd[0] > 2)
		if (close(pipes->old_fd[0]) == -1)
			return (g_error = 1, perror("close"), 1);
	if (pipes->old_fd[1] > 2)
		if (close(pipes->old_fd[1]) == -1)
			return (g_error = 1, perror("close"), 1);
	if (pipes->new_fd[0] > 2)
		if (close(pipes->new_fd[0]) == -1)
			return (g_error = 1, perror("close"), 1);
	pipes->check = ft_check_files(cmd, pipes, shell);
	if (pipes->index + 1 < pipes->count)
		if (!ft_rdrct_checkout(cmd)
			&& dup2(pipes->new_fd[1], STDOUT_FILENO) == -1)
			return (g_error = 1, perror("dup2"), 1);
	if (pipes->new_fd[1] > 2)
		if (close(pipes->new_fd[1]) == -1)
			return (g_error = 1, perror("close"), 1);
	return (pipes->check);
}

void	ft_init_env_dfl(char **env, t_sh *shell)
{
	struct stat	mystat;
	char		buf[PATH_MAX];

	if (!ft_findkey("UID", shell->env_cpy))
	{
		ft_memset(&mystat, 0, sizeof(struct stat));
		fstat(0, &mystat);
		ft_varadd_back(shell->env_cpy,
			ft_varnew(ft_strndup("UID", 3), ft_itoa(mystat.st_uid)));
	}
	if (!*env)
	{
		ft_varadd_back(shell->env_cpy,
			ft_varnew(ft_strndup(".bs", 3), ft_strndup("1", 1)));
		if (!ft_findkey("SHLVL", shell->env_cpy))
			(ft_varadd_back(shell->env_cpy,
					ft_varnew(ft_strndup("SHLVL", 5), ft_strndup("1", 1))),
				ft_varadd_back(shell->exp_cpy,
					ft_varnew(ft_strndup("SHLVL", 5), ft_strndup("1", 1))));
		if (getcwd(buf, sizeof(buf)) != NULL)
			(ft_cd_bis(buf, shell->env_cpy), ft_cd_bis(buf, shell->exp_cpy));
	}
}

/*Function that will copy the environement
into shell->env_cpy and shell->exp_cpy*/
int	ft_init_env(char **env, t_sh *shell)
{
	int		i;
	char	**cpy;

	if (!env)
		return (1);
	shell->env_cpy = malloc (sizeof (t_var *));
	if (!shell->env_cpy)
		return (1);
	ft_memset(shell->env_cpy, 0, sizeof(t_var **));
	shell->exp_cpy = malloc (sizeof (t_var *));
	if (!shell->exp_cpy)
		return (1);
	(ft_memset(shell->exp_cpy, 0, sizeof(t_var **)), cpy = env);
	while (*cpy)
	{
		i = 0;
		while ((*(*cpy + i)) && (*(*cpy + i) != '='))
			i++;
		ft_varadd_back(shell->env_cpy, ft_varnew(ft_strndup(*cpy, i), \
		ft_strndup(*cpy + i + 1, ft_strlen(*cpy + i + 1))));
		ft_varadd_back(shell->exp_cpy, ft_varnew(ft_strndup(*cpy, i), \
		ft_strndup(*cpy + i + 1, ft_strlen(*cpy + i + 1))));
		cpy++;
	}
	return (ft_init_env_dfl(env, shell), 0);
}

/*Core Loop of the minishell , which will wait and process every input line*/
void	ft_mainloop(t_sh *shell)
{
	char	*prompt;
	char	*line;

	prompt = "minishell> ";
	line = NULL;
	while (1)
	{
		ft_signal_main();
		line = readline(prompt);
		if (line == NULL)
		{
			if (ft_findkey(".bs", shell->env_cpy))
				write(1, "\n", 1);
			break ;
		}
		else if (line[0] == '\0' || !ft_checkspaces(line))
			g_error = 0;
		else
		{
			(add_history(line), ft_splitline(line, shell));
			if (shell->status)
				break ;
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_sh	*shell;

	(void)argc;
	(void)argv;
	shell = malloc (sizeof(t_sh));
	if (!shell)
		return (1);
	ft_memset(shell, 0, sizeof(t_sh));
	ft_init_env(env, shell);
	ft_env_child(shell);
	ft_mainloop(shell);
	rl_clear_history();
	ft_free_shell(shell);
	if (g_error == -1)
	{
		g_error = 2;
		exit(g_error);
	}
	exit(g_error);
	return (0);
}

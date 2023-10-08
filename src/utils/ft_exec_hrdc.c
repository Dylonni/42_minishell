/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_hrdc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psan <psan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:13:10 by psan              #+#    #+#             */
/*   Updated: 2023/09/26 15:02:40 by psan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_hrdc_wait(t_cmd *cmd)
{
	t_tkn	*tmp;
	int		check;

	if (!cmd->rdrct_lst || !*(cmd->rdrct_lst))
		return (0);
	tmp = *(cmd->rdrct_lst);
	check = 0;
	while (tmp)
	{
		if (tmp->rtype == 1)
		{
			check = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (check)
	{
		while (wait(NULL) > 0)
			;
	}
	return (0);
}

int	ft_hrdc_ctrl(char *line)
{
	if (g_error == -130)
	{
		g_error = 130;
		return (2);
	}
	if (line == NULL)
		return (1);
	return (0);
}

int	ft_hrdc_loop(char *line, t_pipe *pipes, t_sh *shell)
{
	char	*cpy;

	cpy = NULL;
	ft_xpnd_loop(&cpy, line, shell->env_cpy);
	if (write(pipes->fd[0], cpy, ft_strlen(cpy)) == -1)
		return (g_error = 1, free(cpy), perror("write"), 1);
	free(cpy);
	if (write(pipes->fd[0], "\n", 1) == -1)
		return (g_error = 1, perror("write"), 1);
	return (0);
}

int	ft_hrdc_read(char *lim, t_pipe *pipes, t_sh *shell, int *eof)
{
	char	*line;

	line = NULL;
	line = readline("> ");
	*eof = ft_hrdc_ctrl(line);
	if (*eof > 0)
		return (-1);
	if (ft_strncmp(line, lim, ft_strlen(lim)) == 0
		&& ft_strlen(line) == ft_strlen(lim))
		return (-1);
	else
		if (ft_hrdc_loop(line, pipes, shell) == 1)
			return (1);
	return (0);
}

/*This function is called in child process, it handles the heredoc functionality
by reading the line input by user , when the input matches the limiter
(or the process has been stopped by a signal)
the heredoc closes and executes the associated command*/
int	ft_heredoc(char *lim, t_pipe *pipes, t_sh *shell)
{
	int		eof;
	int		check;

	eof = 0;
	pipes->fd[0] = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipes->fd[0] == -1)
		return (g_error = 1, perror("open"), 1);
	rl_event_hook = event;
	while (1)
	{
		check = ft_hrdc_read(lim, pipes, shell, &eof);
		if (check < 0)
			break ;
		else if (check > 0)
			return (1);
	}
	if (close(pipes->fd[0]) == -1)
		return (g_error = 1, perror("close"), -1);
	if (eof == 1)
		return (g_error = 0, ft_throw_err(lim, 7), 2);
	return (eof);
}

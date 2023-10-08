/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_rdct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:59:34 by dylan             #+#    #+#             */
/*   Updated: 2023/09/27 18:32:10 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_rdrct_checkin(t_cmd *cmd)
{
	t_tkn	*tmp;

	if (!cmd->rdrct_lst || !*(cmd->rdrct_lst))
		return (0);
	tmp = *(cmd->rdrct_lst);
	while (tmp)
	{
		if (tmp->rtype < 2)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_rdrct_checkout(t_cmd *cmd)
{
	t_tkn	*tmp;

	if (!cmd->rdrct_lst || !*(cmd->rdrct_lst))
		return (0);
	tmp = *(cmd->rdrct_lst);
	while (tmp)
	{
		if (tmp->rtype > 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_in(t_tkn *tmp_in, t_pipe *pipes)
{
	if (tmp_in)
	{
		if (tmp_in->rtype == 0)
			pipes->fd[0] = open(tmp_in->str, O_RDONLY);
		else
			pipes->fd[0] = open(".heredoc", O_RDONLY);
		if (pipes->fd[0] == -1)
			return (g_error = 1, perror("open"), -1);
		if (dup2(pipes->fd[0], STDIN_FILENO) == -1)
			return (g_error = 1, perror("dup2"), -1);
		if (pipes->fd[0] > 2 && close(pipes->fd[0]) == -1)
			return (g_error = 1, perror("close"), -1);
	}
	return (0);
}

int	ft_check_loop(t_tkn *tmp, t_pipe *pipes, t_sh *shell)
{
	if (tmp->rtype == 0 && access(tmp->str, R_OK) == -1)
		return (1);
	if (tmp->rtype == 1)
	{
		if (ft_heredoc(tmp->str, pipes, shell))
			return (-1);
	}
	else if (tmp->rtype == 2)
		pipes->fd[1] = open(tmp->str, O_CREAT | O_WRONLY | O_TRUNC,
				0644);
	else if (tmp->rtype == 3)
		pipes->fd[1] = open(tmp->str, O_CREAT | O_WRONLY | O_APPEND,
				0644);
	if (tmp->rtype > 1)
	{
		if (pipes->fd[1] == -1)
			return (g_error = 1, perror("open"), -1);
		if (dup2(pipes->fd[1], STDOUT_FILENO) == -1)
			return (g_error = 1, perror("dup2"), -1);
		if (pipes->fd[1] > 2 && close(pipes->fd[1]) == -1)
			return (g_error = 1, perror("close"), -1);
	}
	return (0);
}

int	ft_check_files(t_cmd *cmd, t_pipe *pipes, t_sh *shell)
{
	t_tkn	*tmp;
	t_tkn	*tmp_in;

	if (!cmd->rdrct_lst)
		return (0);
	tmp = *(cmd->rdrct_lst);
	if (!tmp)
		return (1);
	tmp_in = NULL;
	if (tmp->rtype < 2)
		tmp_in = *(cmd->rdrct_lst);
	while (tmp)
	{
		pipes->check = ft_check_loop(tmp, pipes, shell);
		if (pipes->check > 0)
			break ;
		else if (pipes->check < 0)
			return (-1);
		tmp = tmp->next;
		if (tmp && tmp->rtype < 2)
			tmp_in = tmp;
	}
	return (ft_check_in(tmp_in, pipes));
}

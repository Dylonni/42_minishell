/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psan <psan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:03:28 by psan              #+#    #+#             */
/*   Updated: 2023/09/27 15:58:20 by psan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cmdredirect_add(t_tkn ***rdrct, t_tkn **tkn, int type)
{
	char	*str;

	if (!(*tkn)->next)
		return (-1);
	str = (*tkn)->next->str;
	if (*str == '<' || *str == '>' || *str == '|')
		return (-1);
	if (!(*rdrct))
	{
		*rdrct = (t_tkn **)malloc(sizeof(t_tkn *));
		if (!(*rdrct))
			return (-1);
		ft_memset(*rdrct, 0, sizeof(t_tkn **));
		*(*rdrct) = ft_tknnew(ft_strndup(str, ft_strlen(str)), type);
	}
	else
		ft_tknadd_back(*rdrct, ft_tknnew(
				ft_strndup(str, ft_strlen(str)), type));
	*tkn = (*tkn)->next->next;
	return (1);
}

int	ft_cmdredirect(t_cmd **cmds, t_tkn **tkn)
{
	char	*str;
	int		str_len;

	str = (*tkn)->str;
	str_len = ft_strlen(str);
	if (str[0] == '<')
	{
		if (str_len == 1)
			str_len = ft_cmdredirect_add(&((*cmds)->rdrct_lst), tkn, 0);
		else
			str_len = ft_cmdredirect_add(&((*cmds)->rdrct_lst), tkn, 1);
	}
	else if (str[0] == '>')
	{
		if (str_len == 1)
			str_len = ft_cmdredirect_add(&((*cmds)->rdrct_lst), tkn, 2);
		else
			str_len = ft_cmdredirect_add(&((*cmds)->rdrct_lst), tkn, 3);
	}
	else
		return (0);
	return (str_len);
}

int	ft_cmdloop(t_cmd **cmds, t_tkn **tkn)
{
	int	n;

	while (*tkn && (*tkn)->str && (*tkn)->str[0] != '|')
	{
		n = ft_cmdredirect(cmds, tkn);
		if (n == -1 && !(*tkn)->next)
			return (g_error = 2, ft_throw_err("newline", 9), -1);
		else if (n == -1 && (*tkn)->next && ((*tkn)->next->str[0] == '|'
				|| (*tkn)->next->str[0] == '<' || (*tkn)->next->str[0] == '>'))
			return (g_error = 2, ft_throw_err((*tkn)->next->str, 9), -1);
		else if (n == -1)
			return (g_error = 2, ft_throw_err((*tkn)->str, 9), -1);
		else if (!n)
		{
			ft_tknadd_back((*cmds)->cmd_lst,
				ft_tknnew(ft_strndup((*tkn)->str, ft_strlen((*tkn)->str)), 0));
			*tkn = (*tkn)->next;
		}
	}
	if (*tkn)
	{
		*tkn = (*tkn)->next;
		(ft_cmdadd_back(cmds, ft_cmdnew()), (*cmds) = (*cmds)->next);
	}
	return (0);
}

t_cmd	**ft_cmdcreate(t_tkn **tokens)
{
	t_cmd	**cmds;
	t_tkn	*tmp_tkn;
	t_cmd	*tmp_cmd;

	cmds = (t_cmd **)malloc(sizeof(t_cmd *));
	if (!cmds)
		return (0);
	ft_memset(cmds, 0, sizeof(t_cmd *));
	*cmds = ft_cmdnew();
	tmp_cmd = *cmds;
	tmp_tkn = *tokens;
	while (tmp_tkn)
	{
		if (ft_cmdloop(cmds, &tmp_tkn) == -1)
			return (ft_cmdclear(cmds), NULL);
	}
	*cmds = tmp_cmd;
	return (cmds);
}

int	ft_cmdcount(t_cmd **cmds)
{
	t_cmd	*tmp_cmd;
	int		i;

	i = 0;
	if (!cmds)
		return (-1);
	tmp_cmd = *cmds;
	while (tmp_cmd)
	{
		tmp_cmd = tmp_cmd->next;
		i++;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:03:28 by psan              #+#    #+#             */
/*   Updated: 2023/09/27 18:04:27 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*ft_cmdnew(void)
{
	t_cmd	*tmp;

	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (!tmp)
		return (0);
	tmp->cmd = NULL;
	tmp->cmd_lst = (t_tkn **)malloc(sizeof(t_tkn *));
	if (!tmp->cmd_lst)
		return (free(tmp), NULL);
	*(tmp->cmd_lst) = NULL;
	tmp->rdrct = NULL;
	tmp->rdrct_lst = NULL;
	tmp->next = NULL;
	tmp->final = NULL;
	tmp->rdrct_final = NULL;
	return (tmp);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_cmdclear(t_cmd **lst)
{
	t_cmd	**lst_init;

	if (!lst)
		return ;
	lst_init = lst;
	ft_cmdclear_loop(lst);
	*lst_init = NULL;
	free(lst);
}

void	ft_cmdclear_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (*(tab + i))
		free(*(tab + i++));
	free(tab);
}

void	ft_cmdclear_loop(t_cmd **lst)
{
	t_cmd	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_cmdclear_tab(tmp->cmd);
		ft_cmdclear_tab(tmp->final);
		ft_cmdclear_tab(tmp->rdrct);
		ft_cmdclear_tab(tmp->rdrct_final);
		ft_tknclear(tmp->cmd_lst);
		ft_tknclear(tmp->rdrct_lst);
		free(tmp);
	}
}

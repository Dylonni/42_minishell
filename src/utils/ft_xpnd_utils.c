/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xpnd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:04:20 by psan              #+#    #+#             */
/*   Updated: 2023/09/27 18:09:49 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_xpnd_size(t_tkn	*tmp_lst)
{
	int	size;

	size = 0;
	while (tmp_lst)
	{
		size++;
		tmp_lst = tmp_lst->next;
	}
	return (size);
}

int	ft_xpnd_init(t_cmd *tmp_cmd)
{
	tmp_cmd->cmd = malloc(sizeof(char *) * (
				ft_xpnd_size(*(tmp_cmd->cmd_lst)) + 1));
	if (!tmp_cmd->cmd)
		return (-1);
	tmp_cmd->final = malloc(sizeof(char *) * (
				ft_xpnd_size(*(tmp_cmd->cmd_lst)) + 1));
	if (!tmp_cmd->final)
		return (-1);
	ft_memset(tmp_cmd->cmd, 0, sizeof(char **));
	if (tmp_cmd->rdrct_lst)
	{
		tmp_cmd->rdrct = malloc(sizeof(char *) * (
					ft_xpnd_size(*(tmp_cmd->rdrct_lst)) + 1));
		if (!tmp_cmd->rdrct)
			return (-1);
		tmp_cmd->rdrct_final = malloc(sizeof(char *) * (
					ft_xpnd_size(*(tmp_cmd->rdrct_lst)) + 1));
		if (!tmp_cmd->rdrct_final)
			return (-1);
		ft_memset(tmp_cmd->rdrct, 0, sizeof(char **));
		ft_memset(tmp_cmd->rdrct_final, 0, sizeof(char **));
	}
	return (0);
}

int	ft_xpnd_rdrct_swap(t_cmd *tmp_cmd, t_var **env)
{
	t_tkn	*tmp_lst;
	int		i;

	if (!tmp_cmd->rdrct_lst)
		return (-1);
	ft_xpnd_fill(tmp_cmd->rdrct_lst, tmp_cmd->rdrct, env);
	i = 0;
	tmp_lst = *(tmp_cmd->rdrct_lst);
	while (tmp_lst)
	{
		free(tmp_lst->str);
		tmp_lst->str = ft_strndup(*(tmp_cmd->rdrct + i),
				ft_strlen(*(tmp_cmd->rdrct + i)));
		tmp_lst = tmp_lst->next;
		i++;
	}
	return (0);
}

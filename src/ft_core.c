/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:03:28 by psan              #+#    #+#             */
/*   Updated: 2023/09/27 17:30:57 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_xpnd_end(char **cmd, char *str, t_var **env, t_data *data)
{
	while ((size_t)data->index_prev != ft_strlen(str))
	{
		data->index = ft_xpnd_check(str + data->index_prev, data);
		if (data->index == -1)
		{
			data->cpy = ft_strndup(str + data->index_prev,
					ft_strlen(str + data->index_prev));
			*cmd = ft_strjoin(*cmd, data->cpy);
			free(data->cpy);
			break ;
		}
		else
			ft_xpnd_value_next(cmd, str, env, data);
		data->index_prev += data->index + data->size + 1;
	}
	return (0);
}

/*Used by ft_expander, expands the shell parameter*/
int	ft_xpnd_loop(char **cmd, char *str, t_var **env)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	data.quote = -1;
	data.dquote = -1;
	data.index = ft_xpnd_check(str, &data);
	if (data.index == -1)
		*cmd = ft_strndup(str, ft_strlen(str));
	else
	{
		ft_xpnd_value_first(cmd, str, env, &data);
		ft_xpnd_end(cmd, str, env, &data);
	}
	return (0);
}

int	ft_xpnd_fill(t_tkn **lst, char **cpy, t_var **env)
{
	t_tkn	*lst_cpy;
	int		i;

	i = 0;
	lst_cpy = *(lst);
	while (lst_cpy)
	{
		if (lst_cpy->rtype != 1)
			ft_xpnd_loop((cpy + i), lst_cpy->str, env);
		else
			*(cpy + i) = ft_strndup(lst_cpy->str, ft_strlen(lst_cpy->str));
		i++;
		lst_cpy = lst_cpy->next;
	}
	*(cpy + i) = NULL;
	return (0);
}

/*Function that will expand a shell parameter
(Ex. $GDMSESSION will become ubuntu)*/
int	ft_expander(t_cmd **cmds, t_var **env)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = *cmds;
	while (tmp_cmd)
	{
		if (ft_xpnd_init(tmp_cmd) == -1)
			return (-1);
		ft_xpnd_rdrct_swap(tmp_cmd, env);
		ft_xpnd_fill(tmp_cmd->cmd_lst, tmp_cmd->cmd, env);
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}

int	ft_splitline(char *line, t_sh *shell)
{
	t_tkn	**tokens;

	if (!line)
		return (1);
	tokens = ft_tkncreate(line);
	if (!tokens)
		return (1);
	ft_cmdclear(shell->cmds);
	shell->cmds = ft_cmdcreate(tokens);
	if (!shell->cmds)
		return (ft_tknclear(tokens), 1);
	ft_expander(shell->cmds, shell->env_cpy);
	ft_quotehandler(shell->cmds);
	ft_tknclear(tokens);
	ft_execute(shell->cmds, shell);
	return (0);
}

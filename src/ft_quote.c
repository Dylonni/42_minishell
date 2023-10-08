/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:53:53 by psan              #+#    #+#             */
/*   Updated: 2023/09/27 19:11:50 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_quote_rdrct(t_cmd *tmp_cmd)
{
	t_tkn	*tmp_lst;
	int		i;

	if (!tmp_cmd->rdrct_lst)
		return (-1);
	i = 0;
	tmp_lst = *(tmp_cmd->rdrct_lst);
	while (tmp_lst)
	{
		free(tmp_lst->str);
		tmp_lst->str = ft_strndup(*(tmp_cmd->rdrct_final + i),
				ft_strlen(*(tmp_cmd->rdrct_final + i)));
		tmp_lst = tmp_lst->next;
		i++;
	}
	return (0);
}

void	ft_quote_check(char *str, t_data *data, int *tab, int i)
{
	if (data->quote < 0 && data->dquote < 0)
	{
		if (*(str + i) == '\'')
		{
			data->quote = -data->quote;
			tab[i] = 1;
		}
		else if (*(str + i) == '\"')
		{
			data->dquote = -data->dquote;
			tab[i] = 1;
		}
	}
	else if (data->quote > 0 && *(str + i) == '\'')
	{
		data->quote = -data->quote;
		tab[i] = 1;
	}
	else if (data->dquote > 0 && *(str + i) == '\"')
	{
		data->dquote = -data->dquote;
		tab[i] = 1;
	}
}

int	ft_quote_fill(char *str, t_data *data, int *tab, char **final)
{
	int		i;
	int		j;

	i = 0;
	while (tab[i])
		if (tab[i++] < 0)
			data->size++;
	*final = malloc(sizeof(char) * (data->size + 2));
	if (!*final)
		return (-1);
	i = 0;
	j = 0;
	while (*(str + i))
	{
		if (tab[i] < 0)
			(*final)[j++] = *(str + i);
		i++;
	}
	(*final)[j] = '\0';
	return (0);
}

int	ft_quote_loop(char *str, char **final)
{
	int		i;
	size_t	len_str;
	int		*tab;
	t_data	data;

	i = 0;
	if (!str)
		return (-1);
	ft_memset(&data, -1, sizeof(t_data));
	len_str = ft_strlen(str);
	tab = malloc(sizeof(int) * (len_str + 1));
	if (!tab)
		return (-1);
	ft_memset(tab, -1, sizeof(int) * (len_str + 1));
	while (*(str + i))
	{
		ft_quote_check(str, &data, tab, i);
		i++;
	}
	tab[i] = 0;
	if (ft_quote_fill(str, &data, tab, final))
		return (free(tab), -1);
	free(tab);
	return (0);
}

void	ft_quotehandler(t_cmd **cmds)
{
	t_cmd	*tmp_cmd;
	int		i;

	tmp_cmd = *cmds;
	while (tmp_cmd)
	{
		i = -1;
		while (*(tmp_cmd->cmd + ++i))
			ft_quote_loop(*(tmp_cmd->cmd + i), (tmp_cmd->final + i));
		*(tmp_cmd->final + i) = NULL;
		if (tmp_cmd->rdrct)
		{
			i = -1;
			while (*(tmp_cmd->rdrct + ++i))
				ft_quote_loop(*(tmp_cmd->rdrct + i),
					(tmp_cmd->rdrct_final + i));
			*(tmp_cmd->rdrct_final + i) = NULL;
			ft_quote_rdrct(tmp_cmd);
		}
		tmp_cmd = tmp_cmd->next;
	}
}

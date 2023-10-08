/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tkn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:03:28 by psan              #+#    #+#             */
/*   Updated: 2023/09/18 14:56:21 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_tknsize_quote(char *line, char c)
{
	int	j;
	int	k;

	j = 1;
	k = 0;
	while (*(line + j) && line[j] != c)
		j++;
	if (*(line + j) != c)
		return (-1);
	else
		j++;
	j += ft_tknsize_str(line + j);
	if (*(line + j) == '\'' || *(line + j) == '\"')
		k = ft_tknsize_quote(line + j, *(line + j));
	if (k == -1)
		return (-1);
	return (j + k);
}

int	ft_tknsize_str(char *line)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (*(line + j) && line[j] != ' ' && line[j] != '|'
		&& line[j] != '\'' && line[j] != '\"'
		&& line[j] != '<' && line[j] != '>')
		j++;
	if (*(line + j) == '\'' || *(line + j) == '\"')
		k = ft_tknsize_quote(line + j, *(line + j));
	if (k == -1)
		return (-1);
	return (j + k);
}

int	ft_tknsize(char *line)
{
	if (!line || ft_whitespace(*line))
		return (0);
	if (*line == '\'' || *line == '\"')
		return (ft_tknsize_quote(line, *line));
	else if (*line == '<')
	{
		if (*(line + 1) == '<')
			return (2);
		return (1);
	}
	else if (*line == '>')
	{
		if (*(line + 1) == '>')
			return (2);
		return (1);
	}
	else if (*line == '|')
		return (1);
	return (ft_tknsize_str(line));
}

t_tkn	**ft_tkncreate(char *line)
{
	int		i;
	int		j;
	t_tkn	**tokens;

	if (!line)
		return (0);
	i = 0;
	tokens = (t_tkn **)malloc(sizeof(t_tkn *));
	if (!tokens)
		return (0);
	*tokens = NULL;
	while (*(line + i))
	{
		j = ft_tknsize(line + i);
		if (j == -1)
			return (ft_printf(2, "open quotes\n"), ft_tknclear(tokens), NULL);
		else if (j)
		{
			ft_tknadd_back(tokens, ft_tknnew(ft_strndup(line + i, j), 0));
			i += j;
		}
		else
			i++;
	}
	return (tokens);
}

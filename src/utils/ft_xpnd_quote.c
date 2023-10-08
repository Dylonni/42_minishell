/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xpnd_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psan <psan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:36:12 by daumis            #+#    #+#             */
/*   Updated: 2023/09/26 16:23:11 by psan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_xpnd_quote(char *str, t_data *data, int i)
{
	char	c;

	if (data->quote > 0)
	{
		if (*(str + i) == '\'')
			data->quote = -data->quote;
	}
	else if (data->dquote < 0)
	{
		if (*(str + i) == '\'')
			data->quote = -data->quote;
		else if (*(str + i) == '$')
		{
			c = *(str + i + 1);
			if (c && (ft_isalnum(c) || c == '?' || c == '_'))
				return (i);
		}
	}
	return (-1);
}

int	ft_xpnd_dquote_bis(char *str, t_data *data, int i)
{
	char	c;

	if (*(str + i) == '\"')
		data->dquote = -data->dquote;
	else if (*(str + i) == '$')
	{
		c = *(str + i + 1);
		if (c && (ft_isalnum(c) || c == '?' || c == '_'))
			return (i);
		else if (c && (c == '\'' || c == '\"'))
			return (i);
	}
	return (-1);
}

int	ft_xpnd_dquote(char *str, t_data *data, int i)
{
	char	c;

	if (data->dquote > 0)
	{
		if (*(str + i) == '\"')
			data->dquote = -data->dquote;
		else if (*(str + i) == '$')
		{
			c = *(str + i + 1);
			if (c && (ft_isalnum(c) || c == '?' || c == '_'))
				return (i);
		}
	}
	else if (data->quote < 0)
		return (ft_xpnd_dquote_bis(str, data, i));
	return (-1);
}

int	ft_xpnd_check(char *str, t_data *data)
{
	int		i;

	i = 0;
	if (!str)
		return (-1);
	while (*(str + i))
	{
		if (ft_xpnd_quote(str, data, i) != -1)
			return (i);
		if (ft_xpnd_dquote(str, data, i) != -1)
			return (i);
		i++;
	}
	return (-1);
}

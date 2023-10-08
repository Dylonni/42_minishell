/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xpnd_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psan <psan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:31:57 by daumis            #+#    #+#             */
/*   Updated: 2023/09/26 16:26:35 by psan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_xpnd_index(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (-1);
	if (*(str + i) == '?')
		return (-2);
	if (ft_isdigit(*(str + i)))
		return (i);
	while (*(str + i) && (ft_isalnum(*(str + i)) || *(str + i) == '_'))
		i++;
	return (--i);
}

char	*ft_findvalue(char *target, t_var **env)
{
	t_var	*tmp;

	if (!target || !env)
		return (NULL);
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(target, tmp->key, ft_strlen(target)) == 0
			&& ft_strlen(target) == ft_strlen(tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_var	*ft_findkey(char *target, t_var **env)
{
	t_var	*tmp;

	if (!target || !env)
		return (NULL);
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(target, tmp->key, ft_strlen(target)) == 0
			&& ft_strlen(target) == ft_strlen(tmp->key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_xpnd_value_next(char **cmd, char *str, t_var **env, t_data *data)
{
	data->size = ft_xpnd_index(str + data->index_prev + data->index);
	if (data->size == -2)
	{
		data->err = ft_itoa(g_error);
		*cmd = ft_strjoin(*cmd, data->err);
		free(data->err);
		data->size = 1;
	}
	else if (data->index != 0)
	{
		data->cpy = ft_strndup(str + data->index_prev, data->index);
		*cmd = ft_strjoin(*cmd, data->cpy);
		free(data->cpy);
	}
	data->cpy = ft_strndup(str + data->index_prev + data->index + 1,
			data->size);
	*cmd = ft_strjoin(*cmd, ft_findvalue(data->cpy, env));
	free(data->cpy);
}

void	ft_xpnd_value_first(char **cmd, char *str, t_var **env, t_data *data)
{
	data->size = ft_xpnd_index(str + data->index);
	if (data->size == -2)
	{
		data->err = ft_itoa(g_error);
		*cmd = ft_strjoin(ft_strndup(str, data->index), data->err);
		free(data->err);
		data->size = 1;
	}
	else
	{
		data->cpy = ft_strndup(str + data->index + 1, data->size);
		*cmd = ft_strjoin(ft_strndup(str, data->index),
				ft_findvalue(data->cpy, env));
		free(data->cpy);
	}
	data->index_prev = data->index + data->size + 1;
}

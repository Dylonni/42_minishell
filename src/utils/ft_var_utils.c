/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:49:07 by daumis            #+#    #+#             */
/*   Updated: 2023/09/20 10:02:30 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_var	*ft_varnew(char *key, char *value)
{
	t_var	*tmp;

	tmp = (t_var *)malloc(sizeof(t_var));
	if (!tmp)
		return (0);
	tmp->key = key;
	tmp->value = value;
	tmp->next = NULL;
	return (tmp);
}

void	ft_varadd_back(t_var **lst, t_var *new)
{
	t_var	*tmp;

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

void	ft_varremove(t_var **lst, t_var *old)
{
	t_var	*cpy;
	t_var	*old_prev;
	t_var	*old_next;

	if (!lst || !old || !*lst)
		return ;
	old_next = old->next;
	old->next = NULL;
	old_prev = NULL;
	cpy = *lst;
	if (cpy->next)
	{
		old_prev = cpy;
		while (old_prev->next->next)
			old_prev = old_prev->next;
		old_prev->next = old_next;
	}
	else
		*lst = NULL;
	if (old == cpy)
		*lst = old_next;
	free(old->key);
	free(old->value);
	free(old);
}

void	ft_varprint_bis(t_var *tmp_var, int is_env)
{
	if (is_env)
	{
		if (!(ft_strncmp(".bs", tmp_var->key, 3) == 0
				&& ft_strlen(tmp_var->key) == 3)
			&& !(ft_strncmp("UID", tmp_var->key, 3) == 0
				&& ft_strlen(tmp_var->key) == 3))
		{
			if (!tmp_var->value)
				ft_printf(1, "%s\n", tmp_var->key);
			else
				ft_printf(1, "%s=%s\n", tmp_var->key, tmp_var->value);
		}
	}
	else
	{
		if (!tmp_var->value)
			ft_printf(1, "export %s\n", tmp_var->key);
		else
			ft_printf(1, "export %s=\"%s\"\n", tmp_var->key, tmp_var->value);
	}
}

void	ft_varprint(t_var **env_cpy, int is_env)
{
	t_var	*tmp_var;

	g_error = 0;
	if (!env_cpy || !*env_cpy)
		return ;
	tmp_var = (*env_cpy);
	while (tmp_var)
	{
		ft_varprint_bis(tmp_var, is_env);
		tmp_var = tmp_var->next;
	}
}

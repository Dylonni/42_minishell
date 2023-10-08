/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tkn_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:03:28 by psan              #+#    #+#             */
/*   Updated: 2023/09/20 10:02:49 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tkn	*ft_tknnew(char *str, int type)
{
	t_tkn	*tmp;

	tmp = (t_tkn *)malloc(sizeof(t_tkn));
	if (!tmp)
		return (0);
	tmp->str = str;
	tmp->rtype = type;
	tmp->next = NULL;
	return (tmp);
}

void	ft_tknadd_back(t_tkn **lst, t_tkn *new)
{
	t_tkn	*tmp;

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

void	ft_tknclear(t_tkn **lst)
{
	t_tkn	**lst_init;
	t_tkn	*tmp;

	if (!lst)
		return ;
	lst_init = lst;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->str);
		free(tmp);
	}
	*lst_init = NULL;
	free(lst);
}

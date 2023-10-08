/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkstat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:18:03 by daumis            #+#    #+#             */
/*   Updated: 2023/09/19 15:23:41 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_stat(char *path)
{
	struct stat	path_stat;

	if (!path)
		return (0);
	ft_memset(&path_stat, 0, sizeof(struct stat));
	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	if (S_ISREG(path_stat.st_mode))
		return (2);
	return (0);
}

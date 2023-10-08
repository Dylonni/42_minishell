/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psan <psan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:52:06 by daumis            #+#    #+#             */
/*   Updated: 2023/09/27 15:40:43 by psan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_atoll_check_bis(char *s, int *i, long long *res)
{
	int	size;

	size = 0;
	while (ft_isdigit(s[*i]))
	{
		*res = *res * 10 + (s[*i] - '0');
		*i += 1;
		size++;
		if (size == 18)
			break ;
	}
	return (size);
}

int	ft_atoll_check(char *s, int *i, long long *res, int sign)
{
	int			size;

	size = 0;
	while (ft_isdigit(s[*i + size]))
		size++;
	if (size > 19)
		return (1);
	size = ft_atoll_check_bis(s, i, res);
	if (size < 18)
		return (*res = (sign * *res), 0);
	if (*res > 922337203685477580)
		return (1);
	if (*res == 922337203685477580)
		if ((sign < 0 && (s[*i] - '0') > 8) || (sign > 0 && (s[*i] - '0') > 7))
			return (*res = (sign * *res), 1);
	if (ft_isdigit(s[*i]))
	{
		*res = (sign * *res) * 10 + sign * (s[*i] - '0');
		*i += 1;
	}
	return (0);
}

long long	ft_atoll(char *s)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_whitespace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (ft_atoll_check(s, &i, &res, sign))
		return (g_error = -1, 0);
	while (ft_whitespace(s[i]))
		i++;
	if ((size_t)i != ft_strlen(s))
		return (g_error = -1, 0);
	return (res);
}

void	ft_exit(char **args)
{
	int			i;
	long long	n;

	i = 0;
	if (!args || !*args)
		return (g_error = 0, (void)0);
	while (*(args + i))
		i++;
	n = ft_atoll(*args);
	if (g_error == -1)
		return (ft_throw_err(*args, 10), (void)0);
	if (i > 1)
		return (g_error = 1, ft_throw_err("", 3), (void)0);
	g_error = n % 256;
	if (g_error < 0)
		g_error += 256;
}

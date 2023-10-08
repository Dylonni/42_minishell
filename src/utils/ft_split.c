/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:09:47 by daumis            #+#    #+#             */
/*   Updated: 2023/09/19 12:02:45 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strs_cnt(const char *str, char delimiter)
{
	int	i;
	int	j;
	int	strs_cnt;

	i = 0;
	strs_cnt = 0;
	while (str[i])
	{
		j = i;
		while (!(str[i] == delimiter) && str[i])
			i++;
		if (i != j)
			strs_cnt++;
		else
			i++;
	}
	return (strs_cnt);
}

void	ft_str_len_tab(const char *str, char delimiter, int *strl_tab)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		j = i;
		while (!(str[i] == delimiter) && str[i])
			i++;
		if (i != j)
		{
			strl_tab[k] = i - j;
			k++;
		}
		else
			i++;
	}	
}

char	**ft_fill_strs(const char *str, char delimiter,
			int *nbr, int *str_len_tab)
{
	char	**strs;

	strs = malloc((nbr[0] + 1) * sizeof(char *));
	if (!strs)
		return (0);
	while (nbr[3] < nbr[0])
	{
		strs[nbr[3]] = malloc((str_len_tab[nbr[3]] + 1) * sizeof(char));
		if (!strs[nbr[3]])
			return (ft_clearall(strs, nbr), NULL);
		while ((str[nbr[1]] == delimiter) && str[nbr[1]])
			nbr[1]++;
		nbr[2] = nbr[1];
		while (!(str[nbr[1]] == delimiter) && str[nbr[1]])
		{
			strs[nbr[3]][nbr[1] - nbr[2]] = str[nbr[1]];
			nbr[1]++;
		}
		strs[nbr[3]][nbr[1] - nbr[2]] = '\0';
		nbr[3]++;
	}
	strs[nbr[3]] = 0;
	return (strs);
}

void	ft_clearall(char **strs, int *nbr)
{
	if (!strs)
		return ;
	if (!nbr)
		return (free(strs), (void)0);
	while (nbr[3] > 0)
	{
		free(strs[nbr[3]]);
		nbr[3]--;
	}
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	int		nbr[4];
	char	**strs;
	int		*str_len_tab;

	if (!s)
		return (0);
	nbr[0] = ft_strs_cnt(s, c);
	str_len_tab = malloc((nbr[0] + 1) * sizeof(int));
	if (!str_len_tab)
		return (0);
	ft_memset(str_len_tab, 0, sizeof(int *));
	ft_str_len_tab(s, c, str_len_tab);
	nbr[1] = 0;
	nbr[3] = 0;
	strs = ft_fill_strs(s, c, nbr, str_len_tab);
	free(str_len_tab);
	if (!strs)
	{
		ft_clearall(strs, nbr);
		return (0);
	}
	return (strs);
}

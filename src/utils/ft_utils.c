/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:03:28 by psan              #+#    #+#             */
/*   Updated: 2023/09/19 12:05:10 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_whitespace(char c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

//Refactoriser pour comparer aussi les tailles et return 0 ou 1
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < n && (*s1 || *s2))
	{
		if ((unsigned char) *s1 != (unsigned char) *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
		i++;
	}
	return (0);
}

char	*ft_strndup(const char *s, int len)
{
	char	*dest;
	int		i;

	dest = (char *)malloc((len + 1) * sizeof(const char));
	if (!dest)
		return (0);
	i = 0;
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	int		k;
	char	*ptr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *) malloc(s1_len + s2_len + 1);
	if (!ptr)
		return (0);
	k = 0;
	while (k < (s1_len + s2_len))
	{
		if (s1_len && k < s1_len)
			ptr[k] = s1[k];
		else
			ptr[k] = s2[k - s1_len];
		k++;
	}
	ptr[k] = '\0';
	free(s1);
	return (ptr);
}

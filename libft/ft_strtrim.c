/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:34:39 by mshargan          #+#    #+#             */
/*   Updated: 2025/12/05 17:28:22 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	trim_check(char const c, char const *set)
{
	int	i;

	if (!set)
		return (0);
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	trim_str_len(char const *s1, char const *set)
{
	size_t		len;
	size_t		i;
	size_t		j;

	len = ft_strlen(s1);
	i = 0;
	j = len - 1;
	while (s1[i])
	{
		if (!trim_check(s1[i], set))
			break ;
		len--;
		i++;
	}
	while (i < j)
	{
		if (!trim_check(s1[j], set))
			break ;
		len--;
		j--;
	}
	return ((int)len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*res;
	int		i;

	len = trim_str_len(s1, set);
	res = malloc (sizeof (char) * (len + 1));
	if (!res)
		return (0);
	while (trim_check(*s1, set))
		s1++;
	i = 0;
	while (i < len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	s1[] = "   ... .abcd.. . . ";
// 	printf("%s", ft_strtrim(s1, ". "));
// 	return (0);
// }

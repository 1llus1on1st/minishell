/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:53:42 by mshargan          #+#    #+#             */
/*   Updated: 2026/02/11 20:19:07 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/* Retourne le nombre d'array a creer */

static int	ft_count_words(char const *s, char c)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	if (s[i] != c && s[i])
		res++;
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c && i != 0)
			res++;
		i++;
	}
	return (res);
}

/* Retourne le nombre de char dans l'array actuel */

static int	ft_count_char(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len])
	{
		len++;
	}
	return (len);
}

/*	Si cas1 retourne le compteur i en ayant skip le(s) delimiter
	Si cas2 free les mallocs des strings + le array de string et retourne 0*/

static int	ft_free(char **res, int a)
{
	int	i;

	i = 0;
	while (i <= a)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (0);
}

static int	ft_dup(char const *s, char c, char *res)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		a;
	int		i;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!res)
		return (0);
	res[ft_count_words(s, c)] = 0;
	a = 0;
	i = 0;
	while (a < ft_count_words(s, c))
	{
		while (s[i] == c)
			i++;
		res[a] = malloc(sizeof(char) * (ft_count_char(&(s[i]), c) + 1));
		if (!res[a])
			return (ft_free(res, a), NULL);
		res[a][ft_count_char(&s[i], c)] = 0;
		i += ft_dup(&(s[i]), c, &(res[a][0]));
		a++;
	}
	return (res);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	s[] = "   hello how are you ?  ";
// 	char	**res = ft_split(s, ' ');
// 	int		i;

// 	i = 0;
// 	if (res)
// 	{
// 		while (res[i])
// 		{
// 			printf("%s\n", res[i]);
// 			i++;
// 		}
// 	}
// 	return (0);
// }

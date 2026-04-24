/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:13:42 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/24 15:08:23 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*big_start(void)
{
	char	*res;

	res = malloc(1);
	if (!res)
		return (0);
	res[0] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	size;
	char			*res;

	if (!s)
		return (NULL);
	size = 0;
	if (start > (unsigned int)ft_strlen(s))
		return (big_start());
	while (s[start + size])
		size++;
	if (len < size)
		size = len;
	res = malloc (sizeof(char) * (size + 1));
	if (!res)
		return (0);
	size = 0;
	while (s[start + size] && size < len)
	{
		res[size] = s[start + size];
		size++;
	}
	res[size] = '\0';
	return (res);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char const	s[] = "lorem ipsum dolor sit amet";
// 	char 		*res = ft_substr(s, 0, 10);
// 	printf("%s", res);
// 	return (0);
// }
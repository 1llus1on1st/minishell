/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:34 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/20 16:28:38 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*res;

	res = 0;
	while (*s)
	{
		if (*s == (char)c)
			res = s;
		s++;
	}
	if (*s == (char)c)
		res = s;
	return ((char *)res);
}

// #include <stdio.h>
// #include <string.h>

// int	main()
// {
// 	char	c;
// 	char	s[] = "hello you";

// 	c = 'e';
// 	printf("%s\n", strrchr(s, c));
// 	printf("%s\n", ft_strrchr(s, c));
// 	printf("\n\n\n");

// 	c = 'l';
// 	printf("%s\n", strrchr(s, c));
// 	printf("%s\n", ft_strrchr(s, c));
// 	printf("\n\n\n");

// 	c = 'a';
// 	printf("%s\n", strrchr(s, c));
// 	printf("%s\n", ft_strrchr(s, c));
// 	printf("\n\n\n");

// 	c = '\0';
// 	printf("%s\n", strrchr(s, c));
// 	printf("%s\n", ft_strrchr(s, c));
// }
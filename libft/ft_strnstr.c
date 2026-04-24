/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:09:19 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/24 15:08:11 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <bsd/string.h>

#include "libft.h"

static int	little_checker(const char *big, const char *little, size_t len,
		const char **res)
{
	*res = big;
	while (*big == *little && *big && *little && len > 0)
	{
		big++;
		little++;
		len--;
	}
	if (*little == '\0')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char		*res;
	const char		*lit;

	if (!little)
		return (NULL);
	lit = little;
	if (*little == 0)
		return ((char *)big);
	if (*big == 0)
		return ((char *)0);
	while (len > 0)
	{
		res = 0;
		if (little_checker(big, little, len, &res))
			return ((char *)res);
		little = lit;
		big++;
		len--;
	}
	return ((char *)0);
}

// int	main()
// {
// 	char	big[] = "hello how are you doing today?";
// 	char	little[] = "sir";

// 	printf("%s\n", strnstr(big, little, 3));
// 	printf("%s\n", ft_strnstr(big, little, 3));
// }

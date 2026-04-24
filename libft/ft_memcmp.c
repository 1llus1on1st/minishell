/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:54:03 by mshargan          #+#    #+#             */
/*   Updated: 2025/12/05 17:27:59 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	while ((n - 1) > 0)
	{
		if (*((unsigned char *)(s1)) != *((unsigned char *)(s2)))
			return (*((unsigned char *)(s1)) - *((unsigned char *)(s2)));
		s1++;
		s2++;
		n--;
	}
	return (*((unsigned char *)(s1)) - *((unsigned char *)(s2)));
}

// #include <stdio.h>

// int	main()
// {
// 	char	s1[] = "abcdefghij";
// 	char	s2[] = "abcdefgxyz";

// 	printf("%d\n", memcmp(s1, s2, 7));
// 	printf("%d", ft_memcmp(s1, s2, 7));
// }

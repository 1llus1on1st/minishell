/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:36:58 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/20 16:28:01 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <bsd/string.h>

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	src_dim;

	i = 0;
	src_dim = 0;
	while (src[src_dim])
		src_dim++;
	if (size == 0)
		return (src_dim);
	while (src[i] && (i + 1) < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_dim);
}

// int		main(void)
// {
// 	char	src[] = "coucou";
// 	char	dst[] = "AAAAAAAAAA";
// 	printf("%d", (int)ft_strlcpy(dst, src, 2));
// 	printf("%d", (int)strlcpy(dst, src, 2));
// 	printf("%s", dst);

// 	// printf("%s %s\n", src, dst);
// }

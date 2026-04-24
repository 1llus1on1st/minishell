/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:19:56 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/20 16:28:14 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <bsd/string.h>

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	dst_dim;
	unsigned int	src_dim;
	unsigned int	i;

	dst_dim = 0;
	src_dim = 0;
	i = 0;
	while (dst[dst_dim] && dst_dim < size)
		dst_dim++;
	while (src[src_dim])
		src_dim++;
	if (dst_dim == size)
		return (dst_dim + src_dim);
	while (src[i] && (dst_dim + i + 1) < size)
	{
		dst[dst_dim + i] = src[i];
		i++;
	}
	if (dst_dim + i < size)
		dst[dst_dim + i] = '\0';
	return (dst_dim + src_dim);
}

// int	main(void)
// {
// 	char	src[] = " you there";
// 	char	dst[9] = "hello";
// 	printf("%zu", strlcat(dst, src, 5));
// 	printf("%s", dst);
// 	printf("\n");
// 	char	srce[] = " you there";
// 	char	dest[9] = "hello";
// 	printf("%zu", ft_strlcat(dest, srce, 5));
// 	printf("%s", dest);
// }
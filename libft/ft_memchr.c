/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:34:16 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/20 16:28:59 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t size)
{
	const unsigned char	*temp;

	temp = s;
	while (size > 0)
	{
		if (*temp == (unsigned char)c)
			return ((void *)temp);
		temp++;
		size--;
	}
	return (0);
}
// #include <stdio.h>

// int	main()
// {
// 	char	s[] = "hello you";
// 	char	c = 'o';

// 	printf("%s\n", (char *)memchr(s, c, 7));
// 	printf("%s\n", (char *)ft_memchr(s, c, 7));
// }

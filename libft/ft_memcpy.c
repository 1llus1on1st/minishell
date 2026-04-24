/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:42:43 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/20 16:08:46 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*src_t;
	unsigned char	*dest_t;
	long unsigned	i;

	src_t = (unsigned char *)src;
	dest_t = (unsigned char *)dest;
	if (!dest_t && !src_t)
		return (0);
	if (n == 0 || dest == src)
		return (dest);
	i = 0;
	while (i < n)
	{
		dest_t[i] = src_t[i];
		i++;
	}
	return (dest);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main() {

//     int array [] = { 54, 85, 20, 63, 21 };
//     int * copy = NULL;
//     int length = sizeof( int ) * 5;

//     // Memory allocation and copy
//     copy = (int *) malloc( length );
//     ft_memcpy( copy, array, length );

//     // Display the copied values
//     for( length=0; length<5; length++ ) {
//         printf( "%d ", copy[ length ] );
//     }
//     printf( "\n" );

//     free( copy );

//     return (0);
// }
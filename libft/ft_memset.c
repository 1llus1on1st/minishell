/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:34:47 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/20 16:27:52 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*res;

	res = (unsigned char *)s;
	while (n > 0)
	{
		*res = (unsigned char)c;
		n--;
		res++;
	}
	return (s);
}

// #include<string.h>
// #include<stdio.h>

// int main()
// {

//     int array [] = { 54, 85, 20, 63, 21 };
//     size_t size = sizeof( int ) * 5;
//     int length;

//     // Display the initial values
//     for( length=0; length<5; length++) {
//         printf( "%d ", array[ length ] );
//     }
//     printf( "\n" );

//     // Reset the memory bloc
//     ft_memset( array, 0, size );

//     // Display the new values
//     for( length=0; length<5; length++) {
//         printf( "%d ", array[ length ] );
//     }
//     printf( "\n" );

//     return 0;
// }

// int main()
// {

//     char array [] = { 'h', 'f', 'f', 'h', 'h' };
//     size_t size = sizeof(char) * 5;
//     int length;

//     // Display the initial values
//     for( length=0; length<5; length++) {
//         printf( "%c ", array[ length ] );
//     }
//     printf( "\n" );

//     // Reset the memory bloc
//     ft_memset( array, 'x', size );

//     // Display the new values
//     for( length=0; length<5; length++) {
//         printf( "%c ", array[ length ] );
//     }
//     printf( "\n" );

//     return 0;
// }

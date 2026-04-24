/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:02:11 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/18 12:12:41 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*src_t;
	unsigned char	*dest_t;

	if (!dest && !src)
		return (NULL);
	src_t = (unsigned char *) src;
	dest_t = (unsigned char *) dest;
	if (n == 0)
		return (dest);
	if (src_t > dest_t)
	{
		while (n-- > 0)
			*dest_t++ = *src_t++;
	}
	else
	{
		dest_t += n - 1;
		src_t += n - 1;
		while (n-- > 0)
			*dest_t-- = *src_t--;
	}
	return (dest);
}

// #include <stdio.h>
// #include <stdlib.h>

// #define ELEMENT_COUNT 10

// int main() {

//     // On crée une zone de mémoire de 10 entiers et contenant
//     // que neuf valeurs. La dixième est non utilisée (0).
//     int data[] = {20,30,40,50,60,70,80,90,100,0};

//     // On affiche le contenu de la collection
//     for( int i=0; i<ELEMENT_COUNT; i++ ) {
//         printf( "%d ", data[i] );
//     }
//     puts( "" );  // Un retour à la ligne

//     // On décale les éléménts dans la collection ...
//     void *source = (void *) data;
//     void * destination = (void *) ( data + 1);
//     size_t size = ELEMENT_COUNT * sizeof( int );
// 	// printf("%ld", size);
//     ft_memmove( destination, source, size );

//     // ... pour y insérer une nouvelle valeur en tête
//     data[0] = 10;

//     // On affiche le contenu de la collection
//     for( int i=0; i<ELEMENT_COUNT; i++ ) {
//         printf( "%d ", data[i] );
//     }
//     puts( "" );  // Un retour à la ligne

//     return (0);
// }

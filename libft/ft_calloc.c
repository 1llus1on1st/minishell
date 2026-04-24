/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:52:44 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/13 15:10:43 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char				*res;
	unsigned long		i;

	i = 0;
	if (nmemb > 0 && (SIZE_MAX / nmemb) < size)
		return (0);
	res = malloc(nmemb * size);
	if (!res)
		return (0);
	while (i < (nmemb * size))
	{
		*(res + i) = 0;
		i++;
	}
	return (res);
}
// #include <stdio.h>          
// #include <assert.h>

// #define INT_NUMBER 10

// int main() 
// {
//     int i;
//     int * pointer = (int *) calloc( INT_NUMBER, sizeof(int) );

//     /* Un petit test sur le bon fonctionnement de calloc */
//     assert( pointer != NULL );

// 	/* On verifie que chaque element du tableau a ete initialise a 0 */ 
// 	for (i=0; i<INT_NUMBER; i++ ) {
//         printf( "%d ", pointer[i] );
//     }
//     printf( "\n" );

//     /* Le dernier élément du tableau ne sera pas affecté par la */
//     /* boucle mais n'oubliez pas que calloc initialise de toute */
//     /* façon à 0 chaque octet. */
//     for ( i=0; i<INT_NUMBER-1; i++ ) {
//         pointer[i] = i;
//     }

//     /* On affiche le contenu du tableau d'entier */
//     /* Ce qui donne : 0 1 2 3 4 5 6 7 8 0 */
//     for (i=0; i<INT_NUMBER; i++ ) {
//         printf( "%d ", pointer[i] );
//     }
//     printf( "\n" );

//     /* On libère le bloc de mémoire alloué dynamiquement */
//     free( pointer );

//     return 0;
// }

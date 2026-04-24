/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:27:58 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/20 16:29:08 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		len;
	char	*res;

	len = 0;
	while (s[len])
		len++;
	res = malloc (sizeof(char) * (len + 1));
	if (!res)
		return (0);
	len = 0;
	while (s[len])
	{
		res[len] = s[len];
		len++;
	}
	res[len] = '\0';
	return (res);
}

// #include <ctype.h>
// #include <stdio.h>
// #include <string.h>

// int main() {

//     const char * original = "The original string.";

// 	// On affiche la chaîne initiale
//     printf( "%s\n", original );

//     // On duplique la chaîne de caractères initiale.
//     char * copy = ft_strdup( original );

//     // On passe chaque lettre en majuscule.
//     char * ptr = copy;
//     while( *ptr != '\0' ) {
//         *ptr = toupper( *ptr );
//         ptr++;
//     }

//     // On affiche la chaîne finale
//     printf( "%s\n", copy );

//     // Sans oublier de libérer l'espace mémoire au final.
//     free( copy );

//     return (0);
// }

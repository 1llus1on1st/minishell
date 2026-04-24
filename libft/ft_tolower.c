/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:42:30 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/12 11:17:36 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	else
		return (c);
}

// int	main()
// {
// 	printf("%c ", ft_tolower('c'));
// 	printf("%c", tolower('c'));
// 	printf("\n");
// 	printf("%c ", ft_tolower('G'));
// 	printf("%c", tolower('G'));
// 	printf("\n");
// 	printf("%c ", ft_tolower('%'));
// 	printf("%c", tolower('%'));
// }
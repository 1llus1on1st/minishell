/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:30:22 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/12 11:17:36 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	else
		return (c);
}

// int	main()
// {
// 	printf("%c ", ft_toupper('c'));
// 	printf("%c", toupper('c'));
// 	printf("\n");
// 	printf("%c ", ft_toupper('G'));
// 	printf("%c", toupper('G'));
// 	printf("\n");
// 	printf("%c ", ft_toupper('%'));
// 	printf("%c", toupper('%'));
// }
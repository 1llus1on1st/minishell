/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:26:31 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/20 15:55:53 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_f(unsigned int i, char *c)
// {
// 	*c += i;
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
	return ;
}

// #include <stdio.h>

// int	main(void)
// {
// 	char s[] = "abcd";
// 	printf("%s\n", s);
// 	ft_striteri(s, ft_f);
// 	printf("%s", s);
// 	return (0);
// }
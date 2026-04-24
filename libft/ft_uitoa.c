/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:11:34 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/26 19:17:28 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*zero(void)
{
	char	*res;

	res = malloc(sizeof(char) * (1 + 1));
	if (!res)
		return (0);
	return (ft_memcpy(res, "0", 2));
}

static int	dimension(long num)
{
	if (num < 10)
		return (1);
	else
	{
		return (dimension(num / 10) + 1);
	}
}

static char	*initializer(int *dim, unsigned int *n)
{
	char	*res;

	*dim += dimension(*n);
	res = malloc(sizeof(char) * (*dim + 1));
	if (!res)
		return (0);
	res[*dim] = '\0';
	(*dim)--;
	return (res);
}

char	*ft_uitoa(unsigned int n)
{
	char			*res;
	int				dim;
	int				i;

	dim = 0;
	if (n == 0)
		return (zero());
	res = initializer(&dim, &n);
	if (!res)
		return (0);
	i = 0;
	while (n > 0)
	{
		res[dim - i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	return (res);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s\n", ft_itoa(1));
// 	printf("%s\n", ft_itoa(0));
// 	printf("%s\n", ft_itoa(-1));
// 	printf("%s\n", ft_itoa(1234567));
// 	printf("%s\n", ft_itoa(2147483647));
// 	printf("%s\n", ft_itoa(-2147483648));
// 	return (0);
// }
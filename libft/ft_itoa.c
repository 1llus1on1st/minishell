/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:31:47 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/26 18:55:52 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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

static char	*initializer(int *dim, int n, unsigned int *num)
{
	char	*res;

	if (n < 0)
	{
		(*dim)++;
		*num = -n;
	}
	else
		*num = n;
	*dim += dimension(*num);
	res = malloc(sizeof(char) * (*dim + 1));
	if (!res)
		return (0);
	res[*dim] = '\0';
	(*dim)--;
	if (n < 0)
		res[0] = '-';
	return (res);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	num;
	int				dim;
	int				i;

	dim = 0;
	if (n == 0)
		return (zero());
	res = initializer(&dim, n, &num);
	if (!res)
		return (0);
	i = 0;
	while (num > 0)
	{
		res[dim - i] = (num % 10) + '0';
		num /= 10;
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
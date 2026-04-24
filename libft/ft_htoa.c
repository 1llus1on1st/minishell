/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:44:34 by mshargan          #+#    #+#             */
/*   Updated: 2025/12/04 14:34:05 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	hex_converter(int c)
{
	if (c < 10)
		return (c + '0');
	else
		return (c % 10 + 'a');
}

static char	*zero(void)
{
	char	*res;

	res = malloc(sizeof(char) * (1 + 1));
	if (!res)
		return (0);
	return (ft_memcpy(res, "0", 2));
}

static int	dimension(unsigned int num)
{
	if (num < 16)
		return (1);
	else
	{
		return (dimension(num / 16) + 1);
	}
}

static char	*initializer(int *dim, unsigned int n, unsigned int *num)
{
	char	*res;

	*num = n;
	*dim += dimension(*num);
	res = malloc(sizeof(char) * (*dim + 1));
	if (!res)
		return (0);
	res[*dim] = '\0';
	(*dim)--;
	return (res);
}

char	*ft_htoa(unsigned int n)
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
		res[dim - i] = hex_converter(num % 16);
		num /= 16;
		i++;
	}
	return (res);
}

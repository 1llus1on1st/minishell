/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:33:08 by mshargan          #+#    #+#             */
/*   Updated: 2025/12/01 11:15:45 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	hex_converter(int c)
{
	if (c < 10)
		return (c + '0');
	else
		return (c % 10 + 'a');
}

void	ft_puthex_fd(unsigned long long ptr, int fd)
{
	char	c;

	if (ptr < 16)
	{
		c = hex_converter(ptr);
		write(fd, &c, 1);
	}
	else
	{
		ft_puthex_fd(ptr / 16, fd);
		c = hex_converter(ptr % 16);
		write(fd, &c, 1);
	}
}

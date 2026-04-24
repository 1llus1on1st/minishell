/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:06:30 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/24 15:07:38 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static unsigned int	if_negative(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		return (-n);
	}
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	char			c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	num = if_negative(n, fd);
	if (num < 10)
	{
		c = num + '0';
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd((int)(num / 10), fd);
		c = num % 10 + '0';
		write(fd, &c, 1);
	}
	return ;
}

// int	main(void)
// {
// 	int	fd = 1;
// 	ft_putnbr_fd(1, fd);
// 	write(1, "\n", 1);
// 	ft_putnbr_fd(0, fd);
// 	write(1, "\n", 1);
// 	ft_putnbr_fd(-1, fd);
// 	write(1, "\n", 1);
// 	ft_putnbr_fd(1234567, fd);
// 	write(1, "\n", 1);
// 	ft_putnbr_fd(2147483647, fd);
// 	write(1, "\n", 1);
// 	ft_putnbr_fd(-2147483648, fd);
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_to_integer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:40:58 by mshargan          #+#    #+#             */
/*   Updated: 2025/12/05 18:06:20 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(va_list args)
{
	ft_putchar_fd((char)va_arg(args, int), 1);
	return (1);
}

int	print_string(va_list args)
{
	char	*s;
	int		len;

	s = va_arg(args, char *);
	if (!s)
		return (ft_putstr_fd("(null)", 1), 6);
	len = ft_strlen(s);
	ft_putstr_fd(s, 1);
	return (len);
}

int	print_pointer(va_list args)
{
	char				*ptr;
	unsigned long long	ptr_num;
	int					res;

	ptr = va_arg(args, void *);
	ptr_num = (unsigned long long)ptr;
	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	ft_puthex_fd(ptr_num, 1);
	res = 2;
	while (ptr_num != 0)
	{
		ptr_num /= 16;
		res++;
	}
	return (res);
}

int	print_integer(va_list args)
{
	char	*str_num;
	int		count;

	str_num = ft_itoa(va_arg(args, int));
	ft_putstr_fd(str_num, 1);
	count = ft_strlen(str_num);
	free(str_num);
	return (count);
}

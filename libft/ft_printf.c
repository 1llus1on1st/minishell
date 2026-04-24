/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:15:26 by mshargan          #+#    #+#             */
/*   Updated: 2026/01/09 22:05:29 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	success_case(const char **s, va_list args, t_conv_list *flags)
{
	int	count;

	count = 0;
	if (flags->character)
		count = print_char(args);
	else if (flags->string)
		count = print_string(args);
	else if (flags->pointer)
		count = print_pointer(args);
	else if (flags->decimal)
		count = print_integer(args);
	else if (flags->integer)
		count = print_integer(args);
	else if (flags->u_decimal)
		count = print_u_decimal(args);
	else if (flags->lower_hex)
		count = print_lower_hex(args);
	else if (flags->upper_hex)
		count = print_upper_hex(args);
	else if (flags->percent)
		count = print_percent();
	*s += 1;
	return (count);
}

void	flags_initializer(t_conv_list *flags)
{
	flags->conv = 0;
	flags->character = 0;
	flags->string = 0;
	flags->pointer = 0;
	flags->decimal = 0;
	flags->integer = 0;
	flags->u_decimal = 0;
	flags->lower_hex = 0;
	flags->upper_hex = 0;
	flags->percent = 0;
}

int	ft_printf(const char *s, ...)
{
	va_list		args;
	t_conv_list	flags;
	int			count;

	if (initial_check(s) != 1)
		return (initial_check(s));
	va_start(args, s);
	count = 0;
	while (*s)
	{
		if (percent_check(&s) && *(s + 1))
		{
			flags_initializer(&flags);
			if (conversion_check(s, &flags))
				count += success_case(&s, args, &flags);
		}
		else
		{
			ft_putchar_fd(*s, 1);
			count++;
		}
		s++;
	}
	va_end(args);
	return (count);
}

// #include <stdio.h>
// #include <float.h>

// int	main(void)
// {
// 	int 	count = 0;
	// char	character = '0';
	// char	*s = NULL;
	// char	*pointer = s;
	// int		i = -2147483648;
	// int		x = 0xffff;

	// //Test 01
	// count = ft_printf("Test #01: %c is character to print.\n", character);
	// count = ft_printf("%i\n\n", count);

	// //Test 02
	// count = ft_printf("Test #02: %s is string to print.\n", s);
	// count = ft_printf("%i\n\n", count);

	// count = printf("Test #02: %s is string to print.\n", s);
	// count = printf("%i\n\n", count);

	// // Test 03
	// count = ft_printf("Test #03: %p is pointer to print.\n", pointer);
	// count = ft_printf("%i\n\n", count);
	// count = printf("Test #03: %p is pointer to print.\n", pointer);
	// count = printf("%i\n\n", count);
	// // printf("Test #03: %p is pointer to print.\n", pointer);
	// // ft_printf("%i", ft_printf("%p", pointer));

	// // Test 04
	// count = ft_printf("Test #04: %d is decimal to print.\n", i);
	// count = ft_printf("%i\n\n", count);

	// // Test 05
	// count = ft_printf("Test #05: %i is integer to print.\n", i);
	// count = ft_printf("%i\n\n", count);

	// // Test 06
	// count = ft_printf("Test #06: %u is u decimal to print.\n", 4294967295);
	// count = ft_printf("%i\n\n", count);

	// // Test 07
	// count = ft_printf("Test #07: %x is lower hex to print.\n", x);
	// count = ft_printf("%i\n\n", count);
	// // count = printf("%x\n", x);
	// // count = ft_printf("%x\n", x);

	// // Test 08
	// count = ft_printf("Test #08: %X is upper hex to print.\n", x);
	// count = ft_printf("%i\n\n", count);

	// // Test 09
	// count = ft_printf("Test #09: %% is percent to print.\n", x);
	// count = ft_printf("%i\n\n", count);

	// count = ft_printf("Hello%");
	// count = ft_printf("%i\n", count);

	// count = ft_printf("");
	// count = ft_printf("%i\n", count);

	// count = ft_printf(NULL);
	// count = ft_printf("%i\n", count);

// 	count = ft_printf("%");
// 	count = ft_printf("%i\n", count);
// 	count = printf("%");
// 	count = printf("%i\n", count);
// 	return (0);
// }
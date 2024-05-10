/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ala_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <dmoroz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:08:10 by dmoroz            #+#    #+#             */
/*   Updated: 2024/05/10 14:08:10 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	size;

	size = 0;
	while (str[size])
		size++;
	return (size);
}

static int	ft_isspace(int c)
{
	if (c >= 9 && c <= 13)
		return (1);
	else if (c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*(str++) - '0') * sign;
	}
	return (res);
}

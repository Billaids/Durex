/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 14:13:28 by nidzik            #+#    #+#             */
/*   Updated: 2015/03/10 17:03:45 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int     ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    else
        return (0);
}

uint64_t				ft_atoi(const char *str)
{
	uint64_t				res;
	unsigned long long int	i;
	if (!str)
		return 0;
	i = 0;
	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' ||
				*str == '\r' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	if (strlen(str) > 20)
		return (0);
	while (ft_isdigit(*str) && *str != '\0')
	{
		i = (int)(*str - '0');
		res = (res * 10) + i;
		str++;
	}
	return (res);
}

int main(int ac, char **av)
{
	uint64_t gg = 0;
	gg = ft_atoi(av[1]);
	printf("%llu\n", gg);
	
}

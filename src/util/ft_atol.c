/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnespoli <bnespoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:57:27 by bnespoli          #+#    #+#             */
/*   Updated: 2025/01/21 16:57:28 by bnespoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

suseconds_t	ft_atol(const char *nptr)
{
	char		sign;
	suseconds_t	nb;

	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	sign = 0;
	if (*nptr == '+' || *nptr == '-')
		sign = *nptr++;
	nb = 0;
	while (*nptr >= '0' && *nptr <= '9')
		nb = (nb * 10) + *nptr++ - 48;
	if (sign == '-')
		nb = -nb;
	if (*nptr)
		return (-1);
	return (nb);
}

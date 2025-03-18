/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnespoli <bnespoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:57:43 by bnespoli          #+#    #+#             */
/*   Updated: 2025/01/21 16:57:45 by bnespoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	char	*p;

	if (!s || !*s)
		return ;
	p = s;
	while (*p)
		p++;
	(void) !write(fd, s, p - s);
}

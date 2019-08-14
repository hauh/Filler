/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:21:23 by smorty            #+#    #+#             */
/*   Updated: 2019/08/14 22:00:19 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	error(void)
{
	ft_putstr(strerror(errno));
	exit(-1);
}

int		main(void)
{
	t_filler	*bot;
	char		buf;

	while (1)
		if (read(0, &buf, 1) == 1)
		{
			bot = init();
			break ;
		}
//	while (1)
//		if (read(0, &buf, 1) == 1)
//		{
//			if (buf == '=')
//				break ;
			solve(bot);
//		}
	return (0);
}

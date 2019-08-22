/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:21:23 by smorty            #+#    #+#             */
/*   Updated: 2019/08/22 21:55:33 by smorty           ###   ########.fr       */
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
	t_filler		*bot;
	char			*buf;

	bot = NULL;
	while (1)
		if ((buf = read_input()))
		{
			if (!bot)
				bot = init_bot(buf);
			free(buf);
			solve(bot);
		}
	return (0);
}

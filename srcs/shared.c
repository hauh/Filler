/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 18:07:37 by smorty            #+#    #+#             */
/*   Updated: 2019/08/25 17:24:58 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "filler_visualizer.h"

void	error(const char *error_msg)
{
	if (error_msg)
		ft_putstr(error_msg);
	close(1);
	close(0);
	exit(-1);
}

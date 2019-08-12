/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:05:05 by smorty            #+#    #+#             */
/*   Updated: 2019/08/12 19:10:39 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static char	*output_line(char *tail, char *p)
{
	char *line;
	char *tail0;

	if (!(line = (char *)malloc(sizeof(char) * (p - tail + 1))))
		error();
	p = line;
	tail0 = tail;
	while (*tail && *tail != '\n')
		*p++ = *tail++;
	*p = 0;
	if (*tail)
		++tail;
	while (*tail)
		*tail0++ = *tail++;
	*tail0 = 0;
	return (line);
}

static char	*gnl(char **tail)
{
	char		buf[BUFF_SIZE + 1];
	char		*p;
	int			r;

	if ((r = read(0, buf, BUFF_SIZE)) < 0)
		error();
	if (r)
	{
		buf[r] = 0;
		p = *tail;
		if (!(*tail = ft_strjoin(*tail, buf)))
			error();
		free(p);
	}
	p = *tail;
	while (*p && *p != '\n')
		++p;
	if (*p)
		return (output_line(*tail, p));
	if (r)
		return (gnl(tail));
	return (NULL);
}

char		*read_input(void)
{
	static char	*tail = NULL;
	char		*new;

	if (!tail)
	{
		if (!(tail = (char *)malloc(sizeof(char))))
			error();
		*tail = 0;
	}
	if (!(new = gnl(&tail)))
	{
		free(tail);
		return (NULL);
	}
	return (new);
}

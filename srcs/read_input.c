/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:05:05 by smorty            #+#    #+#             */
/*   Updated: 2019/08/28 20:22:07 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_shared.h"

static char	*output_line(char *tail, char *p)
{
	char *line;
	char *tail0;

	if (!(line = (char *)malloc(sizeof(char) * (p - tail + 1))))
		error(strerror(errno));
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
	char	buf[BUFF_SIZE + 1];
	char	*p;
	int		r;

	if ((r = read(0, buf, BUFF_SIZE)) < 0)
		error(strerror(errno));
	if (!r && !**tail)
		return (NULL);
	buf[r] = 0;
	p = *tail;
	if (!(*tail = ft_strjoin(*tail, buf)))
		error(strerror(errno));
	free(p);
	p = *tail;
	while (*p && *p != '\n')
		++p;
	if (!*p && r)
		return (gnl(tail));
	return (output_line(*tail, p));
}

char		*read_input(void)
{
	static char	*tail = NULL;
	char		*new;

	if (!tail)
	{
		if (!(tail = (char *)malloc(sizeof(char))))
			error(strerror(errno));
		*tail = 0;
	}
	if (!(new = gnl(&tail)))
	{
		free(tail);
		return ((tail = NULL));
	}
	return (new);
}

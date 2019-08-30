/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_shared.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 20:18:11 by smorty            #+#    #+#             */
/*   Updated: 2019/08/30 17:24:32 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_SHARED_H
# define FILLER_SHARED_H

# include <fcntl.h>
# include <errno.h>
# include "libft.h"

# define BUFF_SIZE 16

void	error(const char *error_msg);
char	*read_input(void);

#endif

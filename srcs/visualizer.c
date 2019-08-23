/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 21:42:24 by smorty            #+#    #+#             */
/*   Updated: 2019/08/23 23:56:45 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

static SDL_Rect	*get_rectangle(int x, int y, int width, int height)
{
	SDL_Rect *rect;

	rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	rect->x = x;
	rect->y = y;
	rect->w = width;
	rect->h = height;
	return (rect);
}

void			put_numbers(SDL_Renderer *renderer, t_filler_vis *game)
{
	int i;
	int j;
	int os;
	int xs;

	os = 0;
	xs = 0;
	i = game->height;
	while (i--)
	{
		j = game->width + 4;
		while (j-- > 4)
		{
			if (game->board_states->board[i][j] == 'O' || game->board_states->board[i][j] == '0')
				++os;
			else if (game->board_states->board[i][j] == 'X' || game->board_states->board[i][j] == 'x')
				++xs;
		}
	}
}

void			render_map(SDL_Renderer *renderer, t_filler_vis *game)
{
	SDL_Rect *rect;
	int i;
	int j;
	int height;
	int width;

	int os;
	int xs;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	height = FILLER_SCREEN_HEIGH / (game->height + 2);
	width = FILLER_SCREEN_WIDTH / (game->width + 2);
	i = 0;
	while (i < game->height)
	{
		j = 4;
		while (j < game->width + 4)
		{
			if (game->board_states->board[i][j] == 'X')
				SDL_SetRenderDrawColor(renderer, 0, 150, 0, SDL_ALPHA_OPAQUE);
			else if (game->board_states->board[i][j] == 'x')
				SDL_SetRenderDrawColor(renderer, 0, 250, 0, SDL_ALPHA_OPAQUE);
			else if (game->board_states->board[i][j] == 'O')
				SDL_SetRenderDrawColor(renderer, 0, 0, 100, SDL_ALPHA_OPAQUE);
			else if (game->board_states->board[i][j] == 'o')
				SDL_SetRenderDrawColor(renderer, 0, 0, 250, SDL_ALPHA_OPAQUE);
			else
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			++j;
			rect = get_rectangle((j - 4) * width, (i + 1) * height, width, height);
			SDL_RenderFillRect(renderer, rect);
			free(rect);
		}
		++i;
	}
	put_numbers(renderer, game);
	SDL_RenderPresent(renderer);
}

static t_board	*new_board(t_board *prev, int y)
{
	t_board	*new;
	char	*buf;
	int		i;

	if (!(new = (t_board *)malloc(sizeof(t_board))))
		exit(-1);
	buf = read_input();
	while (buf && *buf != ' ')
	{
		free(buf);
		buf = read_input();
	}
	if (!buf)
	{
		prev->last = 1;
		return (NULL);
	}
	free(buf);
	new->board = (char **)malloc(sizeof(char *) * y);
	i = 0;
	while (i < y)
		new->board[i++] = read_input();
	new->right = NULL;
	new->left = prev;
	if (prev)
		prev->right = new;
	new->last = 0;
	return (new);
}

static void		get_next_board(t_board *p, int height)
{
	char *buf;

	if ((buf = read_input()))
	{
		free(buf);
		while (p->right)
			p = p->right;
		p->right = new_board(p, height);
	}
}

static void		key_handler(SDL_Event *e, t_filler_vis *game, t_vis_status *status)
{
	if (e->key.keysym.sym == SDLK_ESCAPE)
		status->quit = 1;
	else if (e->key.keysym.sym == SDLK_SPACE)
		status->pause = ~status->pause;
	else if (e->key.keysym.sym == SDLK_KP_PLUS && status->speed < 100)
		++status->speed;
	else if (e->key.keysym.sym == SDLK_KP_MINUS && status->speed)
		--status->speed;
	else if (e->key.keysym.sym == SDLK_LEFT && status->pause && game->board_states->left)
		game->board_states = game->board_states->left;
	else if (e->key.keysym.sym == SDLK_RIGHT && status->pause && game->board_states->right)
		game->board_states = game->board_states->right;
}

static void 	visualize(SDL_Renderer *renderer, t_filler_vis *game)
{
	SDL_Event		e;
	t_vis_status	status;

	status.quit = 0;
	status.pause = 0;
	status.ended = 0;
	status.speed = 0;
	while (!status.quit)
	{
		if (SDL_PollEvent(&e) && e.type == SDL_KEYDOWN)
			key_handler(&e, game, &status);
		render_map(renderer, game);
		if (!status.pause && game->board_states->right)
			game->board_states = game->board_states->right;
		if (!status.ended)
			get_next_board(game->board_states, game->height);
		if (game->board_states->last)
		{
			status.ended = -1;
			status.pause = -1;
		}
	}
}

static void		cleanup(SDL_Window *window, SDL_Renderer *renderer, t_filler_vis *game)
{
	t_board	*p;
	char	*buf;
	int		i;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	while ((buf = read_input()))
		free(buf);
	if ((p = game->board_states))
	{
		while (p->left)
			p = p->left;
		while (p->right)
		{
			i = game->height;
			while (i--)
				free(p->board[i]);
			free(p->board);
			p = p->right;
			free(p->left);
		}
		i = game->height;
		while (i--)
			free(p->board[i]);
		free(p->board);
		free(p);
	}
	free(game->p1_name);
	free(game->p2_name);
	free(game);
}

int				main(void)
{
    SDL_Window		*window;
	SDL_Renderer	*renderer;
	t_filler_vis	*game;

	window = NULL;
	renderer = NULL;
	init_visualizer(&window, &renderer, &game);
	game->board_states = new_board(NULL, game->height);
	visualize(renderer, game);
	cleanup(window, renderer, game);
	return (0);
}

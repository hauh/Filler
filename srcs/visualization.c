/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 21:42:24 by smorty            #+#    #+#             */
/*   Updated: 2019/08/21 22:22:23 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl2/include/SDL2/SDL.h"
#include "ft_printf/includes/ft_printf.h"
/*
void	render_map(SDL_Renderer *renderer, int **board, int x, int y)
{
	int i;
	int j;
	int height;
	int width;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	height = 1000 / y;
	width = 1000 / y;
	i = 0;
	while (i < y - 1)
	{
		j = 0;
		SDL_RenderDrawLine(renderer, i * 100, j * 200, i * 300, 240);
		while 
	}
}*/

void	loop(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_Event	e;
	int			quit;

	quit = 0;
	while (!quit)
	{
		if (SDL_PollEvent(&e))
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				quit = 1;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
		SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
		SDL_RenderPresent(renderer);
	}
}

void	init(SDL_Window **window, SDL_Renderer **renderer)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		ft_printf("SDL_Init error: %s\n", SDL_GetError());
		exit (-1);
	}
	*window = SDL_CreateWindow("smorty's Filler", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1920, 1200, SDL_WINDOW_SHOWN);
	if (!*window)
	{
		ft_printf("SDL_CreateWindow error: %s\n", SDL_GetError());
		exit (-1);
	}
	*renderer = SDL_CreateRenderer(*window, -1, 0);
	if (!*renderer)
	{
		ft_printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
		exit (-1);
	}
}

int main (int argc, char **args)
{
    SDL_Window		*window = NULL;
	SDL_Renderer	*renderer = NULL;

	init(&window, &renderer);
	
	SDL_Surface		*image = SDL_LoadBMP("ants.bmp");
	SDL_Texture		*texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_Rect		dstrect = {5, 5, 320, 240};

	loop(window, renderer);

	//destroy
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}

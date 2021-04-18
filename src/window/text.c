/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 20:09:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Create text surface with shaded font
*/
SDL_Surface			*surface_from_font_shaded(t_text_params params,
						TTF_Font *font)
{
	SDL_Surface		*text_surface;
	SDL_Surface		*formatted_surface;
	uint32_t		rgba[4];

	l3d_u32_to_rgba(CLEAR_COLOR, rgba);
	text_surface = TTF_RenderText_Shaded(font,
		params.text, params.text_color,
			(SDL_Color){rgba[0], rgba[1], rgba[2], 0});
	error_check(!text_surface, TTF_GetError());
	formatted_surface = SDL_ConvertSurfaceFormat(text_surface,
		PIXEL_FORMAT, 0);
	SDL_FreeSurface(text_surface);
	error_check(!formatted_surface, SDL_GetError());
	return (formatted_surface);
}

/*
** Create text surface with solid font
*/
SDL_Surface			*surface_from_font_solid(t_text_params params,
						TTF_Font *font)
{
	SDL_Surface		*text_surface;
	SDL_Surface		*formatted_surface;

	text_surface = TTF_RenderText_Solid(font,
		params.text, params.text_color);
	error_check(!text_surface, TTF_GetError());
	formatted_surface = SDL_ConvertSurfaceFormat(text_surface,
		PIXEL_FORMAT, 0);
	SDL_FreeSurface(text_surface);
	error_check(!formatted_surface, SDL_GetError());
	return (formatted_surface);
}

/*
** Create text surface with wrapped (by line break) text
*/
void				window_text_render_wrapped(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;
	char		**parts;
	int32_t		i;
	int32_t		height;

	parts = ft_strsplit(params.text, '\n');
	if (parts == NULL)
		return ;
	TTF_SizeText(font, parts[0], NULL, &height);
	i = 0;
	while (parts[i])
	{
		params.text = parts[i];
		surface = surface_from_font_solid(params, font);
		l3d_image_place(&(t_surface){.h = window->framebuffer->height,
			.w = window->framebuffer->width,
			.pixels = window->framebuffer->buffer
			}, &(t_surface){.h = surface->h,
			.w = surface->w,
			.pixels = surface->pixels}, (int32_t[2]){
				params.xy[0], params.xy[1] + i * height}, params.blend_ratio);
		SDL_FreeSurface(surface);
		ft_strdel(&parts[i++]);
	}
	free(parts);
}

/*
** Render text on window
*/
void				window_text_render(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;

	surface = surface_from_font_solid(params, font);
	l3d_image_place(&(t_surface){.h = window->framebuffer->height,
		.w = window->framebuffer->width,
		.pixels = window->framebuffer->buffer
		}, &(t_surface){.h = surface->h,
		.w = surface->w,
		.pixels = surface->pixels}, params.xy, params.blend_ratio);
	SDL_FreeSurface(surface);
}

/*
** Render text on window so it is centered
*/
void				window_text_render_centered(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;

	surface = surface_from_font_solid(params, font);
	l3d_image_place(&(t_surface){.h = window->framebuffer->height,
		.w = window->framebuffer->width,
		.pixels = window->framebuffer->buffer},
		&(t_surface){.h = surface->h,
		.w = surface->w,
		.pixels = surface->pixels},
		(int[2]){params.xy[0] - surface->w / 2, params.xy[1] - surface->h / 2},
		params.blend_ratio);
	SDL_FreeSurface(surface);
}

/*
** Render text on window centered and wrapped by line breaks
*/
void				window_text_render_centered_wrapped(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;
	char		**parts;
	int32_t		i;
	int32_t		height;

	parts = ft_strsplit(params.text, '\n');
	if (parts == NULL)
		return ;
	TTF_SizeText(font, parts[0], NULL, &height);
	i = 0;
	while (parts[i])
	{
		params.text = parts[i];
		surface = surface_from_font_solid(params, font);
		l3d_image_place(&(t_surface){.h = window->framebuffer->height,
			.w = window->framebuffer->width,
			.pixels = window->framebuffer->buffer},
			&(t_surface){.h = surface->h,
			.w = surface->w, .pixels = surface->pixels},
			(int[2]){params.xy[0] - surface->w / 2,
			params.xy[1] - surface->h / 2 + i * height}, params.blend_ratio);
		SDL_FreeSurface(surface);	
		ft_strdel(&parts[i++]);
	}
	free(parts);
}

/*
** Render shaded text on window wrapped by line breaks
*/
void				window_text_render_wrapped_shaded(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;
	char		**parts;
	int32_t		i;
	int32_t		height;

	parts = ft_strsplit(params.text, '\n');
	if (parts == NULL)
		return ;
	TTF_SizeText(font, parts[0], NULL, &height);
	i = 0;
	while (parts[i])
	{
		params.text = parts[i];
		surface = surface_from_font_solid(params, font);
		l3d_image_place(&(t_surface){.h = window->framebuffer->height,
			.w = window->framebuffer->width,
			.pixels = window->framebuffer->buffer
			}, &(t_surface){.h = surface->h,
			.w = surface->w,
			.pixels = surface->pixels}, (int32_t[2]){
				params.xy[0], params.xy[1] + i * height}, params.blend_ratio);
		SDL_FreeSurface(surface);
		ft_strdel(&parts[i++]);
	}
	free(parts);
}

/*
** Render shaded text on window
*/
void				window_text_render_shaded(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;

	surface = surface_from_font_solid(params, font);
	l3d_image_place(&(t_surface){.h = window->framebuffer->height,
		.w = window->framebuffer->width,
		.pixels = window->framebuffer->buffer
		}, &(t_surface){.h = surface->h,
		.w = surface->w,
		.pixels = surface->pixels}, params.xy, params.blend_ratio);
	SDL_FreeSurface(surface);
}

/*
** Render centered shaded text on window
*/
void				window_text_render_centered_shaded(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;

	surface = surface_from_font_solid(params, font);
	l3d_image_place(&(t_surface){.h = window->framebuffer->height,
		.w = window->framebuffer->width,
		.pixels = window->framebuffer->buffer},
		&(t_surface){.h = surface->h,
		.w = surface->w,
		.pixels = surface->pixels},
		(int[2]){params.xy[0] - surface->w / 2, params.xy[1] - surface->h / 2},
		params.blend_ratio);
	SDL_FreeSurface(surface);
}

/*
** Render shaded and centered text on window wrapped by line breaks
*/
void				window_text_render_centered_wrapped_shaded(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;
	char		**parts;
	int32_t		i;
	int32_t		height;

	parts = ft_strsplit(params.text, '\n');
	if (parts == NULL)
		return ;
	TTF_SizeText(font, parts[0], NULL, &height);
	i = 0;
	while (parts[i])
	{
		params.text = parts[i];
		surface = surface_from_font_solid(params, font);
		l3d_image_place(&(t_surface){.h = window->framebuffer->height,
			.w = window->framebuffer->width,
			.pixels = window->framebuffer->buffer},
			&(t_surface){.h = surface->h,
			.w = surface->w, .pixels = surface->pixels},
			(int[2]){params.xy[0] - surface->w / 2,
			params.xy[1] - surface->h / 2 + i * height}, params.blend_ratio);
		SDL_FreeSurface(surface);	
		ft_strdel(&parts[i++]);
	}
	free(parts);
}

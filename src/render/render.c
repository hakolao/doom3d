/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 02:09:05 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/29 21:14:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	render_game_background(t_doom3d *app)
{
	t_surface			*background;

	background = hash_map_get(app->assets.hud_textures,
			(int64_t)"assets/img/hud_shell.bmp");
	error_check(!background, "Could not find background image");
	l3d_image_place(&(t_surface){
		.h = app->window->framebuffer->height,
		.w = app->window->framebuffer->width,
		.pixels = app->window->framebuffer->buffer},
		background, (int32_t[2]){0, 0}, 1.0);
}

static void	render_effects_on_background(t_doom3d *app)
{
	t_surface	*splash;

	splash = hash_map_get(app->assets.sprite_textures,
			(int64_t)"assets/animations/blood.bmp");
	error_check(!splash, "Blood image not found");
	l3d_image_place(&(t_surface){.h = app->window->framebuffer->height,
		.w = app->window->framebuffer->width,
		.pixels = app->window->framebuffer->buffer}, splash,
		(int32_t[2]){200, 200}, 0.7);
}

static void	render_menu_background(t_doom3d *app)
{
	t_surface	*background;

	if (app->active_scene->scene_id == scene_id_main_menu)
		background = hash_map_get(app->assets.textures,
				(int64_t)"assets/textures/floor_metal_2048.bmp");
	else if (app->active_scene->scene_id == scene_id_main_menu_settings)
		background = hash_map_get(app->assets.textures,
				(int64_t)"assets/textures/rock_toxic.bmp");
	else
		background = hash_map_get(app->assets.textures,
				(int64_t)"assets/textures/wall_metal_panel.bmp");
	error_check(!background, "Background image not found");
	l3d_background_place(&(t_surface){.h = app->window->framebuffer->height,
		.w = app->window->framebuffer->width,
		.pixels = app->window->framebuffer->buffer}, background, 0.75);
	if (app->active_scene->scene_id != scene_id_main_menu)
		return ;
	render_effects_on_background(app);
}

/*
** Render 3d view. It gets a little special treatment as the view
** should not cover whole framebuffer, but instead just a portion of it leaving
** space for the UI.
*/

void	render_3d_view_parallel(t_doom3d *app)
{
	int32_t	x_pos;
	int32_t	y_pos;

	x_pos = app->window->view_3d_pos[0];
	y_pos = app->window->view_3d_pos[1];
	render_parallel_3d_view(app, app->window->framebuffer_3d);
	l3d_image_place(&(t_surface){.pixels = app->window->framebuffer->buffer,
		.w = app->window->framebuffer->width,
		.h = app->window->framebuffer->height},
		&(t_surface){.pixels = app->window->framebuffer_3d->buffer,
		.w = app->window->framebuffer_3d->width,
		.h = app->window->framebuffer_3d->height},
		(int32_t[2]){x_pos, y_pos}, 1.0);
}

/*
** Render everything in app to framebuffer including 3d and UI.
** 1. Render parallel
*/

void	render_to_framebuffer(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game)
		render_game_background(app);
	else
		render_menu_background(app);
	if (app->active_scene->scene_id == scene_id_main_game
		|| app->active_scene->scene_id == scene_id_editor3d)
		render_3d_view_parallel(app);
	render_ui(app);
	if (app->settings.is_debug)
		render_debug_info(app);
}

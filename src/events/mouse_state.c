/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/04 23:58:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Note that this is also used by the editor!
*/

void					handle_player_rotation_input(t_doom3d *app,
							int32_t xrel, int32_t yrel)
{
	if (xrel != 0 || yrel != 0)
	{
		app->player.is_rotating = true;
		player_rotate_vertical(app, -(float)yrel * 0.3);
		player_rotate_horizontal(app, (float)xrel * 0.3);
	}
	else
		app->player.is_rotating = false;
}

static void				handle_game_mouse_state_input(t_doom3d *app)
{
	int32_t	xrel;
	int32_t	yrel;

	SDL_GetRelativeMouseState(&xrel, &yrel);
	handle_player_rotation_input(app, xrel, yrel);
	if (!app->player.is_shooting && (app->mouse.state & SDL_BUTTON_LMASK))
		app->player.is_shooting = true;
	else if (!(app->mouse.state & SDL_BUTTON_LMASK))
	{
		app->player.is_shooting = false;
		set_player_default_frame(app);
	}
	if (app->player.is_shooting && !app->player.is_reloading)
	{
		player_shoot(app, SDL_GetTicks());
	}
}

/*
** Mouse state handling, both editor & game
*/

void					handle_mouse_state_input(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game &&
		!app->active_scene->is_paused)
		handle_game_mouse_state_input(app);
	if (app->active_scene->scene_id == scene_id_editor3d)
	{
		handle_editor_mouse_state_input(app);
	}
}

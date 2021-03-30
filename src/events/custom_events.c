/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:57:41 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 02:16:34 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	custom_event_to_str(char *str, t_doom3d_event code)
{
	if (code == event_object_delete)
		ft_sprintf(str, "ObjectDelete");
	else if (code == event_music_play)
		ft_sprintf(str, "MusicPlay");
	else if (code == event_effect_play)
		ft_sprintf(str, "EffectPlay");
	else if (code == event_scene_change)
		ft_sprintf(str, "SceneChange");
	else if (code == event_scene_reload)
		ft_sprintf(str, "SceneReload");
	else if (code == event_quit)
		ft_sprintf(str, "Quit");
	else if (code == event_window_resize)
		ft_sprintf(str, "WindowResize");
	editor_event_to_str(str, code);
}

/*
** Registers all custom events and their handlers
** Caller must know what to input to handlers in event handling
*/

void		register_custom_events(t_doom3d *app)
{
	app->custom_event_type = SDL_RegisterEvents(1);
	app->custom_event_handles = hash_map_create(NUM_CUSTOM_EVENTS);
	hash_map_add(app->custom_event_handles, event_object_delete,
		(void*)handle_object_deletion);
	hash_map_add(app->custom_event_handles, event_effect_play,
		(void*)handle_play_effect);
	hash_map_add(app->custom_event_handles, event_music_play,
		(void*)handle_play_music);
	hash_map_add(app->custom_event_handles, event_window_resize,
		(void*)handle_window_resize);
	hash_map_add(app->custom_event_handles, event_scene_change,
		(void*)handle_scene_change);
	hash_map_add(app->custom_event_handles, event_scene_reload,
		(void*)handle_scene_reload);
	hash_map_add(app->custom_event_handles, event_quit,
		(void*)handle_quit);
	register_editor_custom_events(app);
}

void		doom3d_push_event(t_doom3d *app,
								t_doom3d_event code,
								void *data1,
								void *data2)
{
	SDL_Event event;

	ft_memset(&event, 0, sizeof(event));
	event.type = app->custom_event_type;
	event.user.code = code;
	event.user.data1 = data1;
	event.user.data2 = data2;
	SDL_PushEvent(&event);
}

/*
** Note that this is rather unsafe code here:
** 1. Push event will set data1 and data2. These should be sufficient to contain
** any event data.
** 2. Handler should not have more than 3 inputs. App, data1, data2.
** 3. All handlers must have been registered at the beginning of the app
*/

void		custom_events_handle(t_doom3d *app, SDL_Event event)
{
	void		(*handle)(void*, void*, void*);
	char		event_str[64];

	handle = hash_map_get(app->custom_event_handles, event.user.code);
	if (handle != NULL)
	{
		custom_event_to_str(event_str, event.user.code);
		ft_printf("Event:%d: %s\n", event.user.code, event_str);
		handle(app, event.user.data1, event.user.data2);
	}
}

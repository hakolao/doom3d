/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 16:26:39 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Scene switch should be the first thing we do if next scene id has changed
** in main loop (before event handling).
*/

static void		handle_scene_switch(t_doom3d *app)
{
	if (app->active_scene->scene_id != app->next_scene_id ||
		app->is_scene_reload)
	{
		if (app->is_debug)
			LOG_INFO("Scen change detected, selecting next");
		select_next_scene(app);
	}
}

static void		app_init(t_doom3d *app)
{
	LOG_INFO("Register Custom Events");
	register_custom_events(app);
	LOG_INFO("Initialize Audio");
	mp_init(app);
	app->active_scene = NULL;
	app->triangles_in_view = 0;
	app->is_running = true;
	app->is_debug = true;
	app->is_scene_reload = false;
	app->unit_size = app->window->width;
	ft_memset(&app->notifications, 0, sizeof(app->notifications));
	read_level_list(app);
	app->current_level = 0;
	editor_init(app, 0);
	app->next_scene_id = scene_id_main_menu;
	select_next_scene(app);
}

static void		cleanup(t_doom3d *app)
{
	int32_t		i;

	LOG_INFO("Destroy thread pool");
	thread_pool_destroy(app->thread_pool);
	LOG_INFO("Destroy scene");
	scene_destroy(app);
	LOG_INFO("Destroy window");
	window_destroy(app->window);
	LOG_INFO("Destroy audio");
	mp_close(app);
	LOG_INFO("Quit SDL");
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	i = -1;
	LOG_INFO("Free level strs");
	while (++i < (int32_t)app->num_levels)
		ft_strdel(&app->level_list[i]);
	LOG_INFO("Delete notifications");
	delete_notifications(app);
}


static void		main_loop(t_doom3d *app)
{
	while (app->is_running)
	{
		app->info.performance_start = SDL_GetPerformanceCounter();
		if (app->window->resized)
			resize_dependent_recreate(app);
		window_frame_clear(app->window);
		handle_scene_switch(app);
		handle_events(app);
		update_player(app);
		update_objects(app);
		render_to_framebuffer(app);
		draw_window_frame(app->window);
		update_notifications(app);
		capture_fps(app);
		update_app_ticks(app);
	}
}

void			doom3d_run(t_doom3d *app)
{
	int32_t	cpu_count;

	cpu_count = ft_max_int((int32_t[2]){
		NUM_THREADS_DEFAULT, SDL_GetCPUCount()}, 2);
	LOG_INFO("Create thread pool");
	app->thread_pool = thread_pool_create(
		cpu_count >= NUM_THREADS_DEFAULT ? cpu_count : NUM_THREADS_DEFAULT);
	LOG_INFO("Initialize SDL");
	error_check(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0, SDL_GetError());
	error_check(TTF_Init() == -1, TTF_GetError());
	LOG_INFO("Initialize App settings");
	settings_init(app);
	LOG_INFO("Create SDL Window & frame buffers");
	window_create(&app->window, app->settings.width, app->settings.height);
	app_init(app);
	// This song has given me brain tumor :D
	// push_custom_event(app,
	// 	event_music_play, (void*)mu_main, s_ini(1, 10, st_main_menu, 0.6));
	main_loop(app);
	cleanup(app);
}

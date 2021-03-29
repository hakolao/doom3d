/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:09:16 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 17:13:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

typedef enum				e_doom3d_event
{
	event_object_delete = 1,
	event_music_play = 2,
	event_effect_play = 3,
	event_editor_start_placement = 4,
	event_editor_end_placement = 5,
	event_window_resize = 6,
	event_scene_change = 7,
	event_quit = 999,
}							t_doom3d_event;

# endif
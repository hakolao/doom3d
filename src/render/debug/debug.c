/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:07:34 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/05 16:12:26 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Draws debug grid to editor.
** Use this as a "How to" example for drawing debug lines, e.g.
** enemy direction vector.
** (1. Access app through work, 2. Access your variables & draw)
*/

void			draw_editor_debug_grid(t_render_work *work)
{
	t_sub_framebuffer	*sub_buffer;
	int32_t				i;
	t_vec3				points[2];
	float				length;
	uint32_t			line_color;

	sub_buffer = work->framebuffer->sub_buffers[work->sub_buffer_i];
	length = 100;
	line_color = 0x202020ff;
	i = -length / 2 - 1;
	while (++i <= length / 2)
	{
		ml_vector3_copy((t_vec3){i * work->app->unit_size, 0,
			(-length / 2.0) * work->app->unit_size}, points[0]);
		ml_vector3_copy((t_vec3){i * work->app->unit_size, 0,
			(length / 2.0) * work->app->unit_size}, points[1]);
		draw_debug_line(work->app, sub_buffer, points, line_color);
		ml_vector3_copy((t_vec3){(-length / 2.0) * work->app->unit_size, 0,
			i * work->app->unit_size}, points[0]);
		ml_vector3_copy((t_vec3){(length / 2.0) * work->app->unit_size, 0,
			i * work->app->unit_size}, points[1]);
		draw_debug_line(work->app, sub_buffer, points, line_color);
	}
}

static void		triangle_wireframe_draw(t_sub_framebuffer *buffers,
					t_vec2 points2d[3], uint32_t color)
{
	l3d_line_draw(buffers->buffer, (uint32_t[2]){
		buffers->width, buffers->height
	}, (int32_t[2][2]){{points2d[0][0] + buffers->x_offset,
			points2d[0][1] + buffers->y_offset},
		{points2d[1][0] + buffers->x_offset,
			points2d[1][1] + buffers->y_offset}}, color);
	l3d_line_draw(buffers->buffer, (uint32_t[2]){
		buffers->width, buffers->height
	}, (int32_t[2][2]){{points2d[1][0] + buffers->x_offset,
			points2d[1][1] + buffers->y_offset},
		{points2d[2][0] + buffers->x_offset,
			points2d[2][1] + buffers->y_offset}}, color);
	l3d_line_draw(buffers->buffer, (uint32_t[2]){
		buffers->width, buffers->height
	}, (int32_t[2][2]){{points2d[2][0] + buffers->x_offset,
			points2d[2][1] + buffers->y_offset},
		{points2d[0][0] + buffers->x_offset,
			points2d[0][1] + buffers->y_offset}}, color);
}

void			draw_selected_wireframe(t_render_work *work)
{
	t_sub_framebuffer	*sub_buffer;
	t_triangle			*triangle;
	int32_t				i;

	sub_buffer = work->framebuffer->sub_buffers[work->sub_buffer_i];
	i = -1;
	while (++i < (int32_t)work->render_triangles->size)
	{
		triangle = work->render_triangles->triangles[i];
		if (!(triangle->material->shading_opts & e_shading_select) ||
			triangle->clipped ||
			triangle_outside_frame(triangle, sub_buffer))
			continue ;
		triangle_wireframe_draw(sub_buffer, triangle->points_2d, 0x00ff00ff);
	}
}

void			draw_selected_aabb(t_render_work *work)
{
	t_doom3d			*app;
	t_sub_framebuffer	*buffers;
	t_3d_object			*obj;

	buffers = work->framebuffer->sub_buffers[work->sub_buffer_i];
	app = work->app;
	obj = app->editor.selected_object;
	draw_debug_line(app, buffers, (t_vec3[2]){
		{obj->aabb.xyz_min[0], obj->aabb.xyz_min[1], obj->aabb.xyz_min[2]},
		{obj->aabb.xyz_min[0], obj->aabb.xyz_min[1], obj->aabb.xyz_max[2]}
	}, 0xff0000ff);
	draw_debug_line(app, buffers, (t_vec3[2]){
		{obj->aabb.xyz_min[0], obj->aabb.xyz_min[1], obj->aabb.xyz_max[2]},
		{obj->aabb.xyz_max[0], obj->aabb.xyz_min[1], obj->aabb.xyz_max[2]},
	}, 0xff0000ff);
	draw_debug_line(app, buffers, (t_vec3[2]){
		{obj->aabb.xyz_max[0], obj->aabb.xyz_min[1], obj->aabb.xyz_max[2]},
		{obj->aabb.xyz_max[0], obj->aabb.xyz_min[1], obj->aabb.xyz_min[2]},
	}, 0xff0000ff);
	draw_debug_line(app, buffers, (t_vec3[2]){
		{obj->aabb.xyz_max[0], obj->aabb.xyz_min[1], obj->aabb.xyz_min[2]},
		{obj->aabb.xyz_min[0], obj->aabb.xyz_min[1], obj->aabb.xyz_min[2]},
	}, 0xff0000ff);
	draw_debug_line(app, buffers, (t_vec3[2]){
		{obj->aabb.xyz_min[0], obj->aabb.xyz_max[1], obj->aabb.xyz_min[2]},
		{obj->aabb.xyz_min[0], obj->aabb.xyz_max[1], obj->aabb.xyz_max[2]}
	}, 0xff0000ff);
	draw_debug_line(app, buffers, (t_vec3[2]){
		{obj->aabb.xyz_min[0], obj->aabb.xyz_max[1], obj->aabb.xyz_max[2]},
		{obj->aabb.xyz_max[0], obj->aabb.xyz_max[1], obj->aabb.xyz_max[2]},
	}, 0xff0000ff);
	draw_debug_line(app, buffers, (t_vec3[2]){
		{obj->aabb.xyz_max[0], obj->aabb.xyz_max[1], obj->aabb.xyz_max[2]},
		{obj->aabb.xyz_max[0], obj->aabb.xyz_max[1], obj->aabb.xyz_min[2]},
	}, 0xff0000ff);
	draw_debug_line(app, buffers, (t_vec3[2]){
		{obj->aabb.xyz_max[0], obj->aabb.xyz_max[1], obj->aabb.xyz_min[2]},
		{obj->aabb.xyz_min[0], obj->aabb.xyz_max[1], obj->aabb.xyz_min[2]},
	}, 0xff0000ff);
	draw_debug_line(app, buffers, (t_vec3[2]){
		{obj->aabb.xyz_min[0], obj->aabb.xyz_min[1], obj->aabb.xyz_min[2]},
		{obj->aabb.xyz_min[0], obj->aabb.xyz_max[1], obj->aabb.xyz_min[2]}
	}, 0xff0000ff);
	draw_debug_line(app, buffers, (t_vec3[2]){
		{obj->aabb.xyz_max[0], obj->aabb.xyz_min[1], obj->aabb.xyz_max[2]},
		{obj->aabb.xyz_max[0], obj->aabb.xyz_max[1], obj->aabb.xyz_max[2]},
	}, 0xff0000ff);
	draw_debug_line(app, buffers, (t_vec3[2]){
		{obj->aabb.xyz_max[0], obj->aabb.xyz_min[1], obj->aabb.xyz_min[2]},
		{obj->aabb.xyz_max[0], obj->aabb.xyz_max[1], obj->aabb.xyz_min[2]},
	}, 0xff0000ff);
	draw_debug_line(app, buffers, (t_vec3[2]){
		{obj->aabb.xyz_min[0], obj->aabb.xyz_min[1], obj->aabb.xyz_max[2]},
		{obj->aabb.xyz_min[0], obj->aabb.xyz_max[1], obj->aabb.xyz_max[2]},
	}, 0xff0000ff);
}

void			draw_selected_enemy_direction(t_render_work *work)
{
	t_npc				*npc;
	t_vec3				add;
	t_vec3				end;
	t_vec3				forward;
	t_mat4				rotation_x;

	npc = work->app->editor.selected_npc;
	ml_matrix4_rotation_y(ml_rad(npc->angle), rotation_x);
	ml_matrix4_mul_vec3(rotation_x, (t_vec3){0, 0, Z_DIR}, forward);
	ml_vector3_mul(forward, work->app->unit_size * 2, add);
	ml_vector3_add(npc->pos, add, end);
	draw_debug_line(work->app,
		work->framebuffer->sub_buffers[work->sub_buffer_i],
		(t_vec3[2]){{npc->pos[0], npc->pos[1], npc->pos[2]},
		{end[0], end[1], end[2]}}, 0xffff00ff);
}
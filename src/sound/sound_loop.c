/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:31:31 by phakakos          #+#    #+#             */
/*   Updated: 2021/03/12 15:31:34 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Helper for the audio loop. Moves all active sounds by len.
** Pops fully played sounds and resets looping sounds
*/

static void		mp_move(t_sound **start, int len)
{
	t_sound	*curr;
	t_sound	*prev[2];

	curr = *start;
	prev[0] = NULL;
	while (curr)
	{
		curr->pos += curr->state == SPLAYING ? len : 0;
		if (curr->pos >= curr->sound->len)
		{
			if (curr->loop)
				curr->pos = 0;
			else
			{
				if (prev[0])
					prev[0]->next = curr->next;
				else
					*start = curr->next;
				prev[1] = curr;
				curr = curr->next;
				free(prev[1]);
			}
		}
		else
		{
			prev[0] = curr;
			curr = curr->next;
		}
	}
}

/*
** Music player mix loop helper, find the next sound to play
** Returns in order the next active track or NULL if none
*/

static t_sound	*mp_mix_next(t_sound *start)
{
	t_sound	*curr;
	t_sound	*ret;

	curr = start;
	ret = NULL;
	while (!ret && curr)
	{
		if (curr->state == SPLAYING && curr->vol > 0)
			ret = curr;
		curr = curr->next;
	}
	return (ret);
}

/*
** Find playable sounds
*/

static t_sound	*mp_mixing(t_sound *curr, t_mp *mp, float vol)
{
	Uint32	amount;

	if (!(curr = mp_mix_next(curr)))
		return (curr);
	amount = curr->sound->len - curr->pos;
	amount = amount > (Uint32)mp->len ? (Uint32)mp->len : amount;
	SDL_MixAudioFormat(mp->stream, &curr->sound->data[curr->pos],
		mp->auspec.format, amount, SDL_MIX_MAXVOLUME * vol * curr->vol);
	return (curr);
}

/*
** Loop thru sounds till max has been reached or no more sounds to play
*/

static void		playing_audio(t_mp *mp, t_sound **start, int max, float vol)
{
	t_sound	*curr;
	int		played;

	if (!(curr = *start))
		return ;
	else if (vol == -1) // insert here exit incase sound/effects paused
		return ;
	played = 0;
	while (played < max && curr && vol > 0)
	{
		if (!(curr = mp_mixing(curr, mp, mp->st_vol)))
			break ;
		played++;
		curr = curr->next;
	}
	mp_move(start, mp->len);
}

/*
** Music player main loop
*/

void			mp_au_mix(void *para, Uint8 *stream, int len)
{
	t_mp	*mp;

	mp = (t_mp*)para;
	SDL_memset(stream, 0, len);
	mp->stream = stream;
	mp->len = len;
	playing_audio(mp, &mp->tracks, NUM_MUSIC, mp->st_vol);
	playing_audio(mp, &mp->effects, NUM_SEFFECTS, mp->sf_vol);
	mp->stream = NULL;
	mp->len = 0;
}
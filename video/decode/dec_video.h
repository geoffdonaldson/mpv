/*
 * This file is part of MPlayer.
 *
 * MPlayer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * MPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with MPlayer; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MPLAYER_DEC_VIDEO_H
#define MPLAYER_DEC_VIDEO_H

#include "demux/stheader.h"

struct osd_state;
struct mp_decoder_list;

struct mp_decoder_list *mp_video_decoder_list(void);

int init_best_video_codec(sh_video_t *sh_video, char* video_decoders);
void uninit_video(sh_video_t *sh_video);

struct demux_packet;
void *decode_video(sh_video_t *sh_video, struct demux_packet *packet,
                   int drop_frame, double pts);

int get_video_quality_max(sh_video_t *sh_video);

int get_video_colors(sh_video_t *sh_video, const char *item, int *value);
int set_video_colors(sh_video_t *sh_video, const char *item, int value);
void resync_video_stream(sh_video_t *sh_video);
void video_reinit_vo(struct sh_video *sh_video);
int get_current_video_decoder_lag(sh_video_t *sh_video);
int vd_control(struct sh_video *sh_video, int cmd, void *arg);

// Used to communicate hardware decoder API handles from VO to video decoder.
// The VO can set the context pointer for supported APIs.
struct mp_hwdec_info {
    struct mp_vdpau_ctx *vdpau_ctx;
    struct mp_vaapi_ctx *vaapi_ctx;
    // Can be used to lazily load a requested API.
    // api_name is e.g. "vdpau" (like the fields above, without "_ctx")
    // Can be NULL, is idempotent, caller checks _ctx fields for success/access.
    void (*load_api)(struct mp_hwdec_info *info, const char *api_name);
    void *load_api_ctx;
};

void hwdec_request_api(struct mp_hwdec_info *info, const char *api_name);

#endif /* MPLAYER_DEC_VIDEO_H */

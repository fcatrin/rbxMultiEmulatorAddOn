/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2011-2015 - Daniel De Matteis
 *
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMON_TASKS_H
#define COMMON_TASKS_H

#include <stdint.h>
#include <boolean.h>

#include <queues/message_queue.h>

#include "../runloop_data.h"

#ifdef __cplusplus
extern "C" {
#endif

void rarch_main_data_nbio_uninit(void);

void rarch_main_data_nbio_init(void);

void rarch_main_data_nbio_init_msg_queue(void);

msg_queue_t *rarch_main_data_nbio_get_msg_queue_ptr(void);

msg_queue_t *rarch_main_data_nbio_image_get_msg_queue_ptr(void);

void *rarch_main_data_nbio_get_ptr(void);

void *rarch_main_data_nbio_get_handle(void);

void *rarch_main_data_nbio_image_get_handle(void);

#ifdef HAVE_NETWORKING
/**
 * rarch_main_data_http_iterate_transfer:
 *
 * Resumes HTTP transfer update.
 *
 * Returns: 0 when finished, -1 when we should continue
 * with the transfer on the next frame.
 **/
void rarch_main_data_http_iterate(bool is_thread);

msg_queue_t *rarch_main_data_http_get_msg_queue_ptr(void);

void rarch_main_data_http_init_msg_queue(void);

void *rarch_main_data_http_get_handle(void);

void *rarch_main_data_http_conn_get_handle(void);

void rarch_main_data_http_uninit(void);

void rarch_main_data_http_init(void);

void *rarch_main_data_http_get_ptr(void);
#endif

#ifdef HAVE_RPNG
void rarch_main_data_nbio_image_iterate(bool is_thread);
void rarch_main_data_nbio_image_upload_iterate(bool is_thread);
#endif

#ifdef HAVE_LIBRETRODB
#ifdef HAVE_MENU
void rarch_main_data_db_iterate(bool is_thread);

bool rarch_main_data_db_pending_scan_finished(void);
#endif

void rarch_main_data_db_init_msg_queue(void);

void *rarch_main_data_db_get_ptr(void);

msg_queue_t *rarch_main_data_db_get_msg_queue_ptr(void);

void rarch_main_data_db_uninit(void);

void rarch_main_data_db_init(void);

bool rarch_main_data_db_is_active(void);
#endif

#ifdef HAVE_OVERLAY
void rarch_main_data_overlay_image_upload_iterate(bool is_thread);

void rarch_main_data_overlay_iterate(bool is_thread);

void rarch_main_data_overlay_thread_uninit(void);

void rarch_main_data_overlay_thread_init(void);
#endif

void rarch_main_data_nbio_iterate(bool is_thread);
    
void data_runloop_osd_msg(const char *s, size_t len);

#ifdef __cplusplus
}
#endif

#endif

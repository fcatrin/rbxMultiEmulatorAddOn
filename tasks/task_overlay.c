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

#include <retro_miscellaneous.h>
#ifdef HAVE_THREADS
#include <rthreads/rthreads.h>
#endif

#include "../input/input_overlay.h"
#include "tasks.h"

#ifdef HAVE_THREADS
static slock_t *overlay_lock;
#endif

void rarch_main_data_overlay_image_upload_iterate(bool is_thread)
{
#ifdef HAVE_THREADS
   if (is_thread)
      slock_lock(overlay_lock);
#endif

   switch (input_overlay_status())
   {
      case OVERLAY_STATUS_DEFERRED_LOADING:
         input_overlay_load_overlays_iterate();
         break;
      default:
         break;
   }

#ifdef HAVE_THREADS
   if (is_thread)
      slock_unlock(overlay_lock);
#endif
}

void rarch_main_data_overlay_iterate(bool is_thread)
{
#ifdef HAVE_THREADS
   if (is_thread)
      slock_lock(overlay_lock);
#endif

   switch (input_overlay_status())
   {
      case OVERLAY_STATUS_DEFERRED_LOAD:
         input_overlay_load_overlays();
         break;
      case OVERLAY_STATUS_DEFERRED_LOADING_RESOLVE:
         input_overlay_load_overlays_resolve_iterate();
         break;
      case OVERLAY_STATUS_DEFERRED_DONE:
         input_overlay_new_done();
         break;
      case OVERLAY_STATUS_DEFERRED_ERROR:
         input_overlay_free();
         break;
      default:
      case OVERLAY_STATUS_NONE:
         break;
   }

#ifdef HAVE_THREADS
   if (is_thread)
      slock_unlock(overlay_lock);
#endif
}

void rarch_main_data_overlay_thread_uninit(void)
{
#ifdef HAVE_THREADS
   slock_free(overlay_lock);
#endif
}

void rarch_main_data_overlay_thread_init(void)
{
#ifdef HAVE_THREADS
   overlay_lock = slock_new();
#endif
}

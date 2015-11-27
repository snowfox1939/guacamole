/* nvstusb.h Copyright (C) 2010 Bjoern Paetzel
 *
 * This program comes with ABSOLUTELY NO WARRANTY.
 * This is free software, and you are welcome to redistribute it
 * under certain conditions. See the file COPYING for details
 * */

#ifndef __NVSTUSB_NVSTUSB_H__
#define __NVSTUSB_NVSTUSB_H__

struct nvstusb_context;

enum nvstusb_eye {
  nvstusb_left = 0,
  nvstusb_right,
  nvstusb_quad,
};

struct nvstusb_keys {
  char deltaWheel;
  char pressedDeltaWheel;
  int  toggled3D;
};

struct nvstusb_context *nvstusb_init(const char *firmware);
void nvstusb_deinit(struct nvstusb_context *ctx);
void nvstusb_set_rate(struct nvstusb_context *ctx, float rate);
void nvstusb_swap(struct nvstusb_context *ctx, enum nvstusb_eye eye, void (*swapfunc)());
void nvstusb_get_keys(struct nvstusb_context *ctx, struct nvstusb_keys *keys);
void nvstusb_invert_eyes(struct nvstusb_context *ctx);
void nvstusb_start_stereo_thread(struct nvstusb_context *ctx);
void nvstusb_stop_stereo_thread(struct nvstusb_context *ctx);

#endif // __NVSTUSB_NVSTUSB_H__

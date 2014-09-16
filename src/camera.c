#include "fswc/src.h"

int camera_on(src_t *src, char *dev_name, uint32_t width, uint32_t height, uint32_t fps)
{
  /* Set source options... */
  memset(&src, 0, sizeof(src));
  src.input      = NULL;
  src.tuner      = 0;
  src.frequency  = 0;
  src.delay      = config->delay;
  src.timeout    = 10; /* seconds */
  src.use_read   = 0;
  src.width      = width;
  src.height     = height;
  src.fps        = fps;

  if(src_open(&src, dev_name) == -1) return(-1);

  return 0;
}

int capture_frame(src_t *src)
{
  return src_grab(&src);
}

void camera_off(&src)
{
  src_close(&src);
}

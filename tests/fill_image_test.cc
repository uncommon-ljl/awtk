﻿#include "base/pixel.h"
#include "base/color.h"
#include "base/bitmap.h"
#include "blend/image_g2d.h"
#include "gtest/gtest.h"
#include "common.h"

static void test_fill_image(bitmap_format_t fmt) {
  uint32_t w = 8;
  uint32_t h = 8;
  bitmap_t* b = bitmap_create_ex(w, h, fmt);
  color_t bg = color_init(0x40, 0x60, 0x80, 0xff);
  rect_t r = rect_init(2, 2, 3, 3);
  uint32_t bpp = bitmap_get_bpp(b);

  ASSERT_EQ(image_fill(b, &r, bg), RET_OK);
  bitmap_dump(b);

  bitmap_check(b, &r, bg.rgba);

  bg = color_init(0x20, 0x30, 0x40, 0x20);
  ASSERT_EQ(image_fill(b, &r, bg), RET_OK);
  bitmap_dump(b);
  if (bpp == 2) {
    bg = color_init(0x38, 0x58, 0x70, 0xff);
  } else {
    bg = color_init(0x3b, 0x59, 0x77, 0xff);
  }

  bitmap_check(b, &r, bg.rgba);

  bitmap_destroy(b);
}

TEST(FillImage, BITMAP_FMT_BGRA8888) {
  test_fill_image(BITMAP_FMT_BGRA8888);
}

TEST(FillImage, BITMAP_FMT_BGR888) {
  test_fill_image(BITMAP_FMT_BGR888);
}

TEST(FillImage, BITMAP_FMT_BGR565) {
  test_fill_image(BITMAP_FMT_BGR565);
}

TEST(FillImage, BITMAP_FMT_RGB565) {
  test_fill_image(BITMAP_FMT_RGB565);
}

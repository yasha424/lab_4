#pragma once
#include <iostream>

#pragma pack(push, 1)
class BMPHEAD{
public:
  uint16_t type;
  uint32_t size;
  uint16_t reserved[2];
  uint32_t headersize;
  uint32_t infosize;
  uint32_t width;
  uint32_t height;
  uint16_t biPlanes;
  uint16_t bits;
  uint32_t biCompression;
  uint32_t biSizeImage;
  uint32_t biXPelsPerMeter;
  uint32_t biYPelsPerMeter;
  uint32_t biClrUsed;
  uint32_t biClrImportant;
  // BMPHEAD(){
  //   type = 0x424d;
  //   size = 0xfc310000;
  //   reserved[0] = 0;
  //   reserved[1] = 0;
  //   headersize = 0x36000000;
  //   infosize = 0x28000000;
  //   width = 65;
  //   height = 65;
  //   biPlanes = 1;
  //   bits = 24;
  //   biCompression;
  //   biSizeImage;
  //   biXPelsPerMeter;
  //   biYPelsPerMeter;
  //   biClrUsed;
  //   biClrImportant;
  // }
};
#pragma pack(pop)


typedef struct {
     uint8_t blue;
     uint8_t green;
     uint8_t red;
} __attribute__((__packed__)) PIXELDATA;

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
  BMPHEAD(){
    type = 19778;
    size = 12796;
    reserved[0] = 0;
    reserved[1] = 0;
    headersize = 54;
    infosize = 40;
    width = 65;
    height = 65;
    biPlanes = 1;
    bits = 24;
    biCompression = 0;
    biSizeImage = 12742;
    biXPelsPerMeter = 2834;
    biYPelsPerMeter = 2834;
    biClrUsed = 0;
    biClrImportant = 0;
  }
};
#pragma pack(pop)


class PIXELDATA {
public:
     uint8_t blue;
     uint8_t green;
     uint8_t red;
     PIXELDATA(){
         blue = 255;
         green = 255;
         red = 255;
     }
     PIXELDATA(int r, int g, int b){
         red = r;
         green = g;
         blue = b;
     }
};

#pragma once
#include <iostream>

#pragma pack(push, 1)
class BMPHEAD{
  uint16_t type;
  uint32_t size;
  uint16_t reserved[2];
  // uint16_t reserved2;
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

public:
  BMPHEAD(){
    type = 19778;
    size = 24883254;
    reserved[0] = 0;
    reserved[1] = 0;
    headersize = 54;
    infosize = 40;
    width = 0;
    height = 0;
    biPlanes = 1;
    bits = 24;
    biCompression = 0;
    biSizeImage = 12742;
    biXPelsPerMeter = 2834;
    biYPelsPerMeter = 2834;
    biClrUsed = 0;
    biClrImportant = 0;
  }
  uint32_t getWidth(){
      return width;
  }
  uint32_t getHeight(){
      return height;
  }
  void changeSize(double k){
      width *= k;
      height *= k;
      int padding = (4 - ((width * 3) % 4)) % 4;
      size = 54 + height * width * 3 + padding * height;
  }
};


class PIXELDATA {
     private:
     uint8_t blue;
     uint8_t green;
     uint8_t red;
     public:
     PIXELDATA();
     PIXELDATA(int r, int g, int b);
     void change(int r, int g, int b);
};
#pragma pack(pop)

class Image{
    BMPHEAD bh;
    PIXELDATA** pixels;

public:
    Image(){}
    int getWidth();
    int getHeight();
    void copy(const char* filename);
    void resize(const char* filename, int k);
    void interpolation(const char* filename, double k);
};

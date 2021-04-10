typedef struct{
  int16_t   bfType;
  int32_t  bfSize;
  int16_t   bfReserved1;
  int16_t   bfReserved2;
  int32_t  bfOffBits;
  int32_t  biSize;
  int32_t   width;
  int32_t   height;
  int16_t   biPlanes;
  int16_t   biBitCount;
  int32_t  biCompression;
  int32_t  biSizeImage;
  int32_t   biXPelsPerMeter;
  int32_t   biYPelsPerMeter;
  int32_t  biClrUsed;
  int32_t  biClrImportant;
} __attribute__((__packed__)) BMPHEAD;


typedef struct {
     int8_t redComponent;
     int8_t greenComponent;
     int8_t blueComponent;
} PIXELDATA;

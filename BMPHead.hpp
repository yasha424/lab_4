typedef struct{
  int16_t type;
  int32_t size;
  int16_t reserved[2];
  int32_t headersize;
  int32_t infosize;
  int32_t width;
  int32_t height;
  int16_t biPlanes;
  int16_t bits;
  int32_t biCompression;
  int32_t biSizeImage;
  int32_t biXPelsPerMeter;
  int32_t biYPelsPerMeter;
  int32_t biClrUsed;
  int32_t biClrImportant;
} __attribute__((__packed__)) BMPHEAD;


typedef struct {
     int8_t blue;
     int8_t green;
     int8_t red;
} PIXELDATA;

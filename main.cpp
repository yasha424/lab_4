#include <iostream>
// #include <fstream>
#include <string>
#include "BMPHead.hpp"
using namespace std;

int main(int argc, char* argv[]){

  if (argc != 4) {
    cout << "Incorrect input, for example use: \"./main bmp.bmp newbmp.bmp 3\"" << endl;
    return 0;
  }

  char* infile = argv[1];
  char* outfile = argv[2];
  int change = stoi(argv[3]);

  FILE* inptr = fopen(infile, "r");
  FILE* outptr = fopen(outfile, "w");

  BMPHEAD bh, out_bh;
  fread(&bh, sizeof(BMPHEAD), 1, inptr);

  fwrite(&bh, sizeof(BMPHEAD), 1, outptr);

  int padding =  (4 - (bh.width * sizeof(PIXELDATA)) % 4) % 4;

  PIXELDATA pixel;

  for (size_t i = 0; i < bh.height; i++) {
      pixel.red = 22;
      pixel.green = 180;
      pixel.blue = 235;
      for (size_t j = 0; j < bh.width; j++) {
          pixel.red += 2;
          pixel.green += 1;
          pixel.blue += -2;
          fwrite(&pixel, sizeof(PIXELDATA), 1, outptr);
      }
      for (size_t j = 0; j < padding; j++) {
          fputc(0x00, outptr);
      }
  }



  fclose(outptr);
  fclose(inptr);
}

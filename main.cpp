#include <iostream>
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

  BMPHEAD in_bh, out_bh;

  fread(&in_bh, sizeof(BMPHEAD), 1, inptr);
  out_bh = in_bh;

  out_bh.height = in_bh.height * change;
  out_bh.width = in_bh.width * change;

  int in_padding = (4 - ((in_bh.width * 3) % 4)) % 4;
  int out_padding = (4 - ((out_bh.width * 3) % 4)) % 4;

  out_bh.size = 54 + out_bh.height * out_bh.width * 3 + out_padding * out_bh.height;

  fwrite(&out_bh, sizeof(BMPHEAD), 1, outptr);

  PIXELDATA** pixels= new PIXELDATA*[in_bh.height];
  for (size_t i = 0; i < in_bh.height; i++) {
      pixels[i] = new PIXELDATA[in_bh.width];
  }

  PIXELDATA pixel;

  for (size_t i = 0; i < in_bh.height; i++) {
      for (size_t j = 0; j < in_bh.width; j++) {
          fread(&pixels[i][j], sizeof(PIXELDATA), 1, inptr);
      }
      fseek(inptr, in_padding, SEEK_CUR);
  }

  for (size_t i = 0; i < in_bh.height; i++) {
      for (size_t j = 0; j < change; j++) {
          for (size_t k = 0; k < in_bh.width; k++) {
              for (size_t l = 0; l < change; l++) {
                  fwrite(&pixels[i][k], sizeof(PIXELDATA), 1, outptr);
              }
          }
          for (size_t l = 0; l < out_padding; l++) {
              fputc(0x00, outptr);
          }
      }
  }


  fclose(inptr);
  fclose(outptr);
}

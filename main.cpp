#include <iostream>
#include <fstream>
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

  BMPHEAD bh;
  fread(&bh, sizeof(BMPHEAD), 1, inptr);

  fwrite(&bh, sizeof(BMPHEAD), 1, outptr);

  for (size_t i = 0; i < bh.height; i++) {
    for (size_t j = 0; j < bh.width; j++) {
      PIXELDATA pixel;
      fread(&pixel, sizeof(PIXELDATA), 1, inptr);

      fwrite(&pixel, sizeof(PIXELDATA), 1, outptr);
    }
  }

}

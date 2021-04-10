#include <iostream>
#include <fstream>
#include <string>
#include "BMPHead.hpp"
using namespace std;

int main(int argc, char* argv[]){
  char* infile = argv[1];
  char* outfile = argv[2];

  FILE* inptr = fopen(infile, "r");
  FILE* outptr = fopen(outfile, "w");

  BMPHEAD bh;
  fread(&bh, sizeof(BMPHEAD), 1, inptr);

  cout << bh.height << endl << bh.width << endl;

}

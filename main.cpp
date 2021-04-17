#include <iostream>
#include "image.hpp"
using namespace std;

int main(int argc, char* argv[]){

  if (argc != 4) {
    cout << "Incorrect input, for example use: \"./main bmp.bmp newbmp.bmp 3\"" << endl;
    return 0;
  }

  char* infile = argv[1];
  char* outfile = argv[2];
  int change = stoi(argv[3]);

  Image image;
  image.copy(infile);
  image.resize(outfile, change);
}

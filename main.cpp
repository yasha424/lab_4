#include <iostream>
#include <ctime>
#include "image.hpp"
using namespace std;

int main(int argc, char* argv[]){

  if (argc != 4) {
    cout << "Incorrect input, for example use: \"./main input.bmp output.bmp 3\"" << endl;
    return 0;
  }

  char* infile = argv[1];
  char* outfile = argv[2];
  double k = stof(argv[3]);

  Image image;
  image.copy(infile);
  if (image.getWidth() == 0 || image.getHeight() == 0) {
      cout << "file cannot be opened or is empty :(" << endl;
  }
  else{
      double start = clock();
      if ((int)k == k && k > 0) {
          image.resize(outfile, k);
      }
      else if (k < 0) {
          image.mirror(outfile, -k);
      }
      else{
          image.interpolation(outfile, k);
      }
      double end = clock();
      cout << "Enlarging image " << k << " times... Done.\n";
      cout << "Written result to " << argv[2] << endl;
      cout << "Elapsed time is: " << (end - start) / 1000000 << "s" << endl;
  }
}

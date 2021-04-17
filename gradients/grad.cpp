#include <iostream>
#include "BMPHead.hpp"
using namespace std;

int main() {
    const char* filename;  // rgb(255, 0, 208);
    string name = "grad.bmp";
    // cin >> name;
    filename = name.data();
    FILE* outptr = fopen(filename, "w");
    BMPHEAD bh;
    bh.biXPelsPerMeter = 72;
    bh.biYPelsPerMeter = 72;


    fwrite(&bh, sizeof(BMPHEAD), 1, outptr);
    // PIXELDATA pixel;
    for (size_t i = 0; i < bh.height; i++) {
        PIXELDATA pixel(140, 255, 0);
        for (size_t j = 0; j < bh.width; j++) {
            if (j % 34 == 0) {
                pixel.red += 1;
            }
            if (j % 16 == 0) {
                pixel.green += -1;
            }
            if (j % 30 == 0) {
                pixel.blue += 1;
            }
            fwrite(&pixel, sizeof(PIXELDATA), 1, outptr);
        }
    }
    fclose(outptr);
}

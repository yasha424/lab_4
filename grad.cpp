#include <iostream>
#include "BMPHead.hpp"
using namespace std;

int main() {
    const char* filename;  // rgb(0, 230, 255);
    string name = "grad.bmp";
    // cin >> name;
    filename = name.data();
    FILE* outptr = fopen(filename, "w");
    BMPHEAD bh;
    fwrite(&bh, sizeof(BMPHEAD), 1, outptr);
    // PIXELDATA pixel;
    for (size_t i = 0; i < bh.height; i++) {
        PIXELDATA pixel(140, 255, 0);
        for (size_t j = 0; j < bh.width; j++) {
            if (j % 32 == 0) {
                pixel.red += -1;
            }
            if (j % 240 == 0) {
                pixel.green += -1;
            }
            if (j % 20 == 0) {
                pixel.blue += 1;
            }
            fwrite(&pixel, sizeof(PIXELDATA), 1, outptr);
        }
    }
    fclose(outptr);
}

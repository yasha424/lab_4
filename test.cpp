#include <iostream>
#include "BMPHead.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    BMPHEAD bh;
    FILE* outfile = fopen("grad.bmp", "w");

    if (outfile) {
        cout << "file is created" << endl;
    }

    bh.height = 60;
    bh.width = 100;
    bh.size = 54 + (bh.height * bh.width) * 3;

    fwrite(&bh, sizeof(BMPHEAD), 1, outfile);

    int padding = (4 - (bh.width * sizeof(PIXELDATA)) % 4) % 4;

    for (size_t i = 0; i < bh.height; i++) {
        PIXELDATA pixel(155, 154, 55);
        for (size_t j = 0; j < bh.width; j++) {
            pixel.red += 1;
            pixel.green += 1;
            pixel.blue += 0;
            fwrite(&pixel, sizeof(PIXELDATA), 1, outfile);
            for (size_t j = 0; j < padding; j++) {
                fputc(0x00, outfile);
            }
        }
    }
    // FILE* infile = fopen("bmp.bmp", "r");
    // fread(&bh, sizeof(BMPHEAD), 1, infile);
    // cout << bh.type << endl;
    // cout << bh.size << endl;
    // cout << bh.reserved[0] << endl;
    // cout << bh.reserved[1] << endl;
    // cout << bh.headersize << endl;
    // cout << bh.infosize << endl;
    // cout << bh.width << endl;
    // cout << bh.height << endl;
    // cout << bh.biPlanes << endl;
    // cout << bh.bits << endl;
    // cout << bh.biCompression << endl;
    // cout << bh.biSizeImage << endl;
    // cout << bh.biXPelsPerMeter << endl;
    // cout << bh.biYPelsPerMeter << endl;
    // cout << bh.biClrUsed << endl;
    // cout << bh.biClrImportant << endl;
    fclose(outfile);
}

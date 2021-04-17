#include <iostream>
#include "image.hpp"
using namespace std;

PIXELDATA::PIXELDATA(){
    blue = 255;
    green = 255;
    red = 255;
}
PIXELDATA::PIXELDATA(int r, int g, int b){
    red = r;
    green = g;
    blue = b;
}
void PIXELDATA::change(int r, int g, int b){
    red += r;
    green += g;
    blue += b;
}


void Image::copy(const char* filename){
    FILE* file = fopen(filename, "r");
    if (file) {
        fread(&bh, sizeof(BMPHEAD), 1, file);
        // cout << bh.getHeight() << ", " << bh.getWidth() << endl;
        int padding = (4 - bh.getWidth() * sizeof(PIXELDATA) % 4) % 4;
        pixels = new PIXELDATA*[bh.getHeight()];

        for (size_t i = 0; i < bh.getHeight(); i++) {
            pixels[i] = new PIXELDATA[bh.getWidth()];
            for (size_t j = 0; j < bh.getWidth(); j++) {
                fread(&pixels[i][j], sizeof(PIXELDATA), 1, file);
            }
            fseek(file, padding, SEEK_CUR);
        }
        fclose(file);
    }
}

void Image::resize(const char* filename, int k){
    FILE* file = fopen(filename, "w");
    bh.changeSize(k);
    fwrite(&bh, sizeof(BMPHEAD), 1, file);
    int padding = (4 - bh.getWidth() * sizeof(PIXELDATA) % 4) % 4;
    for (size_t i = 0; i < bh.getHeight(); i++) {
        for (size_t j = 0; j < bh.getWidth(); j++) {
            fwrite(&pixels[i/k][j/k], sizeof(PIXELDATA), 1, file);
        }
        for (size_t k = 0; k < padding; k++) {
            fputc(0x00, file);
        }
    }
    fclose(file);
}

int Image::getWidth(){
    return bh.getWidth();
}

int Image::getHeight(){
    return bh.getHeight();
}

void Image::interpolation(const char* filename, double k){
    FILE* file = fopen(filename, "w");
    bh.changeSize(k);
    fwrite(&bh, sizeof(BMPHEAD), 1, file);
    int padding = (4 - bh.getWidth() * sizeof(PIXELDATA) % 4) % 4;

    PIXELDATA** pixel = new PIXELDATA*[bh.getHeight()];
    for (size_t i = 0; i < bh.getHeight(); i++) {
        pixel[i] = new PIXELDATA[bh.getWidth()];
    }

    for (size_t i = 0; i < (int)bh.getHeight()/k; i++) {
        for (size_t j = 0; j < (int)bh.getWidth()/k; j++) {
            pixel[int(i*k)][int(j*k)] = pixels[i][j];
        }
    }

    for (size_t i = 0; i < (int)bh.getHeight(); i++) {
        for (size_t j = 0; j < (int)bh.getWidth(); j++) {
            fwrite(&pixel[i][j], sizeof(PIXELDATA), 1, file);
        }
        for (size_t j = 0; j < padding; j++) {
            fputc(0x00, file);
        }
    }

    fclose(file);
}

#include "image.hpp"
void Image::copy(const char* filename){
    FILE* file = fopen(filename, "r");
    fread(&bh, sizeof(BMPHEAD), 1, file);
    pixels = new PIXELDATA*[bh.getHeight()];
    int padding = (4 - bh.getWidth() * sizeof(PIXELDATA) % 4) % 4;
    for (size_t i = 0; i < bh.getHeight(); i++) {
        pixels[i] = new PIXELDATA[bh.getWidth()];
        for (size_t j = 0; j < bh.getWidth(); j++) {
            fread(&pixels[i][j], sizeof(PIXELDATA), 1, file);
        }
        fseek(file, padding, SEEK_CUR);
    }
    fclose(file);
}

void Image::resize(const char* filename, int k){
    FILE* file = fopen(filename, "w");
    bh.changeSize(k);
    fwrite(&bh, sizeof(BMPHEAD), 1, file);
    int padding = (4 - bh.getWidth() * sizeof(PIXELDATA) % 4) % 4;
    for (size_t i = 0; i < bh.getWidth(); i++) {
        for (size_t j = 0; j < bh.getHeight(); j++) {
            fwrite(&pixels[i/k][j/k], sizeof(PIXELDATA), 1, file);
        }
        for (size_t j = 0; j < padding; j++) {
            fputc(0x00, file);
        }
    }
    fclose(file);
}

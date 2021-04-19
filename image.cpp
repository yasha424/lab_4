#include <iostream>
#include <iomanip>
#include "image.hpp"
using namespace std;

PIXELDATA::PIXELDATA(){
    blue = 0;
    green = 0;
    red = 0;
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

    PIXELDATA pixel;

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
    bool** checked = new bool*[bh.getHeight()];
    for (size_t i = 0; i < bh.getHeight(); i++) {
        pixel[i] = new PIXELDATA[bh.getWidth()];
        checked[i] = new bool[bh.getWidth()];
    }

    for (size_t i = 0; i < bh.getHeight()/k; i++) {
        for (size_t j = 0; j < bh.getWidth()/k; j++) {
            pixel[int(i*k)][int(j*k)] = pixels[i][j];
            checked[int(i*k)][int(j*k)] = true;
        }
        delete[] pixels[i];
    }
    delete[] pixels;

    int redstart, greenstart, bluestart, redend, greenend, blueend;
    int i = 0;

    for (size_t i = 0; i < bh.getHeight()/k; i++) {
        int j = 0;
        while (j < bh.getWidth()) {
            int count = 1;
            redstart = pixel[int(i*k)][j].red;
            greenstart = pixel[int(i*k)][j].green;
            bluestart = pixel[int(i*k)][j].blue;
            j++;
            while (!checked[int(i*k)][j] && j < bh.getWidth() - 1) {
                checked[int(i*k)][j] = true;
                count++;
                j++;
            }
            redend = pixel[int(i*k)][j].red;
            greenend = pixel[int(i*k)][j].green;
            blueend = pixel[int(i*k)][j].blue;

            int boostred = (redend - redstart) / count;
            int boostgreen = (greenend - greenstart) / count;
            int boostblue = (blueend - bluestart) / count;


            for (size_t l = j - count + 1; l < j; l++) {
                pixel[int(i*k)][l].red = boostred + pixel[int(i*k)][l-1].red;
                pixel[int(i*k)][l].green = boostgreen + pixel[int(i*k)][l-1].green;
                pixel[int(i*k)][l].blue = boostblue + pixel[int(i*k)][l-1].blue;
            }

        }
        checked[int(i*k)][bh.getWidth()-1] = true;

    }

    for (size_t i = 0; i < bh.getWidth(); i++) {
        int j = 0;
        while (j < bh.getHeight()-1) {
            int count = 1;
            redstart = pixel[j][i].red;
            greenstart = pixel[j][i].green;
            bluestart = pixel[j][i].blue;
            j++;
            while (!checked[j][i] && j < bh.getHeight() - 1) {
                checked[j][i] = true;
                count++;
                j++;
            }
            redend = pixel[j][i].red;
            greenend = pixel[j][i].green;
            blueend = pixel[j][i].blue;

            int boostred = (redend - redstart) / count;
            int boostgreen = (greenend - greenstart) / count;
            int boostblue = (blueend - bluestart) / count;
            for (size_t l = j - count + 1; l < j; l++) {
                pixel[l][i].red = boostred + pixel[l-1][i].red;
                pixel[l][i].green = boostgreen + pixel[l-1][i].green;
                pixel[l][i].blue = boostblue + pixel[l-1][i].blue;
            }
        }
    }


    for (int i = 0; i < bh.getHeight(); i++) {
        for (size_t j = 0; j < bh.getWidth(); j++) {
            fwrite(&pixel[i][j], sizeof(PIXELDATA), 1, file);
        }
        for (size_t j = 0; j < padding; j++) {
            fputc(0x00, file);
        }
    }

    fclose(file);
}

void Image::mirror(const char* filename, double k){
    FILE* file = fopen(filename, "w");
    bh.changeSize(k);
    fwrite(&bh, sizeof(BMPHEAD), 1, file);
    int padding = (4 - bh.getWidth() * sizeof(PIXELDATA) % 4) % 4;

    PIXELDATA** pixel = new PIXELDATA*[bh.getHeight()];
    bool** checked = new bool*[bh.getHeight()];
    for (size_t i = 0; i < bh.getHeight(); i++) {
        pixel[i] = new PIXELDATA[bh.getWidth()];
        checked[i] = new bool[bh.getWidth()];
    }

    for (size_t i = 0; i < bh.getHeight()/k; i++) {
        for (size_t j = 0; j < bh.getWidth()/k; j++) {
            pixel[int(i*k)][int(j*k)] = pixels[i][j];
            checked[int(i*k)][int(j*k)] = true;
        }
        delete[] pixels[i];
    }
    delete[] pixels;

    int redstart, greenstart, bluestart, redend, greenend, blueend;
    int i = 0;

    for (size_t i = 0; i < bh.getHeight()/k; i++) {
        int j = 0;
        while (j < bh.getWidth()) {
            int count = 1;
            redstart = pixel[int(i*k)][j].red;
            greenstart = pixel[int(i*k)][j].green;
            bluestart = pixel[int(i*k)][j].blue;
            j++;
            while (!checked[int(i*k)][j] && j < bh.getWidth() - 1) {
                checked[int(i*k)][j] = true;
                count++;
                j++;
            }
            redend = pixel[int(i*k)][j].red;
            greenend = pixel[int(i*k)][j].green;
            blueend = pixel[int(i*k)][j].blue;

            int boostred = (redend - redstart) / count;
            int boostgreen = (greenend - greenstart) / count;
            int boostblue = (blueend - bluestart) / count;


            for (size_t l = j - count + 1; l < j; l++) {
                pixel[int(i*k)][l].red = boostred + pixel[int(i*k)][l-1].red;
                pixel[int(i*k)][l].green = boostgreen + pixel[int(i*k)][l-1].green;
                pixel[int(i*k)][l].blue = boostblue + pixel[int(i*k)][l-1].blue;
            }

        }
        checked[int(i*k)][bh.getWidth()-1] = true;

    }

    for (size_t i = 0; i < bh.getWidth(); i++) {
        int j = 0;
        while (j < bh.getHeight()-1) {
            int count = 1;
            redstart = pixel[j][i].red;
            greenstart = pixel[j][i].green;
            bluestart = pixel[j][i].blue;
            j++;
            while (!checked[j][i] && j < bh.getHeight() - 1) {
                checked[j][i] = true;
                count++;
                j++;
            }
            redend = pixel[j][i].red;
            greenend = pixel[j][i].green;
            blueend = pixel[j][i].blue;

            int boostred = (redend - redstart) / count;
            int boostgreen = (greenend - greenstart) / count;
            int boostblue = (blueend - bluestart) / count;
            for (size_t l = j - count + 1; l < j; l++) {
                pixel[l][i].red = boostred + pixel[l-1][i].red;
                pixel[l][i].green = boostgreen + pixel[l-1][i].green;
                pixel[l][i].blue = boostblue + pixel[l-1][i].blue;
            }
        }
    }


    for (int i = 0; i < bh.getHeight(); i++) {
        for (int j = bh.getWidth() - 1; j >= 0; j--) {
            fwrite(&pixel[i][j], sizeof(PIXELDATA), 1, file);
        }
        for (size_t j = 0; j < padding; j++) {
            fputc(0x00, file);
        }
    }

    fclose(file);
}

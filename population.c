#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "population.h"

// getters setters de Color
void setR(Color c, int r){c->r = r;}
int getR(Color c){return c->r;}

void setG(Color c, int g){c->g = g;}
int getG(Color c){return c->g;}

void setB(Color c, int b){c->b = b;}
int getB(Color c){return c->b;}

Color createColor(int r, int g, int b) {
    Color c = (Color)malloc(sizeof(col));
    setR(c, r);
    setG(c, g);
    setB(c, b);
    return c;
}

void destroyColor(Color c) {free(c);}


// getters setters de Pixel
void setColor(Pixel p, Color c) {
    p.color = c;
}

Color getColor(Pixel p) {
    return p.color;
}

void setX(Pixel p, int x) {
    p.x = x;
}

int getX(Pixel p) {
    return p.x;
}

void setY(Pixel p, int y) {
    p.y = y;
}

int getY(Pixel p) {
    return p.y;
}

Pixel createPixel(int x, int y, Color c) {
    Pixel p;
    setX(p, x);
    setY(p, y);
    setColor(p, c);
    return p;
}

// getters setters de Image

Pixel getPixel(Image image, int x, int y) {
    return image.tab[x][y];
}

void setPixel(Image image, int x, int y, Pixel p) {
    image.tab[x][y] = p;
}

int getWidth(Image image) {
    return image.width;
}

int getHeight(Image image) {
    return image.height;
}


Pixel ** createPixelTab(int width, int height) {
    Pixel ** tab = (Pixel**)malloc(sizeof(Pixel*) * width);
    for (int i = 0; i < width; i++) {
        tab[i] = (Pixel*)malloc(sizeof(Pixel) * height);
    }
    return tab;
}

Image createImage(int width, int height) {
    Image image;
    image.width = width;
    image.height = height;
    image.tab = createPixelTab(width, height);
    return image;
}

void destroyImage(Image image) {
    for (int i = 0; i < image.width; i++) {
        free(image.tab[i]);
    }
    free(image.tab);
}

void createPopulation(Image image, int populationSize, Color c, bool val) {
    for (int i = 0; i < populationSize; i++){
        Pixel p = createPixel(image.width / 2 + i * (int)cos((double)i), image.height / 2 + i * (int)sin((double)i), c);
        setPixel(image, getX(p), getY(p), p);
    }
}
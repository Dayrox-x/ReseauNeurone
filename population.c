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

void setA(Color c, int a){c->a = a;}
int getA(Color c){return c->a;}

Color createColor(int r, int g, int b, int a) {
    Color c = (Color)malloc(sizeof(SDL_Color));
    setR(c, r);
    setG(c, g);
    setB(c, b);
    setA(c, a);
    return c;
}

void destroyColor(Color c) {free(c);}


// getters setters de Pixel
void setColor(Pixel p, Color c) {
    p->color = c;
}

Color getColor(Pixel p) {
    return p->color;
}

void setX(Pixel p, int x) {
    p->x = x;
}

int getX(Pixel p) {
    return p->x;
}

void setY(Pixel p, int y) {
    p->y = y;
}

int getY(Pixel p) {
    return p->y;
}

Pixel createPixel(int x, int y, Color c) {
    Pixel p = malloc(sizeof(pxl));
    setX(p, x);
    setY(p, y);
    setColor(p, c);
    return p;
}

void destroyPixel(Pixel p) {
    free(p);
}

// getters setters de Image

Pixel getPixel(Image image, int x, int y) {
    return image->tab[x][y];
}

<<<<<<< HEAD
void setPixel(Image image, int x, int y, Pixel p) {
=======
void setPixel(Image *image, int x, int y, Pixel p) {
    if (x < 0 || x >= image->width || y < 0 || y >= image->height) {
        printf("Erreur: setPixel hors limites (%d, %d) !\n", x, y);
        return;
    }
>>>>>>> 32885d9071a9236770d672b5f235472b6b2ac7f7
    image->tab[x][y] = p;
}


int getWidth(Image image) {
    return image->width;
}

int getHeight(Image image) {
    return image->height;
}

Color getPixelColor(Image image, int x, int y) {
    return getColor(getPixel(image, x, y));
}

void setPixelColor(Image image, int x, int y, Color c) {
    setColor(getPixel(image, x, y), c);
}



Pixel ** createPixelTab(int width, int height, Color c) {
    Pixel ** tab = (Pixel**)malloc(sizeof(Pixel*) * width);
    for (int i = 0; i < width; i++) {
<<<<<<< HEAD
        tab[i] = (Pixel*)malloc(sizeof(Pixel) * height);
        for (int j = 0; j < height; j++) {
            tab[i][j] = createPixel(i, j, c);
=======
        for (int j = 0; j < height; j++) {
            tab[i][j] = createPixel(i, j, createColor(0, 0, 0)); // Pixels noirs par défaut
>>>>>>> 32885d9071a9236770d672b5f235472b6b2ac7f7
        }
    }
    return tab;
}

Image createImage(int width, int height, Color c) {
    Image image = (Image)malloc(sizeof(img));
    image->width = width;
    image->height = height;
    image->tab = createPixelTab(width, height, c);
    return image;
}

void destroyImage(Image image) {
<<<<<<< HEAD
    for (int i = 0; i < image->width; i++) {
        for (int j = 0; j < image->height; j++) {
            destroyPixel(image->tab[i][j]);
        }
        free(image->tab[i]);
=======
    if (image.tab == NULL) return;
    for (int i = 0; i < image.width; i++) {
        if (image.tab[i] != NULL) {
            free(image.tab[i]);
        }
>>>>>>> 32885d9071a9236770d672b5f235472b6b2ac7f7
    }
    free(image->tab);
    free(image);
}

void createPopulation(Image image, int populationSize, Color c, bool val) {
<<<<<<< HEAD
    int sign;
    if (val){sign = 1;} else {sign = -1;}
    int x = 0, y = 0;
    float i = 0;
    while (x < image->width && y < image->height && x >= 0 && y >= 0) {
        float cos_x = cos(i);
        float sin_y = sin(i);
        x = (image->width / 2 + sign * (int)(i * cos_x));
        y = (image->height / 2 + sign * (int)(i * sin_y));
        if (x < image->width && y < image->height && x >= 0 && y >= 0) {
            setPixelColor(image, x, y, c);
        }
        i += 0.2;
=======
    int width = getWidth(image);
    int height = getHeight(image);

    for (int i = 0; i < populationSize; i++) {
        int x = width / 2 + (int)(50 * cos(i)); 
        int y = height / 2 + (int)(50 * sin(i));

        if (x < 0 || x >= width || y < 0 || y >= height) {
            printf("Coordonnées invalides : x=%d, y=%d, ignoré.\n", x, y);
            continue;
        }

        Pixel p = createPixel(x, y, c);
        setPixel(&image, x, y, p);
>>>>>>> 32885d9071a9236770d672b5f235472b6b2ac7f7
    }
}

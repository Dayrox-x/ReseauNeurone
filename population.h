#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int r, g, b;
} col;

typedef col* Color;

typedef struct {
    int x;
    int y;
    Color color; // RGB
} Pixel;

typedef struct {
    Pixel** tab;
    int width, height;
} Image;

// getters setters de Color
void setR(Color c, int r);
int getR(Color c);

void setG(Color c, int g);
int getG(Color c);

void setB(Color c, int b);
int getB(Color c);

Color createColor(int r, int g, int b);
void destroyColor(Color c);

// getters setters de Pixel
void setColor(Pixel p, Color c);
Color getColor(Pixel p);

void setX(Pixel p, int x);
int getX(Pixel p);

void setY(Pixel p, int y);
int getY(Pixel p);

Pixel createPixel(int x, int y, Color c);

// getters setters de Image
Pixel getPixel(Image image, int x, int y);
void setPixel(Image *image, int x, int y, Pixel p);

int getWidth(Image image);
int getHeight(Image image);


Pixel** createPixelTab(int width, int height);

Image createImage(int width, int height);

void destroyImage(Image image);

void createPopulation(Image image, int populationSize, Color c, bool val);
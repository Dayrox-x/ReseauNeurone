/**
 * \file population.c
 * \brief Fonctions de gestion des populations (création, destruction, modifications)
 * \author Simon Cossais
 * \author Paul Sarazin
 * \date 28/02/2025
 */

 #include "population.h"
 
 // getters setters de Color
 void setR(Color c, int r){c->r = r % 256;}
 int getR(Color c){return c->r;}
 
 void setG(Color c, int g){c->g = g % 256;}
 int getG(Color c){return c->g;}
 
 void setB(Color c, int b){c->b = b % 256;}
 int getB(Color c){return c->b;}
 
 void setA(Color c, int a){c->a = a % 256;}
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
    if (getColor(p) != NULL){
        destroyColor(getColor(p));
    }
    p->color = createColor(getR(c), getG(c), getB(c), getA(c));
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
    p->color = NULL;
    setColor(p, createColor(getR(c), getG(c), getB(c), getA(c)));
    return p;
 }
 
 void destroyPixel(Pixel p) {
    destroyColor(getColor(p));
    free(p);
 }
 
 // getters setters de Image
 
 Pixel getPixel(Image image, int x, int y) {
    return image->tab[x][y];
 }
 
 void setPixel(Image image, int x, int y, Pixel p) {
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
        tab[i] = (Pixel*)malloc(sizeof(Pixel) * height);
        for (int j = 0; j < height; j++) {
            tab[i][j] = createPixel(i, j, c);
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
 
 void destroyPixelTab(Pixel ** tab, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            destroyPixel(tab[i][j]);
        }
        free(tab[i]);
    }
    free(tab);
 }
 
 void destroyImage(Image image) {
    destroyPixelTab(image->tab, image->width, image->height);
    free(image);
 }


int getDatasetSize(Dataset d){
    return d->size;
}

Dataset createDataset(){
    Dataset d = malloc(sizeof(data));
    d->size = 0;
    d->tab = NULL;
}

void addDatasetPixel(Dataset d, Pixel p){
    d->size++;
    if (d->tab == NULL){
        d->tab = malloc(sizeof(Pixel*));
    } else {
        d->tab = realloc(d->tab, sizeof(Pixel*) * d->size);
    }
    assert(d->tab != NULL);
    d->tab[d->size-1] = p;
}

void destroyDataset(Dataset d){
    if (d->tab != NULL)
        free(d->tab);
    free(d);
}

Pixel getDatasetPixel(Dataset d, int i){
    return d->tab[i];
}
 

 void createPopulation(Image image, Dataset d, Color c, int val) {
    int x = 0, y = 0;
    float i = 0;
    while (x < image->width && y < image->height && x >= 0 && y >= 0) {
        float cos_x = cos(i);
        float sin_y = sin(i);
        x = (image->width / 2 + val * (int)(i * cos_x));
        y = (image->height / 2 + val * (int)(i * sin_y));
        if (x < image->width && y < image->height && x >= 0 && y >= 0) {
            setPixelColor(image, x, y, c);
            addDatasetPixel(d, getPixel(image, x, y));
        }
        i += 0.2;
    }
 }
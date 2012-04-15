#include "SimplexNoise.h"
#include <QApplication>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include "ASHNoise.h"
#include <cstdio>

static const unsigned int width = 512;
static const unsigned int height = 512;
static const unsigned int nOctaves = 16;
static const float  persistence = .5;
static const float frequency = .007;
static const float low = 0;
static const float high = 255;

int main(int argc, char* argv[]) {
    ASHNoise noise;
    QApplication app(argc, argv);
    QImage img(width, height, QImage::Format_RGB32);
    QLabel lbl;
    QPixmap pixmap;
    
    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            int value = (int)noise.octave(nOctaves, i, j, persistence, frequency, low, high);

            //if(value < 100) {
            //    value = 0;
            //}

            QRgb color = qRgb(value, value, value);
            img.setPixel(i, j, color);
        }
    }
    pixmap = QPixmap::fromImage(img);
    lbl.setPixmap(pixmap);
    lbl.show();
    pixmap.save("img.png");

    std::printf("%d %d %d %d\n", noise.getSeedX(), noise.getSeedY(), noise.getSeedZ(), noise.getSeedW()); 

    return app.exec();
}

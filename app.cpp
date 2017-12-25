#include <QApplication>

#include "image_processing.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ImageProcessing processor;
    processor.show();

    return app.exec();
}

#include <QApplication>
#include <QString>
#include <QFileDialog>
#include "Profiler.h"
#include "UVEditeur.h"
#include "UVCreateur.h"
#include "Cursus.h"

int main(int argc, char *argv[]){

    QApplication app(argc, argv);

    Profiler profiler;
    profiler.show();

return app.exec();
}

#ifndef PROFILER_H
#define PROFILER_H

#include <QApplication>
#include <QMainWindow>
#include <QInputDialog>
#include "UVEditeur.h"

class Profiler : public QMainWindow{
    Q_OBJECT

public:
    explicit Profiler(QWidget *parent = 0);

signals:

public slots:
    void openChargerUV();
    void openUV();
    void openChargerCursus();
    void openCursus();
    void nouvelleUV();
    void NouveauCursus();
    void SupprUV();
    void SupprCursus();
    void openChargerDossier();
    void openDossier();
};

#endif // PROFILER_H

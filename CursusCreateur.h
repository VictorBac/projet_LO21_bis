#ifndef CURSUSCREATEUR_H
#define CURSUSCREATEUR_H
#include"Profiler.h"
#include"UTProfiler.h"
#include"UVEditeur.h"
#include"Cursus.h"
#include"CursusEditeur.h"
#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

class CursusCreateur : public QWidget{
    Q_OBJECT

    Cursus& CurCur;
    QComboBox * List;
    QLineEdit* titre;
    QLineEdit* AjouterUneUV;
    QLineEdit* EnleverUneUV;
    QLineEdit* CreditCS;
    QLineEdit* CreditTM;
    QLineEdit* CreditTSH;
    QLineEdit* CreditLibre;
    QLabel* titreLabel;
    QLabel* uvLabel;
    QLabel* NbCreditsToGet;
    QLabel* CSLabel;
    QLabel* TMLabel;
    QLabel* CLLabel;
    QLabel* TSHLabel;
    QPushButton* annuler;
    QPushButton* sauverC;
    QPushButton* ajouter;
    QPushButton* enlever;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;
    QHBoxLayout* coucheH6;
    QHBoxLayout* coucheH7;
    QHBoxLayout* coucheH8;
    QHBoxLayout* coucheH9;
    QHBoxLayout* coucheH10;


public:
    explicit CursusCreateur(Cursus& CursusToEdit, QWidget *parent = 0);

signals:

public slots:
    void sauverCursus();
    void AjouterlUV();
    void EnleverlUV();

private slots:
    void activerSauverC();

};




#endif // CURSUSCREATEUR_H

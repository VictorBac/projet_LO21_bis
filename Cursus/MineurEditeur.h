#ifndef MINEUREDITEUR_H
#define MINEUREDITEUR_H
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
#include "UTProfiler.h"
#include "Cursus.h"
#include <QStackedWidget>


class MineurEditeur : public QWidget{
    Q_OBJECT

    Mineur& CurCur;
    QComboBox * Obligatoire;
    QComboBox * List;
    QLineEdit* titre;
    QLineEdit* AjouterUneUV;
    QLineEdit* EnleverUneUV;
    QLineEdit* CreditCS;
    QLineEdit* CreditTM;
    QLineEdit* CreditTSH;
    QLineEdit* CreditLibre;
    QLineEdit* ajouterObl;
    QLineEdit* enleverObl;
    QLabel * ObligLabel;
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
    QPushButton* AjouterUneUVObl;
    QPushButton* EnleverUneUVObl;
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
    QHBoxLayout* coucheH11;
    QHBoxLayout* coucheH12;
    QHBoxLayout* coucheH13;



public:
    explicit MineurEditeur(Mineur& MineurToEdit, QWidget *parent = 0);

signals:

public slots:
    void sauverCursus();
    void AjouterlUV();
    void EnleverlUV();
    void AjouterlUVObl();
    void EnleverlUVObl();

private slots:
    void activerSauverC();

};
#endif // MINEUREDITEUR_H

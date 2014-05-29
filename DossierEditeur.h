#ifndef DOSSIEREDITEUR_H
#define DOSSIEREDITEUR_H

#include "Dossier.h"
#include "DossierEditeur.h"
#include <QObject>
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



class DossierEditeur : public QWidget{
    Q_OBJECT

    Dossier& dossier;
    QComboBox * List; // Pour les inscriptions

    QLineEdit* id;
    QLabel* idLabel;
    QLineEdit* nom;
    QLabel* nomLabel;
    QLineEdit* prenom;
    QLabel* prenomLabel;

    QLineEdit* cursus;
    QLabel* cursusLabel;

    QLabel* inscriptionLabel;

    /*QTextEdit* titre;
    QLabel* titreLabel;
    QSpinBox* credits;
    QLabel* creditsLabel;
    QComboBox* categorie;
    QLabel* categorieLabel;
    QLabel* ouvertureLabel;
    QCheckBox* automne;
    QCheckBox* printemps;*/
    QPushButton* sauver;
    QPushButton* annuler;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;
    QHBoxLayout* coucheH6;

public:
    explicit DossierEditeur(Dossier& dossierToEdit, QWidget *parent = 0);

signals:

public slots:
    void sauverDossier();

private slots:
    void activerSauver(QString str="");
};


#endif // DOSSIEREDITEUR_H

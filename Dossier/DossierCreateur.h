#ifndef DOSSIERCREATEUR_H
#define DOSSIERCREATEUR_H


#include"Profiler.h"
#include"UTProfiler.h"
#include"Dossier.h"
#include"DossierEditeur.h"
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

class DossierCreateur : public QWidget{
    Q_OBJECT

    Dossier& doss;
    QComboBox * List;
    QLineEdit* id;
    QLineEdit* AjouterUneInscription;
    QLineEdit* EnleverUneInscription;

    QLabel* idLabel;
    QLabel* inscriptionLabel;
    QLabel* NbCreditsToGet;
    QLabel* CSLabel;
    QLabel* TMLabel;
    QLabel* CLLabel;
    QLabel* TSHLabel;
    QPushButton* annuler;
    QPushButton* sauverD;
    QPushButton* ajouter;
    QPushButton* enlever;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;

public:
    explicit DossierCreateur(Dossier& DossierToEdit, QWidget *parent = 0);

signals:

public slots:
    void sauverDossier();
    void AjouterInscription();
    void EnleverInscription();

private slots:
    void activerSauverD();

};



#endif // DOSSIERCREATEUR_H

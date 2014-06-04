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

    Dossier& dossier;


    QLineEdit* id;
    QLabel* idLabel;
    QLineEdit* nom;
    QLabel* nomLabel;
    QLineEdit* prenom;
    QLabel* prenomLabel;

    QLineEdit* cursus;
    QLabel* cursusLabel;

    QComboBox * List; // Pour les inscriptions
    QLabel* inscriptionLabel;
    QLineEdit* code;
    QLabel* codeLabel;
    QLineEdit* res;
    QLabel* resLabel;
    QLineEdit* saison;
    QLabel* saisonLabel;
    QLineEdit* annee;
    QLabel* anneeLabel;

    QComboBox * List2; // Pour les modifications d'inscriptions
    QLabel* modificationLabel;
    QLineEdit* code2;
    QLabel* code2Label;
  //  QLabel* code3Label;
    QLineEdit* res2;
    QLabel* res2Label;
    QLineEdit* saison2;
    QLabel* saison2Label;
    QLineEdit* annee2;
    QLabel* annee2Label;



    QPushButton* ajouter;
    QPushButton* enlever;
    QPushButton* ajouterInscription;
    QPushButton* annulerInscription;
    QPushButton* enleverInscription;
    QPushButton* modifierInscription;

    //QLineEdit* AjouterUneInscription;
    //QLineEdit* EnleverUneInscription;


    QPushButton* sauver;
    QPushButton* annuler;
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

public:
    explicit DossierCreateur(Dossier& DossierToEdit, QWidget *parent = 0);

signals:

public slots:
    void sauverDossier();
    void AjouterInscription();
    void EnleverInscription();
    void ModifList2();
    void AnnulerInscription();
    void ModifierInscription();

private slots:
    void activerSauver();
};



#endif // DOSSIERCREATEUR_H

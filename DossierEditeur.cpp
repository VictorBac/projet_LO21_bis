#include "DossierEditeur.h"

#include "Dossier.h"

#include <QMessageBox>


void DossierEditeur::sauverDossier(){
    dossier.setId(id->text());
    dossier.setNom(nom->text());
    dossier.setPrenom(prenom->text());
    dossier.setCursus(cursus->text());


    QMessageBox::information(this, "Sauvegarde", "Dossier sauvegardée...");
}

void DossierEditeur::activerSauver(QString){
  sauver->setEnabled(true);
}

DossierEditeur::DossierEditeur(Dossier& DossierToEdit, QWidget *parent) :
        QWidget(parent),dossier(DossierToEdit){
    this->setWindowTitle(QString("Edition du Dossier ")+dossier.getId());

    // creation des labels
    //************
    inscriptionLabel = new QLabel("Inscription",this);

    idLabel = new QLabel("id",this);
    nomLabel = new QLabel("Nom",this);
    prenomLabel = new QLabel("Prenom",this);
    cursusLabel = new QLabel("Cursus",this);

    // création des composants éditables
    id = new QLineEdit(dossier.getId(),this);
    nom = new QLineEdit(dossier.getNom(),this);
    prenom = new QLineEdit(dossier.getPrenom(),this);
    cursus = new QLineEdit(dossier.getCursus(),this);
    //**************
    List = new QComboBox(this);



    sauver= new QPushButton("Sauver", this);
    QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverDossier()));
    sauver->setEnabled(false);

    annuler= new QPushButton("Annuler", this);
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));

    // Ajout de la liste des inscriptions.
    for(unsigned int i=0;i<dossier.getNbInscription();i++){
        try{
        List->addItem(dossier.getInscription(i)->getUV());
        }catch(UTProfilerException& e){
            throw UTProfilerException("erreur inscription ", __FILE__,__LINE__);
        }
    }

    // connections******************************
    QObject::connect(id,SIGNAL(textEdited(QString)),this,SLOT(activerSauver(QString)));
    QObject::connect(nom,SIGNAL(textEdited(QString)),this,SLOT(activerSauver(QString)));
    QObject::connect(prenom,SIGNAL(textEdited(QString)),this,SLOT(activerSauver(QString)));
    QObject::connect(cursus,SIGNAL(textEdited(QString)),this,SLOT(activerSauver(QString)));



    // diposition des couches
    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(idLabel);
    coucheH1->addWidget(id);

    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(nomLabel);
    coucheH2->addWidget(nom);

    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(prenomLabel);
    coucheH3->addWidget(prenom);


    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(cursusLabel);
    coucheH4->addWidget(cursus);

    coucheH6 = new QHBoxLayout;
    coucheH6->addWidget(inscriptionLabel);
    coucheH6->addWidget(List);

    coucheH5 = new QHBoxLayout;
    coucheH5->addWidget(annuler);
    coucheH5->addWidget(sauver);
    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    couche->addLayout(coucheH6);
    couche->addLayout(coucheH5);
    setLayout(couche);
};

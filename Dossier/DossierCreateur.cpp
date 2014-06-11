
#include"DossierCreateur.h"
#include"Dossier.h"



void DossierCreateur::sauverDossier(){
    if(DossierManager::getInstance().existDossier(id->text())==0){
    doss.setId(id->text());

    QMessageBox::information(this, "Sauvegarde", "Dossier sauvegardé...");
    }
    else{
        QMessageBox::information(this, "Sauvegarde", "Le Dossier existe déjà !");
    }
}

void DossierCreateur::AjouterInscription(){
   if(UVManager::getInstance().existUV(AjouterUneInscription->text())!=1)
   QMessageBox::information(this, "Sauvegarde", "Cette Inscription n'existe pas.");
   else{
   unsigned int i=0;
   while((i<doss.getNbInscription())&&(doss.getInscription(i)->getUV()!=AjouterUneInscription->text())){
         i++;
    }
    if (i==doss.getNbInscription()){
        UV* uvATrouver = UVManager::getInstance().trouverUV(AjouterUneInscription->text());
        QString uvTrouve = uvATrouver->getCode();
        Saison sa(Printemps);
        Semestre sem(sa,2014);

        Inscription I(uvTrouve, sem, EC);

        doss.AjouterInscription(&I);
        QMessageBox::information(this, "Sauvegarde", "Inscription Ajoutée");
    }
    else
        QMessageBox::information(this, "Sauvegarde", "Cette Inscription existe déjà !");
    AjouterUneInscription->clear();
     }
}

void DossierCreateur::EnleverInscription(){
    unsigned int i=0;
    while((i<doss.getNbInscription())&&(doss.getInscription(i)->getUV()!=EnleverUneInscription->text())){
          i++;
     }
     if (i==doss.getNbInscription())
         QMessageBox::information(this, "Sauvegarde", "Inscription Inexistante dans le Dossier");

     else{
         doss.retirerInscription(i);
         QMessageBox::information(this, "Sauvegarde", "Inscription Supprimée");
     }
  EnleverUneInscription->clear();
  }


void DossierCreateur::activerSauverD(){
    sauverD->setEnabled(true);
}

DossierCreateur::DossierCreateur(Dossier& DossierToEdit, QWidget *parent) :
    QWidget(parent),doss(DossierToEdit){
    this->setWindowTitle(QString("Edition du Dossier ")+doss.getId());

    // creation des labels

    idLabel = new QLabel("id",this);

    // création des composants éditables

    id = new QLineEdit(doss.getId(),this);
    List = new QComboBox(this);
    AjouterUneInscription= new QLineEdit;
    EnleverUneInscription= new QLineEdit;

    //Création des boutons

    sauverD= new QPushButton("Sauver", this);
    QObject::connect(sauverD,SIGNAL(clicked()),this,SLOT(sauverDossier()));
    sauverD->setEnabled(false);

    annuler= new QPushButton("Annuler", this);
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));

    ajouter= new QPushButton("Ajouter", this);
    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(AjouterInscription())) ;

    enlever= new QPushButton("Enlever", this);
    QObject::connect(enlever,SIGNAL(clicked()),this,SLOT(EnleverInscription()));


    // Ajout de la liste des Inscription.
   /* for(unsigned int i=0;i<doss.getNbInscription();i++){
        List->addItem(doss.getInscription(i)->getCode());
    }*/
    // connections******************************

    QObject::connect(id,SIGNAL(textEdited(QString)),this,SLOT(activerSauverD()));
    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(activerSauverD()));
    QObject::connect(enlever,SIGNAL(clicked()),this,SLOT(activerSauverD()));

    //disposition des couches
    coucheH1 = new QHBoxLayout;
    coucheH2 = new QHBoxLayout;
    coucheH3 = new QHBoxLayout;
    coucheH4 = new QHBoxLayout;
    coucheH5 = new QHBoxLayout;


    coucheH1->addWidget(idLabel);
    coucheH1->addWidget(id);
    coucheH2->addWidget(inscriptionLabel);
    coucheH2->addWidget(List);
    coucheH3->addWidget(AjouterUneInscription);
    coucheH3->addWidget(ajouter);
    coucheH4->addWidget(EnleverUneInscription);
    coucheH4->addWidget(enlever);
    coucheH5->addWidget(annuler);
    coucheH5->addWidget(sauverD);

    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    couche->addLayout(coucheH5);

    setLayout(couche);
};

#include "Cursus.h"
#include "MineurEditeur.h"
#include "UTProfiler.h"
#include <QMessageBox>


void MineurEditeur::sauverCursus(){
    CurCur.setTitre(titre->text());
    CurCur.setCreditCS(CreditCS->text().toInt());
    CurCur.setCreditTM(CreditTM->text().toInt());
    CurCur.setCreditTSH(CreditTSH->text().toInt());
    CurCur.setCreditLibre(CreditLibre->text().toInt());
    QMessageBox::information(this, "Sauvegarde", "Cursus sauvegardé...");
}

void MineurEditeur::AjouterlUV(){
    if(UVManager::getInstance().existUV(AjouterUneUV->text())!=1)
   QMessageBox::information(this, "Sauvegarde", "Cette UV n'existe pas.");
   else{
   unsigned int i=0;
   while((i<CurCur.getNbUV())&&(CurCur.getUV(i)->getCode()!=AjouterUneUV->text())){
         i++;
    }
    if (i==CurCur.getNbUV()){
        CurCur.AjouterUv(UVManager::getInstance().trouverUV(AjouterUneUV->text()));
        QMessageBox::information(this, "Sauvegarde", "UV Ajoutée");
    }
    else
        QMessageBox::information(this, "Sauvegarde", "Cette UV existe déjà !");
    AjouterUneUV->clear();
     }
}

void MineurEditeur::AjouterlUVObl(){
    if(UVManager::getInstance().existUV(AjouterUneUVObl->text())!=1)
   QMessageBox::information(this, "Sauvegarde", "Cette UV n'existe pas.");
   else{
   unsigned int i=0;
   while((i<CurCur.getNbUVObl())&&(CurCur.getUVObl(i)->getCode()!=AjouterUneUVObl->text())){
         i++;
    }
    if (i==CurCur.getNbUVObl()){
        CurCur.AjouterUvObl(UVManager::getInstance().trouverUV(AjouterUneUVObl->text()));
        QMessageBox::information(this, "Sauvegarde", "UV Ajoutée");
    }
    else
        QMessageBox::information(this, "Sauvegarde", "Cette UV existe déjà !");
    ajouterObl->clear();
     }
}


void MineurEditeur::EnleverlUV(){
    unsigned int i=0;
    while((i<CurCur.getNbUV())&&(CurCur.getUV(i)->getCode()!=EnleverUneUV->text())){
          i++;
     }
     if (i==CurCur.getNbUV())
         QMessageBox::information(this, "Sauvegarde", "UV Inexistante dans le Cursus");

     else{
         CurCur.retirerUV(i);
         QMessageBox::information(this, "Sauvegarde", "UV Supprimée");
     }
  EnleverUneUV->clear();
  }

void MineurEditeur::EnleverlUVObl(){
    unsigned int i=0;
    while((i<CurCur.getNbUVObl())&&(CurCur.getUVObl(i)->getCode()!=EnleverUneUVObl->text())){
          i++;
     }
     if (i==CurCur.getNbUVObl())
         QMessageBox::information(this, "Sauvegarde", "UV Inexistante dans le Cursus");

     else{
         CurCur.enleverUvObl(i);
         QMessageBox::information(this, "Sauvegarde", "UV Supprimée");
     }
  enleverObl->clear();
  }


void MineurEditeur::activerSauverC(){
    sauverC->setEnabled(true);
}

MineurEditeur::MineurEditeur(Mineur& MineurToEdit, QWidget *parent) :
    QWidget(parent),CurCur(MineurToEdit){
    this->setWindowTitle(QString("Edition du Mineur ")+CurCur.getTitle());

    // creation des labels

    titreLabel = new QLabel("titre",this);
    ObligLabel= new QLabel("Obligatoires",this);
    NbCreditsToGet= new QLabel("Crédits à Obtenir pour valider :",this);
    CSLabel = new QLabel("CS :",this);
    TMLabel= new QLabel("TM:",this);
    CLLabel= new QLabel("Libres:",this);
    TSHLabel= new QLabel("TSH",this);

    // création des composants éditables

    titre = new QLineEdit(CurCur.getTitle(),this);
    uvLabel = new QLabel("Uvs",this);
    List = new QComboBox(this);
    AjouterUneUV= new QLineEdit;
    EnleverUneUV= new QLineEdit;
    ajouterObl= new QLineEdit;
    enleverObl= new QLineEdit;
    CreditCS=new QLineEdit(QString::number(CurCur.getCreditCS()),this);
    CreditTM=new QLineEdit(QString::number(CurCur.getCreditTM()),this);
    CreditTSH=new QLineEdit(QString::number(CurCur.getCreditTSH()),this);
    CreditLibre=new QLineEdit(QString::number(CurCur.getCreditCL()),this);
    Obligatoire = new QComboBox(this);

    //Création des boutons

    sauverC= new QPushButton("Sauver", this);
    QObject::connect(sauverC,SIGNAL(clicked()),this,SLOT(sauverCursus()));
    sauverC->setEnabled(false);

    annuler= new QPushButton("Annuler", this);
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));

    ajouter= new QPushButton("Ajouter", this);
    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(AjouterlUV())) ;

    enlever= new QPushButton("Enlever", this);
    QObject::connect(enlever,SIGNAL(clicked()),this,SLOT(EnleverlUV()));

    AjouterUneUVObl= new QPushButton("Ajouter", this);
    QObject::connect(AjouterUneUVObl,SIGNAL(clicked()),this,SLOT(AjouterlUVObl())) ;

    EnleverUneUVObl= new QPushButton("Enlever", this);
    QObject::connect(EnleverUneUVObl,SIGNAL(clicked()),this,SLOT(EnleverlUVObl()));

    // Ajout de la liste des UV.
    for(unsigned int i=0;i<CurCur.getNbUV();i++){
        List->addItem(CurCur.getUV(i)->getCode());
    }

    for(unsigned int i=0;i<CurCur.getNbUVObl();i++){
        Obligatoire->addItem(CurCur.getUVObl(i)->getCode());
    }
    // connections******************************

    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSauverC()));
    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(activerSauverC()));
    QObject::connect(enlever,SIGNAL(clicked()),this,SLOT(activerSauverC()));
    QObject::connect(CreditCS,SIGNAL(textEdited(QString)),this,SLOT(activerSauverC()));
    QObject::connect(CreditTM,SIGNAL(textEdited(QString)),this,SLOT(activerSauverC()));
    QObject::connect(CreditTSH,SIGNAL(textEdited(QString)),this,SLOT(activerSauverC()));
    QObject::connect(CreditLibre,SIGNAL(textEdited(QString)),this,SLOT(activerSauverC()));
    QObject::connect(AjouterUneUVObl,SIGNAL(clicked()),this,SLOT(activerSauverC()));
    QObject::connect(EnleverUneUVObl,SIGNAL(clicked()),this,SLOT(activerSauverC()));

    //disposition des couches
    coucheH1 = new QHBoxLayout;
    coucheH2 = new QHBoxLayout;
    coucheH3 = new QHBoxLayout;
    coucheH4 = new QHBoxLayout;
    coucheH5 = new QHBoxLayout;
    coucheH6 = new QHBoxLayout;
    coucheH7 = new QHBoxLayout;
    coucheH8 = new QHBoxLayout;
    coucheH9 = new QHBoxLayout;
    coucheH10 = new QHBoxLayout;
    coucheH11 = new QHBoxLayout;
    coucheH12 = new QHBoxLayout;
    coucheH13 = new QHBoxLayout;
    coucheH1->addWidget(titreLabel);
    coucheH1->addWidget(titre);
    coucheH2->addWidget(uvLabel);
    coucheH2->addWidget(List);
    coucheH3->addWidget(AjouterUneUV);
    coucheH3->addWidget(ajouter);
    coucheH4->addWidget(EnleverUneUV);
    coucheH4->addWidget(enlever);
    coucheH5->addWidget(annuler);
    coucheH5->addWidget(sauverC);
    coucheH6->addWidget(NbCreditsToGet);
    coucheH7->addWidget(CSLabel);
    coucheH7->addWidget(CreditCS);
    coucheH8->addWidget(TMLabel);
    coucheH8->addWidget(CreditTM);
    coucheH9->addWidget(TSHLabel);
    coucheH9->addWidget(CreditTSH);
    coucheH10->addWidget(CLLabel);
    coucheH10->addWidget(CreditLibre);
    coucheH11->addWidget(uvLabel);
    coucheH11->addWidget(List);
    coucheH12->addWidget(ajouterObl);
    coucheH12->addWidget(AjouterUneUV);
    coucheH13->addWidget(enleverObl);
    coucheH13->addWidget(EnleverUneUV);
    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    couche->addLayout(coucheH6);
    couche->addLayout(coucheH7);
    couche->addLayout(coucheH8);
    couche->addLayout(coucheH9);
    couche->addLayout(coucheH10);
    couche->addLayout(coucheH11);
    couche->addLayout(coucheH12);
    couche->addLayout(coucheH13);
    couche->addLayout(coucheH5);

    setLayout(couche);
};


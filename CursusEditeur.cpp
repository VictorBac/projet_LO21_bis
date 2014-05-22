#include "Cursus.h"
#include "CursusEditeur.h"
#include "UTProfiler.h"
#include <QMessageBox>



void CursusEditeur::sauverCursus(){
    CurCur.setTitre(titre->text());
    CurCur.setCreditCS(CreditCS->text().toInt());
    CurCur.setCreditTM(CreditTM->text().toInt());
    CurCur.setCreditTSH(CreditTSH->text().toInt());
    CurCur.setCreditLibre(CreditLibre->text().toInt());
    QMessageBox::information(this, "Sauvegarde", "Cursus sauvegardé...");
}

void CursusEditeur::AjouterlUV(){
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


void CursusEditeur::EnleverlUV(){
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


void CursusEditeur::activerSauverC(){
    sauverC->setEnabled(true);
}

CursusEditeur::CursusEditeur(Cursus& CursusToEdit, QWidget *parent) :
    QWidget(parent),CurCur(CursusToEdit){
    this->setWindowTitle(QString("Edition du Cursus ")+CurCur.getTitle());

    // creation des labels

    titreLabel = new QLabel("titre",this);
    uvLabel = new QLabel("Uvs",this);
    NbCreditsToGet= new QLabel("Crédits à Obtenir pour valider :",this);
    CSLabel = new QLabel("CS :",this);
    TMLabel= new QLabel("TM:",this);
    CLLabel= new QLabel("Libres:",this);
    TSHLabel= new QLabel("TSH",this);

    // création des composants éditables

    titre = new QLineEdit(CurCur.getTitle(),this);
    List = new QComboBox(this);
    AjouterUneUV= new QLineEdit;
    EnleverUneUV= new QLineEdit;
    CreditCS=new QLineEdit(QString::number(CurCur.getCreditCS()),this);
    CreditTM=new QLineEdit(QString::number(CurCur.getCreditTM()),this);
    CreditTSH=new QLineEdit(QString::number(CurCur.getCreditTSH()),this);
    CreditLibre=new QLineEdit(QString::number(CurCur.getCreditCL()),this);

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


    // Ajout de la liste des UV.
    for(unsigned int i=0;i<CurCur.getNbUV();i++){
        List->addItem(CurCur.getUV(i)->getCode());
    }
    // connections******************************

    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSauverC()));
    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(activerSauverC()));
    QObject::connect(enlever,SIGNAL(clicked()),this,SLOT(activerSauverC()));
    QObject::connect(CreditCS,SIGNAL(textEdited(QString)),this,SLOT(activerSauverC()));
    QObject::connect(CreditTM,SIGNAL(textEdited(QString)),this,SLOT(activerSauverC()));
    QObject::connect(CreditTSH,SIGNAL(textEdited(QString)),this,SLOT(activerSauverC()));
    QObject::connect(CreditLibre,SIGNAL(textEdited(QString)),this,SLOT(activerSauverC()));


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
    couche->addLayout(coucheH5);

    setLayout(couche);
};

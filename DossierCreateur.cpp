
#include"DossierCreateur.h"
#include"Dossier.h"



void DossierCreateur::sauverDossier(){
    if(DossierManager::getInstance().existDossier(id->text())==0){
    dossier.setId(id->text());
    dossier.setNom(nom->text());
    dossier.setPrenom(prenom->text());
    dossier.setCursus(cursus->text());

    QMessageBox::information(this, "Sauvegarde", "Dossier sauvegardé...");
    }
    else{
        QMessageBox::information(this, "Sauvegarde", "Le Dossier existe déjà !");
    }
}

void DossierCreateur::AjouterInscription(){
    Inscription* newIns = new Inscription;
    Semestre s(StringToSaison(saison->text()),annee->text().toInt());
    newIns->setSemestre(s);
    newIns->setCode(code->text());
    newIns->setResultat(StringToNote(res->text()));
    dossier.AjouterInscription(newIns);
    QMessageBox::information(this, "Sauvegarde", "L'inscription a bien été sauvegardée.");
    code->setText("");
    annee->setText("");
    saison->setText("");
    res->setText("");
    List->addItem(newIns->getUV());
    List2->addItem(newIns->getUV());
}

void DossierCreateur::ModifList2(){
    code2->setText(dossier.getInscription(List2->currentIndex())->getUV());
    annee2->setText(QString::number((dossier.getInscription(List2->currentIndex())->getSemestre().getAnnee())));
    saison2->setText(SaisonToString(dossier.getInscription(List2->currentIndex())->getSemestre().getSaison()));
    res2->setText(NoteToString(dossier.getInscription(List2->currentIndex())->getResultat()));
}

void DossierCreateur::EnleverInscription(){

}



void DossierCreateur::activerSauver(){
    sauver->setEnabled(true);
}

DossierCreateur::DossierCreateur(Dossier& DossierToEdit, QWidget *parent) :
    QWidget(parent),dossier(DossierToEdit){
    this->setWindowTitle(QString("Edition du Dossier ")+dossier.getId());
    // creation des labels
    //************
    inscriptionLabel = new QLabel("Inscription",this);

    idLabel = new QLabel("id",this);
    nomLabel = new QLabel("Nom",this);
    prenomLabel = new QLabel("Prenom",this);
    cursusLabel = new QLabel("Cursus",this);
    codeLabel = new QLabel("Code UV",this);
    resLabel = new QLabel("Resultat",this);
    saisonLabel = new QLabel("Saison",this);
    anneeLabel = new QLabel("Annee",this);

//*** Pour les mdoification d'inscription :
    modificationLabel = new QLabel("Modification");
    code2Label = new QLabel("Code UV",this);
    res2Label = new QLabel("Resultat", this);
    saison2Label = new QLabel("Saison",this);
    annee2Label = new QLabel("Annee",this);
    List2 = new QComboBox(this); // Pour les modifications d'inscriptions
    code2 = new QLineEdit("",this);
    res2 = new QLineEdit("",this);
    saison2 = new QLineEdit("",this);
    annee2 = new QLineEdit("",this);



//    AjouterUneInscription= new QLineEdit;
//    EnleverUneInscription= new QLineEdit; /// A régler

    // création des composants éditables
    id = new QLineEdit(dossier.getId(),this);
    nom = new QLineEdit(dossier.getNom(),this);
    prenom = new QLineEdit(dossier.getPrenom(),this);
    cursus = new QLineEdit(dossier.getCursus(),this);
    code = new QLineEdit("",this);
    res = new QLineEdit("",this);
    saison = new QLineEdit("",this);
    annee = new QLineEdit("",this);
    //**************
    List = new QComboBox(this);

    QObject::connect(List2,SIGNAL(currentIndexChanged(int)),this,SLOT(ModifList2()));


    // Création des buttons.
    ajouterInscription= new QPushButton("Ajouter", this);
    QObject::connect(ajouterInscription,SIGNAL(clicked()),this,SLOT(AjouterInscription())) ;

    enleverInscription= new QPushButton("Enlever", this);
    QObject::connect(enleverInscription,SIGNAL(clicked()),this,SLOT(EnleverInscription()));

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
    QObject::connect(id,SIGNAL(textEdited(QString)),this,SLOT(activerSauver()));
    QObject::connect(nom,SIGNAL(textEdited(QString)),this,SLOT(activerSauver()));
    QObject::connect(prenom,SIGNAL(textEdited(QString)),this,SLOT(activerSauver()));
    QObject::connect(cursus,SIGNAL(textEdited(QString)),this,SLOT(activerSauver()));



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
    coucheH6->addWidget(modificationLabel);
    coucheH6->addWidget(List2);

    //Gestion des Inscriptions
    coucheH7 = new QHBoxLayout;
    coucheH7->addWidget(codeLabel);
    coucheH7->addWidget(code);
    coucheH7->addWidget(code2Label);
    coucheH7->addWidget(code2);
    coucheH8 = new QHBoxLayout;
    coucheH8->addWidget(resLabel);
    coucheH8->addWidget(res);
    coucheH8->addWidget(res2Label);
    coucheH8->addWidget(res2);
    coucheH9 = new QHBoxLayout;
    coucheH9->addWidget(saisonLabel);
    coucheH9->addWidget(saison);
    coucheH9->addWidget(saison2Label);
    coucheH9->addWidget(saison2);
    coucheH10 = new QHBoxLayout;
    coucheH10->addWidget(anneeLabel);
    coucheH10->addWidget(annee);
    coucheH10->addWidget(annee2Label);
    coucheH10->addWidget(annee2);

    coucheH11 = new QHBoxLayout;
    coucheH11->addWidget(ajouterInscription);
    coucheH11->addWidget(enleverInscription);



    coucheH5 = new QHBoxLayout;
    coucheH5->addWidget(sauver);
    coucheH5->addWidget(annuler);
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
    couche->addLayout(coucheH5);
    setLayout(couche);
};

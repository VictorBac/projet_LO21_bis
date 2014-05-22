#include "UVCreateur.h"
#include "UTProfiler.h"
#include <QMessageBox>

void UVCreateur::ajoutUV(){
    if(UVManager::getInstance().existUV(code->text())==0){
        uv.setCode(code->text());
        uv.setTitre(titre->toPlainText());
        uv.setNbCredits(credits->value());
        uv.setCategorie(Categorie(categorie->currentIndex()));
        uv.setOuverturePrintemps(printemps->isChecked());
        uv.setOuvertureAutomne(automne->isChecked());
        QMessageBox::information(this, "Sauvegarde", "UV sauvegardée...");
    }else{
        QMessageBox::information(this, "Sauvegarde", "L'UV existe déjà !");
    }
}


void UVCreateur::activerSauver(QString){
    sauver->setEnabled(true);
}

UVCreateur::UVCreateur(UV& uvToEdit, QWidget *parent) :
        QWidget(parent),uv(uvToEdit){
    this->setWindowTitle(QString("Edition de l’UV ")+uv.getCode());

    // creation des labels
    codeLabel = new QLabel("code",this);
    titreLabel = new QLabel("titre",this);
    creditsLabel = new QLabel("credits",this);
    categorieLabel = new QLabel("categorie",this);
    ouvertureLabel = new QLabel("ouverture",this);

    // création des composants éditables
    code = new QLineEdit("",this);
    titre = new QTextEdit("",this);
    credits=new QSpinBox(this);
    credits->setRange(1,8);
    credits->setValue(1);
    categorie=new QComboBox(this);


    categorie->addItem(CategorieToString(CS));
    categorie->addItem(CategorieToString(TM));
    categorie->addItem(CategorieToString(TSH));
    categorie->addItem(CategorieToString(SP));



    categorie->setCurrentIndex(CS);
    automne=new QCheckBox("automne",this);
    //automne->setChecked(uv.ouvertureAutomne());
    printemps=new QCheckBox("printemps",this);
    //printemps->setChecked(uv.ouverturePrintemps());

    sauver= new QPushButton("Sauver", this);
    QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(ajoutUV()));
    sauver->setEnabled(false);

    annuler= new QPushButton("Annuler", this);
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));

    // connections******************************
    QObject::connect(code,SIGNAL(textEdited(QString)),this,SLOT(activerSauver(
    QString)));
    QObject::connect(titre,SIGNAL(textChanged()),this,SLOT(activerSauver()));
    QObject::connect(categorie,SIGNAL(currentIndexChanged(QString)),this,SLOT(
    activerSauver(QString)));
    QObject::connect(credits,SIGNAL(valueChanged(QString)),this,SLOT(activerSauver(
    QString)));
    QObject::connect(automne,SIGNAL(clicked()),this,SLOT(activerSauver()));
    QObject::connect(printemps,SIGNAL(clicked()),this,SLOT(activerSauver()));

    // diposition des couches
    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(codeLabel);
    coucheH1->addWidget(code);
    coucheH1->addWidget(categorieLabel);
    coucheH1->addWidget(categorie);
    coucheH1->addWidget(creditsLabel);
    coucheH1->addWidget(credits);
    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);
    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(ouvertureLabel);
    coucheH3->addWidget(automne);
    coucheH3->addWidget(printemps);
    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(annuler);
    coucheH4->addWidget(sauver);
    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    setLayout(couche);
};

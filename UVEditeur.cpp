#include "UVEditeur.h"
#include "UTProfiler.h"
#include <QMessageBox>

void UVEditeur::sauverUV(){
    uv.setCode(code->text());
    uv.setTitre(titre->toPlainText());
    uv.setNbCredits(credits->value());
    uv.setCategorie(Categorie(categorie->currentIndex()));
    uv.setOuverturePrintemps(printemps->isChecked());
    uv.setOuvertureAutomne(automne->isChecked());
    QMessageBox::information(this, "Sauvegarde", "UV sauvegardée...");
}

void UVEditeur::activerSauver(QString){
  sauver->setEnabled(true);
}

UVEditeur::UVEditeur(UV& uvToEdit, QWidget *parent) :
        QWidget(parent),uv(uvToEdit){
    this->setWindowTitle(QString("Edition de l’UV ")+uv.getCode());

    // creation des labels
    codeLabel = new QLabel("code",this);
    titreLabel = new QLabel("titre",this);
    creditsLabel = new QLabel("credits",this);
    categorieLabel = new QLabel("categorie",this);
    ouvertureLabel = new QLabel("ouverture",this);

    // création des composants éditables
    code = new QLineEdit(uv.getCode(),this);
    titre = new QTextEdit(uv.getTitre(),this);
    credits=new QSpinBox(this);
    credits->setRange(1,8);
    credits->setValue(uv.getNbCredits());
    categorie=new QComboBox(this);


    categorie->addItem(CategorieToString(CS));
    categorie->addItem(CategorieToString(TM));
    categorie->addItem(CategorieToString(TSH));
    categorie->addItem(CategorieToString(SP));



    categorie->setCurrentIndex(int(uv.getCategorie()));
    automne=new QCheckBox("automne",this);
    automne->setChecked(uv.ouvertureAutomne());
    printemps=new QCheckBox("printemps",this);
    printemps->setChecked(uv.ouverturePrintemps());

    sauver= new QPushButton("Sauver", this);
    QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverUV()));
    sauver->setEnabled(false);

    annuler= new QPushButton("Annuler", this);
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));

    // connections******************************
    QObject::connect(code,SIGNAL(textEdited(QString)),this,SLOT(activerSauver(
    QString)));
    QObject::connect(titre,SIGNAL(textChanged()),this,SLOT(activerSauver()));
    QObject::connect(categorie,SIGNAL(currentIndexChanged(QString)),this,SLOT(activerSauver(QString)));
    QObject::connect(credits,SIGNAL(valueChanged(QString)),this,SLOT(activerSauver(QString)));
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

#include "Profiler.h"
#include "UVEditeur.h"
#include "UTProfiler.h"
#include "CursusEditeur.h"
#include "CursusCreateur.h"
#include "Cursus.h"
#include "Dossier.h"
#include "DossierEditeur.h"
#include "UVCreateur.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>

Profiler::Profiler(QWidget *parent):QMainWindow(parent){
    setMinimumSize(300,300);
    setWindowTitle("UT-Profiler");
    QMenu* mFichier = menuBar()->addMenu("&Fichier");
    QMenu* mCharger=mFichier->addMenu("&Charger");
    QMenu* mEdition = menuBar()->addMenu("&Edition");
    QMenu* mAjout=menuBar()->addMenu("&Ajout");
    QMenu* mSuppr=menuBar()->addMenu("&Suppression");

    QAction *actionChargerUV=mCharger->addAction("Catalogue UVs");
    QAction *actionChargerCursus=mCharger->addAction("Catalogue Cursus");
    QAction *actionChargerDossier=mCharger->addAction("Catalogue Dossiers");
    mFichier->addSeparator();

    QAction *actionQuitter = mFichier->addAction("&Quitter");
    QAction* actionUV=mEdition->addAction("&UV");
    QAction* actionCursus=mEdition->addAction("&Cursus");
    QAction* actionDossier=mEdition->addAction("&Dossier");
    QAction* actionUV2=mAjout->addAction("&UV");
    QAction* actionCursus2=mAjout->addAction("&Cursus");
    QAction* actionDossier2=mAjout->addAction("&Dossier");
    QAction* actionUV3=mSuppr->addAction("&UV");
    QAction* actionCursus3=mSuppr->addAction("&Cursus");
    QAction* actionDossier3=mSuppr->addAction("&Dossier");

    // connections
    connect(actionChargerUV, SIGNAL(triggered()),this,SLOT(openChargerUV()));
    connect(actionChargerCursus, SIGNAL(triggered()),this,SLOT(openChargerCursus()));
    connect(actionChargerDossier, SIGNAL(triggered()),this,SLOT(openChargerDossier()));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionUV, SIGNAL(triggered()),this,SLOT(openUV()));
    connect(actionCursus, SIGNAL(triggered()),this,SLOT(openCursus()));
    connect(actionDossier, SIGNAL(triggered()),this,SLOT(openDossier()));
    connect(actionUV2, SIGNAL(triggered()),this, SLOT(nouvelleUV()));
    connect(actionCursus2, SIGNAL(triggered()),this,SLOT(NouveauCursus()));
    connect(actionDossier2, SIGNAL(triggered()),this, SLOT(nouveauDossier()));
    connect(actionUV3, SIGNAL(triggered()),this, SLOT(SupprUV()));
    connect(actionCursus3, SIGNAL(triggered()),this,SLOT(SupprCursus()));
    connect(actionDossier3, SIGNAL(triggered()),this,SLOT(SupprDossier()));
}

void Profiler::openChargerDossier(){
    QString chemin = QFileDialog::getOpenFileName();
    try {
        if (chemin!="")DossierManager::getInstance().load(chemin);
        QMessageBox::information(this, "Chargement Dossier", "Le catalogue de dossier a été chargé.");
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Chargement Dossier", "Erreur lors du chargement du fichier (non valide ?)");
    }
}


void Profiler::openChargerUV(){
    QString chemin = QFileDialog::getOpenFileName();
    try {
        if (chemin!="")UVManager::getInstance().load(chemin);
        QMessageBox::information(this, "Chargement Catalogue", "Le catalogue d’UVs a été chargé.");
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Chargement Catalogue", "Erreur lors du chargement du fichier (non valide ?)");
    }
}

void Profiler::openChargerCursus(){
    QString chemin = QFileDialog::getOpenFileName();
    try {
        if (chemin!="")CursusManager::getInstance().load(chemin);
        QMessageBox::information(this, "Chargement Catalogue", "Le catalogue de Cursus a été chargé.");
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Chargement Catalogue", "Erreur lors du chargement du fichier (non valide ?)");
    }
}

void Profiler::openCursus(){
    QString code=QInputDialog::getText(this,"Entrez le code du Cursus à éditer","Cursus");
    if (code!="")
    try {
        Cursus& cur=CursusManager::getInstance().getCursus(code);
        CursusEditeur* fenetre=new CursusEditeur(cur,this);
        setCentralWidget(fenetre);
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Edition Cursus", QString("Erreur : le Cursus ")+code+" n’existe pas.");
    }
}

void Profiler::openUV(){
    QString code=QInputDialog::getText(this,"Entrez le code de l'UV' à éditer","UV");
    if (code!="")
    try {
        UV& uv=UVManager::getInstance().getUV(code);
        UVEditeur* fenetre=new UVEditeur(uv,this);
        setCentralWidget(fenetre);
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Edition UV", QString("Erreur : l’UV ")+code+" n’existe pas.");
    }
}

void Profiler::nouvelleUV(){
    QString code="";
    try {
        UV& uv=UVManager::getInstance().creatUV();
        UVCreateur* fenetre=new UVCreateur(uv,this);
        setCentralWidget(fenetre);
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Ajout UV", QString("Impossible de créer une UV"));
    }
}

void Profiler::NouveauCursus(){
    QString code="";
    try {
        Cursus& cur=CursusManager::getInstance().creatCursus();
        CursusCreateur* fenetre=new CursusCreateur(cur,this);
        setCentralWidget(fenetre);
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Ajout UV", QString("Impossible de créer une UV"));
    }
}

void Profiler::SupprUV(){
    QString code=QInputDialog::getText(this,"Entrez le code de l'UV' à supprimer","UV");
    if (code!=""){
     if (UVManager::getInstance().existUV(code)){
         UVManager::getInstance().SupprUV(code);
         QMessageBox::information(this, "Suppression UV", QString("UV "+code+" Supprimée!"));
     }
     else QMessageBox::warning(this, "Suppression UV", QString("Impossible de supprimer cette UV"));
    }
}

void Profiler::SupprCursus(){
    QString code=QInputDialog::getText(this,"Entrez le code du Cursus à supprimer","Cursus");
    if (code!=""){
     if (CursusManager::getInstance().existCursus(code)){
         CursusManager::getInstance().SupprCursus(code);
          QMessageBox::information(this, "Suppression Cursus", QString("Cursus "+code+" Supprimé!"));
     }
     else QMessageBox::warning(this, "Suppression Cursus", QString("Impossible de supprimer ce Cursus"));
    }
}

void Profiler::openDossier(){
    QString id=QInputDialog::getText(this,"Entrez l'id du dossier à éditer","Dossier");
    if (id!="")
    try {
        Dossier& dossier=DossierManager::getInstance().getDossier(id);
        DossierEditeur* fenetre=new DossierEditeur(dossier,this);
        setCentralWidget(fenetre);
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Edition Dossier", QString("Erreur : le dossier ")+id+" n’existe pas.");
    }
}



#include "Dossier.h"
#include <sstream>
#include <QFile>
#include <QTextcodec>
#include <QtXml>
#include <QMessageBox>
#include <QString>

void Dossier::retirerInscription(unsigned int x){
    for(unsigned int j=x; j<nbInscr-1;j++){
        inscr[j]=inscr[j+1];}
    nbInscr--;
}

DossierManager::DossierManager():dossiers(0),nbDossier(0),nbMaxDossier(0),file(""),modification(false){
}

Dossier& DossierManager::creatDossier(){
    try{
        Dossier* newDossier = new Dossier(QString(nbDossier+1)," "," ", " ");
        addItem(newDossier);
        modification = true;
        return *newDossier;
    }
    catch(UTProfilerException& e){
        QMessageBox::warning(NULL, "Chargement Dossier","Heeeer");
    }
};

int DossierManager::existDossier(const QString& id) const{
    try{
        Dossier* Dossier=trouverDossier(id);
        if (Dossier!=0) return 1;
        return 0;
    }catch(UTProfilerException& e){
        throw UTProfilerException("erreurrrr");
    }
}

void DossierManager::load(const QString& f){

    if (file!=f) this->~DossierManager();
    file=f;

    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UTProfilerException("Erreur ouverture fichier Dossier");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named dossiers, we'll go to the next.
            if(xml.name() == "dossiers") continue;
            // If it's named Dossier, we'll dig the information from there.
            if(xml.name() == "dossier") {
                QString id;
                QString nom;
                QString prenom;
                QString cursus;

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named Dossier.


                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "dossier")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found id.
                        if(xml.name() == "id") {
                            xml.readNext(); id=xml.text().toString();
                        }
                        // We've found nom.
                        if(xml.name() == "nom") {
                            xml.readNext(); nom=xml.text().toString();
                        }
                        // We've found prenom.
                        if(xml.name() == "prenom") {
                            xml.readNext(); prenom=xml.text().toString();
                        }
                        if(xml.name() == "cursus") {
                            xml.readNext(); cursus=xml.text().toString();
                        }

                    }
                    // ...and next...
                    xml.readNext();
                }
                ajouterDossier(id,nom,prenom,cursus);


            }
        }


    }

    // Error handling.
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier Dossier, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();

}



void DossierManager::save(const QString& f){

    file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur oDossiererture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("dossiers");
         for(unsigned int i=0; i<nbDossier; i++){
             stream.writeStartElement("dossier");
                stream.writeTextElement("id",dossiers[i]->getId());
                stream.writeTextElement("nom",dossiers[i]->getNom());
                stream.writeTextElement("prenom",dossiers[i]->getPrenom());
                stream.writeTextElement("cursus",dossiers[i]->getCursus());
             stream.writeEndElement();
         }
     stream.writeEndElement();
     stream.writeEndDocument();

     newfile.close();

}

DossierManager::~DossierManager(){
    if (file!="") save(file);
    for(unsigned int i=0; i<nbDossier; i++) delete dossiers[i];
    delete[] dossiers;
}


void DossierManager::addItem(Dossier* dossier){
    if (nbDossier==nbMaxDossier){
        Dossier** newtab = new Dossier*[nbMaxDossier+10];
        for(unsigned int i=0; i<nbDossier; i++) newtab[i]=dossiers[i];
        nbMaxDossier+=10;
        Dossier** old=dossiers;
        dossiers=newtab;
        delete[] old;
    }
    dossiers[nbDossier++]=dossier;
}

void DossierManager::ajouterDossier(const QString& i, const QString& n, const QString& p, const QString& c){
    if (trouverDossier(i)) {
        throw UTProfilerException(QString("erreur, DossierManager, Dossier ")+i+QString("déja existant"));
    }else{
        Dossier* newDossier=new Dossier(i,n,p,c);
        addItem(newDossier);
        modification=true;
    }
}

Dossier* DossierManager::trouverDossier(const QString& c)const{
    //QMessageBox::warning(NULL, "Chargement Dossier","Coucou");
    for(unsigned int i=0; i<nbDossier; i++){
       // StandartButton
      //  QMessageBox::warning(NULL, "Chargement Dossier","Heeeer");
       if (c==dossiers[i]->getId()) return dossiers[i];
    }
    return 0;
}

Dossier& DossierManager::getDossier(const QString& id){
    Dossier* Dossier=trouverDossier(id);
    if (!Dossier) throw UTProfilerException("erreur, DossierManager, Dossier inexistante",__FILE__,__LINE__);
    return *Dossier;
}


const Dossier& DossierManager::getDossier(const QString& id)const{
    return const_cast<DossierManager*>(this)->getDossier(id);
        // on peut aussi dupliquer le id de la m�thode non-const
}

DossierManager::Handler DossierManager::handler=Handler();

DossierManager& DossierManager::getInstance(){
    if (!handler.instance) handler.instance = new DossierManager; /* instance cr��e une seule fois lors de la premi�re utilisation*/
    return *handler.instance;
}

void DossierManager::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

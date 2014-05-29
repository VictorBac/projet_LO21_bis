#include "Dossier.h"
#include <sstream>
#include <QFile>
#include <QTextcodec>
#include <QtXml>
#include <QMessageBox>
#include <QString>
#include "UTProfiler.h"

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

//void DossierManager::load(const QString& f){
//    if (file!=f) this->~DossierManager();
//    file=f;

//    QFile fin(file);
//    // If we can't open it, let's show an error message.
//    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        throw UTProfilerException("Erreur ouverture fichier Dossier");
//    }
//    // QXmlStreamReader takes any QIODevice.
//    QXmlStreamReader reader(&fin);
//    reader.readNext();

//    while (!reader.atEnd())
//    {
//        if (reader.isStartElement())
//        {
//            if (reader.name() == "dossiers")
//            {

//                reader.readNext(); // On va au prochain token
//                // Tant que celui-ci n'est pas un élément de départ on avance au token suivant
//                while(reader.isStartElement()==false)
//                    reader.readNext();

//                if(reader.name() == "dossier")
//                {
//                    Dossier* dos = new Dossier;
////                                        dos->setId("test");
////                                        dos->setNom("test");
////                                        dos->setPrenom("test");
////                                        dos->setCursus("test");


//                    reader.readNext();


//                    while(!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "dossier")) {
//                        if(reader.tokenType() == QXmlStreamReader::StartElement) {

//                            if(reader.name() == "id") {
//                                reader.readNext(); dos->setId(reader.text().toString());
//                            }
//                            // We've found nom.
//                            if(reader.name() == "nom") {
//                                reader.readNext(); dos->setNom(reader.text().toString());
//                            }
//                            // We've found prenom.
//                            if(reader.name() == "prenom") {
//                                reader.readNext(); dos->setPrenom(reader.text().toString());
//                            }
//                            if(reader.name() == "cursus") {
//                               reader.readNext(); dos->setCursus(reader.text().toString());
//                            }
//                        }
//                        reader.readNext();
//                    }
//                    addItem(dos);

//                }//fin du dossier
//            }else{
//                /**********************************************/
//                if(reader.name() == "dossier")
//                {
//                    Dossier* dos = new Dossier;
////                                        dos->setId("test");
////                                        dos->setNom("test");
////                                        dos->setPrenom("test");
////                                        dos->setCursus("test");


//                    reader.readNext();


//                    while(!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "dossier")) {
//                        if(reader.tokenType() == QXmlStreamReader::StartElement) {

//                            if(reader.name() == "id") {
//                                reader.readNext(); dos->setId(reader.text().toString());
//                            }
//                            // We've found nom.
//                            if(reader.name() == "nom") {
//                                reader.readNext(); dos->setNom(reader.text().toString());
//                            }
//                            // We've found prenom.
//                            if(reader.name() == "prenom") {
//                                reader.readNext(); dos->setPrenom(reader.text().toString());
//                            }
//                            if(reader.name() == "cursus") {
//                               reader.readNext(); dos->setCursus(reader.text().toString());
//                            }
//                        }
//                        reader.readNext();
//                    }
//                    addItem(dos);

//                }//fin du dossier
//                /*******************************************************/
//            }
//        }
//        reader.readNext(); // On va au prochain token
//    }
//    reader.clear();
//}




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
            // If it's named uvs, we'll go to the next.
            if(xml.name() == "dossiers") continue;
            // If it's named uv, we'll dig the information from there.
            if(xml.name() == "dossier") {

                Dossier* dos = new Dossier;
//                    dos->setId("test");
//                    dos->setNom("test");
//                    dos->setPrenom("test");
//                    dos->setCursus("test");

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named uv.


                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "dossier")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found id.
                        if(xml.name() == "id") {
                            xml.readNext(); dos->setId(xml.text().toString());
                        }
                        // We've found nom.
                        if(xml.name() == "nom") {
                            xml.readNext(); dos->setNom(xml.text().toString());
                        }
                        // We've found prenom.
                        if(xml.name() == "prenom") {
                            xml.readNext(); dos->setPrenom(xml.text().toString());
                        }
                        if(xml.name() == "cursus") {
                           xml.readNext(); dos->setCursus(xml.text().toString());
                        }
                        if(xml.name() == "ins") {
                            //QMessageBox::information(NULL, "Sauvegarde", "Inscription rencontrée");
                            Inscription* insc = new Inscription();
                            Semestre s(Printemps, 2013);
                            insc->setSemestre(s);
                            insc->setResultat(A);
                            insc->setCode("Heyyyyyy");

                            xml.readNext();

                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "ins")) {
                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if(xml.name() == "code") {
                                      xml.readNext();insc->setCode(xml.text().toString());
                                    }
                                    if(xml.name() == "res") {
                                        xml.readNext();insc->setResultat(StringToNote(xml.text().toString()));
                                    }
                                    if(xml.name() == "sais") {
                                      xml.readNext();s.setSaison(StringToSaison(xml.text().toString()));
                                    }
                                    if(xml.name() == "annee") {
                                      xml.readNext();s.setAnnee(xml.text().toInt());
                                    }

                                }
                                xml.readNext();
                            }
                            insc->setSemestre(s);
                            dos->AjouterInscription(insc);
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                addItem(dos);


            }
        }


    }

    // Error handling.
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier UV, parser xml");
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

                for(unsigned int j=0; j<dossiers[i]->getNbInscription(); j++){
                stream.writeStartElement("ins");
                    stream.writeTextElement("code",dossiers[i]->getInscription(j)->getUV());
                    stream.writeTextElement("res",NoteToString(dossiers[i]->getInscription(j)->getResultat()));
                    stream.writeTextElement("sais",SaisonToString(dossiers[i]->getInscription(j)->getSemestre().getSaison()));
                    stream.writeTextElement("annee",QString::number(dossiers[i]->getInscription(j)->getSemestre().getAnnee()));
                stream.writeEndElement();
                }
              stream.writeEndElement(); // fin de inscription
           }
     stream.writeEndElement(); // fin de dossiers
     stream.writeEndDocument(); // fin du doc

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
/*
void DossierManager::ajouterDossier(Dossier& dos){
    if (trouverDossier(dos->getId())) {
        throw UTProfilerException(QString("erreur, DossierManager, Dossier ")+dos->getId()+QString("déja existant"));
    }else{
        addItem(dos);
        modification=true;
    }
}*/

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



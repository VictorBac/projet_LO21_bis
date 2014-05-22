#include "UTProfiler.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include "Cursus.h"

void Cursus::retirerUV(unsigned int x){
    for(unsigned int j=x; j<nbUv-1;j++){
        Cuvs[j]=Cuvs[j+1];}
    nbUv--;
}

CursusManager::CursusManager():Curs(0),nbCursus(0),nbMaxCursus(0),file(""),modification(false){
}

int CursusManager::existCursus(QString cod){
    unsigned int i=0;
    while((i<nbCursus)&&(Curs[i]->getTitle()!=cod)){
          i++;
     }
    if (i==nbCursus)
        return 0;
    else
        return 1;
};

void CursusManager::SupprCursus(QString cod){
    unsigned int x=0;
    while(CursusManager::getInstance().Curs[x]->getTitle()!=cod)
    {x++;}
        for(unsigned int j=x; j<nbCursus-1;j++){
            Curs[j]=Curs[j+1];}
        nbCursus--;
};

void CursusManager::AjouterCursus(Cursus* cur){
    if (nbCursus==nbMaxCursus){
        Cursus** newtab=new Cursus*[nbMaxCursus+10];
        for(unsigned int i=0; i<nbCursus; i++) newtab[i]=Curs[i];
        nbMaxCursus+=10;
        Cursus** old=Curs;
        Curs=newtab;
        delete[] old;
    }
    Curs[nbCursus++]=cur;
}

Cursus& CursusManager::creatCursus(){
    try{
        Cursus* newcur = new Cursus("");
        AjouterCursus(newcur);
        modification = true;
        return *newcur;
    }
    catch(UTProfilerException& e){
        throw UTProfilerException("erreur", __FILE__,__LINE__);
    }
};

void CursusManager::saveC(const QString& f){
    file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("Cursus");
     for(unsigned int i=0; i<nbCursus; i++){
         stream.writeStartElement("Cur");
         stream.writeTextElement("titre",Curs[i]->getTitle());
         stream.writeTextElement("CreditCS",QString::number(Curs[i]->getCreditCS()));
         stream.writeTextElement("CreditTM",QString::number(Curs[i]->getCreditTM()));
         stream.writeTextElement("CreditTSH",QString::number(Curs[i]->getCreditTSH()));
         stream.writeTextElement("CreditLibre",QString::number(Curs[i]->getCreditCL()));
         for(unsigned int j=0; j<Curs[i]->getNbUV(); j++){
             stream.writeTextElement("Cuv",Curs[i]->getUV(j)->getCode());
         }
         stream.writeEndElement();
     }
     stream.writeEndElement();
     stream.writeEndDocument();
     newfile.close();
}

void CursusManager::load(const QString& f){
    if (file!=f) this->~CursusManager();
    file=f;
    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UTProfilerException("Erreur ouverture fichier Cursus");
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
            // If it's named Cursus, we'll go to the next.
            if(xml.name() == "Cursus") continue;
            // If it's named cur, we'll dig the information from there.
            if(xml.name() == "Cur") {
                QString titre;
                unsigned int NBCS;
                unsigned int NBTM;
                unsigned int NBTSH;
                unsigned int NBCL;
                UV* currUv;
                Cursus* Cur;
                xml.readNext();
                //We'll continue the loop until we hit an EndElement named Cur.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Cur")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext();
                            titre=xml.text().toString();
                            Cur = new Cursus(titre);
                        }
                        if(xml.name() == "CreditCS") {
                            xml.readNext();
                            NBCS=xml.text().toString().toUInt();
                            Cur->setCreditCS(NBCS);
                        }
                        if(xml.name() == "CreditTM") {
                            xml.readNext();
                            NBTM=xml.text().toString().toUInt();
                            Cur->setCreditTM(NBTM);
                        }
                        if(xml.name() == "CreditTSH") {
                            xml.readNext();
                            NBTSH=xml.text().toString().toUInt();
                            Cur->setCreditTSH(NBTSH);
                        }
                        if(xml.name() == "CreditLibre") {
                            xml.readNext();
                            NBCL=xml.text().toString().toUInt();
                            Cur->setCreditLibre(NBCL);
                        }
                        // We've found List of uv.
                        if(xml.name() == "Cuv") {
                            xml.readNext();
                            QString texte=xml.text().toString();
                            currUv=UVManager::getInstance().trouverUV(texte);
                            Cur->AjouterUv(currUv);
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                AjouterCursus(Cur);
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

CursusManager::~CursusManager(){
    if (file!="") saveC(file);
    for(unsigned int i=0; i<nbCursus; i++) delete Curs[i];
    delete[] Curs;
}

Cursus* CursusManager::trouverCursus( QString& c){
    for(unsigned int i=0; i<nbCursus; i++)
        if (c==Curs[i]->getTitle()) return Curs[i];
    return 0;
}

Cursus& CursusManager::getCursus(QString& code){
    Cursus* Cur=trouverCursus(code);
    if (!Cur) throw UTProfilerException("erreur, UVManager, UV inexistante",__FILE__,__LINE__);
    return *Cur;
}

CursusManager::Handler CursusManager::handler=Handler();

CursusManager& CursusManager::getInstance(){
    if (!handler.instance) handler.instance = new CursusManager; /* instance créée une seule fois lors de la première utilisation*/
    return *handler.instance;
}

void CursusManager::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}


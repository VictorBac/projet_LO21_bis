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


template<class T>
Manager<T>::Manager():tab(0),Nb(0),file(""){};

CursusManager::CursusManager():Manager(),nbMaxCursus(0),modification(false){
}

int CursusManager::existCursus(QString cod){
    unsigned int i=0;
    while((i<this->Nb)&&(this->tab[i]->getTitle()!=cod)){
          i++;
     }
    if (i==this->Nb)
        return 0;
    else
        return 1;
};

void CursusManager::SupprCursus(QString cod){
    unsigned int x=0;
    while(CursusManager::getInstance().tab[x]->getTitle()!=cod)
    {x++;}
        for(unsigned int j=x; j<this->Nb-1;j++){
            this->tab[j]=this->tab[j+1];}
        this->Nb--;
};

void CursusManager::AjouterCursus(Cursus* cur){
    if (this->Nb==nbMaxCursus){
        Cursus** newtab=new Cursus*[nbMaxCursus+10];
        for(unsigned int i=0; i<this->Nb; i++) newtab[i]=this->tab[i];
        nbMaxCursus+=10;
        Cursus** old=this->tab;
        this->tab=newtab;
        delete[] old;
    }
    this->tab[this->Nb++]=cur;
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
     for(unsigned int i=0; i<this->Nb; i++){
         stream.writeStartElement("Cur");
         stream.writeTextElement("titre",this->tab[i]->getTitle());
         stream.writeTextElement("CreditCS",QString::number(this->tab[i]->getCreditCS()));
         stream.writeTextElement("CreditTM",QString::number(this->tab[i]->getCreditTM()));
         stream.writeTextElement("CreditTSH",QString::number(this->tab[i]->getCreditTSH()));
         stream.writeTextElement("CreditLibre",QString::number(this->tab[i]->getCreditCL()));
         for(unsigned int j=0; j<this->tab[i]->getNbUV(); j++){
             stream.writeTextElement("Cuv",this->tab[i]->getUV(j)->getCode());
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

template<class T>
Manager<T>::~Manager(){};

CursusManager::~CursusManager(){
    if (file!="") saveC(file);
    for(unsigned int i=0; i<this->Nb; i++) delete this->tab[i];
    delete[] this->tab;
}

Cursus* CursusManager::trouverCursus( QString& c){
    for(unsigned int i=0; i<this->Nb; i++)
        if (c==this->tab[i]->getTitle()) return this->tab[i];
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


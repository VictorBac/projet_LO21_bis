#ifndef CURSUS_H
#define CURSUS_H
#include"Profiler.h"
#include"UTProfiler.h"
#include"UVEditeur.h"

//Composant Abstrait
class Cursus {
protected :
    QString title;
    UV** Cuvs;
    unsigned int CreditCS;
    unsigned int CreditTM;
    unsigned int CreditTSH;
    unsigned int CreditCL;
    unsigned int nbUv;
    unsigned int nbMaxUv;
    public:
    //Accesseurs
        QString getTitle()const{return title;}
        unsigned int getNbUV()const{return nbUv;}
        UV* getUV(unsigned int i) {return Cuvs[i];}
        unsigned int getCreditCS(){return CreditCS;}
        unsigned int getCreditTM(){return CreditTM;}
        unsigned int getCreditTSH(){return CreditTSH;}
        unsigned int getCreditCL(){return CreditCL;}
   //Modificateurs
        void setCreditCS(int x){CreditCS=x;}
        void setCreditTM(int x){CreditTM=x;}
        void setCreditTSH(int x){CreditTSH=x;}
        void setCreditLibre(int x){CreditCL=x;}
        void setTitre(const QString& t) { title=t; }
        void retirerUV(unsigned int);
        //Constructeur
        Cursus(const QString& s, unsigned int CS=0, unsigned int TM=0, unsigned int TSH=0, unsigned int L=0,unsigned int nb=0,unsigned int nb2=0):title(s),CreditCS(CS), CreditTM(TM), CreditTSH(TSH), CreditCL(L),nbUv(nb),nbMaxUv(nb2){}
        //Destructeur
        virtual ~Cursus()=0;
        //Ajouter une UV.
        void AjouterUv(UV* U){
            if(nbMaxUv==nbUv){
                UV** tab2 = new UV*[nbMaxUv+10];
                for(unsigned int i=0; i<nbUv; i++)
                    tab2[i]=Cuvs[i];
                UV** temp=Cuvs;
                Cuvs=tab2;
                delete[] temp;
                nbMaxUv+=10;
                }
            Cuvs[nbUv++]=U;
        }

};

//Objet composite
class ProfilCommun : public Cursus {
Cursus** SousCurs ;
    int Nbsous;
    int NbsousMax;
public :
    ProfilCommun(const QString s):Cursus(s),Nbsous(0),NbsousMax(0),SousCurs(0){};
    ~ProfilCommun(){
        delete[] SousCurs;
    };
    unsigned int getNbsousCursus()const{return Nbsous;}
    Cursus* getSousCursus(unsigned int i) {return SousCurs[i];}
    void EnleverCursus(unsigned int x){
        for(unsigned int j=x; j<Nbsous-1;j++){
            SousCurs[j]=SousCurs[j+1];}
        Nbsous--;
    }
    void AjouterCur(Cursus* U){
        if(NbsousMax==Nbsous){
            Cursus** tab2 = new Cursus*[NbsousMax+10];
            for(unsigned int i=0; i<Nbsous; i++)
                tab2[i]=SousCurs[i];
            Cursus** temp=SousCurs;
            SousCurs=tab2;
            delete[] temp;
            NbsousMax+=10;
            }
         SousCurs[Nbsous++]=U;
}

};

//Objets feuilles

class Filiere : public Cursus {
public:
    Filiere(QString c):Cursus(c){};
    ~Filiere(){};
    };

class Mineur : public Cursus{
   //Contient un tableau d'UV qui sont la liste d'UV obligatoire.
    UV** Obligatoire;
    int NbUvObl;
    int NbUvOblMax;
public :
    //Constructeur
    Mineur(const QString s):Cursus(s),NbUvObl(0),NbUvOblMax(0),Obligatoire(0){};
    ~Mineur(){};
    //Accesseurs
    unsigned int getNbUVObl()const{return NbUvObl;}
    UV* getUVObl(unsigned int i) {return Obligatoire[i];}
    //Enlever une UV.
    void enleverUvObl(unsigned int x){
        for(unsigned int j=x; j<NbUvObl-1;j++){
            Obligatoire[j]=Obligatoire[j+1];}
        NbUvObl--;
    }
    //Ajouter une UV.
    void AjouterUvObl(UV* U){
        if(NbUvOblMax==NbUvObl){
            UV** tab2 = new UV*[NbUvOblMax+10];
            for(unsigned int i=0; i<NbUvObl; i++)
                tab2[i]=Obligatoire[i];
            UV** temp=Obligatoire;
            Obligatoire=tab2;
            delete[] temp;
            NbUvOblMax+=10;
            }
        Obligatoire[NbUvObl++]=U;
    }

};

class CursusManager: public Manager<Cursus>{
private:
    unsigned int nbMaxCursus;
    void addItem(Cursus* cur);
    bool modification;
    CursusManager(const CursusManager& cm);
    CursusManager& operator=(const CursusManager& cm);
    CursusManager();
    ~CursusManager();
    friend struct Handler;
    struct Handler{
        CursusManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:
    void SupprCursus(QString);
    int existCursus(QString);
    Cursus& creatCursus(QString);
    Cursus* trouverCursus( QString& c);
    void load(const QString& f);
    void saveC(const QString& f);
    static CursusManager& getInstance();
    static void libererInstance();
    void AjouterCursus(Cursus*);
    Cursus& getCursus(QString&);

};

#endif // CURSUS_H

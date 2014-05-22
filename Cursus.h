#ifndef CURSUS_H
#define CURSUS_H
#include"Profiler.h"
#include"UTProfiler.h"
#include"UVEditeur.h"

//test modification

//Modif Victor

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

class CursusManager{
private:
    Cursus** Curs;
    unsigned int nbCursus;
    unsigned int nbMaxCursus;
    void addItem(Cursus* cur);
    bool modification;
    CursusManager(const CursusManager& cm);
    CursusManager& operator=(const CursusManager& cm);
    CursusManager();
    ~CursusManager();
    QString file;
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
    Cursus& creatCursus();
    Cursus* trouverCursus( QString& c);
    void load(const QString& f);
    void saveC(const QString& f);
    static CursusManager& getInstance();
    static void libererInstance();
    void AjouterCursus(Cursus*);
    Cursus& getCursus(QString&);
    class Iterator {
        friend class CursusManager;
        Cursus** currentCur;
        unsigned int nbRemain;
        Iterator(Cursus** u, unsigned nb):currentCur(u),nbRemain(nb){}
    public:
        Iterator():nbRemain(0),currentCur(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw UTProfilerException("error, next on an iterator which is done");
            nbRemain--;
            currentCur++;
        }
        Cursus& current() const {
            if (isDone())
                throw UTProfilerException("error, indirection on an iterator which is done");
            return **currentCur;
        }
    };
    Iterator getIterator() {
        return Iterator(Curs,nbCursus);
    }

    class iterator {
        Cursus** current;
        iterator(Cursus** u):current(u){}
        friend class CursusManager;
    public:
        iterator():current(0){};
        Cursus& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(Curs); }
    iterator end() { return iterator(Curs+nbCursus); }
};

#endif // CURSUS_H

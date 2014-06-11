#ifndef DOSSIER_H
#define DOSSIER_H
#include "UTProfiler.h"
#include <QString>

class Inscription {
    QString codeUV;
    Semestre semestre;
    Note resultat;
public:
    Inscription(const QString code="", const Semestre& s=Semestre(Printemps,2010), Note res=EC):codeUV(code),semestre(s),resultat(res){}
    const QString& getUV() const { return codeUV; }
    Semestre& getSemestre() { return semestre; }
    Note getResultat() const { return resultat; }
    void setResultat(Note newres) { resultat=newres; }
    void setSemestre(Semestre s){ semestre=s;}
    void setCode(const QString c){ codeUV=c;}
};

class Dossier {

protected:
    QString id;
    QString nom;
    QString prenom;
    QString cursus;
    Inscription** inscr;
    unsigned int nbInscr;
    unsigned int nbMaxInscr;
    Dossier& operator=(const Dossier& d);
    Dossier(const QString& i, const QString& n, const QString& p, const QString& c, unsigned int nbIns=0,unsigned int nbIns2=0):
        id(i),nom(n),prenom(p),cursus(c),nbInscr(0),nbMaxInscr(nbIns2),inscr(0){}
    Dossier():id(" "),nom(""),prenom(" "),cursus(" "),nbInscr(0),nbMaxInscr(0),inscr(0){}

    friend class DossierManager;

public:
    unsigned int getNbInscription(){return nbInscr;}
    Inscription* getInscription(unsigned int i){
        return inscr[i];
    }

    QString getId() const { return id; }
    QString getNom() const {return nom;}
    QString getPrenom() const {return prenom;}
    QString getCursus() const {return cursus;}
    void setId(const QString& i) { id=i; }
    void setNom(const QString& n) { nom=n; }
    void setPrenom(const QString& p) { prenom=p; }
    void setCursus(const QString& c) { cursus=c; }

    unsigned int compareAvecCursus();
    unsigned int getCredits(Categorie type);


    void retirerInscription(unsigned int x);
    void AjouterInscription(Inscription* I){
        if(nbMaxInscr==nbInscr){
            Inscription** tab2 = new Inscription*[nbMaxInscr+10];
            for(unsigned int i=0; i<nbInscr; i++)
                tab2[i]=inscr[i];
            Inscription** temp=inscr;
            inscr=tab2;
            delete[] temp;
            nbMaxInscr+=10;
            }
        inscr[nbInscr++]=I;
    }

    bool testUV(QString uv){
        for (unsigned int i=0;i<getNbInscription();i++)
            if ((getInscription(i)->getUV()==uv)&&(getInscription(i)->getResultat()!=F)
                    &&(getInscription(i)->getResultat()!=FX)
                    &&(getInscription(i)->getResultat()!=EC))
            return false;
    return true;
    }


};


class DossierManager {

private:
    Dossier** dossiers;
    unsigned int nbDossier;
    unsigned int nbMaxDossier;
    void addItem(Dossier* dossier);
    bool modification;
    DossierManager(const DossierManager& dm);
    DossierManager& operator=(const DossierManager& dm);
    DossierManager();
    ~DossierManager();
    QString file;
    friend struct Handler;
    struct Handler{
        DossierManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:
    unsigned int getNbDossier()const{return nbDossier;}
    Dossier* trouverDossier(const QString& id) const;
    Dossier& creatDossier();
    int existDossier(const QString& id) const;
    void load(const QString& f);
    void save(const QString& f);
    static DossierManager& getInstance();
    static void libererInstance();
    void ajouterDossier(const QString& i, const QString& n, const QString& p, const QString& curs);
    //*SI on ajoute un dossier directement :
    //void ajouterDossier(Dossier &dos);

    const Dossier& getDossier(const QString& id) const;
    Dossier& getDossier(const QString& id);
    class Iterator {
        friend class DossierManager;
        Dossier** currentDossier;
        unsigned int nbRemain;
        Iterator(Dossier** d, unsigned nb):currentDossier(d),nbRemain(nb){}
    public:
        Iterator():nbRemain(0),currentDossier(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw UTProfilerException("error, next on an iterator which is done");
            nbRemain--;
            currentDossier++;
        }
        Dossier& current() const {
            if (isDone())
                throw UTProfilerException("error, indirection on an iterator which is done");
            return **currentDossier;
        }
    };
    Iterator getIterator() {
        return Iterator(dossiers,nbDossier);
    }

    class iterator {
        Dossier** current;
        iterator(Dossier** d):current(d){}
        friend class DossierManager;
    public:
        iterator():current(0){};
        Dossier& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(dossiers); }
    iterator end() { return iterator(dossiers+nbDossier); }

};



#endif // DOSSIER_H

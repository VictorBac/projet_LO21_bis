#ifndef DOSSIER_H
#define DOSSIER_H
#include "UTProfiler.h"
#include <QString>


class Dossier {

protected:
    QString id;
    QString nom;
    QString prenom;
    QString cursus;
    Dossier& operator=(const Dossier& d);
    Dossier(const QString& i, const QString& n, const QString& p, const QString& c):
      id(i),nom(n),prenom(p),cursus(c){}
    friend class DossierManager;

public:
    QString getId() const { return id; }
    QString getNom() const {return nom;}
    QString getPrenom() const {return prenom;}
    QString getCursus() const {return cursus;}
    void setId(const QString& i) { id=i; }
    void setNom(const QString& n) { nom=n; }
    void setPrenom(const QString& p) { prenom=p; }
    void setCursus(const QString& c) { cursus=c; }

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

    Dossier* trouverDossier(const QString& id) const;
    Dossier& creatDossier();
    int existDossier(const QString& id) const;
    void load(const QString& f);
    void save(const QString& f);
    static DossierManager& getInstance();
    static void libererInstance();
    void ajouterDossier(const QString& i, const QString& n, const QString& p, const QString& curs);
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

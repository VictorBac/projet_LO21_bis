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
    Semestre getSemestre() const { return semestre; }
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

};


class DossierManager :  public Manager<Dossier>{

private:
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
    //*SI on ajoute un dossier directement :
    //void ajouterDossier(Dossier &dos);
    const Dossier& getDossier(const QString& id) const;
    Dossier& getDossier(const QString& id);
};



#endif // DOSSIER_H

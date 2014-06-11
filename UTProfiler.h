#ifndef UT_PROFILER_h
#define UT_PROFILER_h

#include <QString>
#include <QTextStream>
#include <vector>
#include <map>
using namespace std;

class UTProfilerException{
public:
    UTProfilerException(const QString& message, const QString &f="na", unsigned int l=0):
        info(message),file(f),line(l){}
    QString getInfo() const { return info; }
#ifndef NDEBUG
    // retourne le fichier dans lequel cettte exception a �t� lev�e.
    QString getFile() const { return file; }
    // retourne la ligne du fichier � laquelle cette exception a �t� lev�e.
    unsigned int getLine() const { return line; }
#endif
private:
    QString info;
    QString file;
    unsigned int line;

};

enum Categorie {
	/* Connaissances Scientifiques */ CS,  /* Techniques et M�thodes */ TM, 
    /* Technologies et Sciences de l'Homme */ TSH, /* Stage et Projet */ SP
};

QTextStream& operator<<(QTextStream& f, const Categorie& s);
Categorie StringToCategorie(const QString& s);
QString CategorieToString(Categorie c);
QTextStream& operator>>(QTextStream& f, Categorie& cat);

enum Note { A, B, C, D, E, F, FX, RES, ABS, /* en cours */ EC  };
enum Saison { Automne, Printemps };
inline QTextStream& operator<<(QTextStream& f, const Saison& s) { if (s==Automne) f<<"A"; else f<<"P"; return f;}

Note StringToNote(const QString& str);
QString NoteToString(Note n);
Saison StringToSaison(const QString& s);
QString SaisonToString(Saison s);

class Semestre {
	Saison saison;
	unsigned int annee;
public:
	Semestre(Saison s, unsigned int a):saison(s),annee(a){ if (annee<1972||annee>2099) throw UTProfilerException("annee non valide"); }
	Saison getSaison() const { return saison; }
	unsigned int getAnnee() const { return annee; }
    void setSaison (Saison s){ saison = s;}
    void setAnnee (unsigned int a){ annee = a;}
};

inline QTextStream& operator<<(QTextStream& f, const Semestre& s) { return f<<s.getSaison()<<s.getAnnee()%100; }

class UV {
    QString code;
    QString titre;
	unsigned int nbCredits;
	Categorie categorie;
    bool automne;
    bool printemps;
	UV(const UV& u);
	UV& operator=(const UV& u);
    UV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p):
      code(c),titre(t),nbCredits(nbc),categorie(cat),automne(a),printemps(p){}
	friend class UVManager;
public:
    QString getCode() const { return code; }
    QString getTitre() const { return titre; }
	unsigned int getNbCredits() const { return nbCredits; }
	Categorie getCategorie() const { return categorie; }
    bool ouvertureAutomne() const { return automne; }
    bool ouverturePrintemps() const { return printemps; }
    void setCode(const QString& c) { code=c; }
    void setTitre(const QString& t) { titre=t; }
    void setNbCredits(unsigned int n) { nbCredits=n; }
    void setCategorie(Categorie c) { categorie=c; }
    void setOuvertureAutomne(bool b) { automne=b; }
    void setOuverturePrintemps(bool b) { printemps=b; }
};

QTextStream& operator<<(QTextStream& f, const UV& uv);

template<typename T>
class Manager {
protected :
    T** tab;
    unsigned int Nb;
    QString file;
    friend struct Handler;
    struct Handler{
        Manager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:
    Manager();
    virtual ~Manager();
    class Iterator {
        friend class Manager;
        T** current;
        unsigned int nbRemain;
        Iterator(T** u, unsigned nb):current(u),nbRemain(nb){}
    public:
        Iterator():nbRemain(0),current(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw UTProfilerException("error, next on an iterator which is done");
            nbRemain--;
            current++;
        }
        T& currents() const {
            if (isDone())
                throw UTProfilerException("error, indirection on an iterator which is done");
            return **current;
        }
    };
    Iterator getIterator() {
        return Iterator(tab,Nb);
    }

    class iterator {
        T** current;
        iterator(UV** u):current(u){}
        friend class Manager;
    public:
        iterator():current(0){};
        T& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(tab); }
    iterator end() { return iterator(tab+Nb); }

};

class UVManager : public Manager<UV> {
private:
    unsigned int nbMaxUV;
    void addItem(UV* uv);
    bool modification;
    UVManager(const UVManager& um);
	UVManager& operator=(const UVManager& um);
	UVManager();
    ~UVManager();
    QString file;
    friend struct Handler;
    struct Handler{
        UVManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:

    void SupprUV(QString);
    UV* trouverUV(const QString& c) const;
    UV &creatUV();
    int existUV(const QString& code) const;
    void load(const QString& f);
    void save(const QString& f);
	static UVManager& getInstance();
	static void libererInstance();
    void ajouterUV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p);
    const UV& getUV(const QString& code) const;
    UV& getUV(const QString& code);
   };


class Formation{
};

#endif

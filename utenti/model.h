#ifndef MODEL_H
#define MODEL_H
#include "utente.h"
#include "deepptr.h"
#include "utente_gia_presente.h"
class Utente;
class Domanda;
class Model
{
private:
    container<DeepPtr<Utente>> utenti;
    bool check_presenza(const string&);
    void sistema_amici_seguaci(Utente*);
    void reverse_seguaci_amici(Utente*);
public:
    Model();
    Model(const container<DeepPtr<Utente>>&);
    const container<DeepPtr<Utente>>& get_utenti() const;
    Utente *get_utente(const string&) const; //OK
    DeepPtr<Utente> *get_utente_deep(const string&username);
    void aggiungi_utente(const DeepPtr<Utente> &);//OK
//    void aggiungi_utente(Utente* utente);//OK
    void togli_utente(Utente* utente);//OK
    Utente* cambia_piano(Utente* utente,const string& piano);//OK

};

#endif // MODEL_H

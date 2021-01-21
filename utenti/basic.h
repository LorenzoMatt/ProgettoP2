#ifndef BASIC_H
#define BASIC_H
#include "utente.h"

class Database;
class Basic : public Utente
{
private:
    static unsigned int puntiPerDomandaData;
    static unsigned int puntiDetrattiDomandaFatta;
    static unsigned int supplementoDomandaPriorita;
    static unsigned int puntiBonus;
public:
    ~Basic();
    Basic() =delete;
    Basic(string username,string password,string nome,string cognome,string email,unsigned int =puntiBonus, unsigned int =0);
    Basic(Profilo p,Accesso c,container<Utente*> a,container<Utente*> s,unsigned int punti,unsigned int risposte);
    void cerca_utente(const string&,const Database&, container<string>&) const override;//viene inserito nel container solo username, nome, cognome ed email
    void fai_domanda(Domanda*) override;//OK
    container<Domanda*> cerca_domanda(const string&,const Database&) const override;//OK, la domanda viene cercata solo negli amici
    void get_punti_domanda() override; //OK
    Basic* clone() const override;//OK
    string piano() const override;
};
#endif // BASIC_H

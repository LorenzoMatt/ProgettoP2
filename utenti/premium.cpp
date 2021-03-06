#include "premium.h"

unsigned int Premium::puntiDetrattiDomandaFatta=5;
unsigned int Premium::puntiPerDomandaData=20;
unsigned int Premium::puntiBonus=60;
unsigned int Premium::limitePerAverePuntiBonus=15;
unsigned int Premium::supplementoDomandaPriorita=3;

Premium::Premium(string username, string password, string nome, string cognome, string email, unsigned int punti, unsigned int risposte_date)
    :Pagamento(username,password,nome,cognome,email,punti,risposte_date)
{
}

Premium::Premium(Profilo p, Accesso c, container<Utente *> a, container<Utente *> s, unsigned int punti, unsigned int risposte)
    :Pagamento(p,c,a,s,punti< puntiBonus ? puntiBonus : punti,risposte)
{

}

void Premium::cerca_utente(const string &username, const Database &model, container<string> &lista_di_elementi) const
{
    Utente* utente = model.get_utente(username);
        if(utente)
        {
            Utente::Funtore f(3);//nelle funzioni polimorfe il numero_funtore sarà sostituito con 1 in account gratuito,2 in gold e 3 in premium
            f(utente, lista_di_elementi);
        }
}

void Premium::get_punti_domanda()
{
    punti+=puntiPerDomandaData;
    risposte_date++;
    if(risposte_date>=limitePerAverePuntiBonus)
    {
        get_punti_bonus();
        risposte_date=0;
    }
}

void Premium::fai_domanda(Domanda *domanda)
{
    unsigned int punti_da_sottrarre=puntiDetrattiDomandaFatta;
    if(domanda->get_priorita()>=3)
    {
        punti_da_sottrarre+=(supplementoDomandaPriorita*(domanda->get_priorita()-3));
    }
    else
    {
        domanda->set_priorita(3);
    }
    if(punti>=punti_da_sottrarre)
    {
        punti-=punti_da_sottrarre;
        get_domande_rif().push_front(domanda);
    }
    else
    {
        throw punti_non_sufficienti();
    }
}

void Premium::get_punti_bonus()
{
    punti+=puntiBonus;
}


Premium *Premium::clone() const
{
    return new Premium(*this);
}

string Premium::piano() const
{
    return "Premium";
}



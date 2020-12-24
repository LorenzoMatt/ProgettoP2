#include "basic.h"

unsigned int Basic::puntiDetrattiDomandaFatta=10;
unsigned int Basic::puntiPerDomandaData=15;
unsigned int Basic::puntiBonus=30;
unsigned int Basic::supplementoDomandaPriorita=5;


Basic::Basic(std::string username, std::string password, std::string nome, std::string cognome, std::string email,unsigned int punti)
    :Utente(username,password,nome,cognome,email,punti)
{

}

Basic::Basic(Profilo p, Accesso c, container<Utente *> a, container<Utente *> s, container<Domanda *> d)
    :Utente(p,c,a,s,d)
{

}

void Basic::cerca_utente(const Model & model, const std::string & username, container<std::string> & lista_di_elementi) const
{
    Utente* utente = model.get_utente(username);
    Utente::Funtore f(1);//nelle funzioni polimorfe il numero_funtore sarà sostituito con 1 in account gratuito,2 in gold e 3 in premium
    f(utente, lista_di_elementi);
}

void Basic::fai_domanda(Domanda* domanda)// il sollevamento dell'eccezione funziona a dovere
{
    try{
        if(this==domanda->get_autore_domanda())
        {
            if(domanda->get_priorita()==1)
            {
                get_domande().push_back(domanda);
            }
            else
            {
                if(supplementoDomandaPriorita*(domanda->get_priorita()-1)>punti)
                    throw punti_non_sufficienti();
                else{
                    get_domande().push_back(domanda);
                    punti-=(domanda->get_priorita()-1)*supplementoDomandaPriorita;
                }

            }
        }
        else
            throw non_autore_domanda();
    }catch(non_autore_domanda){
        std::cerr<<"non è l'autore della domanda";
    }
    catch(punti_non_sufficienti){
        std::cerr<<"punti per fare la domanda non sufficienti";
    }
    // dovrà essere aggiunta il controllo per il punteggio
}

container<Domanda *> Basic::cerca_domanda(const std::string & domanda, const Model & m)
{
        container<string> domanda_fatta=split(domanda," ");// divido la stringa domanda per spazi
        container<Domanda*> domande_trovate;
        for(auto it=get_amici().begin();it!=get_amici().end();++it)//scorro gli amici
        {
            const container<Domanda*>& domande_utente=(*it)->get_domande();//lista di domande dell'amico esaminato
            for(auto it=domande_utente.begin();it!=domande_utente.end();++it)// scorro la lista delle domande dell'amico corrente
            {
                container<string> domanda_esaminata=split((*it)->get_testo()," ");// divido la domanda corrente per spazi
                unsigned int lunghezza_parola_esaminata=domanda_esaminata.countElements();
                unsigned int count=0;//numero di parole che matchano fra domanda_fatta e domande_esaminata
                for(auto ut=domanda_esaminata.begin();ut!=domanda_esaminata.end() && count<=(lunghezza_parola_esaminata*0.6);++ut)
                    //scorri le parole della domanda_esaminata
                {
                    bool ok=false;
                    for(auto d=domanda_fatta.begin();d!=domanda_fatta.end() && !ok;++d)//scorro le parole  della domanda fatta
                    {
                        if(*ut==*d)//confronto fra parola della domanda_esaminata e della parola della domanda_fatta
                        {
                            ok=true;
                            count++;//incremento il numero di parole uguali fra la domanda fatta e quella esaminata
                        }
                    }

                 }
                if(count>=(lunghezza_parola_esaminata*0.6))// basterebbe ==
                {
                    domande_trovate.push_back(*it);
                }
            }

        }
        return domande_trovate;
}

void Basic::get_punti_domanda()
{
    punti+=puntiPerDomandaData;
    risposte_date++;
}



Basic *Basic::clone() const
{
    return new Basic(*this);
}

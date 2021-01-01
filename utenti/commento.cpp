#include "commento.h"


Commento::Commento(const string& t,Utente* u):testo(t),autore(u){}

string Commento::get_testo() const{
    return testo;
}
Utente* Commento::get_autore() const{
    return autore;
}
bool Commento:: operator==(const Commento& c) const{
    return testo==c.get_testo() && autore==c.get_autore();
}

std::ostream &operator<<(std::ostream & os, const Commento& c){

    return os<<"commento di: "<<c.autore->get_credenziali().get_username()<<endl<<c.testo;
}

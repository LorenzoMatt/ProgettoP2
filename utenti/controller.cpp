#include "controller.h"

Controller::Controller(const QString& utente,VistaUtente* vista,QObject *parent) :v(vista),QObject(parent)
{
    a=new Account(utente.toStdString());
}

Controller::~Controller()
{
}

void Controller::setModel(Account * modello)
{
    a=modello;
}

void Controller::setVista(VistaUtente * vista)
{
    v=vista;
}

void Controller::faiDomanda(const QString & testo,int priorita)
{
    try
    {
        a->fai_domanda(testo.toStdString(),priorita);
        v->aggiungiAreaDomandePersonali();//aggiorno la vista
        QMessageBox* messaggio=new QMessageBox(v);
        messaggio->setWindowTitle("Domanda effettuata correttamente");
        messaggio->setText("Domanda effettuata, ti restano in tutto "+QString::fromStdString(std::to_string(a->get_punti()))+" punti");
        messaggio->exec();
        a->salva();
    }
    catch(punti_non_sufficienti)
    {
        QErrorMessage* messaggio=new QErrorMessage(v);
        messaggio->setWindowTitle("Domanda non inserita");
        messaggio->showMessage("Non hai punti sufficienti per fare una domanda,"
                               "prova a rispondere domande di altri utenti oppure a cambiare piano");
    }
}

Profilo Controller::getProfilo() const
{
    return a->get_profilo();
}

Accesso Controller::getAccesso() const
{
    return a->get_credenziali();
}

container<Domanda *> Controller::getDomandeAmici() const
{
    return a->get_domande_amici();
}

container<string> Controller::cercaUtente(const QString & utente) const
{
    container<string> parametri;
        parametri=a->ricerca_contatto(utente.toStdString());
        if(parametri.empty())
        {
            parametri=a->ricerca_utente(utente.toStdString());
        }
        return parametri;
}

bool Controller::check_presenza_amico(const QString& user) const
{
    return a->check_presenza_amico(user.toStdString());
}

void Controller::aggiungi_amico(const QString & user)
{
    Utente* u=a->cerca_utente_per_nome(user.toStdString());
    a->aggiungi_amico(u);
    a->salva();
    v->aggiungiAreaDomandaAmici();
    // funzione per aggiornare le domande deglia amici
}

void Controller::togli_amico(const QString & user)
{
    Utente* u=a->cerca_utente_per_nome(user.toStdString());
    a->togli_amico(u);
    a->salva();
    v->aggiungiAreaDomandaAmici();
}
container<Domanda *> Controller::getDomandePersonali() const
{
    return a->get_domande();
}

int Controller::getPunti() const
{
    return a->get_punti();
}
void Controller::modificaNome(const string& n)
{

    return a->get_profilo().set_nome(n);
}

void Controller::modificaCognome(const string& c)
{
    return a->get_profilo().set_cognome(c);
}

void Controller::modificaEmail(const string& e)
{
    return a->get_profilo().set_email(e);
}

void Controller::modificaPassword(const string& p)
{
    return a->modifica_password(p);
}

void Controller::aggiungiCompetenza(const string& c)
{
    return a->AggiungiCompetenza(c);
}

void Controller::aggiungiTitoloDiStudio(const string& t)
{
    return a->AggiungiTitoloDiStudio(t);
}

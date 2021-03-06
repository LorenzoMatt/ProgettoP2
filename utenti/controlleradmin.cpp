#include "controlleradmin.h"
#include "basic.h"
#include "gold.h"
#include "premium.h"
#include "funzioniutili.h"
controllerAdmin::controllerAdmin(vistaAmministratore* v) :vista(v), db(new Database())
{
    db->import();
}



Database *controllerAdmin::get_db() const
{
    return db;
}

void controllerAdmin::togli_utente(const string & utente)
{
    db->togli_utente(utente);
    vista->aggiorna_tabella();
}

void controllerAdmin::salva() const
{
    db->exportdati();
}

Utente *controllerAdmin::get_utente(const string & utente) const
{
    Utente* ut=db->get_utente(utente);
    return ut;
}

void controllerAdmin::aggiungi_utente(const QString &username, const QString &password, const QString&nome,
                                       const QString&cognome, const QString&email, const QString&piano)
{
    try
    {
        string u=username.toStdString(),pw=password.toStdString(),n=nome.toStdString(),co=cognome.toStdString(),em=email.toStdString(),pi=piano.toStdString();
        if(piano=="Gold")
            db->aggiungi_utente(new Gold(u,pw,n,co,em));
        if(piano=="Basic")
            db->aggiungi_utente(new Basic(u,pw,n,co,em));
        if(piano=="Premium")
            db->aggiungi_utente(new Premium(u,pw,n,co,em));
        messaggio_informativo("utente aggiunto","utente "+username+" aggiunto con successo!",vista);
        vista->aggiorna_tabella();
    }
        catch(utente_gia_presente)
    {
        messaggio_errore("Utente non inserito","l'utente "+username+" è già presente",vista);
    }
}

void controllerAdmin::cambia_piano(const QString & utente,const QString& piano)
{
    Utente* u=db->get_utente(utente.toStdString());
    if(u)
    {
        string p=piano.toStdString();
        if(p==u->piano())
        {
            messaggio_errore("Piano non cambiato","l'utente "+utente+" ha già un piano "+piano,vista);
        }
        else
        {
            db->cambia_piano(u,p);
            messaggio_informativo("Cambio piano completato","Cambio piano andato a buon fine!",vista);
            vista->aggiorna_tabella();
        }
    }
    else
    {
        messaggio_errore("Utente non presente","Utente "+utente+" non presente",vista);
    }

}


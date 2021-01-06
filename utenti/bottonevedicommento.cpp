#include "bottonevedicommento.h"

bottoneVediCommento::bottoneVediCommento(Domanda* d, const QString& user, const QString &t, QWidget *parent):QPushButton(t,parent),utente(user),dom(d)
{

}

void bottoneVediCommento::vediCommenti()
{
    Domanda* d=dom;
    vista_domanda* dettagli=new vista_domanda(d,utente,this);
    dettagli->setWindowTitle("dettagli domanda");
    dettagli->show();
    connect(dettagli,SIGNAL(commento(const QString&,Domanda*)),this,SIGNAL(commento(const QString&,Domanda*)));
    connect(dettagli,SIGNAL(like(int,Domanda*)),this,SIGNAL(like(int,Domanda*)));
    connect(dettagli,SIGNAL(rimuovi(int,Domanda*)),this,SIGNAL(rimuovi(int,Domanda*)));
}

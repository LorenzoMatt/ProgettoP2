#ifndef BOTTONEVEDICOMMENTO_H
#define BOTTONEVEDICOMMENTO_H

#include <QPushButton>
#include "vistadomanda.h"
class Domanda;

class bottoneVediCommento:public QPushButton
{
    Q_OBJECT
private:
    QString utente;
    Domanda* dom;
public:
    bottoneVediCommento(Domanda*,const QString& ut,const QString& testo, QWidget* parent=nullptr);
private slots:
    void vediCommenti();
signals:
    void like(int,Domanda*);
    void commento(const QString&,Domanda*);
    void rimuovi(int,Domanda*);
};

#endif // BOTTONEVEDICOMMENTO_H

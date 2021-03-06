
#include "vistautente.h"
#include "controller.h"
#include "vistaprofilo.h"
#include "vistacercautente.h"
#include "funzioniutili.h"
#include "finestranuovadomanda.h"
#include "finestravistadomande.h"
#include "log.h"
//aggiunge area domanda utente con pulsante commenti
void vistaUtente::aggiungiAreaDomandaAmici()
{

    if (layoutWidgetPagina1) {// mi serve per aggiornare la lista delle domande quando tolgo o aggiungo un nuovo amico
        QLayoutItem *item;
        while((item = layoutWidgetPagina1->takeAt(0)) != 0) {
            if (item->widget()) {
                layoutWidgetPagina1->removeWidget(item->widget());
                delete item->widget();
            }
            delete item;
        }
    }
    //creo il widget da inserire dentro alla scrollArea

    QWidget* widgetDomandaAmici=new QWidget;
    QVBoxLayout* layoutWidgetDomandaAmici=new QVBoxLayout;
    container<Domanda*> contenitoreDomandeAmici=c->getDomandeAmici();
    for(unsigned int i=0;i<contenitoreDomandeAmici.size();i++){
    //costruisco il layout del widget che conterrá le domande che dovranno essere visualizzate e il pulsante
    //Vedi commenti
    Domanda* d=contenitoreDomandeAmici[i];
    string stringaAutore=d->get_autore_domanda()->get_credenziali().get_username();
    QLabel* autoreDomanda=new QLabel(QString::fromStdString(stringaAutore));

    //creo lo spazio che conterrá la domanda
    QTextEdit* testoDomanda=new QTextEdit(QString::fromStdString(d->get_testo()));
    testoDomanda->setReadOnly(true);

    layoutWidgetDomandaAmici->addWidget(autoreDomanda);
    layoutWidgetDomandaAmici->addWidget(testoDomanda);
    //creo la barra orizzontale con il pulsante per visualizzare i commenti
    QString u(QString::fromStdString(c->getAccesso().get_username()));
    bottoneVediCommento* commenti=new bottoneVediCommento(d,u,"vedi commenti");
    //pulsante per vedere i commenti
    connect(commenti,SIGNAL(clicked()),commenti,SLOT(vediCommenti()));

    //aggiungo il pulsante commenti sotto al testo della domanda
    layoutWidgetDomandaAmici->addWidget(commenti);
    layoutWidgetDomandaAmici->setAlignment(commenti,Qt::AlignRight);
    connect(commenti,SIGNAL(commento(const QString&,Domanda*)),c,SLOT(scrivi_commento(const QString&,Domanda*)));
    connect(commenti,SIGNAL(commento(const QString&,Domanda*)),commenti,SLOT(vediCommenti()));//aggiorno la vista delle domande
    connect(commenti,SIGNAL(rimuovi(int,Domanda*)),c,SLOT(rimuovi_commento(int,Domanda*)));
    connect(commenti,SIGNAL(rimuovi(int,Domanda*)),commenti,SLOT(vediCommenti()));//aggiorno la vista delle domande
    }

    //imposto come layout del widget il layout appena creato
    widgetDomandaAmici->setLayout(layoutWidgetDomandaAmici);
    layoutWidgetPagina1->addWidget(widgetDomandaAmici);
}

void vistaUtente::aggiungiAreaDomandePersonali()
{
    QWidget* widgetScrollAreaPagina2=new QWidget;
    QVBoxLayout* layoutScrollAreaPagina2=new QVBoxLayout;

    container<Domanda*> contenitoreDomandePersonali=c->getDomandePersonali();

    for(unsigned int i=0;i<contenitoreDomandePersonali.size();i++){

    //creo lo spazio che conterrá la domanda
    Domanda* d=contenitoreDomandePersonali[i];
    QTextEdit* testoDomanda=new QTextEdit(QString::fromStdString(d->get_testo()));
    testoDomanda->setReadOnly(true);

    layoutScrollAreaPagina2->addWidget(testoDomanda);
    //creo la barra orizzontale con il pulsante per visualizzare i commenti
    QString u(QString::fromStdString(c->getAccesso().get_username()));
    bottoneVediCommento* commenti=new bottoneVediCommento(d,u,"vedi commenti");
    //pulsante per vedere i commenti
    connect(commenti,SIGNAL(clicked()),commenti,SLOT(vediCommenti())); // visualizzo la domanda associata al pulsante
    connect(commenti,SIGNAL(commento(const QString&,Domanda*)),c,SLOT(scrivi_commento(const QString&,Domanda*)));
    connect(commenti,SIGNAL(like(int,Domanda*)),c,SLOT(dai_like(int,Domanda*)));
    connect(commenti,SIGNAL(rimuovi(int,Domanda*)),c,SLOT(rimuovi_commento(int,Domanda*)));
    connect(commenti,SIGNAL(commento(const QString&,Domanda*)),commenti,SLOT(vediCommenti()));//aggiorno la vista delle domande
    connect(commenti,SIGNAL(like(int,Domanda*)),commenti,SLOT(vediCommenti()));//aggiorno la vista delle domande
    connect(commenti,SIGNAL(rimuovi(int,Domanda*)),commenti,SLOT(vediCommenti()));//aggiorno la vista delle domande
    layoutScrollAreaPagina2->addWidget(commenti);
    layoutScrollAreaPagina2->setAlignment(commenti,Qt::AlignRight);
    }

    widgetScrollAreaPagina2->setLayout(layoutScrollAreaPagina2);
    pagina2->setWidget(widgetScrollAreaPagina2);
}

void vistaUtente::buildBarraSuperiore()
{
    layoutBarraSuperiore=new QHBoxLayout;

//  pulsanti della barra di ricerca
    profilo=new QPushButton("Profilo");
    invioDomanda=new QPushButton("Cerca");
    invioUtente=new QPushButton("Cerca");

//  linee di testo della barra di ricerca
    scriviDomanda=new QLineEdit();
    scriviDomanda->setPlaceholderText("cerca domanda");
    scriviDomanda->setMinimumWidth(300);
    scriviUtente=new QLineEdit();
    scriviUtente->setPlaceholderText("cerca utente");

    //aggiungo alla barra di ricerca gli elementi creati
    layoutBarraSuperiore->addWidget(profilo);
    layoutBarraSuperiore->addWidget(scriviDomanda);
    layoutBarraSuperiore->addWidget(invioDomanda);
    layoutBarraSuperiore->addWidget(scriviUtente);
    layoutBarraSuperiore->addWidget(invioUtente);
    connect(invioUtente,SIGNAL(clicked()),this,SLOT(buildCercaUtente()));
    connect(scriviUtente,SIGNAL(returnPressed()),this,SLOT(buildCercaUtente()));
    connect(invioDomanda,SIGNAL(clicked()),this,SLOT(buildDomandeCercate()));
    connect(scriviDomanda,SIGNAL(returnPressed()),this,SLOT(buildDomandeCercate()));
    connect(profilo,SIGNAL(clicked()),this,SLOT(vediProfilo()));
}

//costruisce la tabella con le due pagine (domande amici,domande personali)
//entrambe le pagine sono delle scrollArea ma nella pagina domande amici c'é una barra fissa per aggiungere domande
void vistaUtente::buildTabella()
{
    tabella=new QTabWidget;
    pagina1=new QScrollArea;

    pagina2=new QScrollArea;
    pagina1->setWidgetResizable(true);
    pagina2->setWidgetResizable(true);

    //creo i widget che contengono le scrollArea delle pagine
    QWidget* widgetPagina1=new QWidget;
    QWidget* widgetPagina2=new QWidget;
    layoutWidgetPagina1=new QVBoxLayout;
    layoutWidgetPagina2=new QVBoxLayout;

    //creo layout totale per la tabella
    QWidget* totalePagina2=new QWidget;
    QVBoxLayout* layoutTotalePagina2=new QVBoxLayout();
    totalePagina2->setLayout(layoutTotalePagina2);

    //QHBoxLayout che indica il numero di domande presenti e aggiungi domanda
    QHBoxLayout* layoutAggiungiDomanda=new QHBoxLayout;
    numeroDomandePersonali=new QLabel("numero di domande "+QString::number((c->getDomandePersonali().size())));
    layoutAggiungiDomanda->addWidget(numeroDomandePersonali);
    aggiungiDomanda=new QPushButton("fai domanda");
    layoutAggiungiDomanda->addWidget(aggiungiDomanda);

    widgetPagina1->setLayout(layoutWidgetPagina1);
    widgetPagina2->setLayout(layoutWidgetPagina2);
    //aggiungo i widget alle scrollArea
    pagina1->setWidget(widgetPagina1);
    pagina2->setWidget(widgetPagina2);

    layoutTotalePagina2->addLayout(layoutAggiungiDomanda);
    layoutTotalePagina2->addWidget(pagina2);

    //nella pagina1 devo creare le domande con i commenti degli amici dell'utente
    aggiungiAreaDomandaAmici();

    //nella pagina2 devo creare le domande con i commenti delle domane personali
    aggiungiAreaDomandePersonali();

    //aggiungo le scrollArea alla tabella
    tabella->addTab(pagina1,"Domande amici");
    tabella->addTab(totalePagina2,"Domande personali");
    connect(aggiungiDomanda,SIGNAL(clicked()),this,SLOT(buildFaiDomanda()));
}

vistaUtente::vistaUtente(const QString& utente, QWidget *parent):QWidget(parent),c(new Controller(utente,this))
{
    setAttribute(Qt::WA_DeleteOnClose);// serve a chiamare la delete della finestra, che a sua volta chiama la delete del controller che effettua il salvataggio del contenuto
    QVBoxLayout* mainLayout=new QVBoxLayout();

    //creo gli elementi da aggiungere al mainLayout
    buildBarraSuperiore();
    buildTabella();
    mainLayout->addLayout(layoutBarraSuperiore);
    mainLayout->addWidget(tabella);
    logout=new QPushButton("Logout");
    logout->setObjectName("annulla");
    connect(logout,SIGNAL(clicked()),this,SLOT(buildLogout()));
    mainLayout->addWidget(logout);
    setLayout(mainLayout);
}

vistaUtente::~vistaUtente()
{
    delete c;
}

void vistaUtente::vediProfilo()
{
    vistaProfilo* profilo=new vistaProfilo(c,this);
    profilo->setWindowTitle("Profilo");
    profilo->setMinimumWidth(500);
    profilo->show();
}

void vistaUtente::buildCercaUtente()
{
        container<string> parametri=c->cercaUtente(scriviUtente->text());
        if(scriviUtente->text()==QString::fromStdString(c->getAccesso().get_username()))// se è se stesso
        {
            messaggio_informativo("visita utente","per vedere i tuoi dati vai nella sezione profilo!",this);
            scriviUtente->clear();
        }
        else
        {
            if(!parametri.empty())
            {
                bool amico_presente=c->check_presenza_amico(scriviUtente->text());
                vistaCercaUtente* v=new vistaCercaUtente(parametri,amico_presente,this);
                v->show();
                connect(v,SIGNAL(invia(const QString&)),c,SLOT(aggiungi_amico(const QString&)));
                connect(v,SIGNAL(rimuovi(const QString&)),c,SLOT(togli_amico(const QString&)));
                connect(v,SIGNAL(invia(const QString&)),this,SLOT(buildCercaUtente()));
                connect(v,SIGNAL(rimuovi(const QString&)),this,SLOT(buildCercaUtente()));
            }else
            {
                messaggio_errore("Utente non presente","L'utente "+scriviUtente->text()+" non è stato trovato",this);
                scriviUtente->clear();
            }
        }
}

void vistaUtente::buildFaiDomanda()
{
    finestraNuovaDomanda* domanda=new finestraNuovaDomanda(this);
    domanda->show();
    connect(domanda,SIGNAL(invia(const QString&,int)),c,SLOT(faiDomanda(const QString&,int)));
    connect(domanda,SIGNAL(invia(const QString&,int)),this,SLOT(aggiornaNumeroDomande()));
}

void vistaUtente::buildDomandeCercate()
{
    QString domanda=scriviDomanda->text();
    container<Domanda*> d=c->cercaDomanda(domanda);
    finestraVistaDomande* f=new finestraVistaDomande(d,c,this);
    f->show();
    scriviDomanda->clear();
}

void vistaUtente::aggiornaAreaDomandeAmici()
{
    aggiungiAreaDomandaAmici();
}

void vistaUtente::aggiornaNumeroDomande()
{
    numeroDomandePersonali->clear();
    numeroDomandePersonali->setText("numero di domande "+QString::number((c->getDomandePersonali().size())));
}

void vistaUtente::buildLogout()
{
    Login* l=new Login;
    l->show();
    close();
}


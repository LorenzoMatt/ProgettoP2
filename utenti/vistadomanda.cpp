#include "vistadomanda.h"
#include "funzioniutili.h"
//aggiunge la domanda
void vistaDomanda::aggiungiWidgetDomanda(Domanda* d)
{
    QVBoxLayout* bloccoDomanda=new QVBoxLayout;

    QTextEdit* testoDomanda=new QTextEdit(QString::fromStdString(d->get_testo()));
    testoDomanda->setReadOnly(true);

    QString autoreDomanda=QString::fromStdString(d->get_autore_domanda()->get_credenziali().get_username());
    QLabel* autore=new QLabel(autoreDomanda);
    autore->setBuddy(testoDomanda);
    bloccoDomanda->addWidget(autore);
    bloccoDomanda->addWidget(testoDomanda);


    scrollwidgetLayout->addLayout(bloccoDomanda);
}

//aggiunge i commenti
void vistaDomanda::aggiungiWidgetCommenti(Domanda* d)
{
    QVBoxLayout* bloccoCommenti=new QVBoxLayout;

    //etichetta commenti:
    QLabel* risposte=new QLabel("Commenti:");
    bloccoCommenti->addWidget(risposte);

    //contenitore che contiene tutti i commenti degli amici riguardanti la domanda
    const container<Commento>& com=d->get_commenti();

    int num_commento=0;
    for(auto it=com.cbegin();it!=com.cend();++it,++num_commento){

        //testo commento
        QTextEdit* testoCommento=new QTextEdit(QString::fromStdString(it->get_testo()));
        testoCommento->setReadOnly(true);
        testoCommento->setObjectName("commenti");

        //etichetta autore domanda
        QString autoreCommento=QString::fromStdString(it->get_autore());
        QLabel* autore=new QLabel(autoreCommento);
        autore->setBuddy(testoCommento);
        bloccoCommenti->addWidget(autore);
        bloccoCommenti->addWidget(testoCommento);


        QHBoxLayout* valutaCommento=new QHBoxLayout;
        QString autoreDomanda=QString::fromStdString(d->get_autore_domanda()->get_credenziali().get_username());
        if(utente==autoreCommento || utente==autoreDomanda)// autore del commento e autore della domanda possono cancellare i commenti
        {
            QPushButton* rimuovi=new QPushButton("rimuovi");
            valutaCommento->addWidget(rimuovi);
            connect(rimuovi,SIGNAL(clicked()),signalMapperRimuovi,SLOT(map()));//mappo ogni rimuovi al corrispettivo commento
            signalMapperRimuovi->setMapping(rimuovi,num_commento);
        }
        if(utente==autoreDomanda)// solo l'autore della domanda ha la possibilità di mettere like
        {
            if((!(it->get_like())) && autoreCommento!=autoreDomanda)
            {
                QPushButton* like=new QPushButton("like");
                like->setObjectName("like");
                valutaCommento->addWidget(like);
                connect(like, SIGNAL(clicked()), signalMapperLike,SLOT(map()));
                signalMapperLike->setMapping(like,num_commento);//mappo ogni like al corrispettivo commento
            }
        }
        bloccoCommenti->addLayout(valutaCommento);
    }
    connect(signalMapperLike,SIGNAL(mapped(int)),SLOT(buildLike(int)));
    connect(signalMapperRimuovi,SIGNAL(mapped(int)),SLOT(buildRimuovi(int)));
    scrollwidgetLayout->addLayout(bloccoCommenti);
}

//barra di testo
void vistaDomanda::aggiungiBarraDiTesto()
{
    QHBoxLayout* inserisciCommento=new QHBoxLayout;
    testoCommento=new QLineEdit;
    testoCommento->setPlaceholderText("Scrivi un commento");
    QPushButton* invio=new QPushButton("invio");
    invio->setObjectName("ok");
    inserisciCommento->addSpacing(20);

    inserisciCommento->addWidget(testoCommento);
    inserisciCommento->addWidget(invio);

    scrollwidgetLayout->addLayout(inserisciCommento);

    connect(invio,SIGNAL(clicked()),this,SLOT(buildCommento()));
    connect(testoCommento,SIGNAL(returnPressed()),this,SLOT(buildCommento()));
}

//costruttore
vistaDomanda::vistaDomanda(Domanda * d, const QString & u, QWidget *parent) :QDialog(parent),domanda(new QVBoxLayout), dom(d),utente(u),
    scrollarea(new QScrollArea),scrollwidget(new QWidget),scrollwidgetLayout(new QVBoxLayout)
{
    signalMapperLike=new QSignalMapper;
    signalMapperRimuovi=new QSignalMapper;
    //aggiunge allo scrollWidgetLayout il widget che contiene la domanda
    aggiungiWidgetDomanda(dom);

    //aggiunge allo scrollWidgetLayout il widget che contiene tutti i commenti relativi alla domanda
    aggiungiWidgetCommenti(dom);

    //aggiunge una barra di testo editabile con il pulsante invio
    aggiungiBarraDiTesto();

    //settaggi
    scrollwidget->setLayout(scrollwidgetLayout);
    scrollarea->setWidget(scrollwidget);
    scrollarea->setWidgetResizable(true);
    domanda->addWidget(scrollarea);
    setLayout(domanda);
}

void vistaDomanda::buildCommento()
{
    if(!testoCommento->text().isEmpty())
    {
        emit commento(testoCommento->text(),dom);
        close();
        messaggio_informativo("commento aggiunto","Il messaggio è stato inserito correttamente",this);
    }
    else
    {
        messaggio_errore("commento vuoto","non è possibile scrivere un commento vuoto",this);
    }
}

void vistaDomanda::buildLike(int i)
{
    emit like(i,dom);
    close();
    messaggio_informativo("like aggiunto","l'utente apprezzerà il tuo like!",this);
}

void vistaDomanda::buildRimuovi(int i)
{
    emit rimuovi(i,dom);
    close();
    messaggio_informativo("commento rimosso","hai rimosso il commento",this);
}


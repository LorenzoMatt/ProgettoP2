#include "vistaamministratore.h"
#include "basic.h"
#include "gold.h"
#include "premium.h"
#include "controlleradmin.h"
#include "log.h"
#include "funzioniutili.h"
void vistaAmministratore::build_buttons()
{
    aggiungi=new QPushButton("Aggiungi utente");
    togli_utente_button=new QPushButton("Conferma");
    cambia_piano_button=new QPushButton("Conferma");
    esci=new QPushButton("Esci");
    esci->setObjectName("annulla");
    salva=new QPushButton("Salva database");
    salva->setObjectName("salva");
    connect(aggiungi,SIGNAL(clicked()),this,SLOT(finestra_aggiungi_utente()));
    connect(togli_utente_button,SIGNAL(clicked()),this,SLOT(togli_utente()));
    connect(cambia_piano_button,SIGNAL(clicked()),this,SLOT(cambio_piano()));
    connect(salva,SIGNAL(clicked()),this,SLOT(salva_db()));
    connect(esci,SIGNAL(clicked()),this,SLOT(logout()));
}

void vistaAmministratore::finestra_aggiungi_utente()
{
    creaUtente* utente=new creaUtente(this);
    utente->setWindowTitle("aggiungi un utente");

    utente->show();
    connect(utente,SIGNAL(invia(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&)),
            this, SLOT(aggiungi_utente(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&)));
}

void vistaAmministratore::togli_utente()
{
    Utente* ut=controller->get_utente(togli_utente_line->text().toStdString());
    if(ut)
    {
        controller->togli_utente(togli_utente_line->text().toStdString());
        messaggio_informativo("Utente rimosso","utente "+togli_utente_line->text()+" rimosso",this);
        togli_utente_line->clear();
    }
    else
    {
        messaggio_errore("Utente non rimosso","Utente "+togli_utente_line->text()+" non presente",this);
    }
}

void vistaAmministratore::cambio_piano()
{

    controller->cambia_piano(cambio_piano_username->text(),cambio_piano_combo->currentText());
}

void vistaAmministratore::salva_db()
{
    controller->salva();
    messaggio_informativo("","Salvataggio completato!",this);
}

void vistaAmministratore::logout()
{
    Login* log=new Login;
    log->show();
    close();
}

void vistaAmministratore::aggiungi_utente(const QString & username, const QString & password, const QString & nome, const QString & cognome, const QString & email,const QString& piano)
{
    controller->aggiungi_utente(username,password,nome,cognome,email,piano);
}




void vistaAmministratore::creazione_tabella()
{
    tabella_utenti=new QTableWidget();
    tabella_utenti->setColumnCount(7);
    horizontalheader=new QStringList();
    horizontalheader->append("Username");
    horizontalheader->append("Nome");
    horizontalheader->append("Cognome");
    horizontalheader->append("E-mail");
    horizontalheader->append("Competenze");
    horizontalheader->append("Titoli di studio");
    horizontalheader->append("Piano");
    tabella_utenti->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabella_utenti->setHorizontalHeaderLabels(*horizontalheader);
    tabella_utenti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QHeaderView* header = tabella_utenti->horizontalHeader();// adatta la larghezza delle colonne
    header->setSectionResizeMode(QHeaderView::Stretch);// adatta la larghezza delle colonne
    tabella_utenti->setMaximumHeight(400);

    aggiorna_tabella();
}

void vistaAmministratore::build_togli_utente()
{
    togli_utente_label=new QLabel("togli utente");
    togli_utente_line=new QLineEdit;
    togli_utente_label->setBuddy(togli_utente_line);
}

void vistaAmministratore::build_cambio_piano()
{
    cambio_piano_label=new QLabel("cambio piano utente");
    cambio_piano_username=new QLineEdit;
    cambio_piano_label->setBuddy(cambio_piano_username);
    nuovo_piano=new QLabel("nuovo piano");
    cambio_piano_combo=new QComboBox;
    cambio_piano_combo->addItem("Basic");
    cambio_piano_combo->addItem("Gold");
    cambio_piano_combo->addItem("Premium");
    nuovo_piano->setBuddy(cambio_piano_combo);
}

void vistaAmministratore::layout_parte_superiore()
{
    layout_togli_utente=new QHBoxLayout;
    layout_togli_utente->addWidget(togli_utente_label);
    layout_togli_utente->addWidget(togli_utente_line);

    cambio_piano_layout=new QFormLayout;
    cambio_piano_layout->addRow(cambio_piano_label,cambio_piano_username);
    cambio_piano_layout->addRow(nuovo_piano,cambio_piano_combo);

    layout_salva_esci=new QHBoxLayout;
    layout_salva_esci->addWidget(esci);
    layout_salva_esci->addWidget(salva);
}

void vistaAmministratore::scritta_utente()
{
    utenti=new QLabel("Utenti presenti nel database");
    utenti->setFont(  QFont("Times", 30, QFont::Bold));
    utenti->setBuddy(tabella_utenti);
    utenti->setMargin(50);
}

void vistaAmministratore::creazione_mainLayout()
{
    mainLyaout->addLayout(layout_togli_utente);
    mainLyaout->addWidget(togli_utente_button);
    mainLyaout->addLayout(cambio_piano_layout);
    mainLyaout->addWidget(cambia_piano_button);
    mainLyaout->addWidget(aggiungi);
    mainLyaout->addWidget(utenti,1,Qt::AlignHCenter);
    mainLyaout->addWidget(tabella_utenti,3);
    mainLyaout->addLayout(layout_salva_esci);
}

void vistaAmministratore::aggiorna_tabella()
{
    tabella_utenti->clearContents();
    tabella_utenti->setRowCount(controller->get_db()->get_utenti().size());

    int row=0;

    for(auto it=controller->get_db()->get_utenti().begin();it!=controller->get_db()->get_utenti().end();++it,++row)
    {
        QTableWidgetItem* Username=new QTableWidgetItem(QString::fromStdString((*it)->get_credenziali().get_username()));
        QTableWidgetItem* Nome=new QTableWidgetItem(QString::fromStdString((*it)->get_profilo().get_nome()));
        QTableWidgetItem* Cognome=new QTableWidgetItem(QString::fromStdString((*it)->get_profilo().get_cognome()));
        QTableWidgetItem* email=new QTableWidgetItem(QString::fromStdString((*it)->get_profilo().get_email()));
        QTableWidgetItem* Competenze=new QTableWidgetItem(QString::fromStdString((*it)->get_profilo().competenze_toString()));
        QTableWidgetItem* Titoli=new QTableWidgetItem(QString::fromStdString((*it)->get_profilo().titoli_di_studio_toString()));
        QTableWidgetItem* Piano=new QTableWidgetItem(QString::fromStdString((*it)->piano()));;
        tabella_utenti->setItem(row,0,Username);
        tabella_utenti->setItem(row,1,Nome);
        tabella_utenti->setItem(row,2,Cognome);
        tabella_utenti->setItem(row,3,email);
        tabella_utenti->setItem(row,4,Competenze);
        tabella_utenti->setItem(row,5,Titoli);
        tabella_utenti->setItem(row,6,Piano);
    }

}

vistaAmministratore::vistaAmministratore(QWidget *parent) :QWidget(parent),controller(new controllerAdmin(this))
{
    mainLyaout=new QVBoxLayout;

    build_buttons();

    build_togli_utente();

    build_cambio_piano();

    layout_parte_superiore();

    creazione_tabella();

    scritta_utente();

    creazione_mainLayout();

    setLayout(mainLyaout);
    setMaximumSize(1000,800);
    setWindowTitle("Amministratore");
}



vistaAmministratore::~vistaAmministratore()
{
}

#include "database.h"
#include "basic.h"
#include "gold.h"
#include "premium.h"
#include "funzioniutili.h"
Database::Database()
{
}

Database::~Database()
{
    //il depptr si proccupa di deallocare gli utenti
}

bool Database::check_presenza(const string &username)
{
    bool trovato=false;
    for(auto it=utenti.begin();it!=utenti.end() && !trovato;++it)
    {
        if((*it)->get_credenziali().get_username()==username)
            trovato=true;
    }
    return trovato;
}

void Database::sistema_amici_seguaci(Utente* utente)
{
        for(auto it=utente->seguaci.begin();it!=utente->seguaci.end();++it)
        {
            (*it)->togli_amico_ausiliario(utente);
        }
        for(auto it=utente->amici.begin();it!=utente->amici.end();++it)
        {
            (*it)->togli_seguace_ausiliario(utente);
        }
}

void Database::reverse_seguaci_amici(Utente* utente)
{
        for(auto it=utente->seguaci.begin();it!=utente->seguaci.end();++it)
        {
            (*it)->amici.push_back(utente);
        }
        for(auto it=utente->amici.begin();it!=utente->amici.end();++it)
        {
            (*it)->seguaci.push_back(utente);
        }
}

Database::Database(const container<DeepPtr<Utente> > &u):utenti(u)
{
}

void Database::aggiungi_utente(const DeepPtr<Utente> &utente)
{

        if(!check_presenza(utente->get_credenziali().get_username()))
            utenti.push_back(utente);
        else
            throw utente_gia_presente();
}

void Database::togli_utente(Utente *utente)
{
    bool trovato=false;
    for(auto it=utenti.begin();it!=utenti.end() && !trovato;++it)
        {
            if(&(**it)==utente)
            {
                sistema_amici_seguaci(utente);
                utenti.erase(it);
                trovato=true;
            }
        }
        if(!trovato)
        {
            throw amico_non_presente();
        }

}

void Database::togli_utente(const string & username)
{
        bool trovato=false;
        for(auto it=utenti.begin();it!=utenti.end() && !trovato;++it)
            {
                if((*it)->get_credenziali().get_username()==username)
                {
                    sistema_amici_seguaci(&(**it));
                    utenti.erase(it);
                    trovato=true;
                }
            }
            if(!trovato)
            {
                throw amico_non_presente();
            }

}

Utente* Database::cambia_piano(Utente *utente, const string &piano)
{

    bool trovato=false;
        for(auto it=utenti.begin();it!=utenti.end() && !trovato;++it)
        {
            if(&(**it)==utente)
            {
                sistema_amici_seguaci(utente);
                trovato=true;
                Profilo pf=(*it)->get_profilo();
                Accesso credenziali=(*it)->get_credenziali();
                container<Domanda*> dom=(*it)->get_domande_rif();
                container<Domanda*> domande;
                for(auto ut=dom.begin();ut!=dom.end();++ut)
                {
                    string testo=(*ut)->get_testo();
                    container<Commento> commenti=(*ut)->get_commenti();
                    unsigned int priorita=(*ut)->get_priorita();
                    domande.push_back(new Domanda(testo,priorita,commenti));
                }
                container<Utente*> amici=(*it)->get_amici();
                container<Utente*> seguaci=(*it)->get_seguaci();
                unsigned int risposte_date=(*it)->get_risposte_date();
                unsigned int punti=(*it)->get_punti();
                it=utenti.erase(it);
                if(piano=="Basic")
                    it=utenti.insert(it,DeepPtr<Utente>(new Basic(pf,credenziali,amici,seguaci,punti,risposte_date)));
                if(piano=="Gold")
                    it=utenti.insert(it,DeepPtr<Utente>(new Gold(pf,credenziali,amici,seguaci,punti,risposte_date)));
                if(piano=="Premium")
                    it=utenti.insert(it,DeepPtr<Utente>(new Premium(pf,credenziali,amici,seguaci,punti,risposte_date)));
                reverse_seguaci_amici(&(**it));
                for(auto ut=domande.begin();ut!=domande.end();++ut)
                {
                    (*ut)->set_autore(&(**it));
                }
                (*it)->set_domande(domande);
                return &(**it);
            }
        }
        if(!trovato)
            throw amico_non_presente();
    return 0;
}

Utente* Database::check_credenziali(const string & username, const string & password) const
{
        for(auto it=utenti.begin();it!=utenti.end();++it)
            if((*it)->get_credenziali().get_username()==username)
            {
                if((*it)->get_credenziali().get_password()==password)
                    return &(**it);
                else
                    return 0;
            }
        return 0;
}

const container<DeepPtr<Utente>>& Database::get_utenti() const
{
    return utenti;
}

Utente* Database::get_utente(const string& username) const
{
    bool trovato=false;
        for(auto it=utenti.begin();it!=utenti.end() && !trovato;++it)
            if((*it)->get_credenziali().get_username()==username)
            {
                trovato=true;
                return &(**it);
            }
        return 0;


}

void Database::exportdati() const
{

    QFile* file = new QFile("../database.xml"); //costruttore con il nome del file
        if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
        {
            messaggio_errore("file non aperto","file non aperto correttamente");
        }
        else
        {
            QXmlStreamWriter* inp = new QXmlStreamWriter; //per scrivere dentro a file
            inp->setAutoFormatting(true);
            inp->setDevice(file);
            inp->writeStartDocument(); //inizio a scrivere nel file
            inp->writeStartElement("campi_dati_utenti"); // inizio dei campi dati utenti
            for(auto it=utenti.begin();it!=utenti.end();++it)
            {
                inp->writeStartElement("utente");// inizio singolo utente
                inp->writeTextElement("tipoutente", QString::fromStdString((*it)->piano()));

                inp->writeTextElement("username",QString::fromStdString(((*it)->get_credenziali()).get_username()));
                inp->writeTextElement("password",QString::fromStdString(((*it)->get_credenziali()).get_password()));
                inp->writeTextElement("nome", QString::fromStdString(((*it)->get_profilo()).get_nome()));
                inp->writeTextElement("cognome", QString::fromStdString(((*it)->get_profilo()).get_cognome()));
                inp->writeTextElement("email", QString::fromStdString(((*it)->get_profilo()).get_email()));
                inp->writeStartElement("competenze"); // inizio delle competenze
                container<string> competenze=(*it)->get_profilo().GetCompetenze();
                for(auto com=competenze.begin();com!=competenze.end();++com)
                    inp->writeTextElement("competenza",QString::fromStdString(*com));

                inp->writeEndElement();// fine competenze
                inp->writeStartElement("titoli_di_studio");// inizio titoli di studio
                container<string> titoli=(*it)->get_profilo().GetTitoliDiStudio();
                for(auto tit=titoli.begin();tit!=titoli.end();++tit)
                    inp->writeTextElement("titolo",QString::fromStdString(*tit));

                inp->writeEndElement();// fine dei titoli di studio
                inp->writeTextElement("punti", QString::fromStdString(std::to_string(((*it)->get_punti()))));
                inp->writeTextElement("risposte_date", QString::fromStdString(std::to_string(((*it)->get_risposte_date()))));
                inp->writeEndElement();// fine di un utente
            }
            inp->writeEndElement();// fine campi dati degli utenti

            inp->writeEndDocument();
            file->close();
        }

            /* file per gli amici e le domande  */
            QFile* file2 = new QFile("../database_domande_e_amici.xml");
            if(!file2->open(QIODevice::WriteOnly | QIODevice::Text))
            {
                messaggio_errore("file non aperto","file non aperto correttamente");
            }
            else
            {
                QXmlStreamWriter* inp = new QXmlStreamWriter;
                inp->setAutoFormatting(true);
                inp->setDevice(file2);
                inp->writeStartDocument();
                inp->writeStartElement("domande_e_amici");
                //stampa gli amici, poi le domande e per ciscuna domanda i relativi commenti
            for(auto it=utenti.begin();it!=utenti.end();++it)
            {
                inp->writeStartElement("utente");
                inp->writeTextElement("username",QString::fromStdString(((*it)->get_credenziali()).get_username()));
                inp->writeTextElement("amici",QString::fromStdString((*it)->get_username_amici()));
                container<Domanda*> con=(*it)->get_domande();
                for(auto d=con.begin();d!=con.end();++d)
                {
                    inp->writeStartElement("domanda");
                    inp->writeTextElement("priorita",QString::fromStdString(std::to_string((*d)->get_priorita())));
                    inp->writeTextElement("testo",QString::fromStdString(((*d)->get_testo())));
                    inp->writeStartElement("commenti");
                    container<Commento> commenti=(*d)->get_commenti();
                    for(auto c=commenti.begin();c!=commenti.end();++c)
                    {
                        inp->writeStartElement("commento");// inizio commento
                        inp->writeTextElement("testo",QString::fromStdString(((*c).get_testo())));
                        inp->writeTextElement("autore_commento",QString::fromStdString((*c).get_autore()));
                        inp->writeTextElement("like",((*c).get_like()== true) ? "1" : "0");
                        inp->writeEndElement();// fine commento
                    }
                    inp->writeEndElement();//fine commenti
                    inp->writeEndElement();//fine domanda

                }
                inp->writeEndElement();// fine domande utente
            }
            inp->writeEndElement();// fine domande_amici utenti

            inp->writeEndDocument();
            file2->close();
        }

}

void Database::importa_dati_utenti()
{
    QFile* file=new QFile("../database.xml");
    if (!file->open(QFile::ReadOnly | QFile::Text))
    {
        messaggio_errore("dati non presenti","non è presente il file da cui leggere i dati");
    }
    else
    {
        QDomDocument documento;
        if(!documento.setContent(file)){
            return;
        }
        QDomElement root = documento.documentElement();//salvo la radice del file
        QDomNodeList nodes = root.elementsByTagName("utente");
        for(int i=0; i<nodes.count(); ++i)
        {
            QDomElement el = nodes.at(i).toElement();
            QDomNode nodo = el.firstChild();
            QString tipo,user, psw, nome, cognome,email, punti, risposte;
            container<string> competenze, titoli;
            while (!nodo.isNull()) {
                QDomElement elemento = nodo.toElement();
                QString tagName = elemento.tagName();
                if(tagName=="tipoutente")
                {
                    tipo=elemento.text();
                }
                if(tagName=="username")
                {
                    user=elemento.text();
                }
                if(tagName=="password")
                {
                    psw=elemento.text();
                }
                if(tagName=="nome")
                {
                    nome=elemento.text();
                }
                if(tagName=="cognome")
                {
                    cognome=elemento.text();
                }
                if(tagName=="email")
                {
                    email=elemento.text();
                }
                if(tagName=="competenze")
                {

                    QDomElement comp=elemento.toElement();
                    QDomNodeList lista_competenze =comp.elementsByTagName("competenza");
                    for(int x=0; x<lista_competenze.count(); ++x)
                    {
                        competenze.push_back(lista_competenze.at(x).toElement().text().toStdString());
                    }
                }
                if(tagName=="titoli_di_studio")
                {

                    QDomElement tit=elemento.toElement();
                    QDomNodeList lista_titoli=tit.elementsByTagName("titolo");
                    for(int x=0; x<lista_titoli.count(); ++x)
                    {
                        titoli.push_back(lista_titoli.at(x).toElement().text().toStdString());
                    }
                }
                if(tagName=="punti")
                {
                    punti=elemento.text();
                }
                if(tagName=="risposte_date")
                {
                    risposte=elemento.text();
                }
                nodo=nodo.nextSibling();
            }
            Utente* utente;
            unsigned short int punt=std::stoi(punti.toStdString());
            unsigned short int risp=std::stoi(risposte.toStdString());
            if(tipo=="Basic")
                utente=new Basic(user.toStdString(),psw.toStdString(),nome.toStdString(),
                                 cognome.toStdString(),email.toStdString(),punt,risp);

            if(tipo=="Gold")
                utente=new Gold(user.toStdString(),psw.toStdString(),nome.toStdString(),
                                 cognome.toStdString(),email.toStdString(),punt,risp);
            if(tipo=="Premium")
                utente=new Premium(user.toStdString(),psw.toStdString(),nome.toStdString(),
                                 cognome.toStdString(),email.toStdString(),punt,risp);
            utente->carica_competenze(competenze);
            utente->carica_titoli(titoli);
            aggiungi_utente(utente);
        }
        file->close();
    }
}

void Database::importa_amici_e_domande_utenti()
{
    /********import domande e amici********/
    QFile* file=new QFile("../database_domande_e_amici.xml");
    if (!file->open(QFile::ReadOnly | QFile::Text))
    {
        messaggio_errore("dati non presenti","non è presente il file da cui leggere i dati");
    }
    else
    {
        QDomDocument documento;
        if(!documento.setContent(file)){
            file->close();
            return;
        }
        QDomElement root = documento.documentElement();//salvo la radice del file
        QDomNodeList nodi_utenti = root.elementsByTagName("utente");
        for(int i=0; i<nodi_utenti.count(); ++i)
        {
            QDomElement el = nodi_utenti.at(i).toElement();
            QDomNode nodo = el.firstChild();
            QString user,amici;
            container<Domanda*> domande_utente;
            while (!nodo.isNull()) {
                QDomElement elemento = nodo.toElement();
                QString tagName = elemento.tagName();
                if(tagName=="amici")
                {
                    amici=elemento.text();
                }
                if(tagName=="username")
                {
                    user=elemento.text();
                }
                if(tagName=="domanda")
                {
                    QDomNode domande=elemento.firstChild();//elementi della domanda
                    QString testo_domanda,priorita;
                    container<Commento> commenti_totali;
                    while(!domande.isNull())
                    {
                        QDomElement elemento_domande = domande.toElement();
                        QString tagNameDomande = elemento_domande.tagName();
                        if(tagNameDomande=="priorita")
                        {
                            priorita=elemento_domande.text();
                        }
                        if(tagNameDomande=="testo")
                        {
                            testo_domanda=elemento_domande.text();
                        }
                        if(tagNameDomande=="commenti")
                        {
                            QDomElement commenti=elemento_domande.toElement();
                            QDomNodeList lista_commenti =commenti.elementsByTagName("commento");
                            for(int x=0; x<lista_commenti.count(); ++x)
                            {
                                QDomElement commento= lista_commenti.at(x).toElement();
                                QString testo_commento, autore_commento, like;
                                QDomNode elementi_del_commento=commento.firstChild();
                                while (!elementi_del_commento.isNull())
                                {
                                    QDomElement elemento_commento=elementi_del_commento.toElement(); //che è comento
                                    QString tagNameCommento = elemento_commento.tagName();
                                    if(tagNameCommento=="testo")
                                    {
                                        testo_commento=elemento_commento.text();
                                    }
                                    if(tagNameCommento=="autore_commento")
                                    {
                                        autore_commento=elemento_commento.text();
                                    }
                                    if(tagNameCommento=="like")
                                    {
                                        like=elemento_commento.text();
                                    }
                                    elementi_del_commento=elementi_del_commento.nextSibling();
                               }
                                commenti_totali.push_back(Commento(testo_commento.toStdString(),autore_commento.toStdString(),like.toInt()));//conversione int->bool
                        }
                    }
                        domande=domande.nextSibling();
                }
                    Domanda* domanda=0;
                    domanda=new Domanda(testo_domanda.toStdString(),get_utente(user.toStdString())
                                                 ,std::stoi(priorita.toStdString()));
                    domanda->set_commenti(commenti_totali);
                    domande_utente.push_back(domanda);
            }//fine domanda
                nodo=nodo.nextSibling();
            }//fine singolo utente
            Utente* utente;
            utente=get_utente(user.toStdString());
            aggiungi_amici_ad_utente(amici.toStdString(),user.toStdString());
            utente->set_domande(domande_utente);
        }//fine ciclo for
        file->close();
    }
}

void Database::import()
{
    importa_dati_utenti();
    importa_amici_e_domande_utenti();
}

void Database::aggiungi_amici_ad_utente(const string& amici, const string& user)
{
    container<string> a=Utente::split(amici," ");
    Utente* utente=get_utente(user);
    for(auto it=a.begin();it!=a.end();++it)
    {
        utente->aggiungi_amico(get_utente(*it));
    }
}

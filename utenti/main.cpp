#include "home.h"
#include <QApplication>
#include "utente.h"
#include <list>



int main()
{


//    QApplication a(argc, argv);
//    Home w;
//    w.show();



//    return a.exec();
    //  ////////////////////////////////////////////////////////////TEST UTENTE ///////////////////////////////////////////////////////////
    cout<<"TEST UTENTI"<<endl<<endl;
    Utente ut("Pikachu","dioboia","diostronzo","porco","dio");
    ut.get_profilo().AggiungiCompetenza("stare a letto");
    ut.get_profilo().AggiungiCompetenza("stare a letto");
    cout<<ut.get_profilo();
    Utente x("Lorenzo","dioboia","diostronzo","porco","dio");
    Utente x2("Elisa","dioboia","diostronzo","porco","dio");
    Utente x3("Mirko","dioboia","diostronzo","porco","dio");
    Utente x4("Francesca","dioboia","diostronzo","porco","dio");
    Utente x5("Elton","dioboia","diostronzo","porco","dio");
    ut.aggiungi_amico(x);
    ut.aggiungi_amico(x2);
    ut.aggiungi_amico(x3);
    ut.aggiungi_amico(x4);
    x2.aggiungi_amico(x);
    x3.aggiungi_amico(x);
    x4.aggiungi_amico(x);
    int i=1;

    cout<<"amici di ut ------------------------"<<endl;
    for(container<Utente*>::const_iterator it=ut.get_amici().begin();it!=ut.get_amici().end();++it,i++){
       cout<<"amico n. "<<i<<endl<<**it<<endl;
    }
    i=1;
    cout<<endl<<"seguaci di x--------------------------------------------"<<endl;
    for(container<Utente*>::const_iterator it=x.get_seguaci().begin();it!=x.get_seguaci().end();++it,i++){
        cout<<"seguace n. "<<i<<endl<<endl<<**it;
    }
    i=1;
    cout<<"bastaaaaa seguaci di x--------------------------------------------"<<endl;
    ut.togli_amico(&x);
    for(container<Utente*>::const_iterator it=x.get_seguaci().begin();it!=x.get_seguaci().end();++it,i++){
        cout<<"seguace n. "<<i<<endl<<endl<<**it;
    }
    i=1;
    cout<<"amici di ut ------------------------"<<endl;
    for(container<Utente*>::const_iterator it=ut.get_amici().begin();it!=ut.get_amici().end();++it,i++){
       cout<<"amico n. "<<i<<endl<<**it<<endl;
    }
    cout<<endl<<"fine amici di ut ------------------------"<<endl;



    //for (list<Utente*>::iterator it=l.begin();it!=l.end();++it)
            //cout<<**it;
    container<Utente*> dd= ut.get_amici();
    for(container<Utente*>::iterator it=dd.begin();it!=dd.end();++it){
        (*it)->set_profilo("gesu bastardo");
        cout<<**it<<endl;
    }
    cout<<endl<<endl<<endl<<"dvnssdvnijndjsnvjdvnsjdvnskisdvnjdvnvjdfsbn dvs";
     //container<Utente*> dd2=ut.get_amici();
     for(container<Utente*>::const_iterator it=ut.get_amici().begin();it!=ut.get_amici().end();++it){
         (*it)->set_profilo("madonna bastarda");
        cout<<**it<<endl;
     }
     for(container<Utente*>::iterator it=dd.begin();it!=dd.end();++it){

         cout<<**it<<endl;
     }

   // for(auto it=ut.get_amici().cbegin();it!=ut.get_amici().cend();++it)
        // cout<<(**it)<<endl;
    //container<utente> d;
    //d.insertBack(ut);
    //d.insertBack(utente("non lo so","dioboia","diostronzo","porco","dio"));
    //model c(d);
    //cout<<c.get_utenti();


cout<<endl<<endl<<endl<<"TEST DOMANDE"<<endl<<endl;
    // ///////////////////////////////////////////////////////////TEST DOMANDE ////////////////////////////////////////////////////////////
    Domanda domanda("ho una domanda",&ut,0);
    cout<<*(domanda.get_autore_domanda());// OK
    Commento commento1("vaffanculo",nullptr);
    domanda.aggiungi_commento(Commento("non abbiamo chiesto",nullptr)); //OK
    domanda.aggiungi_commento(Commento("non ho commenti da aggiungere",nullptr)); //OK
    domanda.aggiungi_commento(commento1);//OK
    cout<<domanda; //OK
   // domanda.RimuoviCommento(Commento("non ho commenti da aggiungere",nullptr)); //OK
    //domanda.RimuoviCommento(commento1);//OK
    cout<<endl<<domanda;
    ut.fai_domanda(domanda);
    cout<<endl<<endl<<endl<<"DIOBOIAAAAAAAAAAAA"<<endl;
    container<Domanda*> store=ut.get_domande();
    for(container<Domanda*>::iterator it=store.begin();it!=store.end();++it)
        cout<<**it<<endl;


    // /////////////////////////////////////////////////////// TEST PROFILO //////////////////////////////////////////
    cout<<endl<<endl<<endl<<"TEST PROFILO"<<endl<<endl;

    Profilo e("porco","dio","bastardo");
    e.AggiungiCompetenza("farsi le seghe");
    e.AggiungiCompetenza("bestemmiare");
    e.AggiungiCompetenza("pisciare");
    cout<<e.GetCompetenze();
    Profilo e2("porco","dio","bastardo");
    Profilo e3("porco","dio","bastardo");
    Profilo e4("porco","dio","bastardo");
    container<Profilo*> profili;
    profili.push_back(&e);
    profili.push_back(&e2);
    profili.push_back(&e3);
    profili.push_back(&e4);
    for(container<Profilo*>::iterator it=profili.begin();it!=profili.end();++it)
        cout<<**it<<endl;




}

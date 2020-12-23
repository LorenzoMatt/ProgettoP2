#include "test_utenti.h"
#include "home.h"
#include <QApplication>
#include "utente.h"
#include "model.h"
#include <list>
#include "deepptr.h"
#include <memory>
#include "prova.h"
int test_utenti()
{
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
    x.aggiungi_amico(ut);
    x.aggiungi_amico(x2);
    x.aggiungi_amico(x3);
    x.aggiungi_amico(x4);
    x2.aggiungi_amico(ut);
    x2.aggiungi_amico(x);
    x2.aggiungi_amico(x3);
    x2.aggiungi_amico(x4);
    x3.aggiungi_amico(ut);
    x3.aggiungi_amico(x);
    x3.aggiungi_amico(x2);
    x3.aggiungi_amico(x4);
    x4.aggiungi_amico(ut);
    x4.aggiungi_amico(x);
    x4.aggiungi_amico(x2);
    x4.aggiungi_amico(x3);
    // x4.togli_amico(&x4);*/
    int i=1;

    Utente j("ciao","dd","t","g","w");


    cout<<"amici di ut ------------------------"<<endl;
    for(container<Utente*>::const_iterator it=ut.get_amici().begin();it!=ut.get_amici().end();++it,i++){
        cout<<"amico n. "<<i<<endl<<**it<<endl;
    }
    i=1;
    cout<<"amici di x ------------------------"<<endl;
    for(container<Utente*>::const_iterator it=x.get_amici().begin();it!=x.get_amici().end();++it,i++){
        cout<<"amico n. "<<i<<endl<<**it<<endl;
    }
    i=1;
    cout<<"amici di x2 ------------------------"<<endl;
    for(container<Utente*>::const_iterator it=x2.get_amici().begin();it!=x2.get_amici().end();++it,i++){
        cout<<"amico n. "<<i<<endl<<**it<<endl;
    }
    i=1;
    cout<<endl<<"seguaci di x2--------------------------------------------"<<endl;
    for(container<Utente*>::const_iterator it=x2.get_seguaci().begin();it!=x2.get_seguaci().end();++it,i++){
        cout<<"seguace n. "<<i<<endl<<endl<<**it;
    }
    cout<<"fine seguaci di x2--------------------------------------------"<<endl<<endl;

    i=1;
    cout<<endl<<"seguaci di x--------------------------------------------"<<endl;
    for(container<Utente*>::const_iterator it=x.get_seguaci().begin();it!=x.get_seguaci().end();++it,i++){
        cout<<"seguace n. "<<i<<endl<<endl<<**it;
    }
    cout<<"fine seguaci di x--------------------------------------------"<<endl<<endl;

    ut.togli_amico(&x);
    cout<<"tolto x dagli amici di ut"<<endl;
    //ut.togli_amico(&j);
    i=1;
    cout<<"controllo seguaci di x--------------------------------------------"<<endl;
    for(container<Utente*>::const_iterator it=x.get_seguaci().begin();it!=x.get_seguaci().end();++it,i++){
        cout<<"seguace n. "<<i<<endl<<endl<<**it;
    }
    i=1;
    cout<<endl<<"seguaci di x2--------------------------------------------"<<endl;
    for(container<Utente*>::const_iterator it=x2.get_seguaci().begin();it!=x2.get_seguaci().end();++it,i++){
        cout<<"seguace n. "<<i<<endl<<endl<<**it;
    }
    cout<<"fine seguaci di x2--------------------------------------------"<<endl<<endl;
    i=1;
    cout<<"amici di ut ------------------------"<<endl;
    for(container<Utente*>::const_iterator it=ut.get_amici().begin();it!=ut.get_amici().end();++it,i++){
        cout<<"amico n. "<<i<<endl<<**it<<endl;
    }
    i=1;
    cout<<endl<<"fine amici di ut ------------------------"<<endl;
    ut.aggiungi_amico(x);
    cout<<"riaggiunto x agli amici di ut"<<endl;
    cout<<"amici di ut ------------------------"<<endl;
    for(container<Utente*>::const_iterator it=ut.get_amici().begin();it!=ut.get_amici().end();++it,i++){
        cout<<"amico n. "<<i<<endl<<**it<<endl;
    }
    cout<<endl<<"fine amici di ut ------------------------"<<endl;
    x.togli_seguace(&ut);
    //x.togli_seguace(&j); OK
    i=1;
    cout<<"tolto seguace ut da x"<<endl;
    cout<<"amici di ut ------------------------"<<endl;
    for(container<Utente*>::const_iterator it=ut.get_amici().begin();it!=ut.get_amici().end();++it,i++){
        cout<<"amico n. "<<i<<endl<<**it<<endl;
    }
    cout<<endl<<"fine amici di ut ------------------------"<<endl;

    cout<<"controllo seguaci di x--------------------------------------------"<<endl;
    i=1;
    for(container<Utente*>::const_iterator it=x.get_seguaci().begin();it!=x.get_seguaci().end();++it,i++){
        cout<<"seguace n. "<<i<<endl<<endl<<**it;
    }
    i=1;
    cout<<"fine del controllo seguaci di x--------------------------------------------"<<endl;
    cout<<"controllo seguaci di x2--------------------------------------------"<<endl;
    i=1;
    for(container<Utente*>::const_iterator it=x2.get_seguaci().begin();it!=x2.get_seguaci().end();++it,i++){
        cout<<"seguace n. "<<i<<endl<<endl<<**it;
    }
    i=1;
    cout<<"fine del controllo seguaci di x2--------------------------------------------"<<endl;

    //for (list<Utente*>::iterator it=l.begin();it!=l.end();++it)
    //cout<<**it;

    cout<<"modifica del profilo di ut tramite una copia--------------------------------------------"<<endl;
    container<Utente*> dd= ut.get_amici();
    for(container<Utente*>::iterator it=dd.begin();it!=dd.end();++it){
        (*it)->set_nome_profilo("gesu bastardo");
        cout<<**it<<endl;
    }
    cout<<endl<<endl<<endl<<"dvnssdvnijndjsnvjdvnsjdvnskisdvnjdvnvjdfsbn dvs";
    //container<Utente*> dd2=ut.get_amici();
    for(container<Utente*>::const_iterator it=ut.get_amici().begin();it!=ut.get_amici().end();++it){
        (*it)->set_nome_profilo("madonna bastarda");
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
    cout<<endl<<endl<<"username degli amici di ut"<<endl<<endl;
    cout<<x.get_username_amici(); //OK
    return 0;
}

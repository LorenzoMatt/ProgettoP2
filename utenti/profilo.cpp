//#include "profilo.h"

//profilo::profilo(){}

//void profilo::SetNome(string n){nome=n;}
//void profilo::SetCognome(string c){cognome=c;}
//void profilo::SetEmail(string e){email=e;}

//profilo::nodo::nodo():next(0){}
//profilo::nodo::nodo(int i,nodo* n):info(i),next(n){}

//void profilo::AggiungiLingua(string lingua){
//    lingue.insertBack(lingua);
//}

//void profilo::StampaLingue() const{
//    for(auto it=lingue.cbegin();it!=lingue.cend();++it)
//        cout<<*it<<endl;
//}
#include "profilo.h"


profilo::profilo(){}
profilo::~profilo(){}
profilo::profilo(const string& n,const string& c,const string& e):nome(n),cognome(c),email(e){}

void profilo::SetNome(const string& n){nome=n;}
void profilo::SetCognome(const string& c){cognome=c;}
void profilo::SetEmail(const string& e){email=e;}

void profilo::AggiungiCompetenza(const string& c){
    competenze.insertFront(c);
}
void profilo::AggiungiTitoloDiStudio (const string& t){
    titoli_di_studio.insertFront(t);
}

string profilo::GetNome() const{return nome;}
string profilo::GetCognome() const{return cognome;}
string profilo::GetEmail() const{return email;}

container<string>::const_iterator profilo::GetCompetenze() const{
    auto it=competenze.cbegin();
    return it;
}
container<string>::const_iterator profilo::GetTitoliDiStudio() const{
    auto it=titoli_di_studio.cbegin();
    return it;
}

std::ostream& operator<<(std::ostream& os,const profilo& p){
    os<<"nome: " <<p.GetNome()<<endl<<"cognome: "<<p.GetCognome()<<endl<<"email: "<<p.GetEmail();
    os<<endl<<"competenze: ";
    for(auto it=p.GetCompetenze();it!=p.competenze.cend();++it)
        os<<*it<<"  ";
    os<<endl<<"Titoli di studio: ";
    for(auto it=p.GetTitoliDiStudio();it!=p.titoli_di_studio.cend();++it)
        os<<*it<<"  ";
    return os;

}


#include <bits/stdc++.h>
#include <conio.h>

using namespace std;

class incasari {
    private:
    //facem categori de incasari bazate pe categoria vehiculului
    int A;
    int B;
    int C;
    int D;
    int total;
    public:
    //facem constructor pentru initializarea variabilelor A,B,C,D
    incasari() {
        this->A = 0;
        this->B = 0;
        this->C = 0;
        this->D = 0;
    }
    //introducem valorile
    void input(int A,int B, int C, int D, int total) {
        this->A = A;
        this->B = B;
        this->C = C;
        this->D = D;
        this->total = total;
    }
    //afisam variabilele si folosimm setw() pt a seta latimea campurilor
    void display() {
        cout<<"\n--------------------------------------------------------------------------------------------\n";
        cout<<setw(10)<<"Categoria A:"<<setw(10)<<"Categotia B:"<<setw(10)<<"Categoria C:"<<setw(10)<<"Categoria D:";
        cout<<"\n--------------------------------------------------------------------------------------------\n";
        cout<<setw(9)<<this->A<<' '<<setw(9)<<this->B<<' '<<setw(9)<<this->C<<' '<<setw(9)<<this->D<<endl;
    }

};

class tip_vehicul {
private:
    char nume_tip_vehicul[100];
public:
    tip_vehicul() {
        strcpy(nume_tip_vehicul,"vehicul");
    }
    //selectam tipul vehiculului
    void setare_tip_vehicul(incasari &Incasari) {
while(1){
        cout<<"Selecteaza categoria vehiculuilui: "<<endl;
        cout<<"1.A"<<' '<<"2.B"<<' '<<"3.C"<<' '<<"4.D"<<endl;
        int tip_vehicul;
        cin>>tip_vehicul;
        if(tip_vehicul==1) {
            strcpy(nume_tip_vehicul,"A");
            Incasari.input(20,0,0,0,20);
            break;
        }
        else if(tip_vehicul==2) {
            strcpy(nume_tip_vehicul,"B");
            Incasari.input(0, 20,0,0,20);
            break;
        }
        else if(tip_vehicul==3) {
            strcpy(nume_tip_vehicul,"C");
            Incasari.input(0,0,60,0,60);
            break;
        }
        else if(tip_vehicul==4) {
            strcpy(nume_tip_vehicul,"D");
            Incasari.input(0,0,0,100,100);
            break;
        }
        else {
            //in caz in care sunt date nevalide
            cout<<"Eroare la intrare"<<endl;
        }
}
    }
    void display_tip_vehicul() {
        cout<<nume_tip_vehicul<<' '<<endl;
    }
};

class vehicul:public tip_vehicul {
private:
    //stocam date despre vehicul in private
    int nr_vehicul;//numarul de intrare a vehiculuilui in baza de date a parcarii
    char nr_matriculare[10];
    char culoare[10];
    char marca[20];
    char model[20];
    char ora_intrare[10];
    char ora_iesire[10];
    incasari Incasari;
public:
    //constructorul vehicul() are rolul de a initializa toate variabilele clasei
    vehicul()
    {
    this->nr_vehicul = 0;
        strcpy(this->nr_matriculare,"default");
        strcpy(this->culoare,"default");
        strcpy(this->marca,"default");
        strcpy(this->model,"default");
        time_t tt;
        time(&tt);
        strcpy(this->ora_intrare,asctime(localtime(&tt)));
        strcpy(this->ora_iesire,asctime(localtime(&tt)));
    }
    //introducem detaliile vehiculului
    void intrare(){
        cout<<"Introduceti numarul vehiculului "<<endl;
        cin>>nr_vehicul;
        cout<<"Introduceti numarul matriculare "<<endl;
        cin.getline(nr_matriculare,10);
        cout<<"Introduceti culoarea "<<endl;
        cin>>culoare;
        cout<<"Introduceti marca "<<endl;
        cin>>marca;
        cout<<"Introduceti model "<<endl;
        cin>>model;
        setare_tip_vehicul(Incasari);
        time_t tt;
        time(&tt);
        strcpy(this->ora_intrare,asctime(localtime(&tt)));
        strcpy(this->ora_iesire,asctime(localtime(&tt)));
    }

    //afisarea
    void iesire() {
        cout<<"Numarul vehicului "<<nr_vehicul<<endl;
        cout<<"Numarul matriculare "<<nr_matriculare<<endl;
        cout<<ora_iesire<<" - "<<ora_iesire<<endl;
    }
    void afisare_vehicul() {
        cout<<nr_vehicul<<' '<<marca<<' '<<culoare<<endl;
        Incasari.display();
    }
    //urmeaza sa implementez
    void adauga_vehicul();
    void adauga_in_lista();
    void cautare_vehicul(int nr);//nr-numarul vehiculului
    void stergere_vehicul(int nr);
    void update(int nr);//u[tadatm starea vehiculului
};

//deschidem fisierul in mod binar

void vehicul::adauga_vehicul() {
    ofstream g;
    g.open("add_data.txt",ios_base::app|ios_base::binary);
    getch();
    g.write((char*)this,sizeof(*this));
    g.close();
}

//deschidem fisierul si citim obiectele din acesta

void vehicul::adauga_in_lista() {
    ifstream f;
    int n=0;
    f.open("add_data.txt",ios_base::in|ios_base::binary);
    if(!f) {
        cout<<"Fisier lipsa"<<endl;
    }
    else {
        f.read((char*)this,sizeof(*this));
        while(!f.eof()) {
        this->afisare_vehicul();
            n++;
            f.read((char*)this,sizeof(*this));
        }
        f.close();
    }
}

//cautam vehiculul, daca se gaseste nr de identificare, afisam vehiculul

void vehicul::cautare_vehicul(int nr) {
    ifstream f;
    int n=0;
    f.open("add_data.txt",ios_base::in|ios_base::binary);
    if(!f) {
        cout<<"Fisier lipsa"<<endl;
    }
    else {
        f.read((char*)this,sizeof(*this));
        while(!f.eof()) {
            if(this->nr_vehicul==nr) {
                this->afisare_vehicul();
                n=1;
                break;
            }
            f.read((char*)this,sizeof(*this));
        }
        f.close();
        if(nr==0)
            cout<<"Lipsa date"<<endl;
    }
}

//cautam si stergem si actualizam fisierul, daca flg=0, nu am gasit vehiculul iar daca flg=1 am gasit si afisam "obiect sters"

void vehicul::stergere_vehicul(int nr) {
    ifstream f;
    ofstream g;
    int flg=0;
    f.open("add_data.txt",ios_base::in|ios_base::binary);
    if(!f) {
        cout<<"Fisier lipsa"<<endl;
    }
    else {
        f.read((char*)this,sizeof(*this));
        g.open("add_temp_data.txt",ios_base::in|ios_base::binary);
        while(!f.eof()) {
            if(this->nr_vehicul==nr) {
                flg=1;
            }
            else {
                g.write((char*)this,sizeof(*this));
            }
            f.read((char*)this,sizeof(*this));
        }
        f.close();
        g.close();
        if(nr==0){
            cout<<"Lipsa date, nu putrm sterge obiectul "<<endl;
            getch();
            remove("add_data.txt");
        }
        else {
            cout<<"Obiect sters"<<endl;
            getch();
            remove("add_data.txt");
            getch();
            rename("add_temp_data.txt","add_data.txt");
        }
    }
}

//facem functia de update a starii vehiculului
void vehicul::update(int nr) {

}


int main()
{
    system("cls");
    vehicul v;
    //v.intrare();
    //v.afisare_vehicul();
    //v.adauga_in_lista();
    //v.stergere_vehicul(100);
    getch();
    return 0;
}

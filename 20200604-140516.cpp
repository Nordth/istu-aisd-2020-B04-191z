#include <iostream>


using namespace std;

class Person{
private:
    string firstname;
    string family;
    string lastname;
    int age;
    
public:

    string GetName(){
        return firstname;
    }

    string GetSurname(){
        return family;
    }

    string GetPatronymic(){
        return lastname;
    }

    int GetAge(){
        return age;
    }

    void SetName(string valueName){
        while (valueName.length() > 20){
            cout << "Слишком длинное имя. Повторите ввод:";
            cin >> valueName;
        }
        if (valueName.length() <= 20){
            firstname = valueName;
        }
    }

    void SetSurname(string valueSurname){
        while (valueSurname.length() > 20){
            cout << "Слишком длинная фамилия. Повторите ввод:";
            cin >> valueSurname;
        }
        if (valueSurname.length() <= 20){
            family = valueSurname;
        }
    }

    void SetPatronymic(string valuePatronymic){
        while (valuePatronymic.length() > 20){
            cout << "Слишком длинное отчество. Повторите ввод:";
            cin >> valuePatronymic;
        }

        if (valuePatronymic.length() <= 20){
            lastname = valuePatronymic;
        }
    }

    void SetAge(int valueAge){
        while (valueAge < 0 || valueAge > 200){
            cout << "Возраст не вписывается в рамки ограничений. Повторите ввод:";
            cin >> valueAge;
        }
        if (valueAge >= 0 && valueAge <= 200){
            age = valueAge;
        }
    }

    Person(){
        firstname = "NoFirstName";
        family = "NoFamily";
        lastname = "NoLastName";
        age = 0;
    }

    Person(string valueName,string valueSurname,string valuePatronymic,int valueAge){
        this->SetName(valueName);
        this->SetSurname(valueSurname);
        this->SetPatronymic(valuePatronymic);
        this->SetAge(valueAge);
    }

    void Print(){
        cout << this->GetName() << " ";
        cout << this->GetSurname() << " ";
        cout << this->GetPatronymic() << " ";
        cout << this->GetAge() << endl;
    }
};

class Kassa{
private:
    Person Kassir;
    Person klient;
    string kassa;
public:

    Kassa(){
        this->kassa = "kassa1";
        this->Kassir = Kassir;
        this->klient = klient;
    }

    Kassa(string kass,Person kassir, Person klt){
        this->kassa = kass;
        this->Kassir = kassir;
        this->klient = klt;
    }
    void SetKlient(Person kl)
    {
        this->klient = kl;
    }
    void SetKassir(Person Kassir){
        if (Kassir.GetName() == this->Kassir.GetName()){
            cout << "Кассир не может быть клиентом!" << endl;
        } else {
            this->Kassir = Kassir;
        }
    }


    void Print(){
        cout << kassa << " ";
        cout << Kassir.GetSurname() << " ";
        cout << Kassir.GetName() << " ";
        cout << Kassir.GetPatronymic()<<" ";
        cout <<klient.GetSurname()<<" " ;
        cout <<klient.GetName()<<" ";
        cout <<klient.GetPatronymic()<< endl;
    }
};

int main(){

    Person Kassir("ivan","ivanov","ivanovich",45);
    Person Klient("petr","petrov","petrovich",35);
    Kassir.Print();
    Kassa kassa;
    kassa.SetKassir(Kassir);
    kassa.SetKlient(Klient);
    
    kassa.Print();
    kassa.SetKlient(Kassir);
    kassa.SetKassir(Kassir);

//return 0;
} 
    
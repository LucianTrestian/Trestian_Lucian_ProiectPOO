#include <iostream>

using namespace std;

class Antivirus{
    public:
    static string numeAntivirus;
    const int NumarScanare;
    int numarScanariEfectuate;
    int* nivelulamenintariGasite;
    int numarAmenintariGasite;
    //constructor default
    Antivirus():NumarScanare(1){
        this->numarScanariEfectuate = 0;
        this->numarAmenintariGasite = 0;
        this->nivelulamenintariGasite = NULL;
    }
    //destructor
    ~Antivirus(){
        if(this->nivelulamenintariGasite != NULL){
            delete[] this->nivelulamenintariGasite;
        }
    }
    //constructor cu parametri
    Antivirus(int numarScanariEfectuate, int* nivelulamenintariGasite, int numarAmenintariGasite, int NumarScanare):NumarScanare(NumarScanare){
        this->numarScanariEfectuate = numarScanariEfectuate;
        this->numarAmenintariGasite = numarAmenintariGasite;
        this->nivelulamenintariGasite = new int[numarAmenintariGasite];
        for(int i = 0; i < numarAmenintariGasite; i++){
            this->nivelulamenintariGasite[i] = nivelulamenintariGasite[i];
        }
    }
    void afisare(){
        cout << "Numele antivirusului este " << Antivirus::numeAntivirus << " si a efectuat " << this->numarScanariEfectuate << " scanari" << ", a gasit " << this->numarAmenintariGasite << " amenintari" << " nivelul amenintarilor este ";
        if (numarAmenintariGasite == 0)
            cout << "-";
        else{
            for(int i = 0; i < this->numarAmenintariGasite; i++){
                cout << this->nivelulamenintariGasite[i] << " ";
        }}
        cout << endl;
    }
    float getmedieNivelAmenintari(){
        int suma = 0;
        if (this->numarAmenintariGasite == 0)
            return 0;
        for(int i = 0; i < this->numarAmenintariGasite; i++){
            suma += this->nivelulamenintariGasite[i];
        }
        return suma/(float) this->numarAmenintariGasite;
    }   
    //modificam numele antivirusului
    void setNumeAntivirus(string numeAntivirus){
        Antivirus::numeAntivirus = numeAntivirus;
    } 
};
string Antivirus::numeAntivirus = "Avast";
class LoguriSecuritate{
    public:  
    static string numeLoguri;
    const int nivelImportanta;
    int numarLoguriInregistrate;
    char* eEroare;
    int numarErori;
    //constructor default
    LoguriSecuritate():nivelImportanta(1){
        this->numarLoguriInregistrate = 0;
        this->numarErori = 0;
        this->eEroare = NULL;
    }
    //destructor
    ~LoguriSecuritate(){
        if(this->eEroare != NULL){
            delete[] this->eEroare;
        }
    }
    //constructor cu parametri
    LoguriSecuritate(int numarLoguriInregistrate, char* eEroare, int numarErori, int nivelImportanta):nivelImportanta(nivelImportanta){
        this->numarLoguriInregistrate = numarLoguriInregistrate;
        this->numarErori = numarErori;
        this->eEroare = new char[numarErori];
        for(int i = 0; i < numarErori; i++){
            this->eEroare[i] = eEroare[i];
        }
    }
    void afisare(){
        cout << "Numele logurilor de securitate este " << LoguriSecuritate::numeLoguri << " si a inregistrat " << this->numarLoguriInregistrate << " loguri" << ", a gasit " << this->numarErori << " erori" << " erorile sunt ";
        if (numarErori == 0)
            cout << "-";
        else{
            for(int i = 0; i < this->numarErori; i++){
                cout << this->eEroare[i] << " ";
        }}
        cout << endl;
    }
    //parcurgem vectorul de erori si calculam numarul de erori de tipul respectiv
    int getNumarErori(char eEroare){
        int numarErori = 0;
        for(int i = 0; i < this->numarErori; i++){
            if(this->eEroare[i] == eEroare){
                numarErori++;
            }
        }
        return numarErori;
    }
    void modificaNumeLoguri(string numeLoguri){
        LoguriSecuritate::numeLoguri = numeLoguri;
    }
    
};   
string LoguriSecuritate::numeLoguri = "Loguri Securitate";   
class Token{
    public:
    static string Tip;  
    const int ID;
    int aplicatiiConectate;
    string* numeAplicatii;
    int nivelSecuritate;  
    //constructor default
    Token():ID(1){
        this->aplicatiiConectate = 0;
        this->nivelSecuritate = 0;
        this->numeAplicatii = NULL;
    }
    //destructor
    ~Token(){
        if(this->numeAplicatii != NULL){
            delete[] this->numeAplicatii;
        }
    }
    //constructor cu parametri
    Token(int aplicatiiConectate, string* numeAplicatii, int nivelSecuritate, int ID):ID(ID){
        this->aplicatiiConectate = aplicatiiConectate;
        this->nivelSecuritate = nivelSecuritate;
        this->numeAplicatii = new string[aplicatiiConectate];
        for(int i = 0; i < aplicatiiConectate; i++){
            this->numeAplicatii[i] = numeAplicatii[i];
        }
    }       
    void afisare(){
        cout << "Tipul tokenului este " << Token::Tip << " si are ID-ul " << this->ID << " si are " << this->aplicatiiConectate << " aplicatii conectate" << " nivelul de securitate este " << this->nivelSecuritate << " aplicatiile conectate sunt ";
        if (aplicatiiConectate == 0)
            cout << "-";
        else{
            for(int i = 0; i < this->aplicatiiConectate; i++){
                cout << this->numeAplicatii[i] << " ";
        }}
        cout << endl;
    }
     //parcurgem vectorul de aplicatii si calculam numarul de aplicatii
    int getNumarAplicatii(string numeAplicatii){
        int numarAplicatii = 0;
        for(int i = 0; i < this->aplicatiiConectate; i++){
            if(this->numeAplicatii[i] == numeAplicatii){
                numarAplicatii++;
            }
        }
        return numarAplicatii;
        }
    void modificaTip(string Tip){
        Token::Tip = Tip;
    }
};
string Token::Tip = "ERC-1155";
void main(){
Antivirus av;
av.afisare();
Antivirus av1(2, new int[2]{1,2}, 2, 2);
av1.afisare();
av1.setNumeAntivirus("Bitdefender");
av1.afisare();
cout << "Media nivelului de amenintari este " << av1.getmedieNivelAmenintari() << endl;

LoguriSecuritate ls;
ls.afisare();
LoguriSecuritate ls1(2, new char[3]{'v','v','b'}, 2, 2);
ls1.afisare();
ls1.modificaNumeLoguri("Loguri Securitate 2");
ls1.afisare();
cout << "Numarul de erori de tipul v este " << ls1.getNumarErori('v') << endl;

Token t;
t.afisare();
Token t1(2, new string[2]{"Facebook","Facebook"}, 2, 2);
t1.afisare();
t1.modificaTip("ERC-20");
t1.afisare();
t1.getNumarAplicatii("1");
}
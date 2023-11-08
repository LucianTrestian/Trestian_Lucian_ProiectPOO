#include <iostream>

using namespace std;

class Antivirus{
    private:
    static string numeAntivirus;
    const int NumarScanare;
    int numarScanariEfectuate;
    int* nivelulamenintariGasite;
    int numarAmenintariGasite;
    public:
    //constructor default
    Antivirus():NumarScanare(1){
        this->numarScanariEfectuate = 0;
        this->numarAmenintariGasite = 0;
        this->nivelulamenintariGasite = NULL;
    }
    //destructorii astfel încât să ștergeți memoria alocată în HEAP
    ~Antivirus(){
        if(this->nivelulamenintariGasite != NULL){
            delete[] this->nivelulamenintariGasite;
        }
    }
    //constructor de copiere
    Antivirus(const Antivirus& av):NumarScanare(av.NumarScanare){
        this->numarScanariEfectuate = av.numarScanariEfectuate;
        this->numarAmenintariGasite = av.numarAmenintariGasite;
        this->nivelulamenintariGasite = new int[av.numarAmenintariGasite];
        for(int i = 0; i < av.numarAmenintariGasite; i++){
            this->nivelulamenintariGasite[i] = av.nivelulamenintariGasite[i];
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
    //metode de get si set pentru atributele clasei
    static void setNumeAntivirus(string numeAntivirus){
        Antivirus::numeAntivirus = numeAntivirus;
    }
    static string getNumeAntivirus(){
        return numeAntivirus;
    }
    int getNumarScanariEfectuate(){
        return numarScanariEfectuate;
    }
    void setNumarScanariEfectuate(int numarScanariEfectuate){
        this->numarScanariEfectuate = numarScanariEfectuate;
    }
    int getNumarAmenintariGasite(){
        return numarAmenintariGasite;
    }
    void setNumarAmenintariGasite(int numarAmenintariGasite){
        this->numarAmenintariGasite = numarAmenintariGasite;
    }
    int* getNivelulamenintariGasite(){
        return nivelulamenintariGasite;
    }
    void setNivelulamenintariGasite(int* nivelulamenintariGasite){
        if(this->nivelulamenintariGasite != NULL){
            delete[] this->nivelulamenintariGasite;
        }
        this->nivelulamenintariGasite = new int[this->numarAmenintariGasite];
        for(int i = 0; i < this->numarAmenintariGasite; i++){
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
    //parcurgem vectorul de amenintari si calculam numarul de amenintari de tipul respectiv
    int getNivelulamenintariGasite(int nivelulamenintariGasite){
        int numarAmenintari = 0;
        for(int i = 0; i < this->numarAmenintariGasite; i++){
            if(this->nivelulamenintariGasite[i] == nivelulamenintariGasite){
                numarAmenintari++;
            }
        }
        return numarAmenintari;
    }
    //operatori de atribuire
    friend ostream& operator<<(ostream& out, Antivirus& av);
    //operatori de citire
    friend istream& operator>>(istream& in, Antivirus& av);
    //operatori de egalitate
    friend bool operator==(Antivirus& av1, Antivirus& av2);
    //operatori de indexare
    int& operator[](int index){
        if(index >= 0 && index < this->numarAmenintariGasite){
            return this->nivelulamenintariGasite[index];
        }
        else{
            throw new exception("Index invalid");
        }
    }
};
ostream& operator<<(ostream& out, Antivirus& av){
    out << "Numele antivirusului este " << Antivirus::numeAntivirus << " si a efectuat " << av.numarScanariEfectuate << " scanari" << ", a gasit " << av.numarAmenintariGasite << " amenintari" << " nivelul amenintarilor este ";
    if (av.numarAmenintariGasite == 0)
        out << "-";
    else{
        for(int i = 0; i < av.numarAmenintariGasite; i++){
            out << av.nivelulamenintariGasite[i] << " ";
    }}
    out << endl;
    return out;
};
istream& operator>>(istream& in, Antivirus& av){
    cout << "Introduceti numarul de scanari efectuate: ";
    in >> av.numarScanariEfectuate;
    cout << "Introduceti nivelul amenintarilor: ";
    if(av.nivelulamenintariGasite != NULL){
        delete[] av.nivelulamenintariGasite;
    }
    av.nivelulamenintariGasite = new int[av.numarAmenintariGasite];
    for(int i = 0; i < av.numarAmenintariGasite; i++){
        in >> av.nivelulamenintariGasite[i];
    }
    cout << "Introduceti numarul de amenintari gasite: ";
    in >> av.numarAmenintariGasite;
    return in;
};
bool operator==(Antivirus& av1, Antivirus& av2){
    if(av1.numarScanariEfectuate == av2.numarScanariEfectuate && av1.numarAmenintariGasite == av2.numarAmenintariGasite){
        return true;
    }
    else{
        return false;
    }
};
string Antivirus::numeAntivirus = "Avast";
class LoguriSecuritate{
    private: 
    static string numeLoguri;
    const int nivelImportanta;
    int numarLoguriInregistrate;
    char* eEroare;
    int numarErori;
    public:
    //constructor default
    LoguriSecuritate():nivelImportanta(1){
        this->numarLoguriInregistrate = 0;
        this->numarErori = 0;
        this->eEroare = NULL;
    }
    //destructorii astfel încât să ștergeți memoria alocată în HEAP
    ~LoguriSecuritate(){
        if(this->eEroare != NULL){
            delete[] this->eEroare;
        }
    }
    //constructor de copiere
    LoguriSecuritate(const LoguriSecuritate& ls):nivelImportanta(ls.nivelImportanta){
        this->numarLoguriInregistrate = ls.numarLoguriInregistrate;
        this->numarErori = ls.numarErori;
        this->eEroare = new char[ls.numarErori];
        for(int i = 0; i < ls.numarErori; i++){
            this->eEroare[i] = ls.eEroare[i];
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
    //metode de get si set pentru atributele clasei
    static void setNumeLoguri(string numeLoguri){
        LoguriSecuritate::numeLoguri = numeLoguri;
    }
    static string getNumeLoguri(){
        return numeLoguri;
    }
    int getNumarLoguriInregistrate(){
        return numarLoguriInregistrate;
    }
    void setNumarLoguriInregistrate(int numarLoguriInregistrate){
        this->numarLoguriInregistrate = numarLoguriInregistrate;
    }
    int getNumarErori(){
        return numarErori;
    }
    void setNumarErori(int numarErori){
        this->numarErori = numarErori;
    }
    char* getEroare(){
        return eEroare;
    }
    void setEroare(char* eEroare){
        if(this->eEroare != NULL){
            delete[] this->eEroare;
        }
        this->eEroare = new char[this->numarErori];
        for(int i = 0; i < this->numarErori; i++){
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
    //operatori de atribuire
    friend ostream& operator<<(ostream& out, LoguriSecuritate& ls);
    //operatori de citire
    friend istream& operator>>(istream& in, LoguriSecuritate& ls);
    //operatori de egalitate
    friend bool operator==(LoguriSecuritate& ls1, LoguriSecuritate& ls2);
    //operatori de indexare
    char& operator[](int index){
        if(index >= 0 && index < this->numarErori){
            return this->eEroare[index];
        }
        else{
            throw new exception("Index invalid");
        }
    }
    //operator de citire
    
};  
ostream& operator<<(ostream& out, LoguriSecuritate& ls){
    out << "Numele logurilor de securitate este " << LoguriSecuritate::numeLoguri << " si a inregistrat " << ls.numarLoguriInregistrate << " loguri" << ", a gasit " << ls.numarErori << " erori" << " erorile sunt ";
    if (ls.numarErori == 0)
        out << "-";
    else{
        for(int i = 0; i < ls.numarErori; i++){
            out << ls.eEroare[i] << " ";
    }}
    out << endl;
    return out;
};
istream& operator>>(istream& in, LoguriSecuritate& ls){
    cout << "Introduceti numarul de loguri inregistrate: ";
    in >> ls.numarLoguriInregistrate;
    cout << "Introduceti erorile: ";
    if(ls.eEroare != NULL){
        delete[] ls.eEroare;
    }
    ls.eEroare = new char[ls.numarErori];
    for(int i = 0; i < ls.numarErori; i++){
        in >> ls.eEroare[i];
    }
    cout << "Introduceti nivelul de importanta: ";
    in >> ls.nivelImportanta;
    return in;
};
bool operator==(LoguriSecuritate& ls1, LoguriSecuritate& ls2){
    if(ls1.numarLoguriInregistrate == ls2.numarLoguriInregistrate && ls1.nivelImportanta == ls2.nivelImportanta){
        return true;
    }
    else{
        return false;
    }
};
string LoguriSecuritate::numeLoguri = "Loguri Securitate";   
class Token{
    private:
    static string Tip;  
    const int ID;
    int aplicatiiConectate;
    string* numeAplicatii;
    int nivelSecuritate;  
    //constructor default
    public:
    Token():ID(1){
        this->aplicatiiConectate = 0;
        this->nivelSecuritate = 0;
        this->numeAplicatii = NULL;
    }
    //destructorii astfel încât să ștergeți memoria alocată în HEAP
    ~Token(){
        if(this->numeAplicatii != NULL){
            delete[] this->numeAplicatii;
        }
    }
    //constructor de copiere
    Token(const Token& t):ID(t.ID){
        this->aplicatiiConectate = t.aplicatiiConectate;
        this->nivelSecuritate = t.nivelSecuritate;
        this->numeAplicatii = new string[t.aplicatiiConectate];
        for(int i = 0; i < t.aplicatiiConectate; i++){
            this->numeAplicatii[i] = t.numeAplicatii[i];
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
    //metode de get si set pentru atributele clasei
    static void setTip(string Tip){
        Token::Tip = Tip;
    }
    static string getTip(){
        return Tip;
    }
    int getAplicatiiConectate(){
        return aplicatiiConectate;
    }
    void setAplicatiiConectate(int aplicatiiConectate){
        this->aplicatiiConectate = aplicatiiConectate;
    }
    int getNivelSecuritate(){
        return nivelSecuritate;
    }
    void setNivelSecuritate(int nivelSecuritate){
        this->nivelSecuritate = nivelSecuritate;
    }
    string* getNumeAplicatii(){
        return numeAplicatii;
    }
    void setNumeAplicatii(string* numeAplicatii){
        if(this->numeAplicatii != NULL){
            delete[] this->numeAplicatii;
        }
        this->numeAplicatii = new string[this->aplicatiiConectate];
        for(int i = 0; i < this->aplicatiiConectate; i++){
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
    //operatori de atribuire
    friend ostream& operator<<(ostream& out, Token& t);
    //operatori de citire
    friend istream& operator>>(istream& in, Token& t){
    cout << "Introduceti numarul de aplicatii conectate: ";
    in >> t.aplicatiiConectate;
    cout << "Introduceti numele aplicatiilor conectate: ";
    if(t.numeAplicatii != NULL){
        delete[] t.numeAplicatii;
    }
    t.numeAplicatii = new string[t.aplicatiiConectate];
    for(int i = 0; i < t.aplicatiiConectate; i++){
        in >> t.numeAplicatii[i];
    }
    cout << "Introduceti nivelul de securitate: ";
    in >> t.nivelSecuritate;
    return in;
};
    //operatori de egalitate
    friend bool operator==(Token& t1, Token& t2);
    //operatori de indexare
    string& operator[](int index){
        if(index >= 0 && index < this->aplicatiiConectate){
            return this->numeAplicatii[index];
        }
        else{
            throw new exception("Index invalid");
        }
    }
};
ostream& operator<<(ostream& out, Token& t){
    out << "Tipul tokenului este " << Token::Tip << " si are ID-ul " << t.ID << " si are " << t.aplicatiiConectate << " aplicatii conectate" << " nivelul de securitate este " << t.nivelSecuritate << " aplicatiile conectate sunt ";
    if (t.aplicatiiConectate == 0)
        out << "-";
    else{
        for(int i = 0; i < t.aplicatiiConectate; i++){
            out << t.numeAplicatii[i] << " ";
    }}
    out << endl;
    return out;
};
bool operator==(Token& t1, Token& t2){
    if(t1.aplicatiiConectate == t2.aplicatiiConectate && t1.nivelSecuritate == t2.nivelSecuritate){
        return true;
    }
    else{
        return false;
    }
};
string Token::Tip = "ERC-1155";
void main(){\
    //testare clasei Antivirus
    Antivirus av;
    av.afisare();
    Antivirus av1(2, new int[2]{1,2}, 2, 2);
    av1.afisare();
    av1.setNumeAntivirus("Bitdefender");
    av1.afisare();
    cout << "Media nivelului de amenintari este " << av1.getmedieNivelAmenintari() << endl;
    av1.setNumeAntivirus("Avast");
    av1.getNivelulamenintariGasite();
    av1.setNivelulamenintariGasite(new int[2]{3,4});
    av1.afisare();
    
    //testare clasei LoguriSecuritate
    LoguriSecuritate ls;
    ls.afisare();
    LoguriSecuritate ls1(2, new char[3]{'v','v','b'}, 2, 2);
    ls1.afisare();
    ls1.modificaNumeLoguri("Loguri Securitate 2");
    ls1.afisare();
    cout << "Numarul de erori de tipul v este " << ls1.getNumarErori('v') << endl;
    ls1.modificaNumeLoguri("Loguri Securitate");
    ls1.getEroare();
    ls1.setEroare(new char[3]{'v','v','b'});
    ls1.afisare();

    //testare clasei Token
    Token t;
    t.afisare();
    Token t1(2, new string[2]{"Facebook","Facebook"}, 2, 2);
    t1.afisare();
    t1.modificaTip("ERC-20");
    t1.afisare();
    t1.getNumarAplicatii("1");
    t1.modificaTip("ERC-1155");
    t1.getNumeAplicatii();
    t1.setNumeAplicatii(new string[2]{"Facebook","Facebook"});
    t1.afisare();

}
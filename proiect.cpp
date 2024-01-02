#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
// Clasa abstracta pentru Task
class AbstractTask {
public:
    virtual ~AbstractTask() {}  // Destructor virtual pentru a permite dealocarea corecta a resurselor
    virtual void afisare() const = 0;  // Metoda virtuala pura pentru afisare
};

// Clasa abstracta pentru Server
class AbstractServer {
public:
    virtual ~AbstractServer() {}
    virtual void afisare() const = 0;
};

class Task {
private:
    string numeTask;
    int prioritate;
    bool finalizat;
    int idTask;
    string* descriereTask;
public:
    static int numarTotalTaskuri;
    // constructor default
    Task() : idTask(0) {
        this->numeTask = "Nume implicit";
        this->prioritate = 0;
        this->finalizat = false;
        this->descriereTask = nullptr;
    }

    // constructor de copiere
    Task(const Task& other) :idTask(other.idTask) {
        this->numeTask = other.numeTask;
        this->prioritate = other.prioritate;
        this->finalizat = other.finalizat;
        this->descriereTask = new string(*(other.descriereTask));

    }

    // constructor cu parametri 
    Task(string numeTask, int prioritate, bool finalizat, int idTask, string* descriereTask) : numeTask(numeTask), prioritate(prioritate), finalizat(finalizat), idTask(idTask), descriereTask(descriereTask) {
        numarTotalTaskuri++;
        // afisare
        cout<< "Nume task: " << numeTask << endl;
        cout<< "Prioritate: " << prioritate << endl;
        cout<< "Finalizat: " << finalizat << endl;
        cout<< "Id task: " << idTask << endl;
        cout<< "Descriere task: " << *descriereTask << endl;
    }
    // constructor cu parametri fara descriere
    Task(string numeTask, int prioritate, bool finalizat) : numeTask(numeTask), prioritate(prioritate), finalizat(finalizat), idTask(0) {
        numarTotalTaskuri++;
        descriereTask = new string("Descriere implicita");
    }
    void saveToFile(const string& fileName) const {
        ofstream file(fileName);
        if (file.is_open()) {
            file << numeTask << endl;
            file << prioritate << endl;
            file << finalizat << endl;
            file << idTask << endl;
            file << *descriereTask << endl;
        } else {
            cerr << "Eroare la deschiderea fisierului pentru scriere text." << endl;
        }
    }

    void loadFromFile(const string& fileName) {
        ifstream file(fileName);
        if (file.is_open()) {
            file >> numeTask;
            file >> prioritate;
            file >> finalizat;
            file >> idTask;
            delete descriereTask;  // Eliberam memoria alocata anterior
            descriereTask = new string();
            getline(file, *descriereTask);  // Citim linia newline ramasa in buffer
            getline(file, *descriereTask);
        } else {
            cerr << "Eroare la deschiderea fisierului pentru citire text." << endl;
        }
    }

    // Salvare/Incarcare din fisier binar
    void saveToBinaryFile(const string& fileName) const {
        ofstream file(fileName, ios::binary);
        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(&numeTask), sizeof(numeTask));
            file.write(reinterpret_cast<const char*>(&prioritate), sizeof(prioritate));
            file.write(reinterpret_cast<const char*>(&finalizat), sizeof(finalizat));
            file.write(reinterpret_cast<const char*>(&idTask), sizeof(idTask));
            int descriereSize = descriereTask->size();
            file.write(reinterpret_cast<const char*>(&descriereSize), sizeof(descriereSize));
            file.write(descriereTask->c_str(), descriereSize);
        } else {
            cerr << "Eroare la deschiderea fisierului pentru scriere binara." << endl;
        }
    }

    void loadFromBinaryFile(const string& fileName) {
        ifstream file(fileName, ios::binary);
        if (file.is_open()) {
            delete descriereTask;  // Eliberam memoria alocata anterior

            file.read(reinterpret_cast<char*>(&numeTask), sizeof(numeTask));
            file.read(reinterpret_cast<char*>(&prioritate), sizeof(prioritate));
            file.read(reinterpret_cast<char*>(&finalizat), sizeof(finalizat));
            file.read(reinterpret_cast<char*>(&idTask), sizeof(idTask));

            int descriereSize;
            file.read(reinterpret_cast<char*>(&descriereSize), sizeof(descriereSize));
            descriereTask = new string(descriereSize, ' ');
            file.read(&(*descriereTask)[0], descriereSize);
        } else {
            cerr << "Eroare la deschiderea fisierului pentru citire binara." << endl;
        }
    }
    // destructor
    ~Task() {
        delete descriereTask;
        numarTotalTaskuri--;
    }

    string getNumeTask() const {
        return numeTask;
    }

    void setNumeTask(const string& nume) {
        this->numeTask = nume;
    }

    int getPrioritate() const {
        return prioritate;
    }

    void setPrioritate(int prio) {
        prioritate = prio;
    }

    bool getFinalizat() const {
        return finalizat;
    }

    void setFinalizat(bool fin) {
        finalizat = fin;
    }

    int getIdTask() const {
        return idTask;
    }

    string getDescriereTask() const {
        return *descriereTask;
    }

    void setDescriereTask(const string& descriere) {
        *descriereTask = descriere;
    }

    static void afiseazaNumarTotalTaskuri() {
        cout << "Numar total de taskuri: " << numarTotalTaskuri << endl;
    }
    // operatorul =
    Task& operator=(const Task& other) {
        if (this != &other) {
            delete descriereTask;
            numeTask = other.numeTask;
            prioritate = other.prioritate;
            finalizat = other.finalizat;
            idTask = other.idTask;
            descriereTask = new string(*(other.descriereTask));
        }
        return *this;
    }
    // operatori relationali
    bool operator==(const Task& other) const {
        return (numeTask == other.numeTask && prioritate == other.prioritate && finalizat == other.finalizat && idTask == other.idTask && *descriereTask == *(other.descriereTask));
    }
    // operatori logici
    bool operator!=(const Task& other) const {
        return !(*this == other);
    }
    // operatori aritmetici
    Task operator+(const Task& other) const {
        Task result(*this);
        result.prioritate += other.prioritate;
        return result;
    }
    // operatori de incrementare
    // task& este referinta la obiectul curent
    Task& operator++() {
        prioritate++;
        return *this;
    }
    // incrementare postfixata
    Task operator++(int) {
        Task temp(*this);
        prioritate++;
        return temp;
    }
    // operatorul ostream
    friend ostream& operator<<(ostream& out, const Task& task) {
        out << "Nume task: " << task.numeTask << ", Prioritate: " << task.prioritate << ", Finalizat: " << task.finalizat << ", Descriere task: " << *(task.descriereTask);
        return out;
    }
    // operatorul istream
    friend istream& operator>>(istream& in, Task& task) {
        cout << "Nume task: ";
        in >> task.numeTask;
        cout << "Prioritate: ";
        in >> task.prioritate;
        cout << "Finalizat: ";
        in >> task.finalizat;
        cout << "Descriere task: ";
        in >> *(task.descriereTask);
        return in;
    }

    // Metoda pentru afisare specifica clasei Task
    void afisare() const override {
        cout << "Task: " << numeTask << ", ID: " << idTask << ", Descriere: " << *descriereTask << endl;
    }
};

int Task::numarTotalTaskuri = 0;

class Logger {
private:
    string nivelLogare;
    bool activat;
    string tipLogger;
    int numarInregistrari;
    int* inregistrari;

public:
    static string fisierLog;

    // constructor default
    Logger() {
        this->nivelLogare = "Nivel implicit";
        this->activat = false;
        this->tipLogger = "Tip implicit";
        this->numarInregistrari = 0;
        this->inregistrari = nullptr;
    }

    //constructor de copiere
    Logger(const Logger& other) {
        this->nivelLogare = other.nivelLogare;
        this->activat = other.activat;
        this->tipLogger = other.tipLogger;
        this->numarInregistrari = other.numarInregistrari;
        this->inregistrari = new int(*(other.inregistrari));
        for (int i = 0; i < numarInregistrari; i++) {
            this->inregistrari[i] = other.inregistrari[i];
        }
    }

    // constructor cu parametri
    // se foloseste lista de initializare a membrilor
    // acest constructor este apelat in cazul in care se instantiaza un obiect Logger cu 3 parametri
    Logger(string nivelLogare, bool activat, string tipLogger,int numarInregistrari,int* inregistrari) : nivelLogare(nivelLogare), activat(activat), tipLogger(tipLogger), inregistrari(inregistrari) {
        cout << "Nivel logare: " << nivelLogare << endl;
        cout << "Activat: " << activat << endl;
        cout << "Tip logger: " << tipLogger << endl;
        cout << "Numar inregistrari: " << numarInregistrari << endl;
        cout << "Inregistrari: ";
        for (int i = 0; i < numarInregistrari; i++) {
            cout << inregistrari[i] << " ";
        }
        cout << endl;
    }
    // constructor cu parametri fara numar inregistrari
    Logger(string nivelLogare, bool activat, string tipLogger) : nivelLogare(nivelLogare), activat(activat), tipLogger(tipLogger) {
        numarInregistrari = 0;
        inregistrari = new int[0];
        //afisare
        cout << "Nivel logare: " << nivelLogare << endl;
        cout << "Activat: " << activat << endl;
        cout << "Tip logger: " << tipLogger << endl;
        cout << "Numar inregistrari: " << numarInregistrari << endl;
        cout << "Inregistrari: ";
        for (int i = 0; i < numarInregistrari; i++) {
            cout << inregistrari[i] << " ";
        }
    }
    // Salvare/Incarcare din fisier text
    void saveToFile(const string& fileName) const {
        ofstream file(fileName);
        if (file.is_open()) {
            file << nivelLogare << endl;
            file << activat << endl;
            file << tipLogger << endl;
            file << numarInregistrari << endl;
        } else {
            cerr << "Eroare la deschiderea fisierului pentru scriere text." << endl;
        }
    }

    void loadFromFile(const string& fileName) {
        ifstream file(fileName);
        if (file.is_open()) {
            file >> nivelLogare;
            file >> activat;
            file >> tipLogger;
            file >> numarInregistrari;
        } else {
            cerr << "Eroare la deschiderea fisierului pentru citire text." << endl;
        }
    }

    // Salvare/Incarcare din fisier binar
    void saveToBinaryFile(const string& fileName) const {
        ofstream file(fileName, ios::binary);
        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(&nivelLogare), sizeof(nivelLogare));
            file.write(reinterpret_cast<const char*>(&activat), sizeof(activat));
            file.write(reinterpret_cast<const char*>(&tipLogger), sizeof(tipLogger));
            file.write(reinterpret_cast<const char*>(&numarInregistrari), sizeof(numarInregistrari));
        } else {
            cerr << "Eroare la deschiderea fisierului pentru scriere binara." << endl;
        }
    }

    void loadFromBinaryFile(const string& fileName) {
        ifstream file(fileName, ios::binary);
        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(&nivelLogare), sizeof(nivelLogare));
            file.read(reinterpret_cast<char*>(&activat), sizeof(activat));
            file.read(reinterpret_cast<char*>(&tipLogger), sizeof(tipLogger));
            file.read(reinterpret_cast<char*>(&numarInregistrari), sizeof(numarInregistrari));
        } else {
            cerr << "Eroare la deschiderea fisierului pentru citire binara." << endl;
        }
    }

    // destructor
    ~Logger() {
        delete inregistrari;
    }

    string getNivelLogare() const {
        return nivelLogare;
    }

    void setNivelLogare(const string& nivel) {
        nivelLogare = nivel;
    }

    bool getActivat() const {
        return activat;
    }

    void setActivat(bool act) {
        activat = act;
    }

    string getTipLogger() const {
        return tipLogger;
    }

    void setTipLogger(const string& tip) {
        tipLogger = tip;
    }

    int getNumarInregistrari() const {
        return numarInregistrari;
    }

    void setNumarInregistrari(int nr) {
        numarInregistrari = nr;
    }

    int * getInregistrari() const {
        return inregistrari;
    }

    void setInregistrari(int* inreg) {
        if(inregistrari != nullptr) {
            delete inregistrari;
        }
        inregistrari = new int[numarInregistrari];
        for (int i = 0; i < numarInregistrari; i++) {
            inregistrari[i] = inreg[i];
        }
    }

    static void actualizeazaFisierLog() {
        fisierLog = "new_log.txt";
    }
    // operatorul =
    Logger& operator=(const Logger& other) {
        if (this != &other) {
            delete inregistrari;
            nivelLogare = other.nivelLogare;
            activat = other.activat;
            tipLogger = other.tipLogger;
            numarInregistrari = other.numarInregistrari;
            inregistrari = new int(*(other.inregistrari));
            for (int i = 0; i < numarInregistrari; i++) {
                inregistrari[i] = other.inregistrari[i];
            }
        }
        return *this;
    }
    // operatori relationali
    bool operator==(const Logger& other) const {
        return (nivelLogare == other.nivelLogare && activat == other.activat && tipLogger == other.tipLogger && numarInregistrari == other.numarInregistrari && *inregistrari == *(other.inregistrari));
        }
    // operatori logici
    bool operator!=(const Logger& other) const {
        return !(*this == other);
    }
    // operatori aritmetici
    Logger operator+(const Logger& other) const {
        Logger result(*this);
        result.nivelLogare += other.nivelLogare;
        return result;
    }
    // operatori de incrementare
    // logger& este referinta la obiectul curent
    Logger& operator++() {
        this->numarInregistrari++;
        return *this;
    }
    // incrementare postfixata
    Logger operator++(int) {
        Logger temp(*this);
        this->numarInregistrari++;
        return temp;
    }
    // operatorul ostream
    friend ostream& operator<<(ostream& out, const Logger& logger) {
        out << "Nivel logare: " << logger.nivelLogare << ", Activat: " << logger.activat << ", Tip logger: " << logger.tipLogger << ", Numar inregistrari: " << logger.numarInregistrari;
        return out;
    }
    // operatorul istream
    friend istream& operator>>(istream& in, Logger& logger) {
        cout << "Nivel logare: ";
        in >> logger.nivelLogare;
        cout << "Activat: ";
        in >> logger.activat;
        cout << "Tip logger: ";
        in >> logger.tipLogger;
        cout << "Numar inregistrari: ";
        in >> logger.numarInregistrari;
        return in;
    }
};

string Logger::fisierLog = "log.txt";

class Server {
private:
    string numeServer;
    int capacitate;
    bool activ;
    int idServer;
    bool* redundanta;

public:
    static bool statusGlobal;
    // constructor default
    Server() : idServer(0) {
        numeServer = "Nume implicit";
        capacitate = 0;
        activ = false;
        redundanta = nullptr;
    }
    // constructor de copiere
    Server(const Server& other) : idServer(other.idServer) {
        numeServer = other.numeServer;
        capacitate = other.capacitate;
        activ = other.activ;
        redundanta = new bool(*(other.redundanta));
    }
    // constructor cu parametri
    Server(string numeServer, int capacitate, bool activ, int idServer, bool* redundanta) : numeServer(numeServer), capacitate(capacitate), activ(activ), idServer(idServer), redundanta(redundanta) {
        cout << "Nume server: " << numeServer << endl;
        cout << "Capacitate: " << capacitate << endl;
        cout << "Activ: " << activ << endl;
        cout << "Id server: " << idServer << endl;
        cout << "Redundanta: " << *redundanta << endl;
    }
    // constructor cu parametri fara redundanta
     Server(string numeServer, int capacitate, bool activ) : numeServer(numeServer), capacitate(capacitate), activ(activ), idServer(0) {
        statusGlobal = true;
        redundanta = new bool(true);
    }
    // Salvare/Incarcare din fisier text
    void saveToFile(const string& fileName) const {
        ofstream file(fileName);
        if (file.is_open()) {
            file << numeServer << endl;
            file << capacitate << endl;
            file << activ << endl;
            file << idServer << endl;
            file << *redundanta << endl;
        } else {
            cerr << "Eroare la deschiderea fisierului pentru scriere text." << endl;
        }
    }

    void loadFromFile(const string& fileName) {
        ifstream file(fileName);
        if (file.is_open()) {
            file >> numeServer;
            file >> capacitate;
            file >> activ;
            file >> idServer;
            file >> *redundanta;
        } else {
            cerr << "Eroare la deschiderea fisierului pentru citire text." << endl;
        }
    }

    // Salvare/Incarcare din fisier binar
     void saveToBinaryFile(const string& fileName) const {
        ofstream file(fileName, ios::binary);
        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(&numeServer), sizeof(numeServer));
            file.write(reinterpret_cast<const char*>(&capacitate), sizeof(capacitate));
            file.write(reinterpret_cast<const char*>(&activ), sizeof(activ));
            file.write(reinterpret_cast<const char*>(&idServer), sizeof(idServer));
        } else {
            cerr << "Eroare la deschiderea fisierului pentru scriere binara." << endl;
        }
    }

    void loadFromBinaryFile(const string& fileName) {
        ifstream file(fileName, ios::binary);
        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(&numeServer), sizeof(numeServer));
            file.read(reinterpret_cast<char*>(&capacitate), sizeof(capacitate));
            file.read(reinterpret_cast<char*>(&activ), sizeof(activ));
            file.read(reinterpret_cast<char*>(&idServer), sizeof(idServer));
        } else {
            cerr << "Eroare la deschiderea fisierului pentru citire binara." << endl;
        }
    }   

    // destructor
    ~Server() {
        delete redundanta;
    }

    string getNumeServer() const {
        return numeServer;
    }

    void setNumeServer(const string& nume) {
        numeServer = nume;
    }

    int getCapacitate() const {
        return capacitate;
    }

    void setCapacitate(int cap) {
        capacitate = cap;
    }

    bool getActiv() const {
        return activ;
    }

    void setActiv(bool act) {
        activ = act;
    }

    int getIdServer() const {
        return idServer;
    }

    bool getRedundanta() const {
        return *redundanta;
    }

    void setRedundanta(bool red) {
        *redundanta = red;
    }

    static void schimbaStatusGlobal() {
        statusGlobal = !statusGlobal;
    }
    // operatorul =
    Server& operator=(const Server& other) {
        if (this != &other) {
            delete redundanta;
            numeServer = other.numeServer;
            capacitate = other.capacitate;
            activ = other.activ;
            idServer = other.idServer;
            redundanta = new bool(*(other.redundanta));
        }
        return *this;
    }
    // operatori relationali
    bool operator==(const Server& other) const {
        return (numeServer == other.numeServer && capacitate == other.capacitate && activ == other.activ && idServer == other.idServer && *redundanta == *(other.redundanta));
    }
    // operatori logici
    bool operator!=(const Server& other) const {
        return !(*this == other);
    }
    // operatori aritmetici
    Server operator+(const Server& other) const {
        Server result(*this);
        result.capacitate += other.capacitate;
        return result;
    }
    // operatori de incrementare
    // server& este referinta la obiectul curent
    Server& operator++() {
        capacitate++;
        return *this;
    }
    // incrementare postfixata
    Server operator++(int) {
        Server temp(*this);
        capacitate++;
        return temp;
    }
    // operatorul ostream
    friend ostream& operator<<(ostream& out, const Server& server) {
        out << "Nume server: " << server.numeServer << ", Capacitate: " << server.capacitate << ", Activ: " << server.activ << ", Redundanta: " << *(server.redundanta);
        return out;
    }
    // operatorul istream
    friend istream& operator>>(istream& in, Server& server) {
        cout << "Nume server: ";
        in >> server.numeServer;
        cout << "Capacitate: ";
        in >> server.capacitate;
        cout << "Activ: ";
        in >> server.activ;
        cout << "Redundanta: ";
        in >> *(server.redundanta);
        return in;
    }
    // Metoda pentru afisare specifica clasei Server
    void afisare() const override {
        cout << "Server: " << numeServer << ", Capacitate: " << capacitate << ", Activ: " << (activ ? "Da" : "Nu") << ", Redundanta: " << (redundanta ? "Da" : "Nu") << endl;
    }
};

bool Server::statusGlobal = true;

// Functii globale prietene cu clasele
void procesareTask(const Task& task) {
    cout << "Procesare Task: " << task.getNumeTask() << ", " << task.getPrioritate() << ", " << task.getFinalizat() << endl;
}

void procesareLogger(const Logger& logger) {
    cout << "Procesare Logger: " << logger.getNivelLogare() << ", " << logger.getActivat() << ", " << logger.getTipLogger() << ", " << logger.getNumarInregistrari() << endl;
}
void procesareServer(const Server& server) {
    cout << "Procesare Server: " << server.getNumeServer() << ", " << server.getCapacitate() << ", " << server.getActiv() << ", " << server.getRedundanta() << endl;
}
class Proiect {
private:
    string name;
    string descriere;
    Task task;
    vector<Logger> loggers;

public:
    // constructor default
    Proiect() {
        this->name = "Nume implicit";
        this->descriere = "Descriere implicita";
        this->task = Task();
        this->loggers = vector<Logger>();
    }

    // constructor cu parametri
    Proiect(string name, string descriere, Task task, vector<Logger> loggers) : name(name), descriere(descriere), task(task), loggers(loggers) {
        cout << "Nume proiect: " << name << endl;
        cout << "Descriere proiect: " << descriere << endl;
        cout << "Task: " << task << endl;
        cout << "Loggeri: " << endl;
        for (const auto& logger : loggers) {
            cout << logger << endl;
        }
    }

    // constructor de copiere
    Proiect(const Proiect& other) {
        this->name = other.name;
        this->descriere = other.descriere;
        this->task = other.task;
        this->loggers = other.loggers;
    }
    // destructor
    ~Proiect() {
        // nimic de sters
    }

    // getteri
    string getName() const {
        return name;
    }

    string getdescriere() const {
        return descriere;
    }

    Task getTask() const {
        return task;
    }

    vector<Logger> getLoggers() const {
        return loggers;
    }

    // setteri
    void setName(const string& name) {
        this->name = name;
    }

    void setdescriere(const string& descriere) {
        this->descriere = descriere;
    }

    void setTask(const Task& task) {
        this->task = task;
    }

    void setLoggers(const vector<Logger>& loggers) {
        this->loggers = loggers;
    }

    // operatorul =
    Proiect& operator=(const Proiect& other) {
        if (this != &other) {
            this->name = other.name;
            this->descriere = other.descriere;
            this->task = other.task;
            this->loggers = other.loggers;
        }
        return *this;
    }

    // operatori relationali
    bool operator==(const Proiect& other) const {
        return (name == other.name && descriere == other.descriere && task == other.task && loggers == other.loggers);
    }

    bool operator!=(const Proiect& other) const {
        return !(*this == other);
    }

    // operatori aritmetici
    Proiect operator+(const Proiect& other) const {
        Proiect result(*this);
        result.name += other.name;
        result.descriere += other.descriere;
        result.task = result.task + other.task;
        for (const auto& logger : other.loggers) {
            result.loggers.push_back(logger);
        }
        return result;
    }

    // operatori de incrementare
    // Proiect& este referinta la obiectul curent
    Proiect& operator++() {
        this->task++;
        return *this;
    }

    // incrementare postfixata
    Proiect operator++(int) {
        Proiect temp(*this);
        this->task++;
        return temp;
    }
};
// Noua clasa care mosteneste clasa Server
class ServerSpecial : public Server {
private:
    string detaliiSpeciale;
    bool SecuritateAvansata;

public:
    ServerSpecial() : detaliiSpeciale("Detalii speciale implicite") {}


    // Getteri si setteri pentru atributele clasei ServerSpecial
    void setDetaliiSpeciale(const string& detaliiSpeciale) {
        this->detaliiSpeciale = detaliiSpeciale;
    }
    string getDetaliiSpeciale() const {
        return detaliiSpeciale;
    }
    void setSecuritateAvansata(bool SecuritateAvansata) {
        this->SecuritateAvansata = SecuritateAvansata;
    }
    bool getSecuritateAvansata() const {
        return SecuritateAvansata;
    }
    // Metode specifice clasei ServerSpecial
    void afiseazaDetaliiSpeciale() {
        cout << "Detalii speciale: " << detaliiSpeciale << endl;
    }


};
// Noua clasa care mosteneste clasa Task
class TaskSpecial : public Task {
private:
    string detaliiSpeciale;

public:
    TaskSpecial() : detaliiSpeciale("Detalii speciale implicite") {}

    // Getteri si setteri pentru atributele clasei TaskSpecial
    void setDetaliiSpeciale(const string& detaliiSpeciale) {
        this->detaliiSpeciale = detaliiSpeciale;
    }
    string getDetaliiSpeciale() const {
        return detaliiSpeciale;
    }

    // Metode specifice clasei TaskSpecial
    void afiseazaDetaliiSpeciale() {
        cout << "Detalii speciale: " << detaliiSpeciale << endl;
    }
};

int main() {
    /*
    // Testare metode si functii
    Task task1;
    Task task2("Implementare functie", 1, false);
    Task task3("Testare unitara", 2, true, 123, new string("Scrie codul functiei principale."));

    task1.setNumeTask("Analiza cerinte");
    task1.setPrioritate(3);
    task1.setFinalizat(true);

    cout << "Task 1 - " << task1.getNumeTask() << ", " << task1.getPrioritate() << ", " << task1.getFinalizat() << endl;
    cout << "Task 2 - " << task2.getNumeTask() << ", " << task2.getPrioritate() << ", " << task2.getFinalizat() << endl;
    cout << "Task 3 - " << task3.getNumeTask() << ", " << task3.getPrioritate() << ", " << task3.getFinalizat() << endl;

    Task::afiseazaNumarTotalTaskuri();
    // Vector cu obiecte de tip Task
    vector<Task> vectorTaskuri(3);
    for (int i = 0; i < 3; ++i) {
        cout << "Introduceti detalii pentru Task " << i + 1 << ":" << endl;
        cin >> vectorTaskuri[i];
    }

    // Afișare obiecte din vectorul de Task-uri
    cout << "Obiecte din vectorul de Task-uri:" << endl;
    for (const auto& task : vectorTaskuri) {
        cout << task << endl;
    }

    // Matrice de obiecte de tip Task
    Task matriceTaskuri[2][2];
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << "Introduceti detalii pentru Task [" << i << "][" << j << "]:" << endl;
            cin >> matriceTaskuri[i][j];
        }
    }

    // Afișare obiecte din matricea de Task-uri
    cout << "Obiecte din matricea de Task-uri:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << matriceTaskuri[i][j] << endl;
        }
    }

    Logger logger1;
    Logger logger2("Info", true, "Logger1",5, new int[5]{ 1, 2, 3, 4, 5 });
    Logger logger3("Error", false, "Logger2");

    logger1.setNivelLogare("Debug");
    logger1.setActivat(true);
    logger1.setNumarInregistrari(5);

    cout << "Logger 1 - " << logger1.getNivelLogare() << ", " << logger1.getActivat() << ", " << logger1.getTipLogger() << ", " << logger1.getNumarInregistrari() << endl;
    cout << "Logger 2 - " << logger2.getNivelLogare() << ", " << logger2.getActivat() << ", " << logger2.getTipLogger() << ", " << logger2.getNumarInregistrari() << endl;
    cout << "Logger 3 - " << logger3.getNivelLogare() << ", " << logger3.getActivat() << ", " << logger3.getTipLogger() << ", " << logger3.getNumarInregistrari() << endl;

    Logger::actualizeazaFisierLog();

    // Vector cu obiecte de tip Logger
    vector<Logger> vectorLoggere(3);
    for (int i = 0; i < 3; ++i) {
        cout << "Introduceti detalii pentru Logger " << i + 1 << ":" << endl;
        cin >> vectorLoggere[i];
    }
    
    // Afișare obiecte din vectorul de Loggere
    cout << "Obiecte din vectorul de Loggere:" << endl;
    for (const auto& logger : vectorLoggere) {
        cout << logger << endl;
    }

    // Matrice de obiecte de tip Logger
    Logger matriceLoggere[2][2];
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << "Introduceti detalii pentru Logger [" << i << "][" << j << "]:" << endl;
            cin >> matriceLoggere[i][j];
        }
    }

    // Afișare obiecte din matricea de Loggere
    cout << "Obiecte din matricea de Loggere:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << matriceLoggere[i][j] << endl;
        }
    }
    Server server1;
    Server server2("WebServer", 2, true);
    Server server3("DatabaseServer", 5, false, 4, new bool(false));

    server1.setNumeServer("FileServer");
    server1.setCapacitate(2);
    server1.setActiv(true);
    server1.setRedundanta(true);

    cout << "Server 1 - " << server1.getNumeServer() << ", " << server1.getCapacitate() << ", " << server1.getActiv() << ", " << server1.getRedundanta() << endl;
    cout << "Server 2 - " << server2.getNumeServer() << ", " << server2.getCapacitate() << ", " << server2.getActiv() << ", " << server2.getRedundanta() << endl;
    cout << "Server 3 - " << server3.getNumeServer() << ", " << server3.getCapacitate() << ", " << server3.getActiv() << ", " << server3.getRedundanta() << endl;

    Server::schimbaStatusGlobal();

    // Utilizare functii globale prietene cu clasele
    procesareTask(task1);
    procesareLogger(logger2);

    // Vector cu obiecte de tip Server
    vector<Server> vectorServere(3);
    for (int i = 0; i < 3; ++i) {
        cout << "Introduceti detalii pentru Server " << i + 1 << ":" << endl;
        cin >> vectorServere[i];
    }

    // Afișare obiecte din vectorul de Servere
    cout << "Obiecte din vectorul de Servere:" << endl;
    for (const auto& server : vectorServere) {
        cout << server << endl;
    }

    // Matrice de obiecte de tip Server
    Server matriceServere[2][2];
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << "Introduceti detalii pentru Server [" << i << "][" << j << "]:" << endl;
            cin >> matriceServere[i][j];
        }
    }
    // Afișare obiecte din matricea de Servere
    cout << "Obiecte din matricea de Servere:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << matriceServere[i][j] << endl;
        }
    }
    */
    // 
    // Vectori
    /*
    vector<Task> taskVector;
    vector<Logger> loggerVector;
    vector<Server> serverVector;

    // Citim obiectele si le introducem in vector
    int taskCount, loggerCount, serverCount;
    cout << "Numarul de taskuri: ";
    cin >> taskCount;
    cout << "Numarul de loggeri: ";
    cin >> loggerCount;
    cout << "Numarul de servere: ";
    cin >> serverCount;

    cout << "\nIntrodu taskurile:\n";
    for (int i = 0; i < taskCount; ++i) {
        Task task;
        cin >> task;
        taskVector.push_back(task);
    }

    cout << "\nIntrodu loggeri:\n";
    for (int i = 0; i < loggerCount; ++i) {
        Logger logger;
        cin >> logger;
        loggerVector.push_back(logger);
    }

    cout << "\nIntrodu serverele:\n";
    for (int i = 0; i < serverCount; ++i) {
        Server server;
        cin >> server;
        serverVector.push_back(server);
    }

    // Afisarea vectorilor
    cout << "\nVectorul Task:\n";
    for (const auto& task : taskVector) {
        cout << task << '\n';
    }

    cout << "\nVectorul Logger:\n";
    for (const auto& logger : loggerVector) {
        cout << logger << '\n';
    }

    cout << "\nVectorul Server:\n";
    for (const auto& server : serverVector) {
        cout << server << '\n';
    }

    // Exemplu de matricea Task
    const int matrixSize = 2;
    Task matrix[matrixSize][matrixSize];

    // Citim matricia si le introduce in matrice
    cout << "\nIntrodu task urile pentru matrice:\n";
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            cin >> matrix[i][j];
        }
    }

    // Afisam matricea
    cout << "\nTask Matrix:\n";
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            cout << matrix[i][j] << '\t';
        }
        cout << '\n';
    }*/
        // fisier text
    /*

    Task task1, task2, task3;
    Logger logger1;
    
    // Salvare in fisier text
    task1.saveToFile("task1.txt");
    logger1.saveToFile("logger1.txt");

    // Incarcare din fisier text
    Task task4, task5, task6;
    Logger logger2;
    task4.loadFromFile("task1.txt");
    logger2.loadFromFile("logger1.txt");

    // fisier binar
    Task task7, task8, task9;
    Logger logger3;

    // Salvare in fisier binar
    task7.saveToBinaryFile("task2.bin");
    logger3.saveToBinaryFile("logger2.bin");

    // Incarcare din fisier binar
    Task task10, task11, task12;
    Logger logger4;
    task10.loadFromBinaryFile("task2.bin");
    logger4.loadFromBinaryFile("logger2.bin");
    */
   // Creare obiecte de tipul noilor clase
    TaskSpecial taskSpecial;
    ServerSpecial serverSpecial;

    //testare obiecte de tipul noilor clase
    taskSpecial.setNumeTask("Task special");
    taskSpecial.setPrioritate(1);
    taskSpecial.setFinalizat(false);
    taskSpecial.setDetaliiSpeciale("Detalii speciale pentru task");
    cout << "TaskSpecial: " << taskSpecial << endl;
    taskSpecial.afiseazaDetaliiSpeciale();

    serverSpecial.setNumeServer("Server special");
    serverSpecial.setCapacitate(2);
    serverSpecial.setActiv(true);
    serverSpecial.setRedundanta(true);
    serverSpecial.setDetaliiSpeciale("Detalii speciale pentru server");
    serverSpecial.setSecuritateAvansata(true);
    cout << "ServerSpecial: " << serverSpecial << endl;
    serverSpecial.afiseazaDetaliiSpeciale();

    // Upcasting - conversie de la clasa derivata la clasa de baza
    Task& taskBaseRef = taskSpecial;
    Server& serverBaseRef = serverSpecial;

    // Afisare atributele obiectelor prin intermediul referintelor la clasa de baza
    cout << "TaskSpecial prin Task&: " << taskBaseRef << endl;
    cout << "ServerSpecial prin Server&: " << serverBaseRef << endl;
        // Exemplificare late-binding cu vector de pointeri la tipul abstract

    vector<AbstractTask*> vectorTaskuri;

    // Adaugare obiecte de tip Task si TaskSpecial in vector
    vectorTaskuri.push_back(new Task());
    vectorTaskuri.push_back(new TaskSpecial());

    // Apelare metoda de afisare pentru obiectele din vector
    for (const auto& task : vectorTaskuri) {
        task->afisare();
    }

    // Dealocare resurse (important pentru a evita memory leaks)
    for (auto& task : vectorTaskuri) {
        delete task;
    }
    vectorTaskuri.clear();
    return 0;
}

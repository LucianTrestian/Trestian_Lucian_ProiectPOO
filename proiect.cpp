#include <iostream>
#include <string>

using namespace std;
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
    Task(std::string numeTask, int prioritate, bool finalizat) : numeTask(numeTask), prioritate(prioritate), finalizat(finalizat), idTask(0) {
        numarTotalTaskuri++;
        descriereTask = new std::string("Descriere implicita");
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
            descriereTask = new std::string(*(other.descriereTask));
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
};

int Task::numarTotalTaskuri = 0;

class Logger {
private:
    string nivelLogare;
    bool activat;
    string tipLogger;
    int* numarInregistrari;

public:
    static string fisierLog;

    // constructor default
    Logger() {
        this->nivelLogare = "Nivel implicit";
        this->activat = false;
        this->tipLogger = "Tip implicit";
        this->numarInregistrari = nullptr;
    }

    //constructor de copiere
    Logger(const Logger& other) {
        this->nivelLogare = other.nivelLogare;
        this->activat = other.activat;
        this->tipLogger = other.tipLogger;
        this->numarInregistrari = new int(*(other.numarInregistrari));
    }

    // constructor cu parametri
    // se foloseste lista de initializare a membrilor
    // acest constructor este apelat in cazul in care se instantiaza un obiect Logger cu 3 parametri
    Logger(string nivelLogare, bool activat, string tipLogger, int* numarInregistrari) : nivelLogare(nivelLogare), activat(activat), tipLogger(tipLogger), numarInregistrari(numarInregistrari) {
    
    // afisare
    cout<< "Nivelul logare: " << nivelLogare << endl;
    cout<< "Activat: " << activat << endl;
    cout<< "Tip logger: " << tipLogger << endl;
    cout<< "Numar inregistrari: " << *numarInregistrari << endl;

    }
    // constructor cu parametri fara numar inregistrari
    Logger(std::string nivelLogare, bool activat) : nivelLogare(nivelLogare), activat(activat), tipLogger("Custom") {
        numarInregistrari = new int(0);
    }
    // destructor
    ~Logger() {
        delete numarInregistrari;
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
        return *numarInregistrari;
    }

    void setNumarInregistrari(int nr) {
        for(int i = 0; i < nr; i++) {
            
        }
        
    }

    static void actualizeazaFisierLog() {
        fisierLog = "new_log.txt";
    }
    // operatorul =
    Logger& operator=(const Logger& other) {
        if (this != &other) {
            delete numarInregistrari;
            nivelLogare = other.nivelLogare;
            activat = other.activat;
            tipLogger = other.tipLogger;
            numarInregistrari = new int(*(other.numarInregistrari));
        }
        return *this;
    }
    // operatori relationali
    bool operator==(const Logger& other) const {
        return (nivelLogare == other.nivelLogare && activat == other.activat && tipLogger == other.tipLogger && *numarInregistrari == *(other.numarInregistrari));
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
        (*numarInregistrari)++;
        return *this;
    }
    // incrementare postfixata
    Logger operator++(int) {
        Logger temp(*this);
        (*numarInregistrari)++;
        return temp;
    }
    // operatorul ostream
    friend ostream& operator<<(ostream& out, const Logger& logger) {
        out << "Nivel logare: " << logger.nivelLogare << ", Activat: " << logger.activat << ", Tip logger: " << logger.tipLogger << ", Numar inregistrari: " << *(logger.numarInregistrari);
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
        in >> *(logger.numarInregistrari);
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
     Server(std::string numeServer, int capacitate, bool activ) : numeServer(numeServer), capacitate(capacitate), activ(activ), idServer(0) {
        statusGlobal = true;
        redundanta = new bool(true);
    }
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
};

bool Server::statusGlobal = true;

// Functii globale prietene cu clasele
void procesareTask(const Task& task) {
    cout << "Procesare Task: " << task.getNumeTask() << ", " << task.getPrioritate() << ", " << task.getFinalizat() << endl;
}

void procesareLogger(const Logger& logger) {
    cout << "Procesare Logger: " << logger.getNivelLogare() << ", " << logger.getActivat() << ", " << logger.getTipLogger() << ", " << logger.getNumarInregistrari() << endl;
}

int main() {
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

    Logger logger1;
    Logger logger2("Info", true);
    Logger logger3("Error", false, "Custom Logger", new int(42));

    logger1.setNivelLogare("Debug");
    logger1.setActivat(true);
    logger1.setNumarInregistrari(100);

    cout << "Logger 1 - " << logger1.getNivelLogare() << ", " << logger1.getActivat() << ", " << logger1.getTipLogger() << ", " << logger1.getNumarInregistrari() << endl;
    cout << "Logger 2 - " << logger2.getNivelLogare() << ", " << logger2.getActivat() << ", " << logger2.getTipLogger() << ", " << logger2.getNumarInregistrari() << endl;
    cout << "Logger 3 - " << logger3.getNivelLogare() << ", " << logger3.getActivat() << ", " << logger3.getTipLogger() << ", " << logger3.getNumarInregistrari() << endl;

    Logger::actualizeazaFisierLog();

    Server server1;
    Server server2("WebServer", 100, true);
    Server server3("DatabaseServer", 500, false, 456, new bool(false));

    server1.setNumeServer("FileServer");
    server1.setCapacitate(200);
    server1.setActiv(true);
    server1.setRedundanta(true);

    cout << "Server 1 - " << server1.getNumeServer() << ", " << server1.getCapacitate() << ", " << server1.getActiv() << ", " << server1.getRedundanta() << endl;
    cout << "Server 2 - " << server2.getNumeServer() << ", " << server2.getCapacitate() << ", " << server2.getActiv() << ", " << server2.getRedundanta() << endl;
    cout << "Server 3 - " << server3.getNumeServer() << ", " << server3.getCapacitate() << ", " << server3.getActiv() << ", " << server3.getRedundanta() << endl;

    Server::schimbaStatusGlobal();

    // Utilizare functii globale prietene cu clasele
    procesareTask(task1);
    procesareLogger(logger2);

    return 0;
}

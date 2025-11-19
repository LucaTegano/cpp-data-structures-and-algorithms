/*
Modellare e implementare una classe Webpage che modelli una pagina web. Ciò che ci interessa
memorizzare è il titolo della pagina, il testo contenuto in essa e l’insieme dei suoi link
(collegamenti ad altre Webpage). Si richiede inoltre di poter leggere queste informazioni
dall’esterno della classe, da cui si deve anche poter aggiungere nuovi link ma senza la possibilità
di rimuoverli, mentre il testo e il titolo della pagina, una volta creata, devono essere
immutabili. Infine, si richiede di definire un operatore di confronto tra due Webpage, ritenute
uguali se hanno lo stesso titolo.
Si richiede poi di implementare una classe Website che modelli la struttura di un sito web. Un
Website è sostanzialmente un insieme di Webpage collegate tra loro e da cui si accede tramite
una Webpage specifica detta homepage.
All’interno di Website si richiede di implementare un metodo
int find_webpage(const Webpage& target) const { … }
il quale, presa in input una Webpage, restituisce il minimo numero di link da attraversare per
trovare la pagina target e -1 se target non appartiene al sito.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Webpage; // Forward declaration

//--- Manual Queue Implementation ---
// A struct to hold the items in our queue for the BFS
struct QueueItem
{
    Webpage *page;
    int distance;
};

// A node for our custom queue linked list
struct QueueNode
{
    QueueItem data;
    QueueNode *next;
};

// A simple FIFO Queue for the BFS algorithm
class CustomQueue
{
private:
    QueueNode *head = nullptr;
    QueueNode *tail = nullptr;

public:
    ~CustomQueue()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    void push(QueueItem item)
    {
        QueueNode *newNode = new QueueNode{item, nullptr};
        if (isEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void pop()
    {
        if (isEmpty())
            return;
        QueueNode *temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr)
        {
            tail = nullptr;
        }
    }

    QueueItem front() const
    {
        // This should only be called on a non-empty queue
        return head->data;
    }
};

//--- Manual Set Implementation ---
// A node for our custom set linked list
struct SetNode
{
    string data;
    SetNode *next;
};

// A simple Set to keep track of visited page titles
class VisitedSet
{
private:
    SetNode *head = nullptr;

public:
    ~VisitedSet()
    {
        SetNode *current = head;
        while (current != nullptr)
        {
            SetNode *next = current->next;
            delete current;
            current = next;
        }
    }

    // Checks if a title is in the set
    bool contains(const string &title) const
    {
        SetNode *current = head;
        while (current != nullptr)
        {
            if (current->data == title)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Inserts a title into the set
    void insert(const string &title)
    {
        // The main algorithm already checks for existence,
        // but a real set would do it here.
        SetNode *newNode = new SetNode{title, head};
        head = newNode;
    }
};

class Webpage
{
private:
    const string titolo;
    const string testo;
    vector<Webpage *> links;

public:
    Webpage(const string &titolo, const string &testo) : titolo(titolo), testo(testo) {}

    string getTitolo() const { return titolo; }
    const vector<Webpage *> &getLinks() const { return links; }

    void aggiungiLink(Webpage *page)
    {
        links.push_back(page);
    }

    bool operator==(const Webpage &other) const
    {
        return titolo == other.titolo;
    }
};

class Website
{
private:
    Webpage *homepage;

public:
    Website(Webpage *homepage) : homepage(homepage) {}

    int find_webpage(const Webpage &target) const
    {
        if (*homepage == target)
        {
            return 0;
        }

        CustomQueue q;
        VisitedSet visitati;

        q.push({homepage, 0});
        visitati.insert(homepage->getTitolo());

        while (!q.isEmpty())
        {
            QueueItem currentItem = q.front();
            q.pop();

            Webpage *currentPage = currentItem.page;
            int distanza = currentItem.distance;

            for (const auto &link : currentPage->getLinks())
            {
                if (*link == target)
                {
                    return distanza + 1;
                }
                if (!visitati.contains(link->getTitolo()))
                {
                    visitati.insert(link->getTitolo());
                    q.push({link, distanza + 1});
                }
            }
        }

        return -1; // Target non trovato
    }
};

int main()
{
    // Creazione delle pagine web usando puntatori raw
    Webpage *home = new Webpage("Home", "Benvenuti nel sito!");
    Webpage *about = new Webpage("About", "Informazioni su di noi.");
    Webpage *contact = new Webpage("Contact", "Contattaci qui.");
    Webpage *portfolio = new Webpage("Portfolio", "I nostri lavori.");
    Webpage *project1 = new Webpage("Project 1", "Dettagli del progetto 1.");

    // Creazione dei collegamenti
    home->aggiungiLink(about);
    home->aggiungiLink(contact);
    about->aggiungiLink(portfolio);
    portfolio->aggiungiLink(project1);
    contact->aggiungiLink(home); // Link ciclico per testare

    // Creazione del sito web
    Website mySite(home);

    // Test di find_webpage
    cout << "Distanza per 'Home': " << mySite.find_webpage(Webpage("Home", "")) << endl;
    cout << "Distanza per 'About': " << mySite.find_webpage(Webpage("About", "")) << endl;
    cout << "Distanza per 'Contact': " << mySite.find_webpage(Webpage("Contact", "")) << endl;
    cout << "Distanza per 'Portfolio': " << mySite.find_webpage(Webpage("Portfolio", "")) << endl;
    cout << "Distanza per 'Project 1': " << mySite.find_webpage(Webpage("Project 1", "")) << endl;

    // Test di una pagina non esistente
    Webpage not_found("Not Found", "Questa pagina non esiste.");
    cout << "Distanza per 'Not Found': " << mySite.find_webpage(not_found) << endl;

    // Deallocazione della memoria
    delete home;
    delete about;
    delete contact;
    delete portfolio;
    delete project1;

    return 0;
}
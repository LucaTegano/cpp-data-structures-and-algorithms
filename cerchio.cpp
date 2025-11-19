#include <iostream>
using namespace std;
class Cerchio
{
private:
  float x, y;
  float raggio;

public:
  // Default constructor
  Cerchio() : x(0), y(0), raggio(0) {}

  // Constructor with radius
  Cerchio(float r) : x(0), y(0), raggio(r) {}

  // Constructor with coordinates
  Cerchio(float x1, float y1) : x(x1), y(y1), raggio(0) {}

  // Constructor with coordinates and radius
  Cerchio(float x1, float y1, float r) : x(x1), y(y1), raggio(r) {}

  // Copy constructor
  Cerchio(const Cerchio &c) : raggio(c.raggio), x(c.x), y(c.y)
  {
    cout << "Copy constructor called" << endl;
  }

  // Destructor
  ~Cerchio()
  {
    cout << "Sono il distruttore per i Cerchi con Raggio " << raggio << endl;
  }

  float getX() const
  {
    return x;
  }

  float getY() const
  {
    return y;
  }

  float getRaggio() const
  {
    return raggio;
  }

  Cerchio &operator=(const Cerchio &c)
  {
    cout << "Assignment operator called" << endl;
    if (this != &c)
    {
      raggio = c.raggio;
      x = c.x;
      y = c.y;
    }
    return *this;
  }

  bool operator==(const Cerchio &C) const
  {
    return (raggio == C.raggio) &&
           (x == C.x) &&
           (y == C.y);
  }

  Cerchio &operator+(const Cerchio &c)
  {
    Cerchio NC(raggio + c.raggio);
    return NC;
  }

  bool &operator<(const Cerchio &c)
  {
    raggio < c.raggio;
    x < c.x;
    y < c.y;
  }

  Cerchio &operator+=(const Cerchio &c)
  {
    raggio += c.raggio;
    x += c.x;
    y += c.y;
    return *this;
  }

  friend ostream &operator<<(ostream &os, const Cerchio &c);
  friend istream &operator>>(istream &is, Cerchio &c);
  friend Cerchio &operator-(const Cerchio &c1, const Cerchio &c2);
  void setRaggio(float);
};

float calcolaArea(const Cerchio &c)
{
  return c.getRaggio() * c.getRaggio() * 3.14;
}

ostream &operator<<(ostream &os, const Cerchio &c)
{
  os << "Cerchio(raggio=" << c.raggio << ", x=" << c.x << ", y=" << c.y << ")";
  return os;
}

istream &operator>>(istream &is, Cerchio &c)
{
  cout << "Enter radius: ";
  is >> c.raggio;
  cout << "Enter x coordinate: ";
  is >> c.x;
  cout << "Enter y coordinate: ";
  is >> c.y;
  return is;
}

bool operator<=(const Cerchio &c1, const Cerchio &c2)
{
  return (c1.getRaggio() <= c2.getRaggio()) &&
         (c1.getX() <= c2.getX()) &&
         (c1.getY() <= c2.getY());
}

Cerchio &operator-(const Cerchio &c1, const Cerchio &c2)
{
  Cerchio NC(c1.getRaggio() - c2.getRaggio(),
             c1.getX() - c2.getX(),
             c1.getY() - c2.getY());
  return NC;
}

void Cerchio::setRaggio(float h)
{
  if (h < 0)
  {
    cout << "Invalid radius value" << endl;
    return;
  }
  raggio = h;
}

int main()
{
  Cerchio c1(5);
  cout << "c1: " << c1 << endl;

  Cerchio c2(10);
  cout << "c2: " << c2 << endl;

  cout << "operator + " << c1 + c2 << endl;
  /*
  Viene chiamata c1 + c2.

  La tua funzione operator+ viene eseguita.

  Al suo interno, crei un nuovo oggetto: Cerchio NC(raggio + c.raggio);. Questo oggetto NC è una variabile locale, esiste solo all'interno della funzione.

  La funzione termina e restituisce NC come riferimento (Cerchio&).

  Non appena la funzione termina, tutte le sue variabili locali vengono distrutte per liberare memoria.

  Quindi, il distruttore viene chiamato per NC. Questo è il cout che vedi: "Sono il distruttore per i Cerchi con Raggio 15".

  Il cout nel main ora ha un riferimento a un oggetto (NC) che non esiste più. Questo si chiama riferimento penzolante (dangling reference) ed è un comportamento indefinito (Undefined Behavior). Sei fortunato che il programma non sia crashato.
  */

  c1 += c2;
  cout << "c1 after += c2: " << c1 << endl;

  cout << "Area of c1: " << calcolaArea(c1) << endl;

  Cerchio c3;
  cout << "Enter details for a new circle c3:" << endl;
  cin >> c3;
  cout << "c3: " << c3 << endl;

  Cerchio c4(1, 2, 3);
  cout << "c4: " << c4 << endl;

  Cerchio c5(4, 5, 6);
  cout << "c5: " << c5 << endl;

  c4 += c5;
  cout << "c4 after += c5: " << c4 << endl;

  return 0;
}
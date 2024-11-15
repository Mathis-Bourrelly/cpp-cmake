module;
// Import rapide de la bibliothèque standard
import std;

// Nommage et exportation de ce module
export module exo2;

// On met toutes les classes du module dans un espace de nom
// ayant le même nom que le module pour plus de clarté et éviter
// les conflits de nommage.
// On exporte la totalité des classe de l'espace de nom.
export namespace exo2
{
    class Vector {
        double a;
        double b;
        double c;

    public:
        Vector(double a, double b, double c): a(a),b(b),c(c){
            std::cout<<"triangle cree"<<std::endl;
        }
        Vector(const Vector &other): a(other.a),b(other.b),c(other.c){
            std::cout<<"triangle copie"<<std::endl;
        }


        double GetA() const {
            return a;
        }
        void SetA(double a)
        {
            this->a = a;
        }
        double GetB() const
        {
            return b;
        }
        void SetB(double b)
        {
            this->b = b;
        }
        double GetC() const
        {
            return c;
        }
        void SetC(double c)
        {
            this->c = c;
        }

        void Homothety(double multiplicator){
            a *= multiplicator;
            b *= multiplicator;
            c *= multiplicator;
        }
        void Sum1(Vector adder)
        {
            a += adder.a;
            b += adder.b;
            c += adder.c;
        }
        void Sum2(Vector &adder)
        {
            a += adder.a;
            b += adder.b;
            c += adder.c;
        }

        std::string ToString() {
            return std::format("({:.2f},{:.2f},{:.2f})", a,b,c);
        }
    };

    class Application{
    // Tout le code de l'exercice doit être dans ce constructeur
    public:
        Application() {

        }
    };
}
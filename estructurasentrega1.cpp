#include <iostream>
#include <string>

using namespace std;



//structs para todo
struct implementos {
    string nombre;
    int id;
    implementos* siguiente;
};

struct Personaje {
    int Id;
    string nombre;
    string bando; // lealtad

 Personaje* actual = lista.cabeza;
    #include <iostream>
    #include <string>

    using namespace std;
    )

    struct implementos {
        string nombre;
        int id;
        implementos* siguiente;
    };

    struct Personaje {
        int Id;
        string nombre;
        string bando; // lealtad
        string tipo; // clase
        implementos* inventario;
        Personaje* siguiente;
    }
    ListadePersonajesqueexisten listadepersonajescompleta;
    ListadePersonajes listadepersonajes;
    ListadeEstaciones listadeestaciones;

    //hacer lista de personajes
    Personaje* verlosPersonaje(ListadePersonajes& lista, int id) {
        Personaje* actual = lista.cabeza;
        while (actual != nullptr) {
            if (actual->Id == id) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    //que mostrar si todabia no hay personajes
    void mostrarPersonajes(ListadePersonajesqueexisten& lista) {
        if (lista.cabeza == nullptr) {
            cout << "no existen personajes, si gustas crealos" << endl;
            return;
        }

        Personaje* actual = lista.cabeza;
        //si no hay ningun personaje
        while (actual != nullptr) {
            cout << "ID: " << actual->Id << endl;
            cout << "nombre: " << actual->nombre << endl;
            //lealtad es si son policias o ladrones
            cout << "lealtad: " << actual->bando << endl;
            //tipo de policia o de ladron
            cout << "clase: " << actual->tipo << endl;
            if (actual->bando == "policia") {

                //mostrar las cositas de cada personaje :)
                cout << "inventario:" << endl;
                if (actual->inventario == nullptr) {
                    cout << "  no tienes nada, sigue intentando conseguir cosas" << endl;
                } else {
                    implementos* items = actual->inventario;
                    while (items != nullptr) {
                        cout << " " << items->nombre << " (ID: " << items->id << ")" << endl;
                        items = items->siguiente;
                    }
                }
            }
            //ir al siguiente personaje
            actual = actual->siguiente;
        }

    }


    int main() {
        //declaracion de variables
        int opcionmenubase;
        int opcioncrearomodificar;
        int opcioncrearomodificarestaciones;

        do {
            cout << "bienvenido a policias y ladrones. Escribe el numero de tu opcion y dale enter." << endl;
            cout << "opciones:" << endl;
            cout << "1. modificar y crear personajes" << endl;
            cout << "2. ¿como jugar?" << endl;
            cout << "3. Ver personajes" << endl;
            cout << "4. modificar y ver estaciones" << endl;

            cout << "5. modificar, eliminar y ver implementos" << endl;
            cout << "7.Salir" << endl;

            cin >> opcionmenubase;

             if (opcionmenubase == 1) {
                cout << "¿Deseas crear o modificar personajes?" << endl;
                cout << "1. Crear personaje" << endl;
                cout << "2. Modificar personaje" << endl;
                cout << "3. Eliminar personaje" << endl;
                cin >> opcioncrearomodificar;
                if (opcioncrearomodificar == 1) {
                    cout << "elegiste  crear personaje" << endl;
                    //aqui se mete el crear personajes con su debdido struct

                } else if (opcioncrearomodificar == 2) {
                    cout << "elegiste  modificar personaje,por favor selecciona a quien modificar" << endl;
                    mostrarPersonajes(listadepersonajes);
                    //se selecciona cual se va a modificar

                } else if (opcioncrearomodificar == 3) {
                    cout << "elegiste  eliminar personaje, selecciona cual eliminar" << endl;
                    mostrarPersonajes(listadepersonajes);
                    //se selecciona cual se va a eliminar

                } else {
                    cout << "Opción no válida. Por favor selecciona 1, 2 o 3" << endl;
                }
            } else if (opcionmenubase == 2) {
                cout << "elegiste  ¿como jugar?" << endl;
                cout << " creas tus personajes, tus estaciones y te desplazas para conseguir el oro." << endl;
            } else if (opcionmenubase == 3) {
                cout << "ver personajes" << endl;

                mostrarPersonajes(listadepersonajescompleta);

            }
            //esto es para agregar ago su toca despues
                       else if (opcionmenubase == 4) {
                cout << "elegiste  modificar y ver estaciones" << endl;
                cout << "1. crear estaciones" << endl;
                cout << "2. ver estaciones" << endl;
                cout << "3. modificar estaciones" << endl;
                cout << "4. eliminar estaciones" << endl;
                cin >> opcioncrearomodificarestaciones;
                if (opcioncrearomodificarestaciones == 1) {
                    cout << "elegiste  crear estaciones" << endl;
                    //aqui se mete el crear estaciones con su debdido struct

                } else if (opcioncrearomodificarestaciones == 2) {
                    cout << "elegiste   ver estaciones" << endl;
                    cout << listadeestaciones << endl;
                    //se selecciona cual se va a modificar

                }
                else if (opcioncrearomodificarestaciones == 3) {
                    cout << "elegiste   modificar estaciones" << endl;
                    cout << listadeestaciones << endl;
                }
                else if (opcioncrearomodificarestaciones == 4) {
                    cout << "elegiste eliminar estaciones. Selecciona cual eliminar" << endl;
                    cout << listadeestaciones << endl;
                }
                else {
                    cout << "Opción no válida. Por favor selecciona 1,2,3 o 4" << endl;
                }
                           
             else if (opcionmenubase == 5) {
                cout << "elegiste implementos" << endl;

                cout << "¿Deseas crear o modificar implementos?" << endl;
                cout << "1. Crear implemento" << endl;
                cout << "2. Modificar implemento" << endl;
                cout << "3. Eliminar implemento" << endl;
                    cin >> opcioncrearomodificarimplementos;
                if (opcioncrearomodificarimplementos == 1) {
                    cout << "elegiste  crear implemento" << endl;
                    //aqui se mete el crear implementos con su debdido struct

                } else if (opcioncrearomodificarimplementos == 2) {
                    cout << "elegiste  modificar implemento,por favor selecciona a quien modificar" << endl;
                    mostrarImplementos(listadeimplementos);
                    //se selecciona cual se va a modificar

                } else if (opcioncrearomodificarimplementos == 3) {
                    cout << "elegiste  eliminar implemento, selecciona cual eliminar" << endl;
                    mostrarImplementos(listadeimplementos);
                    //se selecciona cual se va a eliminar

            }
            else if (opcionmenubase == 7) {
                cout << "Ya se libero la memoria. Gracias por su atencion" << endl;

            }
            else {

                cout << "Opción no válida. Por favor selecciona un numero del menu." << endl;
            }

        } while (opcionmenubase != 7);

        return 0;
    }

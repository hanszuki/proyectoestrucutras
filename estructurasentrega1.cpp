#include <iostream>
#include <string>
using namespace std;

struct ImplementoCatalogo{
    int id;
    string nombre;
    string efecto;  //descripcion 
    int durabilidad; //maximo de usos
    string bando; // "Policia", "Ladron", "Ambos"
    ImplementoCatalogo* siguiente;
};

struct ImplementoInventario{
    ImplementoCatalogo* itemCatalago;
    int usosRestantes; //cuando llegue a 0 se debe eliminar el implemento del inventario
    ImplementoInventario* siguiente;
};

struct Estacion {
    int id;           
    int oro;
    Estacion* siguiente;
};

struct Personaje{
    int Id;
    string nombre;
    string bando;
    string tipo;
    string estado;
    int puntosDeVida;
    bool corrupto; //solo se va a utilizar si bando es "policia"
    Estacion* posicionActual;
    ImplementoInventario* inventario;
    Personaje* siguiente;
};


struct ListaPersonajes { 
    Personaje* cabeza = nullptr; 
};

struct ListaImplementosCatalogo { 
    ImplementoCatalogo* cabeza = nullptr; 
};

struct ListaEstaciones { 
    Estacion* cabeza = nullptr; 
};

//FUNCIONES PARA VALIDAR 
int ValidarEntero(const string mensaje){
    int valor;
    while(true){
        cout << mensaje;
        cin >> valor;
        if(cin.fail()){
            cin.clear(); //limpia el cin que tiene error 
            cin.ignore(1000, '\n'); //Quita la entrada incorrecta
            cout << "Valor ingresado invalido, por favor ingresar un numero entero.\n";
        }else{
            cin.ignore(1000, '\n');
            return valor;
        }

    }
}
//Para Personaje:
bool ExisteIdP(ListaPersonajes& lista, int id){
    Personaje* actual = lista.cabeza;
    while(actual != nullptr){
        if(actual->Id == id) return true;
        actual = actual->siguiente;
    }
    return false;
}
//Para Implemento:
bool ExisteIdI(ListaImplementosCatalogo& lista, int id){
    ImplementoCatalogo* actual = lista.cabeza;
    while(actual != nullptr){
        if(actual->id == id) return true;
        actual = actual->siguiente;
    }
    return false;
}
//Para Estaciiones:
bool ExisteIdE(ListaEstaciones &lista, int id){
    Estacion* actual = lista.cabeza;
    while(actual != nullptr){
        if(actual->id == id) return true;
        actual = actual->siguiente;
    }
    return false;
}

//validacion de strings :/
bool EstaVacio(const string texto){ //Si esta vacia devuelve true, sino false
    return texto.empty();
}

string EliminarEspacios(string texto){ //elimina los espacios al principio y al final del string
    while(!texto.empty() && isspace(texto.front())){
        texto.erase(0, 1);
    }
    while(!texto.empty() && isspace(texto.back())){
        texto.pop_back();
    }
    return texto;
}

string ConseguirNombreValido(string nombre){
    do{
        cout<< "Ingrese Nombre: ";
        getline(cin, nombre); 
        nombre = EliminarEspacios(nombre);
        if(EstaVacio(nombre)){
            cout << "Su nombre no puede estar vacio ingrese nombre valido\n";
        }else{
            break;
        }
    }while(true);
    return nombre;
}

bool ExisteNombre(ListaPersonajes& lista, string nombre){
    Personaje* actual = lista.cabeza;
    while(actual != nullptr){
        if(actual->nombre == nombre) return true;
        actual = actual->siguiente;
    }
    return false;
}

bool ExisteNombreI(ListaImplementosCatalogo& lista, string nombre){
    ImplementoCatalogo* actual = lista.cabeza;
    while(actual != nullptr){
        if(actual->nombre == nombre) return true;
        actual = actual->siguiente;
    }
    return false;
}

//FUNCIONES CRUD PARA PERSONAJES

//CREATE
Personaje* MenuCrearPersonaje(ListaPersonajes &lista){
    //Entrada de datos por usuario
    int id;
    string nombre, bando, tipo;
    int opcion_bando, opcion_tipo;
    bool corrupto = false;
    bool validoBando = false;
    bool validoTipo = false;

    cout << "Vamos a crear un personaje\n";
    //ID
    do{
        id = ValidarEntero("Ingrese ID para su personaje: ");
        if(ExisteIdP(lista, id)){
            cout<< "El id ingresado ya existe, por favor ingresar otro distinto.\n";
        }
    }while(ExisteIdP(lista, id));
    //Nombre
    do{
        nombre = ConseguirNombreValido(nombre);
        if(ExisteNombre(lista, nombre)){
            cout<< "El nombre ingresado ya existe, por favor ingresar otro distinto.\n";
        }
    }while(ExisteNombre(lista, nombre));
    //Bando
    do{
        opcion_bando = ValidarEntero("Seleccione el Bando de su personaje: \n1 -> Policia\n2 -> Ladron\n");
        switch (opcion_bando)
        {
            case 1:
            bando = "Policia";
            validoBando = true;
            break;
            
            case 2:
            bando = "Ladron";
            validoBando = true;
            break;
            
            default:
            cout << "Opcion invalida, por favor ingresar un numero correcto.\n";
            break;
        }
    }while(!validoBando);

    do{
        if(bando == "Policia"){
            opcion_tipo = ValidarEntero("Seleccione el Tipo de su Policia (1-5): \n\nTipos de policias:\n1 -> Inspector Jefe\n2 -> Perito Forense\n3 -> Oficial de Asalto\n4 -> Analista de Datos\n5 -> Negociador\n"); 
        }
        if(bando == "Ladron"){
            opcion_tipo = ValidarEntero("Seleccione el Tipo de su ladron (1-6): \n\nTipos de ladrones:\n1 -> Cerebro\n2 -> Fantasma\n3 -> Mulo\n4 -> Saboteador\n5 -> Hacker\n6 -> Lobero(Carismatico)\n"); 
        }
        
        switch (opcion_tipo)
        {
            case 1:
            if (bando == "Policia") {
            tipo = "Inspector Jefe";
            }else if(bando == "Ladron"){
            tipo = "Cerebro";
            }
            validoTipo = true;
            break;
            
            case 2:
            if (bando == "Policia") {
            tipo = "Perito Forense";
            }else if(bando == "Ladron"){
            tipo = "Fantasma";
            }
            validoTipo = true;
            break;

            case 3:
            if(bando == "Policia"){
            tipo = "Oficial de Asalto";
            }else if(bando == "Ladron"){
            tipo = "Mulo";
            }
            validoTipo = true;
            break;
            
            case 4:
            if(bando == "Policia"){
            tipo = "Analista de Datos";
            }else if(bando == "Ladron"){
            tipo = "Saboteador";
            }
            validoTipo = true;
            break;

            case 5:
            if(bando == "Policia"){
            tipo = "Negociador";
            }else if(bando == "Ladron"){
            tipo = "Hacker";
            }
            validoTipo = true;
            break;
            
            case 6:
            if(bando == "Policia"){
            cout << "Opcion invalida, por favor ingresar un numero correcto.\n";
            break;
            }else if(bando == "Ladron"){
            tipo = "Lobero (Carismatico)";
            validoTipo = true;
            }
            break;

            default:
            cout << "Opcion invalida, por favor ingresar un numero correcto.\n";
            break;
        }
    }while(!validoTipo);

    //Asignacion de datos
    Personaje *agregar = new Personaje();
    agregar->Id = id;
    agregar->nombre = nombre;
    agregar->bando = bando;
    agregar->tipo = tipo;
    agregar->estado = "activo";
    agregar->puntosDeVida = 100; //todos inician con vida base.
    agregar->corrupto = corrupto;
    agregar->siguiente = nullptr;
    agregar->inventario = nullptr;
    agregar->posicionActual = nullptr;
    return agregar;
}

void CrearPersonaje(ListaPersonajes &lista){
    Personaje* agregar = MenuCrearPersonaje(lista);
    //Agregar al final de la lista
    if(lista.cabeza == nullptr){
        lista.cabeza = agregar;
    }else{
        Personaje *actual = lista.cabeza;
        while(actual->siguiente != nullptr){
            actual = actual->siguiente;
        }
        actual->siguiente = agregar;
    }
    cout << "Ha creado su personaje correctamente." << endl;
}

//READ
Personaje* BuscarPersonaje(ListaPersonajes &lista){
    int opcionBusqueda;
    bool validaOpcionBusqueda = false;
    string valorBusquedaN = "";
    int valorBusquedaId = 0; 

    if(lista.cabeza == nullptr){
        cout<<"No existen personajes creados."<< endl;
        return nullptr;
    }
    
    do{
        opcionBusqueda = ValidarEntero("Presione 1 si desea buscar su personaje por nombre.\nPresione 2 si desea buscar su personaje por ID.\n");
        switch (opcionBusqueda)
        {
        case 1:
            valorBusquedaN = ConseguirNombreValido("Ingrese el Nombre de su personaje: ");
            if(!ExisteNombre(lista, valorBusquedaN)){
                cout << "Nombre no encontrado, personaje no se encuentra en la lista , ingrese un valor de busqueda correcto\n";
                break;
            }
            validaOpcionBusqueda = true;
            break;
        case 2:
            valorBusquedaId = ValidarEntero("Ingrese el ID de su personaje: ");
            if(!ExisteIdP(lista, valorBusquedaId)){
                cout << "ID no encontrado, personaje no se encuentra en la lista, ingrese un valor de busqueda correcto\n";
                break;
            }
            validaOpcionBusqueda = true;
            break;
        default:
            cout << "Opcion invalida, por favor ingresar un numero correcto.\n";
            break;
        }
    }while(!validaOpcionBusqueda);
    
    Personaje* actual = lista.cabeza;
    while(actual->nombre != valorBusquedaN && actual->Id != valorBusquedaId){
        actual = actual->siguiente;
    }
    return actual;
}

void MostrarPersonaje(Personaje* personaje) {
    if(personaje == nullptr){
        cout << "No se encontro el personaje \n";
        return;
    }
    cout << "-- Datos del personaje --\n";
    cout << "ID:     " << personaje->Id << endl;
    cout << "Nombre: " << personaje->nombre << endl;
    cout << "Bando:  " << personaje->bando << endl; //bando es si son policias o ladrones
    cout << "Tipo:   " << personaje->tipo << endl; //tipo de policia o de ladron
    cout << "Estado: " << personaje->estado << endl;
    cout << "Puntos de Vida: " << personaje->puntosDeVida << endl;
    //mostrar las cositas del personaje :)
    cout << "Inventario:" << endl;
    if (personaje->inventario == nullptr) {
        cout << " no tienes nada, sigue intentando conseguir cosas" << endl;
    } else {
        ImplementoInventario* itemActual = personaje->inventario;
        while (itemActual != nullptr) {
            cout << " " << itemActual->itemCatalago->nombre
            << " (ID: " << itemActual->itemCatalago->id << ")" << endl;
            itemActual = itemActual->siguiente;
        }
    }
    if (personaje->posicionActual == nullptr) {
        cout << " no tienes posicion actual asignada" << endl;
    } else {
        Estacion* posicionActual = personaje->posicionActual;
        cout << "Posicion Actual: \n" 
        << "ID: " << posicionActual->id 
        << posicionActual->oro << endl;
    }
}

void MostrarPersonajes(ListaPersonajes& lista) {
    //si no hay ningun personaje
    if (lista.cabeza == nullptr) {
        cout << "no existen personajes, si gustas crealos" << endl;
        return;
    }
    cout << "-- Lista de Personajes --\n\n";
    Personaje* actual = lista.cabeza;
    while (actual != nullptr) {
        cout << "-- Datos del personaje --\n";
        cout << "ID: " << actual->Id << endl;
        cout << "Nombre: " << actual->nombre << endl;
        //Bando es si son policias o ladrones
        cout << "Bando: " << actual->bando << endl;
        //tipo de policia o de ladron
        cout << "Tipo: " << actual->tipo << endl;
        //mostrar las cositas de cada personaje :)
        cout << "Inventario: " << endl;
        if (actual->inventario == nullptr) {
            cout << " no tienes nada, sigue intentando conseguir cosas" << endl;
        } else {
            ImplementoInventario* itemActual = actual->inventario;
            while (itemActual != nullptr) {
                cout << " " << itemActual->itemCatalago->nombre << " (ID: " << itemActual->itemCatalago->id << ")" << endl;
                itemActual = itemActual->siguiente;
            }
        }
        //ir al siguiente personaje
        actual = actual->siguiente;
    }
}

//UPDATE
void ModificarPersonaje(ListaPersonajes &lista){
    Personaje* personaje = BuscarPersonaje(lista);
    if(personaje == nullptr){
        cout << "Personaje no encotrado. No se puede modificar.\n";
        return;
    }
    cout << "Su personaje actualmente tiene las siguientes caracteristicas: \n";
    MostrarPersonaje(personaje);
    //Menu modificacion
    cout << "¿Que desea modificar?\n Seleccione una opcion valida:\n";
    cout << "1 -> Cambiar nombre\n" 
         << "2 -> Cambiar tipo\n" 
         << "3 -> Cambiar estado\n"
         << "4 -> Cambiar puntos de vida\n"  
         << "5 -> Cancelar\n";
    int opcionModificar = ValidarEntero("Elija una de las opciones presentadas\n");
    switch (opcionModificar) {
    case 1: {
        personaje->nombre = ConseguirNombreValido(personaje->nombre);
        cout << "Nombre actualizado con exito\n";
        break;
    }
    
    case 2:{

        bool validoTipo = false;
        int opcion_tipo = 0;
        do{
            if(personaje->bando == "Policia"){
                opcion_tipo = ValidarEntero("Seleccione el Tipo de su Policia (1-5): \n\nTipos de policias:\n1 -> Inspector Jefe\n2 -> Perito Forense\n3 -> Oficial de Asalto\n4 -> Analista de Datos\n5 -> Negociador\n"); 
            }
            if(personaje->bando == "Ladron"){
                opcion_tipo = ValidarEntero("Seleccione el Tipo de su ladron (1-6): \n\nTipos de ladrones:\n1 -> Cerebro\n2 -> Fantasma\n3 -> Mulo\n4 -> Saboteador\n5 -> Hacker\n6 -> Lobero(Carismatico)\n"); 
            }
            
            switch (opcion_tipo)
            {
                case 1:
                if (personaje->bando == "Policia") {
                    personaje->tipo = "Inspector Jefe";
                }else if(personaje->bando == "Ladron"){
                    personaje->tipo = "Cerebro";
                }
                validoTipo = true;
                break;
                
                case 2:
                if (personaje->bando == "Policia") {
                    personaje->tipo = "Perito Forense";
                }else if(personaje->bando == "Ladron"){
                    personaje->tipo = "Fantasma";
                }
                validoTipo = true;
                break;
                
                case 3:
                if(personaje->bando == "Policia"){
                    personaje->tipo = "Oficial de Asalto";
                }else if(personaje->bando == "Ladron"){
                    personaje->tipo = "Mulo";
                }
                validoTipo = true;
                break;
                
                case 4:
                if(personaje->bando == "Policia"){
                    personaje->tipo = "Analista de Datos";
                }else if(personaje->bando == "Ladron"){
                    personaje->tipo = "Saboteador";
                }
                validoTipo = true;
                break;
                
                case 5:
                if(personaje->bando == "Policia"){
                    personaje->tipo = "Negociador";
                }else if(personaje->bando == "Ladron"){
                    personaje->tipo = "Hacker";
                }
                validoTipo = true;
                break;
                
                case 6:
                if(personaje->bando == "Policia"){
                    cout << "Opcion invalida, por favor ingresar un numero correcto.\n";
                    break;
                }else if(personaje->bando == "Ladron"){
                    personaje->tipo = "Lobero (Carismatico)";
                    validoTipo = true;
                }
                break;
                
                default:
                cout << "Opcion invalida, por favor ingresar un numero correcto.\n";
                break;
            }
        }while(!validoTipo);
        cout << "Tipo actualizado con exito\n";
        break;
    }
    
    case 3:{

        bool validoEstado = false;
        int opcion_estado = 0;
        do{
            opcion_estado = ValidarEntero("Seleccione la opcion de nuevo estado (1-3): \nOpciones de estado:\n1 -> Activo\n2 -> Capturado\n3 -> Inhabilitado\n"); 
            
            switch (opcion_estado)
            {
                case 1:
                personaje->estado = "Activo";
                validoEstado = true;
                break;
                
                case 2:
            personaje->estado = "Capturado";
            validoEstado = true;
            break;
            
            case 3:
            personaje->estado = "Inhabilitado";
            validoEstado = true;
            break;
            
            default:
            cout << "Opcion invalida, por favor ingresar un numero correcto.\n";
            break;
        }
    }while(!validoEstado);
    cout << "Estado actualizado con exito\n";
    break;
    }
    
    case 4:{
        personaje->puntosDeVida = ValidarEntero("Ingrese un valor entre 1 y 100");
        cout << "Puntos de vida actualizado con exito\n";
        break;
    }
        
    case 5:{
        cout << "Modificacion Cancelada\n";
        break;
    }
    default:
    cout << "Opcion invalida, por favor ingresar un numero correcto.\n";
    break;
    }
}

//DELETE
void LiberarInvetario(ImplementoInventario* inventario) {
    while (inventario != nullptr) {
        ImplementoInventario* siguiente = inventario->siguiente;
        delete inventario;
        inventario = siguiente;
    }
}

void LiberarPersonajes(ListaPersonajes &lista) {
    Personaje* actual = lista.cabeza;
    while (actual != nullptr) {
        Personaje* siguiente = actual->siguiente;
        //Liberar inventario
        LiberarInvetario(actual->inventario);
        delete actual;
        actual = siguiente;
    }
    lista.cabeza = nullptr;
}

void EliminarPersonaje(ListaPersonajes &lista){
    if(lista.cabeza == nullptr){
        cout << "No hay personajes en la lista. \n";
        return;
    }
    cout << "Busquemos a tu seleccionado a eliminar\n";
    Personaje* condenadoAEliminar = BuscarPersonaje(lista);
    if(condenadoAEliminar == nullptr){
        cout << "No se encontro el personaje, no se puede eliminar.\n";
        return;
    }
    Personaje* actual = lista.cabeza;
    Personaje* previo = nullptr;

    while (actual != nullptr && actual != condenadoAEliminar) {
        previo = actual;
        actual = actual->siguiente;
    }

    // Liberar inventario antes de eliminar
    LiberarInvetario(actual->inventario);

    // Eliminar el nodo
    if (previo == nullptr) {
        lista.cabeza = actual->siguiente; //en caso de ser la cabeza el condenado se pasa de una vez la cabeza al siguiente y delete actual
    } else {
        previo->siguiente = actual->siguiente;
    }

    delete actual;
    cout << "Personaje eliminado correctamente.\n";
}

//FUNCIONES CRUD PARA IMPLEMENTOS 
//CREATE 
ImplementoCatalogo* MenuCrearImplemento(ListaImplementosCatalogo &lista){
    //Entrada de datos por usuario
    int id, durabilidad;
    string nombre, bando, efecto;
    int opcion_bando;
    bool validoBando = false;

    cout << "Vamos a crear un implemento\n";
    //Durabilidad 
    durabilidad = ValidarEntero("Ingrese la cantidad de usos maximo de su implemento: ");
    //Efecto
    cout << "Describe tu implemento: (Referencia al comportamiento en el juego)\n";
    getline(cin,efecto);

    //ID
    do{
        id = ValidarEntero("Ingrese ID para su implemento: ");
        if(ExisteIdI(lista, id)){
            cout<< "El id ingresado ya existe, por favor ingresar otro distinto.\n";
        }
    }while(ExisteIdI(lista, id));


    //Nombre
    do{
        nombre = ConseguirNombreValido(nombre);
        if(ExisteNombreI(lista, nombre)){
            cout<< "El nombre ingresado ya existe, por favor ingresar otro distinto.\n";
        }
    }while(ExisteNombreI(lista, nombre));
    //Bando
    do{
        opcion_bando = ValidarEntero("Seleccione el Bando que puede acceder al implemento: \n1 -> Policia\n2 -> Ladron\n3 -> Ambos\n");
        switch (opcion_bando)
        {
            case 1:
            bando = "Policia";
            validoBando = true;
            break;
            
            case 2:
            bando = "Ladron";
            validoBando = true;
            break;

            case 3:
            bando = "Ambos";
            validoBando = true;
            break;
            
            default:
            cout << "Opcion invalida, por favor ingresar un numero correcto.\n";
            break;
        }
    }while(!validoBando);

    //Asignacion de datos a Implemento del catalogo
    ImplementoCatalogo *agregar = new ImplementoCatalogo();
    agregar->id = id;
    agregar->nombre = nombre;
    agregar->bando = bando;
    agregar->durabilidad = durabilidad;
    agregar->efecto = efecto; 
    agregar->siguiente = nullptr;
    return agregar;
}

void CrearImplemento(ListaImplementosCatalogo &lista){
    ImplementoCatalogo* agregar = MenuCrearImplemento(lista);
    //Agregar al final de la lista
    if(lista.cabeza == nullptr){
        lista.cabeza = agregar;
    }else{
        ImplementoCatalogo* actual = lista.cabeza;
        while(actual->siguiente != nullptr){
            actual = actual->siguiente;
        }
        actual->siguiente = agregar;
    }
    cout << "Ha creado su Implemento y se ha agregado al catalogo correctamente." << endl;
}

// AGREGAR A INVENTARIO
//READ (Buscar) lo declaramos aqui porque lo llamamos en la funcion de Agregar
ImplementoCatalogo* BuscarImplementoCatalogo(ListaImplementosCatalogo &lista){
    int opcionBusqueda;
    bool validaOpcionBusqueda = false;
    int valorBusquedaId = 0; 

    if(lista.cabeza == nullptr){
        cout<<"No existen implementos creados."<< endl;
        return nullptr;
    }
    ImplementoCatalogo* actual = nullptr;
    do{
        actual = lista.cabeza;
        valorBusquedaId = ValidarEntero("Ingrese el ID de su implemento: ");
        while(actual != nullptr){
            if(actual->id == valorBusquedaId){
                break;
            }
            actual = actual->siguiente;
        }
        if(actual == nullptr){
            cout << "ID no encontrado. El implemento no se encuentra en la lista, por favor ingresar un id valido\n";
        }
    }while(actual == nullptr);
    return actual;
}

void AgregarImplementoAInvetario(ListaPersonajes &personajes, ListaImplementosCatalogo &catalogo){
    if(personajes.cabeza == nullptr){
        cout << "No existen personajes creados\n";
        return;
    }
    Personaje* personaje = BuscarPersonaje(personajes);
    if(personaje == nullptr) return;
    
    if(catalogo.cabeza == nullptr){
        cout << "No hay implementos en el catálogo.\n";
        return;  
    }
    cout << "Implementos disponibles para " << personaje->bando << ":\n";
    //mostrar implementos compatibles
    ImplementoCatalogo* actual = catalogo.cabeza;
    while (actual != nullptr) {
        if(actual->bando == "Ambos" || actual->bando == personaje->bando) {
            cout << "ID: " << actual->id 
            << "\nNombre: " << actual->nombre 
            << "\nDurabilidad: " << actual->durabilidad
            << "\nEfecto: \n" << actual->efecto;
        }
        actual = actual->siguiente;
    }
    //Buscar por ID el implemento que se desea agregar
    ImplementoCatalogo* seleccionado = BuscarImplementoCatalogo(catalogo);
    if (seleccionado==nullptr) {
        return;
    }
    if (seleccionado->bando != "Ambos" && seleccionado->bando != personaje->bando) {
        cout << "Este implemento no puede ser usado por personajes del bando " << personaje->bando << ".\n";
        return;
    }
    //Crear la "copia" del implemento que estara en el inventario
    ImplementoInventario* nuevo = new ImplementoInventario();
    nuevo->itemCatalago = seleccionado;
    nuevo->usosRestantes = seleccionado->durabilidad; // comienza con toda la durabilidad
    nuevo->siguiente = nullptr;
    //Insertar al final en el inventario deel personaje
    if(personaje->inventario == nullptr) {
        personaje->inventario = nuevo;
    } else {
        ImplementoInventario* temp = personaje->inventario;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
    cout << "El implemento seleccionado se ha agg al invetario de: " << personaje->nombre << " correctamente. Usalo sabiamente\n";
}

//READ
void MostrarCatalogo(ListaImplementosCatalogo& lista) {
    //si no hay ningun implemento
    if (lista.cabeza == nullptr) {
        cout << "no existen implementos, si gustas crealos" << endl;
        return;
    }
    cout << "-- Catalogo --\n\n";
    ImplementoCatalogo* actual = lista.cabeza;
    while (actual != nullptr) {
        cout << "-- Datos del implemento --\n";
        cout << "ID: " << actual->id << endl;
        cout << "Nombre: " << actual->nombre << endl;
        //Bando es si son policias o ladrones o ambos
        cout << "Bando(Quien lo puede usar): " << actual->bando << endl;
        //descripcion del comportamiento del implemento
        cout << "Descripcion: \n" << actual->efecto << endl;
        //Cantidad de usos maximo 
        cout << "Durabilidad: \n" << actual->durabilidad << endl; 
        //ir al siguiente implemento en el catalogo
        actual = actual->siguiente;
    }
}

void MostrarImplementoCatalogo(ImplementoCatalogo* implemento) {
    if(implemento == nullptr){
        cout << "No se encontro el implemento \n";
        return;
    }

    cout << "-- Datos del implemento --\n";
    cout << "ID: " << implemento->id << endl;
    cout << "Nombre: " << implemento->nombre << endl;
    //Bando es si son policias o ladrones o ambos
    cout << "Bando(Quien lo puede usar): " << implemento->bando << endl;
    //descripcion del comportamiento del implemento
    cout << "Descripcion: \n" << implemento->efecto << endl;
    //Cantidad de usos maximo 
    cout << "Durabilidad: \n" << implemento->durabilidad << endl; 
}

void MostrarInventario(ListaPersonajes& personajes) {
    Personaje* personaje = BuscarPersonaje(personajes);
    if(personaje == nullptr){
        return;
    }
    if (personaje->inventario == nullptr) {
        cout << "El inventario de " << personaje->nombre << " no tiene implementos\n";
        return;
    }
    cout << "Inventario de " << personaje->nombre << ":\n";

    ImplementoInventario* ItemActual = personaje->inventario;
    int contador = 1;
    while (ItemActual != nullptr){
        cout << "Implemento # " << contador << endl;
        cout << "ID base: " << ItemActual->itemCatalago->id << endl;
        cout << "Nombre: " << ItemActual->itemCatalago->nombre << endl;
        cout << "Descripcion: " << ItemActual->itemCatalago->efecto << endl;
        cout << "Bando: " << ItemActual->itemCatalago->bando << endl;
        cout << "Durabilidad: " << ItemActual->itemCatalago->durabilidad << endl;
        cout << "Usos restantes: " << ItemActual->usosRestantes << endl;
        ItemActual = ItemActual->siguiente;
        contador++;
    }
}

//UPDATE 
void ModificarImplementoCatalogo(ListaImplementosCatalogo &lista){
    ImplementoCatalogo* implemento = BuscarImplementoCatalogo(lista);
    if(implemento == nullptr){
        cout << "Implemento no encotrado. No se puede modificar.\n";
        return;
    }
    cout << "Su Implemento actualmente tiene las siguientes caracteristicas: \n";
    MostrarImplementoCatalogo(implemento);
    //Menu modificacion
    cout << "¿Que desea modificar?\n Seleccione una opcion valida:\n";
    cout << "1 -> Cambiar nombre\n" 
         << "2 -> Cambiar bando\n" 
         << "3 -> Cambiar id\n"
         << "4 -> Cambiar durabilidad\n"  
         << "5 -> Cambiar efecto\n"  
         << "6 -> Cancelar\n";
    int opcionModificar = ValidarEntero("Elija una de las opciones presentadas\n");
    switch (opcionModificar) {
    case 1: {
        implemento->nombre = ConseguirNombreValido(implemento->nombre);
        cout << "Nombre actualizado con exito\n";
        break;
    }
    
    case 2:{

        bool validoBando = false;
        int opcion_bando = 0;
        do{
            opcion_bando = ValidarEntero("Seleccione la opcion de nuevo estado (1-3): \nOpciones de estado:\n1 -> Policia\n2 -> Ladron\n3 -> Ambos\n"); 
            
            switch (opcion_bando)
            {
                case 1:
                implemento->bando = "Policia";
                validoBando = true;
                break;
                
                case 2:
                implemento->bando = "Ladron";
                validoBando = true;
                break;
                
                case 3:
                implemento->bando = "Ambos";
                validoBando = true;
                break;
                
                default:
                cout << "Opcion invalida, por favor ingresar un numero correcto.\n";
                break;
        }
    }while(!validoBando);
    cout << "Bando actualizado con exito\n";
    break;
    }
    
    case 3:{
        do{
            implemento->id = ValidarEntero("Ingrese el nuevo id de su implemento: ");
            if(ExisteIdI(lista , implemento->id)){
            cout << "El id ya existe en el catalogo, ingrese un nuevo id\n";   
            }else{
                break;
            }
        }while(true);
        cout << "ID actualizado con exito\n";
        break;
    }

    case 4:{
        implemento->durabilidad = ValidarEntero("Ingrese la nueva durabilidad del implemento: ");
        cout << "Durabilidad actualizado con exito\n";
        break;
    }

    case 5:{
        cout << "Ingrese la nueva descripcion de su implemento: \n";
        getline(cin, implemento->efecto);
        cout << "Efecto actualizado con exito\n";
        break;
    }
        
    case 6:{
        cout << "Modificacion Cancelada\n";
        break;
    }
    default:
    cout << "Opcion invalida, por favor ingresar un numero correcto.\n";
    break;
    }
}

void ModificarImplementoInventario(ListaPersonajes &personajes) {
    Personaje* personaje = BuscarPersonaje(personajes);
    
    if(personaje->inventario == nullptr) {
        cout << "El inventario de: " << personaje->nombre << "no tiene implementos\n";
        return;
    }
    MostrarInventario(personajes);
    ImplementoInventario* actual = nullptr;
    do{
        actual = personaje->inventario;
        int valorModificar = ValidarEntero("Ingrese el ID del implemento que desea modificar: ");
        while(actual != nullptr) {
            if (actual->itemCatalago->id == valorModificar) {
                cout << "Item a modificar: " << actual->itemCatalago->nombre << endl;
                actual->usosRestantes = ValidarEntero("Ingrese la cantidad de usos restantes: \n");
                cout << "Implemento en inventario modificado correctamente\n ";
                return;
            }
            actual = actual->siguiente;
        }
        cout << "No se encontro ningun implemento con ese ID, por favor ingresar uno que este en el inventario.";
    }while(actual == nullptr);
}
//DELETE 
void LiberarCatalogo(ListaImplementosCatalogo &catalogo) {
    ImplementoCatalogo* actual = catalogo.cabeza;
    while (actual != nullptr) {
        ImplementoCatalogo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    catalogo.cabeza = nullptr;
}

void EliminarImplementoCatalogo(ListaImplementosCatalogo &catalogo, ListaPersonajes &personajes){
    if(catalogo.cabeza == nullptr){
        cout << "No hay implementos en el catalogo. \n";
        return;
    }
    cout << "Busquemos tu implemento seleccionado a eliminar\n";
    ImplementoCatalogo* condenadoAEliminar = BuscarImplementoCatalogo(catalogo);
    if(condenadoAEliminar == nullptr){
        cout << "No se encontro el implemento, no se puede eliminar.\n";
        return;
    }
    //Eliminar el implemento de cada inventario 
    Personaje* personajeActual = personajes.cabeza;
    while (personajeActual != nullptr){
        ImplementoInventario* actual = personajeActual->inventario;
        ImplementoInventario* previo = nullptr;

        while (actual != nullptr) {
            if(actual->itemCatalago == condenadoAEliminar){
                //eliminacion del nodo del inventario 
                ImplementoInventario* borrar = actual;
                actual = actual->siguiente;
                if(previo == nullptr){
                    personajeActual->inventario = actual;
                }else{
                    previo->siguiente = actual;
                }
                delete borrar;
            }else{
                previo = actual;
                actual = actual->siguiente;
            }
        }
        personajeActual = personajeActual->siguiente;
    }
    //Eliminar implemento del catalogo
    ImplementoCatalogo* actual = catalogo.cabeza;
    ImplementoCatalogo* previo = nullptr;
    
    while (actual != nullptr && actual != condenadoAEliminar) {
        previo = actual;
        actual = actual->siguiente;
    }
    // Eliminar el nodo
    if (actual != nullptr) {
        if(previo == nullptr) {
            catalogo.cabeza = actual->siguiente; //en caso de ser la cabeza el condenado se pasa de una vez la cabeza al siguiente y delete actual
        } else {
        previo->siguiente = actual->siguiente;
    }

    delete actual;
    cout << "Implemento eliminado del catalogo y de todos los inventarios correctamente.\n";
    }
}

void EliminarImplementoInventario(ListaPersonajes &personajes){
    Personaje* personaje = BuscarPersonaje(personajes);
    if(personaje->inventario == nullptr){
        cout << "El inventario de: " << personaje->nombre << "no tiene items\n";
        return;
    }
    MostrarInventario(personajes);
    int valorEliminar = ValidarEntero("Ingrese el ID del implemento que desea eliminar: ");

    ImplementoInventario* actual = nullptr;
    ImplementoInventario* previo = nullptr;
    do{
        actual = personaje->inventario;
        while (actual != nullptr) {
            if (actual->itemCatalago->id == valorEliminar) {
                if (previo == nullptr) {
                    personaje->inventario = actual->siguiente;
                } else {
                    previo->siguiente = actual->siguiente;
                }
                delete actual;
                cout << "Implemento eliminado correctamente del inventario de " << personaje->nombre << "\n";
                return;
            }
            previo = actual;
            actual = actual->siguiente;
        }
        cout << "No se encontró el ID ingresado en el invetario, por favor ingresar uno correcto\n";
    }while(actual == nullptr);
}

//FUNCIONES CRUD PARA ESTACIONES 
//CREATE
void CrearEstacion(ListaEstaciones &lista){
    int id, oro;
    cout << "Vamos a crear una estacion!\n";
    //ID
    do{
        id = ValidarEntero("Ingrese ID para su estacion: ");
        if(ExisteIdE(lista, id)){
            cout<< "El id ingresado ya existe, por favor ingresar otro distinto.\n";
        }
    }while(ExisteIdE(lista, id));
    oro = ValidarEntero("Ingrese la cantidad de oro de la estacion: ");
    Estacion* agregar = new Estacion{id, oro, nullptr}; //las llaves asignan directo los datos me hubiese gustado saberlo antes ://
    if(lista.cabeza == nullptr){
        lista.cabeza = agregar;
    }else{
        Estacion *actual = lista.cabeza;
        while(actual->siguiente != nullptr){
            actual = actual->siguiente;
        }
        actual->siguiente = agregar;
    }
    cout << "Ha creado su Estacion correctamente." << endl;
}

//READ
void MostrarEstaciones(ListaEstaciones &lista) {
    if (lista.cabeza == nullptr) {
        cout << "No existen estacionees aun\n";
        return;
    }
    Estacion* actual = lista.cabeza;
    while (actual != nullptr) {
        cout << "ID: " << actual->id << "\nOro: " << actual->oro << endl;
        actual = actual->siguiente;
    }
}

Estacion* BuscarEstacion(ListaEstaciones& lista) {
    if (lista.cabeza == nullptr) {
        cout << "No hay estaciones, no hay nada que buscar\n";
        return nullptr;
    }
    Estacion* actual = nullptr;
    do{
        cout << "Estaciones disponibles:\n";
        MostrarEstaciones(lista);
        
        int valorBuscar = ValidarEntero("Ingrese el ID de la estación que desea seleccionar: ");
        actual = lista.cabeza;
        
        while (actual != nullptr) {
            if (actual->id == valorBuscar){
                break;
            }   
            actual = actual->siguiente;
        }
        cout << "No se encontró una estación con ese ID, por favor ingresar un id valido\n";
    }while(actual == nullptr);
    return actual;
}

//UPDATE
void ModificarEstacion(ListaEstaciones& lista) {
    Estacion* estacion = BuscarEstacion(lista);
    if (estacion == nullptr){
        return;
    }
    cout << "Datos de la estacion:\n ID: " << estacion->id << "\nOro: " << estacion->oro << endl;
    estacion->oro = ValidarEntero("Ingrese el nuevo valor de oro: ");
    cout << "Estación modificada correctamente.\n";
}

//DELETE 
void EliminarEstacion(ListaEstaciones& lista) {
    if (lista.cabeza == nullptr) {
        cout << "No hay estaciones creadas, no se puede eliminar.\n";
        return;
    }

    Estacion* eliminar = BuscarEstacion(lista);
    if (eliminar == nullptr) return;

    Estacion* actual = lista.cabeza;
    Estacion* previo = nullptr;

    while (actual != nullptr) {
        if (actual == eliminar) {
            if (previo == nullptr) {
                lista.cabeza = actual->siguiente;
            } else {
                previo->siguiente = actual->siguiente;
            }
            delete actual;
            cout << "Estación eliminada correctamente.\n";
            return;
        }
        previo = actual;
        actual = actual->siguiente;
    }
}

void LiberarEstaciones(ListaEstaciones& lista) {
    Estacion* actual = lista.cabeza;
    while (actual != nullptr) {
        Estacion* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    lista.cabeza = nullptr;
}

int main(){
    //Declaracion de Listas
    ListaPersonajes listaPersonajes;
    ListaEstaciones listaEstaciones;
    ListaImplementosCatalogo catalogo;

    int opcionmenubase;
    int opcioncrearomodificar;
    int opcioncrearomodificarestaciones;
    int opcioncrearomodificarimplementos;

    do {
        cout << "Bienvenido a policias y ladrones." << endl;
        cout << "Opciones:" << endl;
        cout << "1. modificar y crear personajes" << endl;
        cout << "2. ¿como jugar?" << endl;
        cout << "3. Ver personajes" << endl;
        cout << "4. modificar y ver estaciones" << endl;
        cout << "5. modificar, eliminar y ver implementos" << endl;
        cout << "7.Salir" << endl;

        opcionmenubase = ValidarEntero("Ingrese el numero de su opcion y pulse enter: ");

        if (opcionmenubase == 1) {

            cout << "¿Deseas crear, modificar, gestionar inventario o eliminar personajes?" << endl;
            cout << "1. Crear personaje" << endl;
            cout << "2. Modificar personaje" << endl;
            cout << "3. Eliminar personaje" << endl;
            cout << "4. Gestionar inventario de personaje" << endl;
            opcioncrearomodificar = ValidarEntero("Ingrese el numero de su opcion y pulse enter: ");
            if (opcioncrearomodificar == 1) {
                cout << "elegiste  crear personaje" << endl;
                CrearPersonaje(listaPersonajes);
            } else if (opcioncrearomodificar == 2) {
                cout << "elegiste  modificar personaje, por favor selecciona a quien modificar" << endl;
                ModificarPersonaje(listaPersonajes);
            } else if (opcioncrearomodificar == 3) {
                cout << "elegiste  eliminar personaje, selecciona cual eliminar" << endl;
                EliminarPersonaje(listaPersonajes);
            } else if (opcioncrearomodificar == 4) {
                cout << "elegiste gestionar inventario de personaje" << endl;
                cout << "1. Agregar implemento al inventario" << endl;
                cout << "2. Ver inventario" << endl;
                cout << "3. Modificar implemento" << endl;
                cout << "4. Eliminar implemento" << endl;
                
                int opcioninventario = ValidarEntero("Ingrese el numero de su opcion y pulse enter: ");
                
                if (opcioninventario == 1) {
                    AgregarImplementoAInvetario(listaPersonajes, catalogo);
                } else if (opcioninventario == 2) {
                    MostrarInventario(listaPersonajes);
                } else if (opcioninventario == 3) {
                    ModificarImplementoInventario(listaPersonajes);
                } else if (opcioninventario == 4) {
                    EliminarImplementoInventario(listaPersonajes);
                }else {
                    cout << "Opción no válida. Por favor selecciona 1, 2, 3 o 4" << endl;
                }
            }else {
                cout << "Opción no válida. Por favor selecciona 1, 2 o 3" << endl;
            }
        } else if (opcionmenubase == 2) {
            cout << "elegiste  ¿como jugar?" << endl;
            cout << " creas tus personajes, tus estaciones y te desplazas para conseguir el oro." << endl;

        } else if (opcionmenubase == 3) {
            cout << "ver personajes" << endl;
            MostrarPersonajes(listaPersonajes);

        } else if (opcionmenubase == 4) {
            cout << "elegiste  modificar y ver estaciones" << endl;
            cout << "1. crear estaciones" << endl;
            cout << "2. ver estaciones" << endl;
            cout << "3. modificar estaciones" << endl;
            cout << "4. eliminar estaciones" << endl;
            opcioncrearomodificarestaciones = ValidarEntero("Ingrese el numero de su opcion y pulse enter: ");

            if (opcioncrearomodificarestaciones == 1) {
                cout << "elegiste  crear estaciones" << endl;
                CrearEstacion(listaEstaciones);
            } else if (opcioncrearomodificarestaciones == 2) {
                cout << "elegiste   ver estaciones" << endl;
                MostrarEstaciones(listaEstaciones);
            } else if (opcioncrearomodificarestaciones == 3) {
                cout << "elegiste   modificar estaciones" << endl;
                ModificarEstacion(listaEstaciones);
            } else if (opcioncrearomodificarestaciones == 4) {
                cout << "elegiste eliminar estaciones. Selecciona cual eliminar" << endl;
                EliminarEstacion(listaEstaciones);
            } else {
                cout << "Opción no válida. Por favor selecciona 1,2,3 o 4" << endl;
            }

        } else if (opcionmenubase == 5) {
            cout << "elegiste implementos" << endl;
            cout << "¿Deseas crear o modificar implementos?" << endl;
            cout << "1. Crear implemento" << endl;
            cout << "2. Modificar implemento" << endl;
            cout << "3. Eliminar implemento" << endl;
            opcioncrearomodificarimplementos = ValidarEntero("Ingrese el numero de su opcion y pulse enter: ");
        
            if (opcioncrearomodificarimplementos == 1) {
                cout << "elegiste  crear implemento" << endl;
                CrearImplemento(catalogo);
            } else if (opcioncrearomodificarimplementos == 2) {
                cout << "elegiste  modificar implemento,por favor selecciona a quien modificar" << endl;
                ModificarImplementoCatalogo(catalogo);
            } else if (opcioncrearomodificarimplementos == 3) {
                cout << "elegiste  eliminar implemento, selecciona cual eliminar" << endl;
                EliminarImplementoCatalogo(catalogo, listaPersonajes);
            } else {
                cout << "Opción no válida. Por favor selecciona 1, 2 o 3" << endl;
            }

        } else if (opcionmenubase == 7) {
            cout << "Ya se libero la memoria. Gracias por su atencion" << endl;
            LiberarPersonajes(listaPersonajes);
            LiberarEstaciones(listaEstaciones);
            LiberarCatalogo(catalogo);

        } else {
            cout << "Opción no válida. Por favor selecciona un numero del menu." << endl;
        }

    } while (opcionmenubase != 7);

    return 0;
}

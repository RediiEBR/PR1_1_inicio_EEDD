//
// Created by rediiebr on 9/11/22.
//

#ifndef PR3_AVL_LISTADE_H
#define PR3_AVL_LISTADE_H
#include <string>
/**
 * @brief Definición de la clase de <b>lista doblemente enlazada</b>
 * @author José Manuel Martín Cerezo
 * */
template<typename T>
class ListaDe
{
    //defino la clase lista Nodo necesaria para esto
    template<typename U>
    class Nodo
    {
    public:
        U dato;
        Nodo *ant,*sig;
        Nodo(U &aDato, Nodo *aAnt, Nodo *aSig): dato(aDato), ant(aAnt), sig(aSig){}
    };
    Nodo<T> *cabecera,*cola;
public:
    class Iterador;

    int tamanio;
    class Iterador
    {
    public:
        Nodo<T> *nodo;
        Iterador(Nodo<T> *nodoant):nodo(nodoant){};
        bool fin(){return nodo==0;}
        void anterior(){nodo=nodo->ant;};
        void siguiente(){nodo=nodo->sig;}
        T& dato(){return nodo->dato;}
    };//FIXME falta hayAnterior y haySiguiente, es lo suyo comprobar

public:
    ///TODO cosas propias de la lista doblemente enlazada a partir de ahora
    ListaDe();
    ListaDe(const ListaDe<T>&origen);
    ListaDe<T> &operator=(const ListaDe<T>&orig);
    Iterador desdeInicio() const {return Iterador(cabecera);};
    Iterador desdeCola(){return Iterador(cola);};
    void insertarInicio( T& dato);
    void insertarFinal(T &dato);
    void insertar(Iterador &p,  T &dato);
    void borrarInicio();
    void borrarFin();
    void borrar(Iterador &i);
    ListaDe<T> concatena( const ListaDe<T> &ej);
    ListaDe<T> operator+( const ListaDe<T> &ej);
    int tam();

};



template<typename T>
ListaDe<T>::ListaDe(const ListaDe<T> &origen) {
    Nodo<T> *copia;
    this->cabecera=0;
    this->cola=0;
    copia=origen.cabecera;
    while(!(copia == 0))
    {
        insertarFinal(copia->dato);
    }
}

template<typename T>
ListaDe<T>& ListaDe<T>::operator=(const ListaDe<T> &orig) {

    Nodo<T> *p;
    this->cabecera=0;
    this->cola=0;
    p=this->cabecera;
    while(!(p==0))
    {
        borrarInicio(p->dato);
        p=p->sig;
    }
    ListaDe<T>::Iterador it= orig.desdeInicio();
    while(!it.fin())
    {
        insertarFinal(orig.dato);
        p=p->sig;
        it.siguiente();
    }
    return *this;
}

template<typename T>
void ListaDe<T>::insertarInicio( T &dato)
{
    Nodo<T> *nuevo;
    nuevo = new Nodo<T>(dato, 0, cabecera);

    if (cola == 0)
        cola = nuevo;

    if (cabecera != 0)
        cabecera->ant = nuevo;

    cabecera = nuevo;
    ++tamanio;
}

template<typename T>
void ListaDe<T>::insertarFinal(T &dato)
{
    Nodo<T> *nuevo = new Nodo<T>(dato,cola,0);
    tamanio++;
    if (cabecera == 0)
        cabecera = nuevo;
    if (cola != 0)
        cola->sig = nuevo;
    cola = nuevo;

}

template<typename T>
void ListaDe<T>::insertar(Iterador &p, T &dato)
{
    Nodo<T> *nuevo;

    nuevo = new Nodo<T>(dato, cola, 0);
    // Caso especial: si la lista estaba vac�a, poner la cabecera apuntando al nodo
    if (this->cabecera == 0)
        this->cabecera = nuevo;   //Idem al de Lista normal

    if (this->cola != 0)
        this->cola->sig = nuevo;

    this->cola = nuevo;
    ++this->tamanio;
}

template<typename T>
void ListaDe<T>::borrarInicio()
{
    Nodo<T> *borrar;
    borrar=this->cabecera;
    cabecera=cabecera->sig;
    delete borrar;
    if(this->cabecera!=0)
    {
        this->cabecera.ant=0;
    }
    else//estoy borrando el último nodo de la lista
    {
        cola=0;
    }
    tamanio--;
}
/**
 *
 * @tparam T
 */
template<typename T>
void ListaDe<T>::borrarFin()
{
    Nodo<T> *borrar;
    borrar=this->cola;
    cola=cabecera->ant;
    delete borrar;
    if(this->cola!=0)
    {
        this->cola.sig=0;
    }
    else
    {//caso especial: estoy borrando el último nodo de la lista
        cabecera=0;
    }
    tamanio--;
}

/**
 * función de borrado de un nodo concreto mediante el uso de iteradores
 * si está al inicio o al final estas funciones ya han sido implementadas, pero si se trata de un nodo intermedio hay que introducir el elemento conectando
 * los punteros de forma que quede correctamente añadido teniendo un puntero al anterior y otro al siguiente mientras que es accesible por los nodos entre los que se encuentra
 * @tparam T
 * @param i
 */
template<typename T>
void ListaDe<T>::borrar(ListaDe::Iterador &i)
{
    if (i.nodo != 0 && cabecera != 0){
        if (cabecera==cola){
            cabecera=cola= 0;
        } else {
            if (i.nodo == cabecera){
                //Aqui podemos llamar a borrar el nodo inicio
                borrarInicio();

            } else {
                if (i.nodo == cola){
                    //aqui podemos llamar a borrar por el final
                    borrarFin();
                } else{
                    //este caso es con un nodo intermedio
                    i.nodo->ant->sig=i.nodo->sig;
                    i.nodo->sig->ant=i.nodo->ant;
                }
            }
        }
        delete i;
        this->tamanio--;//actualizo el tamaño de la estructura
    }
}
/**
 * función para conectar 2 listas, creando una tercera lista a partir de la primera y la conexión de los elementos de la segunda
 * @tparam T
 * @param ej
 * @return una lista doblemente enlazada con los elementos de la actual(this) y a continuación los elementos de la lista a conectar(ej)
 */
template<typename T>
ListaDe<T> ListaDe<T>::concatena(const ListaDe<T> &ej)
{
    ListaDe<T> resultado(*this);//creo una lista auxiliar con el constructor de copia pasándome a mi mismo
    Nodo<T> *puntero=ej.cabecera;
    Iterador i=ej.desdeInicio();
    //genero un iterador para recorrer la estructura empezando por la lista que quiero conectar a la mía
    while (!i.fin()){
        resultado.insertarFinal(i.dato());
        i.siguiente();
        tamanio++;
        //voy conectando nodo a nodo la información de la lista objetivo
        //también desplazo el iterador
    }
    return resultado;//finalmente tengo la lista inicial con los elementos de la lista objetivo a continuación de la misma, lista para el retorno
}
/**
 * sobrecarca del <b>operador</b> de suma para la lista doblemente enlazada, hace lo mismo que la función concatena, de ahí la llamada directa
 * @tparam T
 * @param ej
 * @return
 */
template<typename T>
ListaDe<T> ListaDe<T>::operator+(const ListaDe<T> &ej) {
    return this->concatena(ej);
}
/**
 * función pública de lectura de la propiedad tamaño de la lista doblemente enlazada
 * @tparam T
 * @return
 */
template<typename T>
int ListaDe<T>::tam() {
    return this->tamanio;
}
/**
 * constructor por defecto para la lista doblemente enlazada
 * inicializa la cabecera y la cola apuntando a nullptr mientras que el tamaño es 0 al no asignarse ningún nodo en su construcción
 * @tparam T
 */
template<typename T>
ListaDe<T>::ListaDe():cabecera(0),cola(0),tamanio(0){}


#endif //PR3_AVL_LISTADE_H
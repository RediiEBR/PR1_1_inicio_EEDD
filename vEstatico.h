#ifndef IMAGENES_VESTATICO_H
#define IMAGENES_VESTATICO_H
#include <string>

template < typename T >
/**
 * <h1>Definicion de vector estatico</h1>
 * @tparam T
 */
class vEstatico
{
private:
    unsigned int tama = 1;
    T* memoria;
    T*algClasico( int ini , int fin , T & dato );
    int algClasicoPos( int ini,  int fin, T & dato );

public:
    vEstatico();
    vEstatico( unsigned int tam );
    vEstatico( const vEstatico < T > & original );
    vEstatico( const vEstatico < T > & original , unsigned int inicio , unsigned int numelementos );
    vEstatico < T > & operator=( const vEstatico < T > & original );
    T& operator [] ( unsigned int pos );
    void asigna ( const T &dato , unsigned int pos );
    T recupera ( unsigned int pos );
    void ordenar();
    void revertir();
    unsigned int getTam();
    T * buscaBin( T & dato , unsigned int ini , unsigned int fin );//buscamos por búsqueda binaria
    int buscaBinPos( T & dato , int ini , int fin ); //busqueda binaria retornando la posicion
    ~vEstatico();
};

template < typename T >
int vEstatico<T>::algClasicoPos( int ini , int fin , T & dato )
{
    for (int i = ini; i < fin; ++i)
    {
        if(memoria[i] == dato) return i;
    }
    return -1;
}

template < typename T >
int vEstatico<T>::buscaBinPos( T & dato , int ini , int fin )
{

    if(fin - ini <= 2 )//umbral
    {
        return algClasicoPos(ini , fin , dato );
    }
    int mitad = fin - ini / 2;
    if( memoria[mitad ]  == dato) return  mitad ;
    if( memoria[ mitad ] < dato) return buscaBinPos(dato , ini , mitad - 1 );
    else return buscaBinPos(dato,mitad +1, fin);
}


template<typename T>
T *vEstatico<T>::algClasico( int ini , int fin , T & dato )
{
    for (int i = ini; i < fin; ++i)
    {
        if(memoria[i] == dato) return memoria[i];
    }
    return nullptr;
}

template<typename T>
T* vEstatico<T>::buscaBin(T & dato , unsigned int ini , unsigned int fin )
{
    if(fin - ini <= 2 )//umbral
    {
        return algClasico(ini , fin , dato );
    }
    unsigned int mitad = fin - ini / 2;
    if( memoria[mitad ]  == dato ) return memoria[ mitad ];
    if( memoria[ mitad ] < dato ) return buscaBin(dato , ini , mitad - 1 );
    else return buscaBin( dato ,mitad +1 , fin );
    
}


template<typename T>
vEstatico<T> &vEstatico<T>::operator=( const vEstatico < T > & original )
{
    if( original != * this )
    {
        delete [] memoria;
        this -> tama = original . tama;
        this -> memoria = new T [ this -> tama ];
        for ( int i = 0; i < tama ; ++i )
        {
            memoria [ i ] = original . memoria[ i ];
        }

    }

    return * this ;
}


template <typename T>
vEstatico< T >::vEstatico(): tama(100) , memoria(new T[tama]) {for (int i = 0; i < tama ; ++i) {memoria[i]=T();}}
template<typename T>
vEstatico<T>::vEstatico(unsigned int tam): tama(tam),memoria(new T[tama]){}
template<typename T>
vEstatico<T>::vEstatico(const vEstatico<T> &original):tama(original.tama){for (int i = 0; i < original.tama ; ++i) {this->memoria[i]=original.memoria[i];}}//constructor de copia
template<typename T>
vEstatico<T>::vEstatico(const vEstatico<T> &original, unsigned int inicio, unsigned int numelementos) : tama(numelementos)
{
    if(inicio+numelementos>=this->tama-1)
    {
        throw std::out_of_range("vEstatatico<T>::vEstatico(const v original, unsigned int inicio): fuera de rango");
    }
    this->memoria = new T[numelementos];
    for (unsigned int i = inicio,j=0; i < inicio+numelementos; ++i,++j)
    {
        this->memoria[j] = original.memoria[i];
    }
    
}

template<typename T>
void vEstatico<T>::asigna(const T &dato, unsigned int pos)
{
    if(pos>(tama)-1)
    {
        throw std :: out_of_range( "vEstatatico<T>::asigna(const T& dato, unsigned int pos): fuera de rango" ) ;
    }
    else
    {
        this -> memoria [ pos ] = dato;
    }
}
template<typename T>
T vEstatico<T>::recupera( unsigned int pos )
{
    if(pos>this->tama)//capturamos el error primero, sino no hay problema
    {
        throw std::out_of_range( "vEstatatico<T>::recupera( unsigned int pos): fuera de rango" );
    }
    return memoria[ pos ];
}
template<typename T>
void vEstatico<T>::ordenar(){ std :: sort( memoria , memoria + tama ) ; }
template<typename T>
void vEstatico<T>::revertir() { std :: reverse( this->memoria , this->memoria+tama ) ; }
template<typename T>

vEstatico<T>::~vEstatico()
{
    delete [] memoria;
}
template<typename T>
T &vEstatico<T>::operator[](unsigned int pos) {return memoria[pos];}
template<typename T>
unsigned int vEstatico<T>::getTam() {return this -> tama;}
#endif //IMAGENES_VESTATICO_H

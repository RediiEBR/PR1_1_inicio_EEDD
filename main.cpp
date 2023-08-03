#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include "vEstatico.h"
#include "Imagen.h"


int main()
{
    int v[4];
    std::cout<<v[17];
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string id = "";
    std::string email="";
    std::string nombre="";
    int tam = 0;
    int dia = 0;
    int mes = 0;
    int anno = 0;
    std::string etiquetas="";

    vEstatico<Imagen> vImgs(10000);
    int j = 0;
    is.open("../imagenes_v1.csv"); //carpeta de proyecto
    if ( is.good() )
    {


        auto start = std::chrono::steady_clock::now();
        std::string resultado;
        while ( getline(is, fila ) )
        {

            //¿Se ha leído una nueva fila?
            if (fila!="")
            {

                columnas.str(fila);

                //formato de fila: id;email;nombre;tam;fecha;etiquetas

                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas,email,';');
                getline(columnas,nombre,';');

                columnas >> tam;   //las secuencia numéricas se leen y trasforman directamente
                columnas.ignore(); //omitimos carácter ';' siguiente

                columnas >> dia; columnas.ignore();
                columnas >> mes; columnas.ignore();
                columnas >> anno; columnas.ignore();

                getline(columnas,etiquetas,';');

                fila="";
                columnas.clear();
                resultado.append(std::to_string(++contador));
                resultado.append(" Imagen: ( ID="+ id);
                resultado.append(" Email=" + email );
                resultado.append(" Fichero=" + nombre);
                resultado.append(" Tam=" + std::to_string(tam));
                resultado.append( " Fecha=" + std::to_string(dia)+ "/" + std::to_string(mes) + "/" + std::to_string(anno));
                resultado.append(" Etiquetas=" + etiquetas+")\n");
                Fecha fecha(dia,mes,anno);
                vImgs.asigna(Imagen(id,email,nombre,tam,fecha,etiquetas),j);
                ++j;
            }
        }

        is.close();
        //ejercicio 1
        for (int i = 0; i < 50 ; ++i)
        {
            cout << vImgs.recupera(i).toCSV(); ;
        }
        //ejercicio 2
        vImgs.revertir();
        //ejercicio 3
        vImgs.ordenar();
        for (int i = 0; i < 20 ; ++i)
        {
            cout << vImgs.recupera(i).toCSV();
        }
        //ejercicio 4
        Fecha date(5,8,2020);
        Imagen abuscar((string &) "527683076", (string &)"bernadine_goyette@yahoo.com", (string &)"user95683.jpeg", 249307, date, (string &)"musculo");

        Imagen * ressultado = vImgs.buscaBin(abuscar,0,vImgs.getTam());
        if(ressultado == nullptr)
        {
            cout<<"no encontrada"<<"\n";
        }
        Imagen afallar((string &) "527683076527683076", (string &)"bernadine_goyette@yahoo.com", (string &)"user95683.jpeg", 249307, date, (string &)"musculo");

        Imagen * notFound = vImgs.buscaBin(afallar,0,vImgs.getTam());
        if(notFound == nullptr)
        {
            cout<<"no encontrada"<<"\n";
        }
        //527683076 id valido
        //527683076527683076 no valido

        //std::cout <<resultado;
        auto final = std::chrono::steady_clock::now();
        std::chrono::duration<double> tiempo = final-start;
        std::cout << "Tiempo ejecucion: " << tiempo.count() << " segs." << std::endl;

    }

    else
    {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
}
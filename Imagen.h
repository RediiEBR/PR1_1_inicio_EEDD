#ifndef IMAGENES_IMAGEN_H
#define IMAGENES_IMAGEN_H
#include <string>
#include "fecha.h"
/**
 * Implementacion de la primera version de la clase Imagen
 */
class Imagen
{
private:
    std::string id;
    std::string email;
    std::string nombre;
    int tam;
    Fecha date;
    std::string etiquetas;

public:
    /**
     * <h3>bool operator<(const Imagen &original)</h3><hr/>
     * @param original como la imagen de la cual extraemos el id, tanto como de la nuestra como criterio de mayor o menor
     * @return true si this es mas peque&ntilde;a que la imagen a comparar
     */
    bool operator<(const Imagen &original);
    /**
    * <h3>bool operator<(const Imagen &original)</h3><hr/>
    * @param original como la imagen de la cual extraemos el id, tanto como de la nuestra como criterio de mayor o menor
    * @return true si original es mas peque&ntilde;a que this
    */
    bool operator>(const Imagen &original);
    /**
     * <h3>bool operator==(const Imagen &original)</h3><hr/>
     * @param original como la imagen a comparar con this, en este caso se comparan si son exactamente iguales
     * @return si son iguales en todos los campos las dos im&aacute;genes a comparar.
     */
    bool operator==(const Imagen &original);
    Imagen();
    Imagen(std::string &nid,std::string &nmail,std::string &nNombre,int ntam, Fecha &ndate, std::string &netiquetas);
    Imagen(const Imagen &original);
    std::string toCSV();
};


#endif //IMAGENES_IMAGEN_H

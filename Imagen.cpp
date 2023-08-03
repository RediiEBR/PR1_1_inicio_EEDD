#include "Imagen.h"
Imagen::Imagen(const Imagen &original)
:id(original.id),email(original.id),nombre(original.nombre),tam(original.tam),date(original.date),etiquetas(original.etiquetas){}
Imagen::Imagen():id(),email(),nombre(),tam(1),date(),etiquetas(){}
Imagen::Imagen(std::string &nid,std::string &nmail,std::string &nNombre,int ntam, Fecha &ndate, std::string &netiquetas):id(nid),email(nmail),nombre(nNombre),tam(ntam),date(ndate),etiquetas(netiquetas){}

bool Imagen::operator==(const Imagen &original)
{
    return this->id == original.id && this->email == original.email && this->tam == original.tam && this->date.verDia() == original.date.verDia()
    && this->date.verMes()==original.date.verMes() && this->date.verAnio() == original.date.verAnio() && this->etiquetas==original.etiquetas;
}

bool Imagen::operator>(const Imagen &original)
{
    int idOrig = stoi(original.id);
    int idThis = stoi(this->id);
    return idThis>idOrig;
}

bool Imagen::operator<(const Imagen &original){return !(*this == original || *this > original);}

std::string Imagen::toCSV()
{
    std::string retur;
    retur.append(" Imagen: ( ID="+ this -> id);
    retur.append(" Email=" + this->email );
    retur.append(" Fichero=" + this->nombre);
    retur.append(" Tam=" + std::to_string(this->tam));
    retur.append( " Fecha=" + std::to_string(this->date.verDia())+ "/" + std::to_string(this->date.verMes()) + "/" + std::to_string(this->date.verAnio()));
    retur.append(" Etiquetas=" + this->etiquetas+")\n");
    return retur;
}

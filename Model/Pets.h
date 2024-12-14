#pragma once
#include <string>
using namespace std;

class Pets {
private:
    string nombre_mascota, especie, raza;
    int cedula_owner;

public:
    Pets() : nombre_mascota(""), especie(""), raza(""), cedula_owner(0) {}
    Pets(string nombre_mascota, string especie, string raza, int cedula_owner)
        : nombre_mascota(nombre_mascota), especie(especie), raza(raza), cedula_owner(cedula_owner) {}

    int getCedula_Owner() const { return cedula_owner; }
    void setCedula_Owner(int cedula_owner) { this->cedula_owner = cedula_owner; }

    string getNombre_mascota() const { return nombre_mascota; }
    void setNombre_mascota(const string& nombre_mascota) { this->nombre_mascota = nombre_mascota; }

    string getEspecie() const { return especie; }
    void setEspecie(const string& especie) { this->especie = especie; }

    string getRaza() const { return raza; }
    void setRaza(const string& raza) { this->raza = raza; }
};

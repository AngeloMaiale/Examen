#pragma once
#include <string>
using namespace std;

class Owners {
private:
    string nombre, apellido, email;
    int cedula;

public:
    Owners() : nombre(""), apellido(""), email(""), cedula(0) {}
    Owners(string nombre, string apellido, string email, int cedula_owner)
        : nombre(nombre), apellido(apellido), email(email), cedula(cedula_owner) {}

    int getCedula_Owner() const { return cedula; }
    void setCedula_Owner(int cedula_owner) { this->cedula= cedula_owner; }

    string getNombre() const { return nombre; }
    void setNombre(const string& nombre_mascota) { this->nombre = nombre_mascota; }

    string getApellido() const { return apellido; }
    void setApellido(const string& apellido) { this->apellido = apellido; }

    string getEmail() const { return email; }
    void setEmail(const string& email) { this->email = email; }
};
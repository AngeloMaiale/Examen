#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../Model/Owners.h"
using namespace std;

void leerOwners(const string& nombreArchivo, Owners*& owners, int& numOwners) {
    ifstream file(nombreArchivo);
    string line;

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    numOwners = 0;
    while (getline(file, line)) {
        numOwners++;
    }

    file.clear(); 
    file.seekg(0);

    owners = new Owners[numOwners];

    getline(file, line); 
    int i = 0;
    while (getline(file, line)) {
        istringstream ss(line);
        string nombre, apellido, email;
        int cedula_owner;

        getline(ss, nombre, ',');
        getline(ss, apellido, ',');
        getline(ss, email, ',');
        ss >> cedula_owner; ss.ignore();

        owners[i].setNombre(nombre);
        owners[i].setApellido(apellido);
        owners[i].setEmail(email);
        owners[i].setCedula_Owner(cedula_owner);

        i++;
    }
    file.close();
}

void InsertarOwner(string nombreArchivo) {
    bool SoN;
    ofstream archivo(nombreArchivo, ios::app);
    Owners o;

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    cout << "Ingrese los detalles del dueño:\n";

    cout << "Nombre: ";
    string nombre;
    cin.ignore();
    getline(cin, nombre);
    o.setNombre(nombre);

    cout << "Apellido: ";
    string apellido;
    getline(cin, apellido);
    o.setApellido(apellido);

    cout << "Email: ";
    string email;
    getline(cin, email);
    o.setEmail(email);

    cout << "Cedula: ";
    int cedula_owner;
    cin >> cedula_owner;
    o.setCedula_Owner(cedula_owner);

    archivo << o.getNombre() << "," << o.getApellido() << "," << o.getEmail() << "," << o.getCedula_Owner() << "\n";
    archivo.close();
    cout << "Linea insertada en " << nombreArchivo << endl;
}

void BorrarDuenio(int cedula, const string& archivoOwners, const string& archivoPets) {
    string line;
    bool foundOwner = false;

    ifstream inputFileOwners(archivoOwners);
    ofstream tempFileOwners("tempOwners.csv");
    if (!inputFileOwners.is_open() || !tempFileOwners.is_open()) {
        cerr << "Error al abrir los archivos de dueños." << endl;
        return;
    }

    while (getline(inputFileOwners, line)) {
        stringstream ss(line);
        string nombre, apellido, email;
        int cedula_owner;

        getline(ss, nombre, ',');
        getline(ss, apellido, ',');
        getline(ss, email, ',');
        ss >> cedula_owner;

        if (cedula_owner == cedula) {
            foundOwner = true;
        } else {
            tempFileOwners << line << endl;
        }
    }
    inputFileOwners.close();
    tempFileOwners.close();

    ifstream inputFilePets(archivoPets);
    ofstream tempFilePets("tempPets.csv");
    if (!inputFilePets.is_open() || !tempFilePets.is_open()) {
        cerr << "Error al abrir los archivos de mascotas." << endl;
        return;
    }

    while (getline(inputFilePets, line)) {
        stringstream ss(line);
        string nombre_mascota, especie, raza;
        int cedula_owner;

        getline(ss, nombre_mascota, ',');
        getline(ss, especie, ',');
        getline(ss, raza, ',');
        ss >> cedula_owner;

        if (cedula_owner != cedula) {
            tempFilePets << line << endl;
        }
    }
    inputFilePets.close();
    tempFilePets.close();

    if (foundOwner) {
        if (remove(archivoOwners.c_str()) != 0) {
            cerr << "Error al eliminar el archivo original de dueños." << endl;
            return;
        }
        if (rename("tempOwners.csv", archivoOwners.c_str()) != 0) {
            cerr << "Error al renombrar el archivo temporal de dueños." << endl;
            return;
        }
        cout << "El dueño ha sido borrado exitosamente." << endl;
    } else {
        cerr << "No se encontro un dueño con la cedula proporcionada." << endl;
        remove("tempOwners.csv");
    }

    if (remove(archivoPets.c_str()) != 0) {
        cerr << "Error al eliminar el archivo original de mascotas." << endl;
        return;
    }
    if (rename("tempPets.csv", archivoPets.c_str()) != 0) {
        cerr << "Error al renombrar el archivo temporal de mascotas." << endl;
    } else {
        cout << "Las mascotas del dueño han sido borradas exitosamente." << endl;
    }
}

#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void actualizarOwner(int cedula, const string& archivoOwners) {
    ifstream fileOwners(archivoOwners);
    ofstream tempFile("tempOwners.csv");
    string line;
    bool foundOwner = false;

    if (!fileOwners.is_open() || !tempFile.is_open()) {
        cerr << "Error al abrir los archivos." << endl;
        return;
    }

    while (getline(fileOwners, line)) {
        stringstream ss(line);
        string nombre, apellido, email;
        int cedula_owner;

        getline(ss, nombre, ',');
        getline(ss, apellido, ',');
        getline(ss, email, ',');
        ss >> cedula_owner;

        if (cedula_owner == cedula) {
            foundOwner = true;

            cout << "Ingrese los nuevos datos del dueño (exceptuando la cedula):\n";
            cout << "Nombre actual: " << nombre << "\n";
            cout << "Nuevo nombre: ";
            getline(cin, nombre);
            cout << "Apellido actual: " << apellido << "\n";
            cout << "Nuevo apellido: ";
            getline(cin, apellido);
            cout << "Email actual: " << email << "\n";
            cout << "Nuevo email: ";
            getline(cin, email);

            tempFile << nombre << "," << apellido << "," << email << "," << cedula_owner << "\n";
        } else {
            tempFile << line << "\n";
        }
    }
    fileOwners.close();
    tempFile.close();

    if (!foundOwner) {
        cout << "No se encontro un dueño con la cedula proporcionada." << endl;
        remove("tempOwners.csv");
        return;
    }

    if (remove(archivoOwners.c_str()) != 0) {
        cerr << "Error al eliminar el archivo original de dueños." << endl;
        return;
    }
    if (rename("tempOwners.csv", archivoOwners.c_str()) != 0) {
        cerr << "Error al renombrar el archivo temporal de dueños." << endl;
    } else {
        cout << "Los datos del dueño han sido modificados exitosamente." << endl;
    }
}



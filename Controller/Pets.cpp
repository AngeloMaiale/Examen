#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../Model/Pets.h"
#include "../Model/Owners.h"
using namespace std;

void leerPets(const string& nombreArchivo, Pets*& pets, int& numPets) {
    ifstream file(nombreArchivo);
    string line;

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    numPets = 0;
    while (getline(file, line)) {
        numPets++;
    }

    file.clear(); 
    file.seekg(0);

    pets = new Pets[numPets];

    getline(file, line); 
    int i = 0;
    while (getline(file, line)) {
        istringstream ss(line);
        string nombre_mascota, especie, raza;
        int cedula_owner;

        getline(ss, nombre_mascota, ',');
        getline(ss, especie, ',');
        getline(ss, raza, ',');
        ss >> cedula_owner; ss.ignore();

        pets[i].setNombre_mascota(nombre_mascota);
        pets[i].setEspecie(especie);
        pets[i].setRaza(raza);
        pets[i].setCedula_Owner(cedula_owner);

        i++;
    }
    file.close();
}

void InsertarMascota(string nombreArchivo) {
    bool SoN;
    ofstream archivo(nombreArchivo, ios::app);
    Pets p;
    
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    cout << "Ingrese los detalles de la mascota:\n";

    cout << "Nombre de la mascota: ";
    string nombre_mascota;
    cin.ignore();
    getline(cin, nombre_mascota);
    p.setNombre_mascota(nombre_mascota);

    cout << "Especie: ";
    string especie;
    getline(cin, especie);
    p.setEspecie(especie);

    cout << "Raza: ";
    string raza;
    getline(cin, raza);
    p.setRaza(raza);

    cout << "Cedula del dueño: ";
    int cedula_owner;
    cin >> cedula_owner;
    p.setCedula_Owner(cedula_owner);

    archivo << p.getNombre_mascota() << "," << p.getEspecie() << "," << p.getRaza() << "," << p.getCedula_Owner() << "\n";
    archivo.close();
    cout << "Linea insertada en " << nombreArchivo << endl;
}

void BorrarMascota(int cedula, const string& nombreArchivo) {
    ifstream file(nombreArchivo);
    string line;
    int numMascotas = 0;

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }
    while (getline(file, line)) {
        istringstream ss(line);
        string nombre_mascota, especie, raza;
        int cedula_owner;
        getline(ss, nombre_mascota, ',');
        getline(ss, especie, ',');
        getline(ss, raza, ',');
        ss >> cedula_owner;

        if (cedula_owner == cedula) {
            numMascotas++;
        }
    }
    file.clear();
    file.seekg(0);

    Pets* mascotas = new Pets[numMascotas];
    int index = 0;

    while (getline(file, line)) {
        istringstream ss(line);
        string nombre_mascota, especie, raza;
        int cedula_owner;
        getline(ss, nombre_mascota, ',');
        getline(ss, especie, ',');
        getline(ss, raza, ',');
        ss >> cedula_owner;

        if (cedula_owner == cedula) {
            mascotas[index++] = Pets(nombre_mascota, especie, raza, cedula_owner);
        }
    }
    file.close();

    if (index == 0) {
        cout << "No se encontraron mascotas para la cedula proporcionada." << endl;
        delete[] mascotas;
        return;
    }

    cout << "Mascotas encontradas para la cedula " << cedula << ":\n";
    for (int i = 0; i < index; ++i) {
        cout << i + 1 << ". " << mascotas[i].getNombre_mascota() << " (Especie: " << mascotas[i].getEspecie()
             << ", Raza: " << mascotas[i].getRaza() << ")\n";
    }

    int opcion;
    cout << "Ingrese el número de la mascota que desea borrar: ";
    cin >> opcion;

    if (opcion < 1 || opcion > index) {
        cout << "Opcion inválida." << endl;
        delete[] mascotas;
        return;
    }

    string nombreMascotaABorrar = mascotas[opcion - 1].getNombre_mascota();

    ifstream inputFile(nombreArchivo);
    ofstream tempFile("temp.csv");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Error al abrir los archivos." << endl;
        delete[] mascotas;
        return;
    }

    while (getline(inputFile, line)) {
        if (line.find(nombreMascotaABorrar) == string::npos) {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    if (remove(nombreArchivo.c_str()) != 0) {
        cerr << "Error al eliminar el archivo original." << endl;
        delete[] mascotas;
        return;
    }
    if (rename("temp.csv", nombreArchivo.c_str()) != 0) {
        cerr << "Error al renombrar el archivo temporal." << endl;
    } else {
        cout << "La mascota ha sido borrada exitosamente." << endl;
    }

    delete[] mascotas;
}

void mostrarDatos(int cedula, const string& archivoOwners, const string& archivoPets) {
    ifstream fileOwners(archivoOwners);
    ifstream filePets(archivoPets);
    string line;
    bool foundOwner = false;

    if (!fileOwners.is_open()) {
        cerr << "Error al abrir el archivo " << archivoOwners << endl;
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
            Owners owner(nombre, apellido, email, cedula_owner);
            cout << "Datos del dueño:\n";
            cout << "Nombre: " << owner.getNombre() << "\n";
            cout << "Apellido: " << owner.getApellido() << "\n";
            cout << "Email: " << owner.getEmail() << "\n";
            cout << "Cedula: " << owner.getCedula_Owner() << "\n";
            foundOwner = true;
            break;
        }
    }
    fileOwners.close();

    if (!foundOwner) {
        cout << "No se encontro un dueño con la cedula proporcionada." << endl;
        return;
    }

    if (!filePets.is_open()) {
        cerr << "Error al abrir el archivo " << archivoPets << endl;
        return;
    }

    bool foundPets = false;
    cout << "\nMascotas del dueño:\n";
    while (getline(filePets, line)) {
        stringstream ss(line);
        string nombre_mascota, especie, raza;
        int cedula_owner;

        getline(ss, nombre_mascota, ',');
        getline(ss, especie, ',');
        getline(ss, raza, ',');
        ss >> cedula_owner;

        if (cedula_owner == cedula) {
            Pets pet(nombre_mascota, especie, raza, cedula_owner);
            cout << "Nombre de la mascota: " << pet.getNombre_mascota() << "\n";
            cout << "Especie: " << pet.getEspecie() << "\n";
            cout << "Raza: " << pet.getRaza() << "\n";
            cout << "Cedula del dueño: " << pet.getCedula_Owner() << "\n";
            cout << "--------------------------" << endl;
            foundPets = true;
        }
    }
    filePets.close();

    if (!foundPets) {
        cout << "No se encontraron mascotas para la cedula proporcionada." << endl;
    }
}

void actualizarPets(int cedula, const string& archivoPets) {
    ifstream filePets(archivoPets);
    string line;
    int numMascotas = 0;

    if (!filePets.is_open()) {
        cerr << "Error al abrir el archivo " << archivoPets << endl;
        return;
    }

    while (getline(filePets, line)) {
        istringstream ss(line);
        string nombre_mascota, especie, raza;
        int cedula_owner;
        getline(ss, nombre_mascota, ',');
        getline(ss, especie, ',');
        getline(ss, raza, ',');
        ss >> cedula_owner;

        if (cedula_owner == cedula) {
            numMascotas++;
        }
    }
    filePets.clear();
    filePets.seekg(0);

    if (numMascotas == 0) {
        cout << "No se encontraron mascotas para la cedula proporcionada." << endl;
        return;
    }

    Pets* mascotas = new Pets[numMascotas];
    int index = 0;

    while (getline(filePets, line)) {
        istringstream ss(line);
        string nombre_mascota, especie, raza;
        int cedula_owner;
        getline(ss, nombre_mascota, ',');
        getline(ss, especie, ',');
        getline(ss, raza, ',');
        ss >> cedula_owner;

        if (cedula_owner == cedula) {
            mascotas[index++] = Pets(nombre_mascota, especie, raza, cedula_owner);
        }
    }
    filePets.close();

    cout << "Mascotas encontradas para la cedula " << cedula << ":\n";
    for (int i = 0; i < index; ++i) {
        cout << i + 1 << ". " << mascotas[i].getNombre_mascota() << " (Especie: " << mascotas[i].getEspecie()
             << ", Raza: " << mascotas[i].getRaza() << ")\n";
    }

    int opcion;
    cout << "Ingrese el número de la mascota que desea modificar: ";
    cin >> opcion;

    if (opcion < 1 || opcion > index) {
        cout << "Opcion inválida." << endl;
        delete[] mascotas;
        return;
    }

    Pets& mascotaSeleccionada = mascotas[opcion - 1];

    cout << "Ingrese los nuevos datos de la mascota (exceptuando la cedula del dueño):\n";
    cout << "Nombre actual: " << mascotaSeleccionada.getNombre_mascota() << "\n";
    cout << "Nuevo nombre: ";
    cin.ignore();
    string nuevoNombre;
    getline(cin, nuevoNombre);
    mascotaSeleccionada.setNombre_mascota(nuevoNombre);

    cout << "Especie actual: " << mascotaSeleccionada.getEspecie() << "\n";
    cout << "Nueva especie: ";
    string nuevaEspecie;
    getline(cin, nuevaEspecie);
    mascotaSeleccionada.setEspecie(nuevaEspecie);

    cout << "Raza actual: " << mascotaSeleccionada.getRaza() << "\n";
    cout << "Nueva raza: ";
    string nuevaRaza;
    getline(cin, nuevaRaza);
    mascotaSeleccionada.setRaza(nuevaRaza);

    ifstream inputFile(archivoPets);
    ofstream tempFile("tempPets.csv");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Error al abrir los archivos." << endl;
        delete[] mascotas;
        return;
    }

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string nombre_mascota, especie, raza;
        int cedula_owner;
        getline(ss, nombre_mascota, ',');
        getline(ss, especie, ',');
        getline(ss, raza, ',');
        ss >> cedula_owner;

        if (cedula_owner == cedula && nombre_mascota == mascotaSeleccionada.getNombre_mascota()) {
            tempFile << mascotaSeleccionada.getNombre_mascota() << "," << mascotaSeleccionada.getEspecie() << ","
                     << mascotaSeleccionada.getRaza() << "," << mascotaSeleccionada.getCedula_Owner() << "\n";
        } else {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    if (remove(archivoPets.c_str()) != 0) {
        cerr << "Error al eliminar el archivo original de mascotas." << endl;
        delete[] mascotas;
        return;
    }
    if (rename("tempPets.csv", archivoPets.c_str()) != 0) {
        cerr << "Error al renombrar el archivo temporal de mascotas." << endl;
    } else {
        cout << "Los datos de la mascota han sido modificados exitosamente." << endl;
    }

    delete[] mascotas;
}

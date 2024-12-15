#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "../Model/Owners.h"
#include "../Model/Pets.h"
#include "../Controller/Owners.cpp"
#include "../Controller/Pets.cpp"
using namespace std;

void Consola() {
    string nombreArchivoPets = "Pets.csv";
    string nombreArchivoOwners = "Owners.csv";
    bool wh=true;
    char confirmar = 0;
    bool cambiosRealizados = false;

    Pets* pets = nullptr;
    int numPets = 0;

    Owners* owners = nullptr;
    int numOwners = 0; 
    int CedulaB = 0; 

    leerPets(nombreArchivoPets, pets, numPets);
    leerOwners(nombreArchivoOwners, owners, numOwners);
    do {
        cout << "Que quiere hacer: " << endl;
        cout << "1. Insertar mascota" << endl;
        cout << "2. Borrar mascota, o duenio y mascotas" << endl;
        cout << "3. Consultar duenio y sus mascotas" << endl;
        cout << "4. Actualizar mascota o duenio" <<endl;
        cout << "5. Cerrar el programa" <<endl;
        int opcion=0;
        int opcionA=0;
        int Nlinea=0;
        int ind=0;
        string ValorN;
        cin >> opcion;
        bool SoN;
        switch (opcion) {
        case 1: 
            InsertarMascota(nombreArchivoPets);
            InsertarOwner(nombreArchivoOwners);
            continue;
        case 2: 
            cout<<"Que desea hacer: "<<endl;
            cout<<"1. Borrar mascota"<<endl;
            cout<<"2. Borrar duenio y mascotas"<<endl;
            cin>>opcionA;
            switch(opcionA){
                case 1:
                    cout<<"Ingrese la cedula del duenio de las mascotas:"<<endl;
                    cin>>CedulaB;
                    BorrarMascota(CedulaB,nombreArchivoPets);
                    continue;
                case 2:
                    cout<<"Ingrese la cedula del duenio: "<<endl;
                    cin>>CedulaB;
                    BorrarDuenio(CedulaB,nombreArchivoOwners,nombreArchivoPets);
                    continue;
            }
            
            continue;
        case 3: 
            cout<<"Ingrese la cedula del duenio: ";
            cin>>CedulaB;  
            mostrarDatos(CedulaB,nombreArchivoOwners,nombreArchivoPets);
            continue;
        case 4:
            cout<<"Desea actualizar los datos de la mascota o del duenio: "<<endl;
            cout<<"1. Duenio"<<endl;
            cout<<"2. Mascota"<<endl;
            cin>>opcionA;
            switch(opcionA){
                case 1:
                    cout<<"Ingrese la cedula del duenio que desea modificar"<<endl;
                    cin>>CedulaB;
                    actualizarOwner(CedulaB,nombreArchivoOwners);
                    continue;
                case 2:
                    cout<<"Ingrese la cedula del duenio de la mascota que desea modificar"<<endl;
                    cin>>CedulaB;
                    actualizarPets(Nlinea,nombreArchivoPets);
                    continue;
            }
        continue;
        case 5:
            wh=false;
            break;  
        default: 
            cout << "Opcion no valida. Intente de nuevo." << endl;
            continue; 
        }
    delete[] pets;
    delete[] owners;
    } while(wh==true);
}
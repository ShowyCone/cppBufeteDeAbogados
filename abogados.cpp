#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

int menu() {
    int option;
    system("cls");
    cout << "<----- B I E N V E N I D O S ----->" << endl;
    cout << "1. Agregar registros" << endl;
    cout << "2. Ver registros" << endl;
    cout << "3. Buscar registros(por ID)" << endl;
    cout << "4. Modificar registros" << endl;
    cout << "5. Eliminar registros" << endl;
    cout << "6. Salir" << endl;
    cout << "Opcion: ";
    cin >> option;

    return option;
}

// Verifica si ya existe el id en el archivo
bool verify(string idVerify) {
    ifstream read("registros.txt", ios::in);
    string id, date, attorney, client, description, caseCondition;


    read >> id;
    while (!read.eof()) {
        read >> date;
        read >> attorney;
        read >> client;
        read >> description;
        read >> caseCondition;
        if (id == idVerify) {
            read.close();
            return false;
        }
        read >> id;
    }
    read.close();
    return true;
}

void addedToFile(ofstream &es) {
    system("cls");
    string id, date, attorney, client, description, caseCondition;
    es.open("registros.txt", ios::out | ios::app);

    cout << "Ingrese el id(no debe olvidarlo): ";
    cin >> id;
    cout << endl << "Ingrese la fecha en la que se acepta/acepto el caso: ";
    cin >> date;
    cout << endl << "Ingrese el nombre del abogado responsable del caso: ";
    cin >> attorney;
    cout << endl << "Ingrese el nombre del cliente: ";
    cin >> client;
    cout << endl << "Ingrese la descripcion del caso: ";
    cin >> description;
    cout << endl << "Ingrese la condicion actual del caso (abierto o cerrado): ";
    cin >> caseCondition;

    if (verify(id))
        es << id << endl << date << endl << attorney << endl << client << endl << description << endl << caseCondition << endl << endl;
    else cout << "No se ha guardado, ya existe un archivo con esa ID. Intente usando otro ID." << endl;
    system("pause");
    es.close();

}

void readRegister(ifstream &Lec) {
    system("cls");
    string id, date, attorney, client, description, caseCondition;

    Lec.open("registros.txt", ios::in);
    Lec >> id;
    try {
        if(Lec.is_open()) {
            while(!Lec.eof()) {
                Lec >> date;
                Lec >> attorney;
                Lec >> client;
                Lec >> description;
                Lec >> caseCondition;
                cout << "ID ------------------------: " << id << endl;
                cout << "Fecha ---------------------: " << date << endl;
                cout << "Abogado -------------------: " << attorney << endl;
                cout << "Cliente -------------------: " << client << endl;
                cout << "Descripcion ---------------: " << description << endl;
                cout << "Condicion del caso --------: " << caseCondition << endl;
                cout << "------------------------------------------------" << endl;
                Lec >> id;
            }
            Lec.close();
        } else {
            throw 404;
        }
    }
    catch (...) {
        cout << "Error, no existe el archivo" << endl;
    }
    system("pause");
}

// Buscar en el archivo mediante la cedula
void searchRegister(ifstream &Lec) {
    system("cls");
    Lec.open("registros.txt", ios::in);
    string id, date, attorney, client, description, caseCondition, auxId;
    bool found = false;
    cout << "Digite el ID correspondiente: ";
    cin >> auxId;
    Lec >> id;
    cout << endl;
    while (!Lec.eof() && !found) {
        Lec >> date;
        Lec >> attorney;
        Lec >> client;
        Lec >> description;
        Lec >> caseCondition;
        if (id == auxId) {
            cout << "ID ------------------------: " << id << endl;
            cout << "Fecha ---------------------: " << date << endl;
            cout << "Abogado -------------------: " << attorney << endl;
            cout << "Cliente -------------------: " << client << endl;
            cout << "Descripcion ---------------: " << description << endl;
            cout << "Condicion del caso --------: " << caseCondition << endl;
            cout << "------------------------------------------------" << endl;
            found = true;
        }
        Lec >> id;
    }
    Lec.close();
    if (!found) {
        cout << "No se ha encontrado el dato" << endl;
    }
    system("pause");

}

int modifyMenu() {
    int option;
    system("cls");
    cout << "<-- SELECCIONE EL PARAMETRO QUE DESA EDITAR -->" << endl;
    cout << "1. ID" << endl;
    cout << "2. Fecha" << endl;
    cout << "3. Nombre del abogado" << endl;
    cout << "4. Nombre del cliente" << endl;
    cout << "5. Descripcion" << endl;
    cout << "6. Condicion del caso" << endl;
    cout << "7. Salir y guardar" << endl;
    cout << "Opcion: ";
    cin >> option;

    return option;
}

void modifyRegister(ifstream &Lec) {
    system("cls");
    int option;
    string id, date, attorney, client, description, caseCondition;
    string auxId, auxDate, auxAttorney, auxClient, auxDescription, auxCaseCondition;
    Lec.open("registros.txt", ios::in);
    ofstream aux("auxiliar.txt", ios::out);
    if (Lec.is_open()) {
        cout << "Ingrese ID del resgistro que desea editar: ";
        cin >> auxId;
        Lec >> id;
        while (!Lec.eof()) {
            Lec >> date;
            Lec >> attorney;
            Lec >> client;
            Lec >> description;
            Lec >> caseCondition;
            if (id == auxId) {
                do {
                    system("cls");
                    option = modifyMenu();
                    if (option == 1) {
                        cout << "Ingresa el nuevo ID(no olvidar): ";
                        cin >> auxId;
                        aux << auxId << endl << date << endl << attorney << endl << client << endl << description << endl << caseCondition << endl << endl;
                    } else if (option == 2) {
                        cout << "Ingresa la nueva fecha: ";
                        cin >> auxDate;
                        aux << id << endl << auxDate << endl << attorney << endl << client << endl << description << endl << caseCondition << endl << endl;
                    } else if (option == 3) {
                        cout << "Ingresa el nombre y apellido del abogado: ";
                        cin >> auxAttorney;
                        aux << id << endl << date << endl << auxAttorney << endl << client << endl << description << endl << caseCondition << endl << endl;
                    } else if (option == 4) {
                        cout << "Ingresa el nombre y apellido del cliente: ";
                        cin >> auxClient;
                        aux << id << endl << date << endl << attorney << endl << auxClient << endl << description << endl << caseCondition << endl << endl;
                    } else if (option == 5) {
                        cout << "Ingresa la nueva descripcion: ";
                        cin >> auxDescription;
                        aux << id << endl << date << endl << attorney << endl << client << endl << auxDescription << endl << caseCondition << endl << endl;
                    } else if (option == 6) {
                        cout << "Ingresa la actual condicion del caso (abierto o cerrado): ";
                        cin >> auxCaseCondition;
                        aux << id << endl << date << endl << attorney << endl << client << endl << description << endl << auxCaseCondition << endl << endl;
                    } else {
                        aux << id << endl << date << endl << attorney << endl << client << endl << description << endl << caseCondition << endl << endl;
                    }
                    Lec >> id;
                } while(option != 7);
            }
        }
        Lec.close();
        aux.close();
    } else cout << "Error" << endl;
    
    remove("registros.txt");
    rename("auxiliar.txt", "registros.txt");
    system("pause");
}

void deleteRegister(ifstream &Lec) {
    system("cls");
    string id, date, attorney, client, description, caseCondition, auxId;
    Lec.open("registros.txt", ios::in);
    ofstream aux("auxiliar.txt", ios::out);
    if (Lec.is_open()) {
        cout << "Ingrese el ID del registro que desea eliminar: ";
        cin >> auxId;
        Lec >> id;
        while (!Lec.eof()) {
            Lec >> date;
            Lec >> attorney;
            Lec >> client;
            Lec >> description;
            Lec >> caseCondition;
            if (id == auxId) {
                cout << "Eliminado satisfactoriamente" << endl;
            } else {
                aux << id << endl << date << endl << attorney << endl << client << endl << description << endl << caseCondition << endl << endl;
            }
            Lec >> id;
        }
        Lec.close();
        aux.close();
    } else cout << "Error" << endl;
    remove("registros.txt");
    rename("auxiliar.txt", "registros.txt");
    system("pause");
}

int main() {
    ofstream Esc;
    ifstream Lec;
    int option;

    do {
        system("cls");
        option = menu();
        if (option == 1) addedToFile(Esc);
        if (option == 2) readRegister(Lec);
        if (option == 3) searchRegister(Lec);
        if (option == 4) modifyRegister(Lec);
        if (option == 5) deleteRegister(Lec);
    }
    while(option != 6);
}
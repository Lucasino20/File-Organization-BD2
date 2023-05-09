#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include "Sequential/sequential.h"
#include "DynamicHash/extendibleHash.h"

using namespace std;

#define salto cout<<endl
#define ARCHIVO_CARS "cars.csv"
#define ARCHIVO_ACCIDENTES "accidentes.csv"

void post_insertar_aleatorio(Sequential<Record<char[40]>, string> &seq);
void post_insertar_aleatorio_hash(ExtendibleHash<int> &eh);

bool esEntero_p(string linea) {
	bool esEntero = true;
	int longitud = linea.size();
	
	if (longitud == 0) {
		esEntero = false;
	} else if (longitud == 1 && !isdigit(linea[0])) {
		esEntero = false;
	} else {
		int indice = 0;
		if (linea[0] == '+' || linea[0] == '-') {
			indice = 1;
		} else {
			indice = 0;
		}
		
		while (indice < longitud) {
			if (!isdigit(linea[indice])) {
				esEntero = false;
				break;
			}
			indice++;
		}
	}
	
	return esEntero;	
}

bool esEntero_r(string linea) {
	bool esEntero = true;
	int longitud = linea.size();
	
	if (longitud == 0) {
		esEntero = false;
	} else if (longitud == 1 && !isdigit(linea[0])) {
		esEntero = false;
	} else {
		int indice = 0;
		if (linea[0] == '+' || linea[0] == '-') {
			indice = 1;
		} else {
			indice = 0;
		}
		
		while (indice < longitud) {
			if (!isdigit(linea[indice])) {
				esEntero = false;
				break;
			}
			indice++;
		}
	}
	
	return esEntero;	
}

void insertar_secuencial(Sequential<Record<char[40]>, string> &seq){

    ifstream archivo(ARCHIVO_CARS);
    string linea;
    char delimitador = ';';
    // Leemos la primea linea para descartarla, pues es el encabezado
    getline(archivo,linea);
    vector<Record<char[40]>> records;
    
    // Leemos todos las linea
    clock_t t;

    while (getline(archivo,linea))
    {
        float mpg = 0;
        int cylinders = 0;
        float displacement = 0;
        float horsepower = 0;
        float weight = 0;
        float acceleration = 0;
        int model = 0;

        stringstream stream(linea);//Convertir la cadena a un stream
        string Name, MPG, Cylinders, Displacement, Horsepower, Weight, Acceleration, Model, Origin;
        //Extraer todos los valores
        getline(stream, Name, delimitador);
        getline(stream, MPG, delimitador);
        getline(stream, Cylinders, delimitador);
        getline(stream, Displacement, delimitador);
        getline(stream, Horsepower, delimitador);
        getline(stream, Weight, delimitador);
        getline(stream, Acceleration, delimitador);
        getline(stream, Model, delimitador);
        getline(stream, Origin, delimitador);

        stringstream _mpg(MPG);
        stringstream _cylinders(Cylinders);
        stringstream _displacement(Displacement);
        stringstream _horsepower(Horsepower);
        stringstream _weight(Weight);
        stringstream _acceleration(Acceleration);
        stringstream _model(Model);
        
        _mpg >> mpg;
        _cylinders >> cylinders;
        _displacement >> displacement;
        _horsepower >> horsepower;
        _weight >> weight;
        _acceleration >> acceleration;
        _model >> model;
        
        Record<char[40]> temp(Name, mpg, cylinders, displacement, horsepower, weight, acceleration, model, Origin);
        
        //guardar en vector
        records.push_back(temp);
    }
    t = clock();
    int accesos = seq.insertAll(records);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
    cout<<endl;
    printf("El programa demoro %f segundos en realizar el proceso", time_taken);
    printf("\nEl programa tomó %d accesos a memoria", accesos);
    dump();
    post_insertar_aleatorio(seq);
}

void insertar_hash(ExtendibleHash<int> &eh){

    ifstream archivo(ARCHIVO_ACCIDENTES);
    string linea;
    int counter=0;
    clock_t t;
    char delimitador = ';';
    // Leemos la primea linea para descartarla, pues es el encabezado
    getline(archivo,linea);
    vector<RecordHash<int>> records;
    // Leemos todos las linea
    while (getline(archivo,linea) and counter!=300)
    {
        stringstream stream(linea);//Convertir la cadena a un stream
        string id, corte, fecha, hora, departamento, codigo, kilometro, modalidad, fallecidos, heridos;
        //Extraer todos los valores
        getline(stream, id, delimitador);
        getline(stream, corte, delimitador);
        getline(stream, fecha, delimitador);
        getline(stream, hora, delimitador);
        getline(stream, departamento, delimitador);
        getline(stream, codigo, delimitador);       
        getline(stream, kilometro, delimitador);
        getline(stream, modalidad, delimitador);
        getline(stream, fallecidos, delimitador);
        getline(stream, heridos, delimitador);
        RecordHash<int> temp(stoi(id), stoi(corte), stoi(fecha), hora, departamento, codigo, stoi(kilometro), modalidad, stoi(fallecidos), stoi(heridos));
        records.push_back(temp);
        counter++;

    }
    
    t = clock();
    int accesos = eh.insertAll(records);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
    cout<<endl;
    printf("El programa demoro %f segundos en realizar el proceso", time_taken);
    printf("\nEl programa tomó %d accesos a memoria", accesos);
    post_insertar_aleatorio_hash(eh);

}

void post_insertar_aleatorio(Sequential<Record<char[40]>, string> &seq){
  
  string input;
  int opcion;
  bool repite = true;
  do{
    cout<<"\e[1;1H\e[2J";
    cout<<"Se insertaron los datos existosamente"<<endl;
    cout<<endl;
    cout<<"¿Deseas verlos?"<<endl;
    cout<<"-> Elige un número"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"1. Si -> Mostrar datos"<<endl;
    cout<<endl;
    cout<<"2. No -> Regresar al menu de inicio"<<endl;
    cout<<endl;
    cout<<"3. Salir"<<endl;
    cout<<endl;

    getline(cin, input);
    if(esEntero_p(input)){
      repite = false;
    }
  }
  while(repite);

  opcion = atoi(input.c_str());

  switch(opcion){
    case 1:
      seq.showRecords();
      break;
    case 2:
      return;
      break;
    case 3:
      exit(-1);
      break;
    default:
      post_insertar_aleatorio(seq);
      break;
  }
  dump();
}

void post_insertar_aleatorio_hash(ExtendibleHash<int> &eh){
  string input;
  int opcion;
  bool repite = true;
  do{
    cout<<"\e[1;1H\e[2J";
    cout<<"Se insertaron los datos existosamente"<<endl;
    cout<<endl;
    cout<<"¿Deseas verlos?"<<endl;
    cout<<"-> Elige un número"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"1. Si -> Mostrar datos"<<endl;
    cout<<endl;
    cout<<"2. No -> Regresar al menu de inicio"<<endl;
    cout<<endl;
    cout<<"3. Salir"<<endl;
    cout<<endl;

    getline(cin, input);
    if(esEntero_r(input)){
      repite = false;
    }
  }
  while(repite);

  opcion = atoi(input.c_str());

  switch(opcion){
    case 1:
      eh.showRecords();
      break;
    case 2:
      return;
      break;
    case 3:
      exit(-1);
      break;
    default:
      post_insertar_aleatorio_hash(eh);
      break;
  }
  dump();
}

void insertar_registro_secuencial(Sequential<Record<char[40]>, string> &seq){
  cout << "\n\n----------Insertar----------\n\n";
  string Name;
  float Mpg;
  int Cylinders;
  float Displacement;
  float Horsepower;
  float Weight;
  float Acceleration;
  int Model;
  string Origin;
  clock_t t;
  
  cout << "Ingrese el Nombre (40 carac. max): ";
  getline(cin, Name); 
  cout << "Ingrese el MPG: ";
  cin >> Mpg;
  cout << "Ingrese los cilindros: ";
  cin >> Cylinders;
  cout << "Ingrese el Displacement: ";
  cin >> Displacement;
  cout << "Ingrese los caballos de fuerza: ";
  cin >> Horsepower;
  cout << "Ingrese el peso: ";
  cin >> Weight;
  cout << "Ingrese la aceleración: ";
  cin >> Acceleration;
  cout << "Ingrese el Model: ";
  cin >> Model;
  cout << "Ingrese el lugar de fabricación: ";
  cin >> Origin;
  t = clock();
  Record<char[40]> rec(Name, Mpg, Cylinders, Displacement, Horsepower, Weight, Acceleration, Model, toLower(Origin));
  int accesos = 0;
  seq.insert(rec, accesos);
  
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
  cout<<endl;
  printf("El programa tomó %f segundos en insertar el registro", time_taken);
  printf("\nEl programa tomó %d accesos a memoria secundaria", accesos);

  dump();
}

void insertar_registro_hash(ExtendibleHash<int> &eh){
  cout << "\n\n----------Insertar----------\n\n";
  int id;
  int corte;
  int fecha;
  string hora;
  string departamento;
  string codigo;
  int kilometro;
  string modalidad;
  int fallecidos;
  int heridos;

  clock_t t;
  cout << "Ingrese el id: ";
  cin >> id;
  cout << "Ingrese la fecha de corte: ";
  cin >> corte;
  cout << "Ingrese la fecha actual: ";
  cin >> fecha;
  cout << "Ingrese la hora: ";
  cin >> hora;
  cout << "Ingrese el departamento: ";
  cin >> departamento;
  cout << "Ingrese el codigo: ";
  cin >> codigo;
  cout << "Ingrese el kilometro: ";
  cin >> kilometro;
  cout << "Ingrese la modalidad: ";
  cin >> modalidad;
  cout << "Ingrese la cantidad de fallecidos: ";
  cin >> fallecidos;
  cout << "Ingrese la cantidad de heridos: ";
  cin >> heridos;

  RecordHash<int> rec(id, corte, fecha, hora, toUpper(departamento), codigo, kilometro, toUpper(modalidad), fallecidos, heridos);
  int accesos = 0;
  t = clock();
  eh.insert(rec, accesos);
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
  cout<<endl;
  printf("El programa tomó %f segundos en insertar el registro", time_taken);
  printf("\nEl programa tomó %d accesos a memoria secundaria", accesos);
  dump();
}

void buscar_registro_secuencial(Sequential<Record<char[40]>, string> &seq){
  cout << "\n\n----------Busqueda----------\n\n";
  cout << "Ingrese nombre a buscar: ";
  string key;
  clock_t t;

  getline(cin, key);
  int accesos = 0;
  t = clock();
  auto result = seq.search(key, accesos);
  if(result){
    (*result).showRecord(1);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the  elapsed time
    cout<<endl;
    printf("El programa tomo %f segundos en buscar el registro", time_taken);
    printf("\nEl programa tomo %d accesos a memoria secundaria", accesos);
  }else{
    cout << "No se encontro " << key << "\n";
  }
  dump();
}

void buscar_registro_hash(ExtendibleHash<int> &eh){
  cout << "\n\n----------Busqueda----------\n\n";
  cout << "Ingrese codigo a buscar: ";
  int key;
  clock_t t;
  cin >> key;
  int accesos = 0;
  t = clock();
  auto result = eh.search(key, accesos);
  if(result){
    (*result).showRecord(1);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
    cout<<endl;
    printf("El programa tomó %f segundos en buscar el registro", time_taken);
    printf("\nEl programa tomó %d accesos a memoria secundaria", accesos);
  }else{
    cout << "No se encontro " << key << "\n";
  }
  dump();
}

void buscar_rango_registro_secuencial(Sequential<Record<char[40]>, string> &seq){
  cout << "\n\n----------Busqueda por rango----------\n\n";
  string key1, key2;
  clock_t t;
  cout << "Inserte registro inicial: ";
  getline(cin, key1);
  cout << "Inserte registro final: ";
  getline(cin, key2);
  if(key1 > key2){
    auto t = key1;
    key1 = key2;
    key2 = t;
  }
  
  t = clock();
  auto result = seq.search(toLower(key1), toLower(key2));
  cout << "Resultados: " << result.size() << "\n";
  int cont = 1;
  for(auto r : result){
    r.showRecord(cont++);
  }
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the  elapsed time
  cout<<endl;
  printf("El programa tomó %f segundos en buscar el rango de registros", time_taken);
  dump();
}

void buscar_rango_registro_hash(ExtendibleHash<int> &eh){
  cout << "\n\n----------Busqueda por rango----------\n\n";
  int key1, key2;
  clock_t t;
  cout << "Inserte registro inicial: ";
  cin >> key1;
  cout << "Inserte registro final: ";
  cin >> key2;
  if(key1 > key2){
    auto t = key1;
    key1 = key2;
    key2 = t;
  }
  t = clock();
  auto result = eh.searchRange(key1, key2);
  cout << "Resultado: " << result.size() << "\n";
  int cont = 1;
  for(auto r : result){
    r.showRecord(cont++);
  }
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
    cout<<endl;
    printf("El programa tomó %f segundos en buscar el rango de registros", time_taken);
  dump();
}

void eliminar_registro_secuencial(Sequential<Record<char[40]>, string> &seq){
  cout << "\n\n----------Eliminar----------\n\n";
  cout << "Ingrese codigo a eliminar: ";
  string key;
  cin >> key;
  if(seq.erase(toLower(key))){
    cout << "Registro eliminado\n";
  }else{
    cout << "No se elimino\n";
  }
  dump();
}

void eliminar_registro_hash(ExtendibleHash<int> &eh){
  cout << "\n\n----------Eliminar----------\n\n";
  cout << "Ingrese codigo a eliminar: ";
  int key;
  cin >> key;
  if(eh.erase(key)){
    cout << "Registro eliminado\n";
  }else{
    cout << "No se elimino\n";
  }

  dump();
}

void showData(Sequential<Record<char[40]>, string> &seq)
{
  seq.showRecords();
  dump();
}

void showDataHash(ExtendibleHash<int> &eh){
  eh.showRecords();
  dump();
}

bool esEntero(string linea) {
	bool esEntero = true;
	int longitud = linea.size();
	
	if (longitud == 0) {
		esEntero = false;
	} else if (longitud == 1 && !isdigit(linea[0])) {
		esEntero = false;
	} else {
		int indice = 0;
		if (linea[0] == '+' || linea[0] == '-') {
			indice = 1;
		} else {
			indice = 0;
		}
		
		while (indice < longitud) {
			if (!isdigit(linea[indice])) {
				esEntero = false;
				break;
			}
			indice++;
		}
	}
	
	
	return esEntero;	
}

void menu_principal(Sequential<Record<char[40]>, string> &seq, ExtendibleHash<int> &eh);

void cars(Sequential<Record<char[40]>, string> &seq){
    string input;
    int opcion;
    bool repite = true;
    do{
      cout<<"\e[1;1H\e[2J";
      cout<<"Cars Database"<<endl;
      salto;
      cout<<"¿Que deseas hacer?"<<endl;
      cout<<"-> Elige un numero"<<endl;
      salto;
      salto;
      cout<<"1. Volver al inicio"<<endl;
      salto;
      cout<<"2. Insertar registros aleatorios"<<endl;
      salto;
      cout<<"3. Insertar registro nuevo"<<endl;
      salto;
      cout<<"4. Buscar un registro"<<endl;
      salto;
      cout<<"5. Buscar un rango de registros"<<endl;
      salto;
      cout<<"6. Eliminar un registro"<<endl;
      salto;
      cout<<"7. Ver todos los registros"<<endl;
      salto;
      cout<<"8. Salir"<<endl;
      salto;

      getline(cin, input);
      if(esEntero(input)){
        repite = false;
      }
  }
  while(repite);

  opcion = atoi(input.c_str());
  switch(opcion){
      case 1:
        return;
        break;
      case 2:
        insertar_secuencial(seq);
        break;
      case 3:
        insertar_registro_secuencial(seq);
        break;
      case 4:
        buscar_registro_secuencial(seq);
        break;
      case 5:
        buscar_rango_registro_secuencial(seq);
        break;
      case 6:
        eliminar_registro_secuencial(seq);
        break;
      case 7:
        showData(seq);
        break;
      case 8:
        exit(-1);
        break;
      default:
        cars(seq);
        break;
  }
}

void accidentes(ExtendibleHash<int> &eh){
    string input;
    int opcion;
    bool repite = true;
    do{
      cout<<"\e[1;1H\e[2J";
      cout<<"Accidentes Database"<<endl;
      salto;
      cout<<"¿Que deseas hacer?"<<endl;
      cout<<"-> Elige un numero"<<endl;
      salto;
      salto;
      cout<<"1. Volver a inicio"<<endl;
      salto;
      cout<<"2. Insertar registros aleatorios"<<endl;
      salto;
      cout<<"3. Insertar registro nuevo"<<endl;
      salto;
      cout<<"4. Buscar un registro"<<endl;
      salto;
      cout<<"5. Buscar un rango de registros"<<endl;
      salto;
      cout<<"6. Eliminar un registro"<<endl;
      salto;
      cout<<"7. Ver todos los registros"<<endl;
      salto;
      cout<<"8. Salir"<<endl;
      salto;

      getline(cin, input);
      if(esEntero(input)){
        repite = false;
      }
  }
  while(repite);

  opcion = atoi(input.c_str());
  switch(opcion){
      case 1:
        return;
        break;
      case 2:
        insertar_hash(eh);
        break;
      case 3:
        insertar_registro_hash(eh);
        break;
      case 4:
        buscar_registro_hash(eh);
        break;
      case 5:
        buscar_rango_registro_hash(eh);
        break;
      case 6:
        eliminar_registro_hash(eh);
        break;
      case 7:
        showDataHash(eh);
        break;
      case 8:
        exit(-1);
        break;
      default:
        accidentes(eh);
        break;
  }
}

void parcer(Sequential<Record<char[40]>, string> &seq, ExtendibleHash<int> &eh) {
    std::string command;
    std::getline(std::cin, command);

    std::string table;

    if (command.substr(0, 6) == "SELECT") {
        if (command.find("FROM") != std::string::npos && command.find("WHERE") != std::string::npos) {
            std::string from = command.substr(command.find("FROM") + 5, command.find("WHERE") - command.find("FROM") - 6);
            table = from;
            
            std::string condition = command.substr(command.find("WHERE") + 6);
            std::istringstream iss(condition);
            std::string field, op, value;
            iss >> field >> op;
            
            
            //cout << value.size() << " ";
            if (table == "cars") {
                if (op == "==") {
                    getline(iss >> ws ,value);
                    string key = value;
                    int accesos = 0;
                    clock_t t;
                    t = clock();
                    auto result = seq.search(key, accesos);
                    if(result){
                        (*result).showRecord(1);
                        t = clock() - t;
                        double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the  elapsed time
                        cout<<endl;
                        printf("El programa tomo %f segundos en buscar el registro", time_taken);
                        printf("\nEl programa tomo %d accesos a memoria secundaria", accesos);
                    }else{
                        cout << "No se encontro " << key << "\n";
                    }
                    dump();
                    return;
                } else if (op == "BETWEEN") {
                    string begin, end;
                    getline(iss >> ws, value);
                    size_t pos = value.find(" and ");
                    if (pos != std::string::npos) {
                      begin = value.substr(0, pos);
                      end = value.substr(pos + 5, value.size()+1);
                    }
                   
                    clock_t t;
                    if(begin > end){
                        auto t = begin;
                        begin = end;
                        end = t;
                    }
                    
                    t = clock();
                    auto result = seq.search(toLower(begin), toLower(end));
                    cout << "Resultados: " << result.size() << "\n";
                    int cont = 1;
                    for(auto r : result){
                        r.showRecord(cont++);
                    }
                    t = clock() - t;
                    double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the  elapsed time
                    cout<<endl;
                    printf("El programa tomó %f segundos en buscar el rango de registros", time_taken);
                    dump();
                    return;
                } else {
                    cout << "Operacion no soportada " << endl;
                    dump();
                    return;
                }
            } else if (table == "accidentes") {
                getline(iss >> ws ,value);
                if (op == "==" && esEntero(value)) {
        
                    int key = stoi(value);
                    int accesos = 0;
                    clock_t t;
                    
                    t = clock();
                    auto result = eh.search(key, accesos);
                    if(result){
                        (*result).showRecord(1);
                        t = clock() - t;
                        double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
                        cout<<endl;
                        printf("El programa tomó %f segundos en buscar el registro", time_taken);
                        printf("\nEl programa tomó %d accesos a memoria secundaria", accesos);
                    }else{
                        cout << "No se encontro " << key << "\n";
                    }
                    dump();
                    return;
                } else if (op == "BETWEEN" ) {
                    string begin_, end_;
                    getline(iss >> ws, value);
                    size_t pos = value.find(" and ");
                    if (pos != std::string::npos) {
                      begin_ = value.substr(0, pos);
                      end_ = value.substr(pos + 5, value.size()+1);
                    }
                    
                    int begin = stoi(begin_);
                    int end = stoi(end_);
                    clock_t t;
                    if(begin > end){
                        auto t = begin;
                        begin = end;
                        end = t;
                    }
                    t = clock();
                    auto result = eh.searchRange(begin, end);
                    cout << "Resultado: " << result.size() << "\n";
                    int cont = 1;
                    for(auto r : result){
                      r.showRecord(cont++);
                    }
                      t = clock() - t;
                      double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
                      cout<<endl;
                      printf("El programa tomó %f segundos en buscar el rango de registros", time_taken);
                    dump();
                    return;
                }
            } else {
              cout << "Tabla no encontrada "<< endl;
              dump();
              return;
            }
             
        } else {
          cout << "Sentencia invalida o no soportada "<< endl;
          dump();
          return;
        } 
    } else if (command.substr(0, 6) == "INSERT") {
        if (command.find("INTO") != std::string::npos && command.find("VALUES") != std::string::npos) {
            std::string into = command.substr(command.find("INTO") + 4, command.find("VALUES") - command.find("INTO") - 5);
            istringstream iss(into);
            string table;
            getline(iss >> ws, table);
            std::string values = command.substr(command.find("VALUES") + 6);
            if (table == "cars") {
              
              string Name;
              float Mpg;
              int Cylinders;
              float Displacement;
              float Horsepower;
              float Weight;
              float Acceleration;
              int Model;
              string Origin;
              clock_t t;
              
              std::istringstream iss(values);
              std::string value;
              std::vector<std::string> valueList;
              iss.get();
              while (std::getline(iss, value, ',')) {
                  valueList.push_back(value);
              }             
              string & str = valueList[8];
              str = str.substr(0,str.size()-1);
              
              if (valueList.size() == 9 ) {
                  Name = valueList[0];
                  Mpg = std::stof(valueList[1]);
                  Cylinders = std::stoi(valueList[2]);
                  Displacement = std::stof(valueList[3]);
                  Horsepower = std::stof(valueList[4]);
                  Weight = std::stof(valueList[5]);
                  Acceleration = std::stof(valueList[6]);
                  Model = std::stoi(valueList[7]);
                  Origin = valueList[8];
                                    
                  int accesos = 0;
                  Record<char[40]> rec(Name, Mpg, Cylinders, Displacement, Horsepower, Weight, Acceleration, Model, toLower(Origin));
                
                  seq.insert(rec, accesos);
                  
                  t = clock() - t;
                  double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
                  cout<<endl;
                  printf("El programa tomó %f segundos en insertar el registro", time_taken);
                  printf("\nEl programa tomó %d accesos a memoria secundaria", accesos);

                  dump();
                  return;
              } else {
                cout << "Valores ingresados invalidos";
                dump();
                return;
              }
              
            } else if (table == "accidentes") {
                int id;
                int corte;
                int fecha;
                string hora;
                string departamento;
                string codigo;
                int kilometro;
                string modalidad;
                int fallecidos;
                int heridos;
                clock_t t;

                std::istringstream iss(values);
                std::string value;
                std::vector<std::string> valueList;
                iss.get();
                while (std::getline(iss, value, ',')) {
                    valueList.push_back(value);
                }             
                string & str = valueList[9];
                str = str.substr(0,str.size()-1);

                if (valueList.size() == 10) {
                  
                  id = stoi(valueList[0]);
                  corte = stoi(valueList[1]);
                  fecha = stoi(valueList[2]);
                  hora = (valueList[3]);
                  departamento = (valueList[4]);
                  codigo = (valueList[5]);
                  kilometro = stoi(valueList[6]);
                  modalidad = (valueList[7]);
                  fallecidos = stoi(valueList[8]);
                  heridos = stoi(valueList[9]);

                  RecordHash<int> rec(id, corte, fecha, hora, toUpper(departamento), codigo, kilometro, toUpper(modalidad), fallecidos, heridos);
                  int accesos = 0;
                  t = clock();
                  eh.insert(rec, accesos);
                  t = clock() - t;
                  double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
                  cout<<endl;
                  printf("El programa tomó %f segundos en insertar el registro", time_taken);
                  printf("\nEl programa tomó %d accesos a memoria secundaria", accesos);
                  dump();
                  return;
                } else {
                    cout << "Valores ingresados invalidos";
                    dump();
                    return;
                }
            } else {
              cout << "Tabla no encontrada "<< endl;
              dump();
              return;
            }

            
        }
    } else if (command.substr(0, 6) == "DELETE") {
        if (command.find("FROM") != std::string::npos && command.find("WHERE") != std::string::npos) {
            std::string from = command.substr(command.find("FROM") + 5, command.find("WHERE") - command.find("FROM") - 6);
            table = from;

            std::string condition = command.substr(command.find("WHERE") + 6);
            std::istringstream iss(condition);
            std::string field, op, value;
            iss >> field >> op;
            
            if (table == "cars") {
              if (op == "==") {
                getline(iss >> ws ,value);
                string key = value;
                if(seq.erase(toLower(key))){
                  cout << "Registro eliminado\n";
                }else{
                  cout << "No se elimino\n";
                }
                dump();
                return;
              } else {
                cout << "Operacion invalida"<< endl;
                dump();
                return;
              }
            }else if (table == "accidentes") {
              if (op == "==") {
                getline(iss >> ws ,value);
                int key = stoi(value);
                
                if(eh.erase(key)){
                  cout << "Registro eliminado\n";
                }else{
                  cout << "No se elimino\n";
                }

                dump();
                return;

              } else {
                cout << "Operacion invalida"<< endl;
                dump();
                return;
              }
            } else {
              cout << "Tabla no encontrada "<< endl;
              dump();
              return;
            }
            
        }
    }

    return;
}


void menu_principal(Sequential<Record<char[40]>, string> &seq, ExtendibleHash<int> &eh){
  insertar_secuencial(seq);
  insertar_hash(eh);
  while(1){
    string input;
    int opcion;
    bool repite = true;
      
      cout<<"\e[1;1H\e[2J";
      cout<<"DATA BASE :D"<<endl;
      salto;
      cout<<"Ingresa la sentencia SQL"<<endl;
      cout<<"-> Dadas las tablas:"<<endl;
      salto;
      salto;
      cout<<"Secuencial File - cars database"<<endl;
      salto;
      cout<<"Extendible Hash, Dinamic Hashing - accidentes database"<<endl;
      salto;

      parcer(seq,eh);

  
  
}

}


#endif
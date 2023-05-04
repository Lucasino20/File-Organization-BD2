#ifndef RECORD_HASH_H
#define RECORD_HASH_H

#include "../lib.h"

template <typename TKey>
class RecordHash
{

    TKey key;
    int corte;
    int fecha;
    char hora[5];
    char departamento[12];
    char codigo[5];
    int kilometro;
    char modalidad[12];
    int fallecidos;
    int heridos;
public:
    RecordHash()
    {
        string hora = "00:00";
        string departamento = "ninguno";
        string codigo = "PE-00";
        string modalidad = "ninguna";

        this->key = 0;
        this->corte = 0;
        this->fecha = 0;
        strcpy(this->hora, hora.c_str());
        strcpy(this->departamento, departamento.c_str());
        strcpy(this->codigo, codigo.c_str());
        this->kilometro = 0;
        strcpy(this->modalidad, modalidad.c_str());
        this->fallecidos = 0;
        this->heridos = 0;
    }

  
    RecordHash(TKey key,int corte, int fecha, string hora, string departamento, string codigo, int kilometro, string modalidad, int fallecidos, int heridos)
    {
        this->key = key;
        this->corte = corte;
        this->fecha = fecha;
        strcpy(this->hora, hora.c_str());
        strcpy(this->departamento, departamento.c_str());
        strcpy(this->codigo, codigo.c_str());
        this->kilometro = kilometro;
        strcpy(this->modalidad, modalidad.c_str());
        this->fallecidos = fallecidos;
        this->heridos = heridos;
    }

    void setData(TKey key,int corte, int fecha, string hora, string departamento, string codigo, int kilometro, string modalidad, int fallecidos, int heridos)
    {
        this->key = key;
        this->corte = corte;
        this->fecha = fecha;
        strcpy(this->hora, hora.c_str());
        strcpy(this->departamento, departamento.c_str());
        strcpy(this->codigo, codigo.c_str());
        this->kilometro = kilometro;
        strcpy(this->modalidad, modalidad.c_str());
        this->fallecidos = fallecidos;
        this->heridos = heridos;
    }


    void showData()
    {
        cout << "\tKey: " << key << "\n";
        cout << "\tCorte: " << corte << "\n\n";
        cout << "\tFecha: " << fecha << "\n\n";
        cout << "\tHora: " << hora << "\n\n";
        cout << "\tDepartamento: " << departamento << "\n\n";
        cout << "\tCodigo: " << codigo << "\n";
        cout << "\tKilometro: " << kilometro << "\n\n";
        cout << "\tModalidad: " << modalidad << "\n\n";
        cout << "\tFallecidos: " << fallecidos << "\n\n";
        cout << "\tHeridos: " << heridos << "\n\n";
    }
    TKey getKey()
    {
        return key;
    }

    RecordHash &operator=(const RecordHash &a)
    {
        TKey key;
        int corte;
        int fecha;
        char hora[5];
        char departamento[12];
        char codigo[5];
        int kilometro;
        char modalidad[12];
        int fallecidos;
        int heridos;

        this->key = a.key;
        this->corte = a.corte;
        this->fecha = a.fecha;
        for (int i = 0; i < 5; i++)
            this->hora[i] = a.hora[i];
        for (int i = 0; i < 12; i++)
            this->departamento[i] = a.departamento[i];
        for (int i = 0; i < 5; i++)
            this->codigo[i] = a.codigo[i];
        this->kilometro = a.kilometro;
        for (int i = 0; i < 12; i++)
            this->modalidad[i] = a.modalidad[i];
        this->fallecidos = a.fallecidos;
        this->heridos = a.heridos;
        return *this;
    }
    bool operator<(const RecordHash &a) { return this->key < a.key; }
    bool operator>(const RecordHash &a) { return this->key > a.key; }
    bool operator<=(const RecordHash &a) { return this->key <= a.key; }
    bool operator>=(const RecordHash &a) { return this->key >= a.key; }
    bool operator==(const RecordHash &a) { return this->key == a.key; }
    bool operator!=(const RecordHash &a) { return this->key != a.key; }

    void showRecord(int cont){
        cout << setw(5) << cont << setw(5) << key << setw(10) << corte << setw(10) << fecha << setw(6) << hora << setw(12) << departamento << setw(6) << codigo << setw(5) << kilometro << setw(12) << modalidad << setw(3) << fallecidos << setw(3) << heridos << endl;
    }
};

#endif //RECORD_HASH.H
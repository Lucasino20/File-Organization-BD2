#ifndef RECORD_H
#define RECORD_H

#include "../lib.h"
#include <C:\Users\soto_\OneDrive\Desktop\BD2-proyect\jsong\include\nlohmann\json.hpp>

using namespace std;
using json = nlohmann::json;

template <typename TKey>
class Record
{
    TKey key; //nombre[40]
    float mpg;
    int cylinders;
    float displacement;
    float horsepower;
    float weight;
    float acceleration;
    int model;
    char origin[10];

    long next = -1;
    char file = 'd';

public:
    Record()
    {
        string name = "No name";
        this->mpg = 0;
        this->cylinders = 0;
        this->displacement = 0;
        this->horsepower = 0;
        this->weight = 0;
        this->acceleration = 0;
        this->model = 0;
        string origin = "no origin";

        strcpy(this->key, name.c_str());
        strcpy(this->origin, origin.c_str());
    }





    float getMpg()  {
        return mpg;
    }

    int getCylinders()  {
        return cylinders;
    }

    float getDisplacement()  {
        return displacement;
    }

    float getHorsepower()  {
        return horsepower;
    }

    float getWeight()  {
        return weight;
    }

    float getAcceleration()  {
        return acceleration;
    }

    int getModel ()  {
        return int(model);
    }
    
    string getOrigin() 
    {
        return string(origin);
    }


    Record(string name, float mpg, int cylinders, float displacement, float horsepower, float weight, float acceleration, int model, string origin)
    {
        strcpy(this->key, name.c_str());
        this->mpg = mpg;
        this->cylinders = cylinders;
        this->displacement = displacement;
        this->horsepower = horsepower;
        this->weight = weight;
        this->acceleration = acceleration;
        this->model = model;
        strcpy(this->origin, origin.c_str());

        this->next = -1;
        char file = 'd';
    }
    void setData(string name, float mpg, int cylinders, float displacement, float horsepower, float weight, float acceleration, int model, string origin)
    {
        strcpy(this->key, name.c_str());
        this->mpg = mpg;
        this->cylinders = cylinders;
        this->displacement = displacement;
        this->horsepower = horsepower;
        this->weight = weight;
        this->acceleration = acceleration;
        this->model = model;
        strcpy(this->origin, origin.c_str());

        this->next = -1;
        char file = 'd';
    }

    void showData()
    {
        cout << "Key: " << key << "\n";
        cout << "MPG: " << mpg << "\n";
        cout << "Cylinders: " << cylinders << "\n";
        cout << "Displacement: " << displacement << "\n";
        cout << "Horsepower: " << horsepower << "\n";
        cout << "Weight: " << weight << "\n";
        cout << "Acceleration: " << acceleration << "\n";
        cout << "Model: " << model << "\n";
        cout << "Origin: " << origin << "\n";
        cout << "Next : " << next << "\n";
        cout << "NextFile : " << file << "\n\n";

        nlohmann::json j;

        j["Key"] = key;
        j["MPG"] = mpg;
        j["Cylinders"] = cylinders;
        j["Displacement"] = displacement;
        j["Horsepower"] = horsepower;
        j["Weight"] = weight;
        j["Acceleration"] = acceleration;
        j["Model"] = model;
        j["Origin"] = origin;

     // guardar objeto json en archivo
     std::ofstream o("showData.json");
     o << std::setw(4) << j << std::endl;
     o.close();
    }
    void setNext(long _next, char _file)
    {
        next = _next;
        file = _file;
    }
    long getNext()
    {
        return next;
    }
    char getFile()
    {
        return file;
    }
    string getKey()
    {
        return string(key);
    }
    Record &operator=(const Record &a)
    {
        for (int i = 0; i < 40; i++)
            this->key[i] = a.key[i];
        this->mpg = a.mpg;
        this->cylinders = a.cylinders;
        this->displacement = a.displacement;
        this->horsepower = a.horsepower;
        this->weight = a.weight;
        this->acceleration = a.acceleration;
        this->model = a.model;
        for (int i = 0; i < 10; i++)
            this->origin[i] = a.origin[i];
        this->next = a.next;
        this->file = a.file;
        return *this;
    }
    bool operator<(const Record &a) { return string(this->key) < string(a.key); }
    bool operator>(const Record &a) { return string(this->key) > string(a.key); }
    bool operator<=(const Record &a) { return string(this->key) <= string(a.key); }
    bool operator>=(const Record &a) { return string(this->key) >= string(a.key); }
    bool operator==(const Record &a) { return string(this->key) == string(a.key); }
    bool operator!=(const Record &a) { return string(this->key) != string(a.key); }

    void showRecord(int cont) const{
      if(cont == 1){
        cout << setw(5) << "Nº" << setw(40) << "Key" << setw(8) << "MPG" << setw(9) << "Cylinders" << setw(12) << "Displacement" << setw(10) << "Horsepower" << setw(8) << "Weight" << setw(12) << "Acceleration" << setw(8) << "Model" << setw(10) << "Origin" << endl;
      }
        cout << setw(5) << cont << setw(40) << key << setw(8) << mpg << setw(9) << cylinders << setw(12) << displacement << setw(10) << horsepower << setw(8) << weight << setw(12) << acceleration << setw(8) << model << setw(10) << origin << endl;
     nlohmann::json j;

        j["N"] = cont;
        j["Key"] = key;
        j["MPG"] = mpg;
        j["Cylinders"] = cylinders;
        j["Displacement"] = displacement;
        j["Horsepower"] = horsepower;
        j["Weight"] = weight;
        j["Acceleration"] = acceleration;
        j["Model"] = model;
        j["Origin"] = origin;

     // guardar objeto json en archivo
     std::ofstream o("output.json");
     o << std::setw(4) << j << std::endl;
     o.close();
    
    }
};

#endif //RECORD.H

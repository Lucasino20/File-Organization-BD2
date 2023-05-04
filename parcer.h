#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> parcer(string sql) {
    
    // Split the SQL string into individual words
    vector<string> words;
    string word = "";
    for (char c : sql) {
        if (isspace(c)) {
            if (word != "") {
                words.push_back(word);
                word = "";
            }
        }
        else {
            word += c;
        }
    }
    if (word != "") {
        words.push_back(word);
    }

    // Parse the SQL query
    string operation = "";
    string table = "";
    string columns = "";
    string values = "";
    string where = "";
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "SELECT") {
            operation = "SELECT";
            table = words[i+3];
            if (words[i+1] == "*") {
                columns = "*";
            }
            else {
                columns = words[i+1];
            }
            if (i < words.size() - 3 && words[i+4] == "WHERE") {
                where = words[i+5] + " " + words[i+6] + " " + words[i+7];
            }
        }
        else if (words[i] == "INSERT") {
            operation = "INSERT";
            table = words[i+2];
            if (words[i+3] == "VALUES") {
                int start = i+4;
                int end = words.size() - 2;
                for (int j = start; j <= end; j++) {
                    values += words[j];
                    if (j < end) {
                        values += ",";
                    }
                }
            }
            else {
                int start = i+3;
                int end = words.size() - 2;
                for (int j = start; j <= end; j++) {
                    columns += words[j];
                    if (j < end) {
                        columns += ",";
                    }
                }
                int start2 = words.size() - 1;
                int end2 = words.size() - 1;
                values = words[start2];
                for (int j = start2+1; j <= end2; j++) {
                    values += words[j];
                }
            }
        }
        else if (words[i] == "DELETE") {
            operation = "DELETE";
            table = words[i+2];
            where = words[i+4] + " " + words[i+5] + " " + words[i+6];
        }
    }

    // Save the results
    vector<string> result;
    //operation
    result.push_back(operation);
    //Table
    result.push_back(table);

    if (operation == "SELECT") {
        //Columns 
        result.push_back(columns);
    }
    else if (operation == "INSERT") {
        //Values
        result.push_back(values);
    }
    if (where != "") {
        //Where
        result.push_back(where);
    }
    return result;
}
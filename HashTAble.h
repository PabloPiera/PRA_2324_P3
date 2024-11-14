#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "/home/alumno.upv.es.ppienav/W/PRA/PRA_2324_P1/ListLinked.h"
using namespace std;

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
	int max;
	ListLinked<TableEntry<V>>*table;

    public:
        int h(string key){
		int i = 0;
		int suma = 0;

		for(int i = 0; i < key.size(); i++){
			char c = key.at(i);
			int valor_ascii = int(c);
			suma+=valor_ascii;
		}
		return suma % n;
	}

	HashTable(int size){
		table = new ListLinked<TableEntry<V>>[size];
		n = 0;
		max = size;
	}

	~HashTable(){
		delete[]table;
	}

	int capacity(){
		return n;
	}

	friend ostream& operator<<(ostream &out, const HashTable<V> &th){
		out << "{" << th.key << " -> " << th.valor;
		return out;
	}

	V operator[](string key){
		for(int i = 0; i < n; i++){
			if(table.key == key){
				return table.valor;
			}
		}
		throw runtime_error("No existe key");
	}

        
};

#endif

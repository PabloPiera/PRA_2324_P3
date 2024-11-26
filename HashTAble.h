#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "/home/alumno.upv.es.ppienav/W/PRA/PRA_2324_P1/ListLinked.h" //para etsinf linux
//#include "/home/alumno.upv.es/ppienav/W/PRA/PRA_2324_P1/ListLinked.h" //para ubuntu
using namespace std;

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
	int max;
	ListLinked<TableEntry<V>>*table;

    public:
        int h(string key){
		int suma = 0;
		for(int i = 0; i < key.size(); i++){
			char c = key.at(i);
			int valor_ascii = int(c);
			suma+=valor_ascii;
		}
		return suma % max;
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
		return max;
	}

	friend ostream& operator<<(ostream &out, const HashTable<V> &th){
		out << "{";
		for(int i = 0; i < th.max; i++){
			Node<TableEntry<V>>* current = th.table[i].first;
			while (current != nullptr){
				out << current -> data.key << " -> " << current -> data.value;
				if(current -> next != nullptr){
					out << ", ";
				}
				current = current -> next;
			}
		}
		out << "}";
		return out;
	}

	V operator[](string key){
		int index = h(key);
			Node<TableEntry<V>>* current = table[index].first;
			while(current != nullptr){
				if(current -> data.key == key){
					return current -> data.value;
				}
			}
		throw runtime_error("No existe key");
	}

	int entries(){
		return n;
	}

	V remove(string key){
		int index = h(key);
        	Node<TableEntry<V>>* current = table[index].first;
        	Node<TableEntry<V>>* prev = nullptr;
		while(current != nullptr){
			if(current -> data.key == key){
				if(prev == nullptr){
					V valor = current -> data.value;
					table[index].first = current -> next;
					delete current;
					return valor;
				}
				else{
					V valor = current -> data.value;
					prev -> next = current -> next;
					delete current;
					return valor;
				}
			}
			else{
				prev = current;
				current = current -> next;
			}
		}
		throw runtime_error ("No existe la clave");
	}

	void insert(string key, V valor){
		TableEntry<V> entry(key, valor);  
		Node<TableEntry<V>>* newNode = new Node<TableEntry<V>>(entry, nullptr);
		int index = h(key);
		if(!existeClave(key)){
			 Node<TableEntry<V>>* current = table[index].first;
			 if(n == max){
				 delete newNode;
				 throw runtime_error("Tabla completa");
			 }
			 if(current != nullptr){
			 	while(current -> next != nullptr){
					current = current -> next;
			 	}
			 	current -> next = newNode;
			}
			else{
				table[index].first = newNode;
				}
		}
		else{
			throw runtime_error("La clave ya existe");
		}
	}

	V search(string key){
		int index = h(key);
		Node<TableEntry<V>>* current = table[index].first;
		while(current != nullptr){
			if(current -> data.key == key){
				return current -> data.value;
			}
			current = current -> next;
		}
		throw runtime_error("La clave no existe");
	}
        
	bool existeClave(string key) {
    		try {
        		V valor = search(key);  // Intenta buscar la clave
        		return true;            // Si no lanza excepción, la clave existe
    		} 
		catch (const std::runtime_error& e) {
        		return false;           // Si lanza excepción, la clave no existe
    		}
}

};

#endif

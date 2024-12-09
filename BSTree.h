#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T> 
class BSTree {
    private:
        int nelem;
	BSNode<T> *root;
	BSNode<T>* search(BSNode<T>* n, T e)const{
		if(n == nullptr){
			throw runtime_error("No hay root");
		}
		else if (n -> elem < e){
			return search(n -> right, e);
		}
		else if (n -> elem > e){
		       return search(n -> left, e);
		}
 		else{
			return n;
		}
	}
	
	BSNode<T>* insert(BSNode<T>* n, T e){
		if (n == nullptr){
			n = new BSNode<T>(e);
			nelem ++;
			return n;
		}
		else if(n -> elem == e){
			throw runtime_error("El elemento ya existe");
		}
		else if(n -> elem > e){
			n -> left = insert(n -> left, e);
		}
		else{
			n -> right = insert(n -> right, e);
		}
		return n;
	}

	void print_inorder(ostream &out, BSNode<T>* n) const{
		if(n != nullptr){
			print_inorder(out, n -> left);
			out << n -> elem << " ";
			print_inorder(out, n -> right);
		}
	}

	BSNode<T>* remove(BSNode<T>* n, T e){
		if(n == nullptr){
		throw runtime_error("Root no existe");
		}
		else if(n -> elem < e){
			n -> right = remove(n -> right, e);
		}
		else if(n -> elem > e){
			n -> left = remove(n -> left, e);
		}
		else{
			if(n -> left != nullptr && n -> right != nullptr){
				n -> elem = max(n -> left);
				n -> left = remove_max(n -> left);
			}
			else{
				if (n->left != nullptr) {
    					n = n -> left;
				} 
				else {
    					n = n -> right;
				}
			}
		}
		return n;
	}
	

	T max(BSNode<T>* n) const{
		if(n == nullptr){
			throw runtime_error("No hay root");
		}
		else if(n -> right != nullptr){
			return max(n -> right);
		}
		else{
			return n -> elem;
		}
	}

	BSNode<T>* remove_max(BSNode<T>* n){
		if(n -> right == nullptr){
			return n -> left;
		}
		else{
			n -> right = remove_max(n -> right);
			return n;
		}
	}
	
	void delete_cascade(BSNode<T>* n){
		if(n != nullptr){
			delete_cascade(n -> left);
			delete_cascade(n -> right);
			delete n;
		}
	}

     public:
        ~BSTree(){
		delete_cascade(root);
	}
	
	T search(T e) const{
		if(root == nullptr){
			throw out_of_range("Arbol vacio");
		}
		BSNode <T>* newNode = search(root, e);
		return newNode -> elem;
	}

	void insert(T e){
		root = insert(root, e);
	}

	T& operator[](const T& e) {
        	BSNode<T>* result = search(e);
        	if (result == nullptr) {
            		throw std::out_of_range("Elemento no encontrado en el árbol");
        	}
        	return result->elem;
   	 }

	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
                bst.print_inorder(out, bst.root);
                return out;
        }

	int size() const{
		return nelem;
	}

	BSTree(){
		root = nullptr;
	}

	void remove(T e){
		remove (root, e);
	}


    
};

#endif

/* =========================================== //
    Jose Alberto Aguilar Sanchez - A01735612
    Binary Search Tree
// =========================================== */

#ifndef BST_H
#define BST_H

#include <string>
#include <sstream>

// Encabezado clase compadre BST
template <class T> class BST;

// -- CLASE AUXILIAR NODO -- //
template <class T>
class TreeNode {
private:
	// Tipo de valor y nod derecho e izquierdo
	T value;
	TreeNode *left, *right; 

public:
	// Constructores // 
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);

	// Metodos principales //
	void add(T);
	bool find(T);
	void removeChilds();
	void ancestors(std::stringstream&, T) const;

	// Metodos auxilaires //
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	void postorder(std::stringstream&) const;
	void levelbylevel(std::stringstream&, const TreeNode<T>*, int) const;

	// Clase compadre BST //
	friend class BST<T>;
};

// -- CONSTRCUTORES -- //

// Por default (Iniciamos todo en 0)
template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(0), right(0){}

// Por parametros
template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) : value(val), left(le), right(ri) {}

// -- METODOS -- //

// Agregar
template <class T>
void TreeNode<T>::add(T val) {
	// A la izquierda
	if (val < value) {
		if (left != 0) {
			left->add(val);
		} else {
			left = new TreeNode<T>(val);
		}
	// A la derecha 
	} else {
		if (right != 0) {
			right->add(val);
		} else {
			right = new TreeNode<T>(val);
		}
	}
}

// Buscamos 
template <class T>
bool TreeNode<T>::find(T val) {
	// Caso base (Elemento encontrado)
	if (val == value) {
		return true; //Si el valor es igual al valor del nodo, valor encontrado
	}
	// Si es menor... 
	else if (val < value) {
		return (left != 0 && left->find(val)); // ...Busca en el hijo izquierdo
	}
	// Si es mayor---
	else if (val > value) {
		return (right != 0 && right->find(val)); // ...busca en el hijo derecho
	}

	return false; // Valor no hayado
}

// Eliminamos hijos
template <class T>
void TreeNode<T>::removeChilds() {
	// Si hay hijos a la izquierda...
	if (left != 0) {
		// Llamate recurisvamante y elimina 
		left->removeChilds();
		delete left;
		left = 0;
	}
	// Si hay hijos a la drecha...
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

// Anceestros (Devulve los ancestros. xd)
template <class T>
void TreeNode<T>::ancestors(std::stringstream &aux, T val) const {
	// Mientras que no llegemos al nodo buscado...
    if (value != val) {
		// Sino esta vacio, ponle espacios 
        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << value; // Agrega el valor actual al string

		// Si el valor es MENOR al nodo actual y LEFT no esta vacio, busca aqui
        if (val < value && left != nullptr) {
            left->ancestors(aux, val);
        }
		// Si el valor es MAYOR al nodo actual y RIGHT no esta vacio, busca aqui
        if (val > value && right != nullptr) {
            right->ancestors(aux, val);
        }
    }
}

// -- METODOS AUXILAIRES PARA FUNCION VISIT BST -- //

// Inorder
template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

// Preorder
template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

// PostOrder
template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
	}
	if (right != 0) {
		right->postorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
}

// Por nivel (Level By Level)
template <class T>
void TreeNode<T>::levelbylevel(std::stringstream &aux, const TreeNode<T>* node, int level) const {
    if (level == 1) {
		if (aux.tellp() != 1) {
			aux << " ";
		}
        aux << node->value;
    } else if (level > 1) {
        if (node->left != nullptr) {
            levelbylevel(aux, node->left, level - 1);
        }
        if (node->right != nullptr) {
            levelbylevel(aux, node->right, level - 1);
        }
    }
}

// -- CLASE PRINCIPAL BST -- //

template <class T>
class BST {
private:
	// Nodo raiz
	TreeNode<T> *root;

public:
	// Constructor y destructor
	BST();
	~BST();

	// Metodos requeridos //
	bool empty() const;
	void add(T);
	bool find(T) const;
	void removeAll();
	// Metodos Auxiliares //
	std::string preorder() const;
	std::string inorder() const;
	std::string postorder() const;
	std::string levelbylevelstring() const;
	std::string visit() const;
	// Metodos Principales //
	int height() const;
	int heightAux(const TreeNode<T>*) const;
	std::string ancestors(T) const;
	int whatlevelamI(T) const;
	int findLevel(TreeNode<T>*, T, int) const;
};

// Constructor por omision 
template <class T>
BST<T>::BST() : root(0) {}

// Destrcutor
template <class T>
BST<T>::~BST() {
	removeAll();
}

// Metodo Auxiliar para destrucotr
template <class T>
void BST<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

// Vacio?
template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

// Agregar
template <class T>
void BST<T>::add(T val) {
	if (root != 0) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root = new TreeNode<T>(val);
	}
}

// Buscar
template <class T>	
bool BST<T>::find(T val) const {
	if (root != 0) {
		return root->find(val);
	} else {
		return false;
	}
}

// -- METODOS AUXILAIRES -- //

template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::postorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::levelbylevelstring() const {
	std::stringstream aux;
	int h = height();

	aux << "[";
	if (!empty()) {
    	for (int i = 1; i <= h; i++) {
        	root->levelbylevel(aux, root, i);
    	}
		
	}
	aux << "]";
	return aux.str();
}

// -- METODOS PRINCIPALES -- //

// Imprimir el arbol de diferentes formas
template <class T>
std::string BST<T>::visit() const {
	std::stringstream aux;

	/*
	1. Preodred 
	2. In order 
	3. Post Order
	4. Level Order
	*/

	aux << preorder() << "\n";
	aux << inorder() << "\n";
	aux << postorder() << "\n";	
	aux << levelbylevelstring();

	return aux.str();
}

// Alutra Auxiliar para recursion 
template <class T>
int BST<T>::heightAux(const TreeNode<T>* node) const {
	int lheight = 0, rheight = 0;
    if (node == 0) {
        return 0;
    } else {
        lheight = heightAux(node->left);
        rheight = heightAux(node->right);
        if (lheight > rheight) {
            return(lheight + 1);
        } else {
            return(rheight + 1);
        }
    }
}

// Llamamos recursivamante
template <class T>
int BST<T>::height() const {
    return heightAux(root);
}

// Ancestros de un valor dado
template <class T>
std::string BST<T>::ancestors(T val) const {
    std::stringstream aux;
	if (!find(val)) {
		return "[]";
	}
    aux << "[";
    root->ancestors(aux, val);
    aux << "]";
    return aux.str();
}

// Función auxiliar para buscaer mi nivel 
template <class T>
int BST<T>::findLevel(TreeNode<T>* node, T val, int level) const {
	// No se encontro el valor
    if (node == nullptr) {
        return -1; 
    }

	// El valor esta en este nivel 
    if (val == node->value) {
        return level; 
	// Si el valor es menor busca por la izquierda
    } else if (val < node->value) {
        return findLevel(node->left, val, level + 1); 
	// Sino busca por la derecha
    } else { 
        return findLevel(node->right, val, level + 1); // Busca en el subárbol derecho.
    }
}

// En que nivel estoy? (LLamado recursivo)
template <class T>
int BST<T>::whatlevelamI(T val) const {
    return findLevel(root, val, 1); 
}

#endif
#pragma once
template <typename T>
struct NodoLista{
	T val;
	NodoLista* next;

	NodoLista(T val, NodoLista* next) :val(val), next(next) { }
};



template <typename T>
class ListaEnlazada {
private:
	NodoLista<T>* head = nullptr;
	NodoLista<T>* cola = nullptr;
public:
	NodoLista<T>** buscarPorID(const int& id);
	NodoLista<T>* insertar(const T& val);
	void eliminar(NodoLista<T>** p);

	void print() const;
};

#include "MetodosLista.h"

#pragma once
template<typename T>
NodoLista<T>** ListaEnlazada<T>::buscarPorID(const int& id) {
	NodoLista<T>**p = &head;
	for (; head != cola; p = &((*p)->next)) {
		if ((*p)->val.id == id)
			return p;
	}
	if ((*p)->val.id == id)
		return p;
	return nullptr;
}

template<typename T>
NodoLista<T>* ListaEnlazada<T>::insertar(const T& val) {
	NodoLista<T>* p = new NodoLista<T>(val, nullptr);
	if (head == nullptr) {
		head = cola = p;
	}
	else{
		cola->next = p;
		cola = cola->next;
	}
	return p;
}


template<typename T>
void ListaEnlazada<T>::eliminar(NodoLista<T>** p) {
	NodoLista<T>* nodoAEliminar = *p;
	if (nodoAEliminar == cola) {
		NodoLista<T>* anteriorCola = head;
		for (; anteriorCola->next->next != nullptr; anteriorCola = anteriorCola->next);
		cola = anteriorCola;
	}
	*p = (*p)->next;
	delete nodoAEliminar;
}

template<typename T>
void ListaEnlazada<T>::print() const {
	cout << " Id   Camiseta   Apellido        Posicion     Edad  Seleccion" << endl;
	for (NodoLista<T>* const* itr = &head; *itr != nullptr; itr = &((*itr)->next)) {
		(*itr)->val.print();
		cout << '\n';
	}
	cout << endl;
}
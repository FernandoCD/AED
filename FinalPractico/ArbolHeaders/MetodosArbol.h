#include "Arbol.h"
#pragma once
template <typename T>
bool ArbolAVL<T>::find(const T& val, NodoArbolIndex**& p) {
	for (p = &Copa; 
		*p && (*p)->dato != val;
		Vec.push_back(p),
		p = &((*p)->hijo[(*p)->dato < val]));
	Vec.push_back(p);
	return *p != nullptr;
}

template<typename T>
bool ArbolAVL<T>::insert(const T& val, NodoLista<infoJugador>* ptrNodoLista) {
	Vec.clear();
	NodoArbolIndex** p;
	if (find(val, p)) { 
		(*p)->vectorColisiones.push_back(ptrNodoLista);
		return false; 
	}
	*p = new NodoArbolIndex(val);
	(*p)->vectorColisiones.push_back(ptrNodoLista);
	comprobarInsertado();
	return true;
}


template<typename T>
bool ArbolAVL<T>::remove(const T& val) {
	Vec.clear();
	NodoArbolIndex** p;
	if (!find(val, p)) return false;
	
	if ((*p)->hijo[0] && (*p)->hijo[1]) {
		NodoArbolIndex** q = Rep(p);
		(*p)->dato = (*q)->dato;
		(*p)->vectorColisiones = (*q)->vectorColisiones;
		p = q;
	}

	NodoArbolIndex* t = *p;
	*p = (*p)->hijo[(*p)->hijo[1] != 0];
	delete t;

	comprobarBorrado();
	return true;
}

template<typename T>
void ArbolAVL<T>::imprimirVector()
{
	int prof = 0;//Codigo sacado de GetProfundidad();
	const NodoArbolIndex* p = Copa;
	for (vector<NodoArbolIndex*> nodos(1, const_cast<NodoArbolIndex*>(p)); !all_of(nodos.begin(), nodos.end(), [](NodoArbolIndex* n) {return !n; }); ++prof) {
		vector<NodoArbolIndex*> nuevosNodos;
		for (NodoArbolIndex* itr : nodos) {
			if (itr) {
				cout << itr->dato;
				cout << "->[";
				for (auto& i : itr->vectorColisiones) {
					cout << i->val.apellido << ',';
				}
				cout << "]" << endl;
				nuevosNodos.push_back(itr->hijo[0]);
				nuevosNodos.push_back(itr->hijo[1]);
			}
			else {
				nuevosNodos.push_back(nullptr);
				nuevosNodos.push_back(nullptr);
			}
		}
		nodos = move(nuevosNodos);
	}

}

template<typename T>
void ArbolAVL<T>::borrarCascada(NodoLista<infoJugador>* ptrNodoLista, T campo)
{
	NodoArbolIndex** p;
	if (find(campo, p)) {
		(*p)->vectorColisiones.erase(std::find((*p)->vectorColisiones.begin(), (*p)->vectorColisiones.end(), ptrNodoLista));
		if ((*p)->vectorColisiones.size() == 0) {
			remove(campo);    //Remover el nodo
		}
	}
}

///Metodos auxiliares
template<typename T>
NodoArbolIndex<T>** ArbolAVL<T>::Rep(NodoArbolIndex**& p)
{
	NodoArbolIndex** q;
	for (q = &(*p)->hijo[0]; (*q)->hijo[1] ; q = &(*q)->hijo[1]);
	return q;
}

///Metodos especiales
template<typename T>
int ArbolAVL<T>::getProfundidad(const NodoArbolIndex* p) {
	int prof = 0;
	for (vector<NodoArbolIndex*> nodos(1, const_cast<NodoArbolIndex*>(p)); !all_of(nodos.begin(), nodos.end(), [](NodoArbolIndex* n) {return !n; }); ++prof) {
		vector<NodoArbolIndex*> nuevosNodos;
		for (NodoArbolIndex* itr : nodos) {
			if (itr) {
				nuevosNodos.push_back(itr->hijo[0]);
				nuevosNodos.push_back(itr->hijo[1]);
			}
			else {
				nuevosNodos.push_back(nullptr);
				nuevosNodos.push_back(nullptr);
			}
		}
		nodos = move(nuevosNodos);
	}
	return prof;
}

template<typename T>
inline int ArbolAVL<T>::getDiferencia(const NodoArbolIndex* p)
{
	if(!p) return false;
	return getProfundidad(p->hijo[1]) - getProfundidad(p->hijo[0]);
}

template<typename T>
void ArbolAVL<T>::comprobarInsertado() {
	if (Vec.empty()) return;
	for (int pos = Vec.size() - 1; pos >= 0; --pos) {
		if (abs(getDiferencia(*Vec[pos])) == 2) {
			balancearInsertado(pos);
		}
	}	
}

template<typename T>
void ArbolAVL<T>::comprobarBorrado() {
	if (Vec.empty()) return;
	for (int pos = Vec.size() - 1; pos >= 0; --pos) {
		if (abs(getDiferencia(*Vec[pos])) == 2) {
			balancearBorrado(pos);
		}
	}
}

template<typename T>
void ArbolAVL<T>::balancearInsertado(const int& pos)
{
	NodoArbolIndex** abuelo = Vec[pos];
	NodoArbolIndex** padre = Vec[pos+1];
	NodoArbolIndex** hijo = Vec[pos+2];

	int difAbuelo = getDiferencia(*abuelo);
	int difPadre = getDiferencia(*padre);

	balancear(abuelo, padre, hijo, difAbuelo, difPadre);
}

template<typename T>
void ArbolAVL<T>::balancearBorrado(const int& pos)
{
	NodoArbolIndex** abuelo = Vec[pos];
	bool direccion = getProfundidad((*abuelo)->hijo[0]) < getProfundidad((*abuelo)->hijo[1]);
	NodoArbolIndex** padre = &(*abuelo)->hijo[direccion];
	int difAbuelo = getDiferencia(*abuelo);
	int difPadre = getDiferencia(*padre);
	NodoArbolIndex** hijo = &(*padre)->hijo[difPadre >= 1];

	balancear(abuelo, padre, hijo, difAbuelo, difPadre);
}

template<typename T>
void ArbolAVL<T>::balancear(NodoArbolIndex** abuelo, NodoArbolIndex** padre, NodoArbolIndex** hijo, int difAbuelo, int difPadre) {
	NodoArbolIndex** temp = abuelo;
	auto RR = [&]() {
		NodoArbolIndex* aux = *abuelo;
		*abuelo = *padre;
		aux->hijo[1] = (*abuelo)->hijo[0];
		(*abuelo)->hijo[0] = aux;
	};
	auto LL = [&]() {
		NodoArbolIndex* aux = *abuelo;
		*abuelo = *padre;
		aux->hijo[0] = (*abuelo)->hijo[1];
		(*abuelo)->hijo[1] = aux;
	};

	if (difAbuelo > 0) { //RR o LR
		if (difPadre >= 0) {//RR
			RR();
		}
		else { //LR
			abuelo = padre;
			padre = hijo;
			hijo = &(*hijo)->hijo[0];
			LL();
			abuelo = temp;
			padre = &(*abuelo)->hijo[1];
			hijo = &(*padre)->hijo[1];
			RR();
		}
	}
	else { //LL o RL
		if (difPadre >= 0) { // RL
			abuelo = padre;
			padre = hijo;
			hijo = &(*hijo)->hijo[1];
			RR();
			abuelo = temp;
			padre = &(*abuelo)->hijo[0];
			hijo = &(*padre)->hijo[0];
			LL();
		}
		else { //LL
			LL();
		}
	}
}

template<typename T>
void ArbolAVL<T>::visualizarNodos()
{
	auto calcularEspacios = [](const int x) {
		if (x < 0) return 0;
		int rpta = 2;
		for (int i = 0; i < x; ++i, rpta = rpta * 2 + 2);
		return rpta;
	};
	auto hacerEspacios = [](const int n) {
		for (int i = 0; i < n; ++i) {
			cout.put(' ');
		}
	};

	NodoArbolIndex* head = Copa;
	int prof_1 = getProfundidad(head->hijo[0]);
	int prof_2 = getProfundidad(head->hijo[1]);
	int max_profundidad = (prof_1 > prof_2 ? prof_1 : prof_2);

	int nivel = 1;
	for (vector<NodoArbolIndex*> niveles(1, head); !all_of(niveles.begin(), niveles.end(), [](NodoArbolIndex* n) {return !n; }); ++nivel) {
		vector<NodoArbolIndex*> nuevosNiveles;
		hacerEspacios(calcularEspacios(max_profundidad - nivel));

		for (NodoArbolIndex* pn : niveles) {
			if (pn) {
				cout << setfill('0') << setw(2) << pn->dato;
				nuevosNiveles.push_back(pn->hijo[0]);
				nuevosNiveles.push_back(pn->hijo[1]);
			}
			else {
				cout << "  ";
				nuevosNiveles.push_back(nullptr);
				nuevosNiveles.push_back(nullptr);
			}
			hacerEspacios(calcularEspacios(max_profundidad - nivel + 1));
		}
		niveles = move(nuevosNiveles);
		cout << endl;
	}
}
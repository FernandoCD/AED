#pragma once

static vector<string> definicionDePosicion{ "Portero","Defensa","Mediocampista","Delantero" };

struct infoJugador {
	int id;
	short int nroCamiseta;
	string apellido;
	short int posicion;
	short int edad;
	string seleccion;

	infoJugador(int id, short int nroCamiseta, string apellido, short int posicion, short int edad, string seleccion)
		:id(id), nroCamiseta(nroCamiseta), apellido(apellido), posicion(posicion), edad(edad), seleccion(seleccion) {}

	void print() {
		cout << setw(3) << id << "-> [" << setw(3) << nroCamiseta << ", " 
			<< setw(15) << apellido << ", " << setw(15) << definicionDePosicion[posicion] << ", " <<  setw(3) << edad << ", " << setw(8) << seleccion << ']';
	}
};

template<typename T>
struct NodoArbolIndex
{
	T dato;
	NodoArbolIndex<T>* hijo[2];
	vector< NodoLista<infoJugador>* > vectorColisiones;
	NodoArbolIndex(const T val) :dato(val), hijo{ nullptr,nullptr } { ; }
};


template<typename T>
class ArbolAVL
{
public:
	using self = ArbolAVL<T>;
	using Type = T;
	using NodoArbolIndex = NodoArbolIndex<T>;

	NodoArbolIndex* Copa;
	std::vector<NodoArbolIndex**> Vec;
public:
	ArbolAVL() :Copa(nullptr) { ; }
	bool find(const T& val, NodoArbolIndex**& p);
	bool insert(const T& val, NodoLista<infoJugador>* ptrNodoLista);
	bool remove(const T& val);
	void imprimirVector();
	void visualizarNodos();

	void borrarCascada(NodoLista<infoJugador>* ptrNodoLista, T campo);
	
private:
	///Metodos Binarios
	NodoArbolIndex** Rep(NodoArbolIndex**& p);
	NodoArbolIndex* getPuntCopa() { return Copa; }

	///Metodos AVL
	int getProfundidad(const NodoArbolIndex* p);
	void comprobarInsertado();
	void comprobarBorrado();
	int getDiferencia(const NodoArbolIndex* p);
	void balancearInsertado(const int & pos);
	void balancearBorrado(const int & pos);

	void balancear(NodoArbolIndex ** abuelo, NodoArbolIndex ** padre, NodoArbolIndex ** hijo, int difAbuelo, int difPadre);
	
};


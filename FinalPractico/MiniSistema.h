#pragma once

static bool factorOrdenacionPorCamisetas(NodoLista<infoJugador>* ptrNodo1, NodoLista<infoJugador>* ptrNodo2)
{
	return ptrNodo1->val.nroCamiseta < ptrNodo2->val.nroCamiseta;
}

class MiniSistema
{
private:
	ListaEnlazada<infoJugador> todosLosJugadores;
	int currentId = 1;

	ArbolAVL<short int> CampoCamisetas;
	ArbolAVL<string>    CampoApellido;
	ArbolAVL<short int> CampoPosicion;
	ArbolAVL<short int> CampoEdad;
	ArbolAVL<string>    CampoSeleccion;

public:
	MiniSistema() 
	{
		importarJugadoresTXT();
	}

	void insertarJugador(short int nroCamiseta, string apellido, short int posicion, short int edad, string seleccion)
	{
		infoJugador infoJug(currentId++, nroCamiseta, apellido, posicion, edad, seleccion);
		NodoLista<infoJugador>* p = todosLosJugadores.insertar(infoJug);

		CampoCamisetas.insert(nroCamiseta, p);
		CampoApellido.insert(apellido, p);
		CampoPosicion.insert(posicion, p);
		CampoEdad.insert(edad, p);
		CampoSeleccion.insert(seleccion, p);
	}

	void removerJugador(int id) {
		NodoLista<infoJugador>** p = buscarID(id);
		CampoCamisetas.borrarCascada(*p, (*p)->val.nroCamiseta);
		CampoApellido.borrarCascada(*p, (*p)->val.apellido);
		CampoPosicion.borrarCascada(*p, (*p)->val.posicion);
		CampoEdad.borrarCascada(*p, (*p)->val.edad);
		CampoSeleccion.borrarCascada(*p, (*p)->val.seleccion);
		todosLosJugadores.eliminar(p);
	}

	NodoLista<infoJugador>** buscarID(int id)
	{
		return todosLosJugadores.buscarPorID(id);
	}

	void imprimirTodosLosJugadores()
	{
		todosLosJugadores.print();
	}

	void buscarPorSeleccion(string equipo) {
		NodoArbolIndex<string> **p;
		CampoSeleccion.find(equipo, p);
		if (*p) imprimirVector((*p)->vectorColisiones);
	}
	void buscarPorPosicion(short int pos) {
		NodoArbolIndex<short int> **p;
		CampoPosicion.find(pos, p);
		if (*p) imprimirVector((*p)->vectorColisiones);
	}
	void buscarPorRangoEdades(short int edadMin, short int edadMax) {
		NodoArbolIndex<short int> **p;
		vector< NodoLista<infoJugador>* > acumulador;
		for (short int i = edadMin; i <= edadMax; ++i) {
			CampoEdad.find(i, p);
			if (*p) {
				for (auto& itr : (*p)->vectorColisiones) {
					acumulador.push_back(itr);
				}
			}
		}
		imprimirVector(acumulador);
	}

	void imprimirVector(vector< NodoLista<infoJugador>* >& vec) {
		std::sort(vec.begin(), vec.end(), factorOrdenacionPorCamisetas);
		for (NodoLista<infoJugador>* p : vec) {
			p->val.print();
			cout << endl;
		}
	}

	void imprimirArbol() {
		cout << "Campo de Camisetas" << endl;
		CampoCamisetas.visualizarNodos();
		CampoCamisetas.imprimirVector();
		cout << "------------------------------------" << endl;
		cout << "Campo de Apellidos" << endl;
		CampoApellido.visualizarNodos();
		CampoApellido.imprimirVector();
		cout << "------------------------------------" << endl;
		cout << "Campo de Posiciones" << endl;
		CampoPosicion.visualizarNodos();
		CampoPosicion.imprimirVector();
		cout << "------------------------------------" << endl;
		cout << "Campo de Edades" << endl;
		CampoEdad.visualizarNodos();
		CampoEdad.imprimirVector();
		cout << "------------------------------------" << endl;
		cout << "Campo de Selecciones" << endl;
		CampoSeleccion.visualizarNodos();
		CampoSeleccion.imprimirVector();
	}


	void importarJugadoresTXT() {
		ifstream inputFile("input/Jugadores.txt");
		if (!inputFile.is_open()) {
			cout << "No se puede abrir el archivo denominado Jugadores.txt" << endl;
		}

		int nroCamiseta;
		string apellido;
		short int posicion;
		short int edad;
		string seleccion;

		while (!inputFile.eof())
		{
			inputFile >> nroCamiseta;
			inputFile >> apellido;
			inputFile >> posicion;
			inputFile >> edad;
			inputFile >> seleccion;
			insertarJugador(nroCamiseta, apellido, posicion, edad, seleccion);
		}
	}

	void Imprimirleyenda()
	{
		cout << "         LEYENDA        " << endl;
		cout << " POSICIONES: ";
		for (int i = 0; i < 4; ++i) {
			cout << i << " = " << definicionDePosicion[i] << "    ";
		}

	}
};

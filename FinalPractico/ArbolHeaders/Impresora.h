#pragma once
///Metodos de impresiones
//
template<typename T>
void Impresora<T>::visualizarNodos()
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

	NodoArbolIndex* head = arbol->getPuntCopa();
	int prof_1 = arbol->getProfundidad(head->hijo[0]);
	int prof_2 = arbol->getProfundidad(head->hijo[1]);
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

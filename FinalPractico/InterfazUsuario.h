#pragma once
class interfazUsuario
{
private:
	MiniSistema miniSistema;
public:
	void ejecutar() 
	{
		
		int input;
		do {
			system("CLS");
			miniSistema.Imprimirleyenda();
			cout << "\n" << endl;

			cout << "            TABLA          " << endl;
			miniSistema.imprimirTodosLosJugadores();
			cout << "\n\n\n" << endl;
			
			verComandos();
			input = entrada();
			procesarEntrada(input);
			
			system("PAUSE");

			
		} while (input != 10);
	}
	void verComandos()
	{
		cout << "1.- Ingresar un Jugador" << endl;
		cout << "2.- Borra un jugador" << endl;
		cout << "3.- Imprimir por seleccion" << endl;
		cout << "4.- Imprimir por posicion" << endl;
		cout << "5.- Imprimir por rango de edades" << endl;
		cout << "10.- Salir" << endl;
	}
	int entrada() {
		int i;
		cout.put('>');
		cin >> i;
		return i;
	}

	void procesarEntrada(int input) {
		switch (input)
		{
		case 1: 
			{
				short int nroCamiseta;
				string apellido;
				short int posicion;
				short int edad;
				string seleccion;
				cout << "nroCamiseta:      "; cin >> nroCamiseta;
				cout << "apellido:         "; cin >> apellido;
				cout << "posicion(leyenda):"; cin >> posicion;
				cout << "edad:             "; cin >> edad;
				cout << "seleccion:        "; cin >> seleccion;

				miniSistema.insertarJugador(nroCamiseta, apellido, posicion, edad, seleccion);
			}
			break;

		case 2:
			int id;
			cout << "id: "; cin >> id;
			miniSistema.removerJugador(id);

			break;
		case 3:
		{
			string seleccion;
			cout << "Seleccion: ";		 cin >> seleccion;
			miniSistema.buscarPorSeleccion(seleccion);
		}
			break;
		case 4:
		
			int pos;
			cout << "Posicion: ";        cin >> pos;
			miniSistema.buscarPorPosicion(pos);
			break;

		case 5:
			int edadMinima, edadMaxima;
			cout << "edadMinima: ";        cin >> edadMinima;
			cout << "edadMaxima: ";        cin >> edadMaxima;
			miniSistema.buscarPorRangoEdades(edadMinima, edadMaxima);
			break;
			
		case 10:
			cout << "Saliendo" << endl;
			break;

		default:
			cout << "No es una entrada valida" << endl;
			break;
		}
	}
};
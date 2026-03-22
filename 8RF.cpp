#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <limits>
#include <cmath>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

const int N = 8;
int tablero[N][N];
bool solucionEncontrada = false;

// Variables globales para el modo de dos jugadores
int puntuacionJugador1 = 10;
int puntuacionJugador2 = 10;
string nombreJugador1 = "Jugador 1";
string nombreJugador2 = "Jugador 2";
int colorJugador1 = 11; // Azul claro por defecto
int colorJugador2 = 13; // Fucsia por defecto

// Nombres de los participantes
const string PARTICIPANTES[] = {"[John Fredy Cordoba Oquendo]", "[Luis Fernando Puentes Burgos]", "[Joel Mateo Balanta Moreno]"};
const int NUM_PARTICIPANTES = 3;

// 92 soluciones únicas predefinidas para el problema de las 8 reinas
const int SOLUCIONES[92][N] = {
    {0, 4, 7, 5, 2, 6, 1, 3}, {0, 5, 7, 2, 6, 3, 1, 4}, {0, 6, 3, 5, 7, 1, 4, 2}, {0, 6, 4, 7, 1, 3, 5, 2},
    {1, 3, 5, 7, 2, 0, 6, 4}, {1, 4, 6, 0, 2, 5, 7, 3}, {1, 5, 7, 2, 0, 3, 6, 4}, {1, 6, 2, 5, 7, 4, 0, 3},
    {2, 0, 6, 4, 7, 1, 3, 5}, {2, 4, 6, 0, 3, 1, 7, 5}, {2, 5, 7, 0, 3, 6, 4, 1}, {2, 6, 1, 7, 4, 0, 3, 5},
    {3, 0, 4, 7, 1, 5, 2, 6}, {3, 0, 4, 7, 5, 2, 6, 1}, {3, 1, 7, 4, 6, 0, 2, 5}, {3, 5, 2, 0, 6, 1, 7, 4},
    {3, 5, 2, 6, 1, 7, 4, 0}, {3, 5, 2, 6, 4, 1, 7, 0}, {3, 5, 7, 1, 4, 2, 0, 6}, {3, 5, 7, 4, 1, 6, 0, 2},
    {3, 6, 0, 7, 4, 1, 5, 2}, {3, 6, 2, 5, 7, 1, 4, 0}, {3, 6, 4, 1, 5, 7, 2, 0}, {4, 0, 3, 5, 7, 2, 6, 1},
    {4, 0, 5, 7, 2, 6, 1, 3}, {4, 1, 5, 0, 6, 2, 7, 3}, {4, 1, 5, 2, 6, 0, 3, 7}, {4, 1, 5, 2, 6, 3, 7, 0},
    {4, 1, 5, 7, 2, 0, 6, 3}, {4, 1, 7, 0, 3, 6, 2, 5}, {4, 1, 7, 5, 2, 6, 0, 3}, {4, 2, 0, 5, 7, 1, 3, 6},
    {4, 2, 0, 6, 1, 7, 5, 3}, {4, 2, 5, 7, 0, 3, 6, 1}, {4, 2, 7, 3, 6, 0, 5, 1}, {4, 3, 0, 5, 7, 1, 6, 2},
    {4, 3, 1, 6, 2, 5, 7, 0}, {4, 3, 6, 2, 7, 5, 0, 1}, {4, 6, 0, 3, 5, 7, 1, 2}, {4, 6, 0, 7, 1, 3, 5, 2},
    {4, 6, 1, 3, 5, 7, 2, 0}, {4, 6, 1, 5, 2, 0, 7, 3}, {4, 6, 1, 5, 2, 7, 0, 3}, {5, 0, 4, 1, 7, 2, 6, 3},
    {5, 0, 4, 6, 1, 3, 7, 2}, {5, 1, 6, 0, 3, 7, 4, 2}, {5, 1, 6, 2, 0, 3, 7, 4}, {5, 1, 6, 4, 2, 0, 3, 7},
    {5, 2, 0, 6, 4, 7, 1, 3}, {5, 2, 0, 7, 3, 1, 6, 4}, {5, 2, 4, 6, 0, 3, 1, 7}, {5, 2, 6, 1, 3, 7, 0, 4},
    {5, 2, 6, 1, 7, 4, 0, 3}, {5, 3, 0, 4, 7, 1, 6, 2}, {5, 3, 0, 6, 1, 4, 2, 7}, {5, 3, 1, 7, 4, 6, 0, 2},
    {5, 3, 6, 0, 2, 4, 1, 7}, {5, 3, 6, 0, 2, 7, 1, 4}, {5, 3, 6, 1, 7, 4, 2, 0}, {5, 3, 6, 2, 0, 7, 4, 1},
    {5, 7, 1, 3, 0, 6, 4, 2}, {6, 0, 2, 7, 5, 3, 1, 4}, {6, 1, 3, 5, 7, 2, 4, 0}, {6, 1, 4, 2, 0, 5, 7, 3},
    {6, 2, 0, 5, 7, 4, 1, 3}, {6, 2, 0, 7, 5, 3, 1, 4}, {6, 2, 5, 1, 4, 0, 3, 7}, {6, 3, 0, 4, 7, 1, 5, 2},
    {6, 3, 1, 4, 7, 5, 2, 0}, {6, 3, 1, 7, 5, 0, 2, 4}, {6, 3, 5, 0, 2, 4, 1, 7}, {6, 3, 5, 7, 2, 0, 4, 1},
    {6, 4, 1, 3, 0, 7, 5, 2}, {6, 4, 2, 0, 5, 7, 1, 3}, {6, 4, 2, 0, 5, 7, 3, 1}, {6, 4, 2, 5, 7, 1, 3, 0},
    {6, 4, 7, 1, 3, 5, 2, 0}, {7, 1, 3, 0, 6, 4, 2, 5}, {7, 1, 4, 2, 0, 5, 3, 6}, {7, 2, 0, 5, 1, 4, 6, 3},
    {7, 2, 0, 6, 1, 3, 5, 4}, {7, 2, 4, 1, 5, 3, 0, 6}, {7, 2, 4, 6, 0, 3, 1, 5}, {7, 3, 0, 2, 5, 1, 6, 4},
    {7, 3, 0, 4, 6, 1, 5, 2}, {7, 3, 0, 5, 1, 6, 4, 2}, {7, 4, 1, 3, 6, 2, 5, 0}, {7, 4, 2, 0, 6, 1, 3, 5},
    {7, 4, 2, 5, 1, 6, 3, 0}, {7, 4, 6, 1, 3, 5, 2, 0}
};
const int NUM_SOLUCIONES = 92;

// Funciones para el color de la consola
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Resetea el color de la consola
void resetColor() {
    setColor(7);
}

// Función para imprimir el tablero con colores
void imprimirTablero() {
    system("cls");

    cout << "  ";
    for (int i = 0; i < N; ++i) {
        cout << " " << i << " ";
    }
    cout << endl;

    for (int i = 0; i < N; ++i) {
        cout << i << " ";
        for (int j = 0; j < N; ++j) {
            if (tablero[i][j] != 0) {
                // Asigna color basado en si la reina es del jugador 1, 2 o de la IA
                if (tablero[i][j] == colorJugador1) {
                    setColor(colorJugador1);
                } else if (tablero[i][j] == colorJugador2) {
                    setColor(colorJugador2);
                } else if (tablero[i][j] == 1) { // Para la opción de resolver, todas del mismo color
                    setColor(14); // Un color amarillo brillante
                }
                cout << " Q ";
            } else {
                setColor(15);
                cout << " - ";
            }
        }
        resetColor();
        cout << endl;
    }
}

// Función para verificar si una posición es segura para una reina
bool esSegura(int fila, int columna) {
    // Verifica si hay una reina en la misma fila, columna o diagonal.
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (tablero[i][j] != 0) {
                if (i == fila || j == columna || abs(i - fila) == abs(j - columna)) {
                    if (i != fila || j != columna) { // Para no considerar la misma posición
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Función de backtracking para resolver el problema de forma recursiva
bool resolver(int reinasColocadas) {
    if (reinasColocadas >= N) {
        solucionEncontrada = true;
        return true;
    }

    for (int fila = 0; fila < N; ++fila) {
        for (int col = 0; col < N; ++col) {
            if (tablero[fila][col] == 0 && esSegura(fila, col)) {
                tablero[fila][col] = reinasColocadas + 1;
                if (resolver(reinasColocadas + 1)) {
                    return true;
                }
                tablero[fila][col] = 0;
            }
        }
    }
    return false;
}

// Función para predecir y mostrar una solución
void predecir() {
    int fila1 = -1, col1 = -1;
    int fila2 = -1, col2 = -1;
    int reinasIniciales = 0;

    cout << "Modo de Prediccion" << endl;
    cout << "Puede ingresar una o dos posiciones iniciales." << endl;
    cout << "Ingrese la fila de la primera reina (-1 para omitir): ";
    while (!(cin >> fila1)) {
        cout << "Entrada no valida. Ingrese un numero: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

    if (fila1 != -1) {
        cout << "Ingrese la columna de la primera reina: ";
        while (!(cin >> col1)) {
            cout << "Entrada no valida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

        if (fila1 >= 0 && fila1 < N && col1 >= 0 && col1 < N) {
            if (esSegura(fila1, col1)) {
                tablero[fila1][col1] = 1;
                reinasIniciales++;
            } else {
                cout << "Posicion inicial no valida. No se puede colocar una reina aqui." << endl;
                return;
            }
        } else {
            cout << "Coordenadas fuera de rango." << endl;
            return;
        }
    }

    cout << "Ingrese la fila de la segunda reina (-1 para omitir): ";
    while (!(cin >> fila2)) {
        cout << "Entrada no valida. Ingrese un numero: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

    if (fila2 != -1) {
        cout << "Ingrese la columna de la segunda reina: ";
        while (!(cin >> col2)) {
            cout << "Entrada no valida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
        if (fila2 >= 0 && fila2 < N && col2 >= 0 && col2 < N) {
            if (esSegura(fila2, col2)) {
                tablero[fila2][col2] = 2;
                reinasIniciales++;
            } else {
                cout << "Posicion inicial no valida. No se puede colocar una segunda reina aqui." << endl;
                return;
            }
        } else {
            cout << "Coordenadas fuera de rango." << endl;
            return;
        }
    }

    cout << "\nPrediciendo soluciones a partir de las posiciones dadas..." << endl;
    if (resolver(reinasIniciales)) {
        imprimirTablero();
        cout << "\nSe pueden ubicar " << N << " reinas en total." << endl;
        cout << "Una posible solucion es:" << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (tablero[i][j] != 0) {
                    cout << "Reina " << tablero[i][j] << " en (" << i << ", " << j << ")" << endl;
                }
            }
        }
    } else {
        cout << "No es posible ubicar las 8 reinas a partir de las posiciones dadas." << endl;
    }
}

// Función para seleccionar color
int seleccionarColor(string nombreJugador) {
    int color;
    cout << "\nElige un color para " << nombreJugador << ":" << endl;
    cout << "1. Negro\t\t2. Azul\n3. Verde\t\t4. Aqua\n5. Rojo\t\t6. Purpura\n7. Amarillo\t\t8. Blanco\n9. Gris\t\t10. Azul Claro" << endl;
    cout << "Tu eleccion (1-10): ";
    while (!(cin >> color) || color < 1 || color > 10) {
        cout << "Opcion no valida. Intente de nuevo (1-10): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return color;
}

// Función del modo de dos jugadores
void modoDosJugadores() {
    int fila, col;
    int reinasColocadas = 0;
    int turnoActual = 1;

    // Reiniciar el tablero y puntuaciones
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            tablero[i][j] = 0;
        }
    }
    puntuacionJugador1 = 10;
    puntuacionJugador2 = 10;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

    cout << "--- Modo de Dos Jugadores ---" << endl;
    cout << "Ingrese el nombre del Jugador 1: ";
    getline(cin, nombreJugador1);
    cout << "Ingrese el nombre del Jugador 2: ";
    getline(cin, nombreJugador2);

    colorJugador1 = seleccionarColor(nombreJugador1);
    colorJugador2 = seleccionarColor(nombreJugador2);
    while (colorJugador1 == colorJugador2) {
        cout << "ANo pueden tener el mismo color! Elige de nuevo para " << nombreJugador2 << ": ";
        colorJugador2 = seleccionarColor(nombreJugador2);
    }

    cout << "\n" << nombreJugador1 << " inicia con " << puntuacionJugador1 << " puntos y color " << colorJugador1 << "." << endl;
    cout << nombreJugador2 << " inicia con " << puntuacionJugador2 << " puntos y color " << colorJugador2 << "." << endl;
    cout << "\nPara salir del juego, ingrese -1 en la fila. Ingrese 'S' para ver el puntaje." << endl;
    
    while (reinasColocadas < N) {
        imprimirTablero();
        cout << "\n--- Turno de " << (turnoActual == 1 ? nombreJugador1 : nombreJugador2) << " ---" << endl;
        cout << "Puntuacion - " << nombreJugador1 << ": " << puntuacionJugador1 << " | " << nombreJugador2 << ": " << puntuacionJugador2 << endl;
        cout << "Ingrese la fila para la reina " << reinasColocadas + 1 << " ('S' para ver puntaje, '-1' para salir): ";
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (!(cin >> fila)) {
            cin.clear();
            char temp_char;
            cin >> temp_char;
            if (toupper(temp_char) == 'S') {
                imprimirTablero();
                cout << "\n--- Puntuacion Actual ---" << endl;
                cout << nombreJugador1 << ": " << puntuacionJugador1 << " puntos." << endl;
                cout << nombreJugador2 << ": " << puntuacionJugador2 << " puntos." << endl;
                cout << "Presiona una tecla para continuar...";
                getch();
                continue;
            } else {
                cout << "Entrada no valida. Pierdes 1 punto." << endl;
                if (turnoActual == 1) {
                    puntuacionJugador1--;
                } else {
                    puntuacionJugador2--;
                }
                cout << "Presiona una tecla para continuar...";
                getch();
                turnoActual = (turnoActual == 1) ? 2 : 1;
                continue;
            }
        }

        if (fila == -1) {
            cout << "\nSaliendo del juego de dos jugadores..." << endl;
            return;
        }

        cout << "Ingrese la columna: ";
        if (!(cin >> col)) {
            cout << "Entrada no valida. Pierdes 1 punto." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (turnoActual == 1) {
                puntuacionJugador1--;
            } else {
                puntuacionJugador2--;
            }
            cout << "Presiona una tecla para continuar...";
            getch();
            turnoActual = (turnoActual == 1) ? 2 : 1;
            continue;
        }
        
        if (fila >= 0 && fila < N && col >= 0 && col < N) {
            if (tablero[fila][col] == 0 && esSegura(fila, col)) {
                reinasColocadas++;
                tablero[fila][col] = (turnoActual == 1) ? colorJugador1 : colorJugador2;
                cout << "APosicion valida! Ganas 1 punto." << endl;
                if (turnoActual == 1) {
                    puntuacionJugador1++;
                } else {
                    puntuacionJugador2++;
                }
            } else {
                cout << "APosicion invalida! Pierdes 1 punto." << endl;
                if (turnoActual == 1) {
                    puntuacionJugador1--;
                } else {
                    puntuacionJugador2--;
                }
            }
        } else {
            cout << "Coordenadas fuera de rango. Pierdes 1 punto." << endl;
            if (turnoActual == 1) {
                puntuacionJugador1--;
            } else {
                puntuacionJugador2--;
            }
        }
        cout << "Presiona una tecla para continuar...";
        getch();

        turnoActual = (turnoActual == 1) ? 2 : 1;
    }

    imprimirTablero();
    cout << "\nAFin del juego! Se han colocado 8 reinas." << endl;
    cout << "Puntuacion final:" << endl;
    cout << nombreJugador1 << ": " << puntuacionJugador1 << " puntos." << endl;
    cout << nombreJugador2 << ": " << puntuacionJugador2 << " puntos." << endl;
    if (puntuacionJugador1 > puntuacionJugador2) {
        cout << "AEl ganador es " << nombreJugador1 << "!" << endl;
    } else if (puntuacionJugador2 > puntuacionJugador1) {
        cout << "AEl ganador es " << nombreJugador2 << "!" << endl;
    } else {
        cout << "AEs un empate!" << endl;
    }
}

// Función para el modo de un jugador contra la IA
void modoContraIA() {
    int fila, col;
    int reinasColocadas = 0;
    int turnoActual = 1; // 1 para jugador, 2 para IA

    // Reiniciar el tablero y puntuaciones
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            tablero[i][j] = 0;
        }
    }
    puntuacionJugador1 = 10;
    puntuacionJugador2 = 10;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "--- Modo de Un Jugador contra la IA ---" << endl;
    cout << "Ingrese su nombre: ";
    getline(cin, nombreJugador1);
    nombreJugador2 = "IA";

    colorJugador1 = seleccionarColor(nombreJugador1);
    cout << "La IA jugará con el color opuesto." << endl;
    colorJugador2 = (colorJugador1 % 10) + 1;

    cout << "\n" << nombreJugador1 << " inicia con " << puntuacionJugador1 << " puntos." << endl;
    cout << "La IA inicia con " << puntuacionJugador2 << " puntos." << endl;
    cout << "\nPara salir del juego, ingrese -1 en la fila." << endl;

    while (reinasColocadas < N) {
        imprimirTablero();
        
        if (turnoActual == 1) { // Turno del jugador
            cout << "\n--- Tu turno, " << nombreJugador1 << " ---" << endl;
            cout << "Puntuacion - " << nombreJugador1 << ": " << puntuacionJugador1 << " | IA: " << puntuacionJugador2 << endl;
            cout << "Ingrese la fila para la reina " << reinasColocadas + 1 << ": ";
            if (!(cin >> fila)) {
                cout << "Entrada no valida. Pierdes 1 punto." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                puntuacionJugador1--;
                cout << "Presiona una tecla para continuar...";
                getch();
                turnoActual = 2; // Pasa el turno a la IA
                continue;
            }

            if (fila == -1) {
                cout << "\nSaliendo del juego..." << endl;
                return;
            }

            cout << "Ingrese la columna: ";
            if (!(cin >> col)) {
                cout << "Entrada no valida. Pierdes 1 punto." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                puntuacionJugador1--;
                cout << "Presiona una tecla para continuar...";
                getch();
                turnoActual = 2; // Pasa el turno a la IA
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (fila >= 0 && fila < N && col >= 0 && col < N) {
                if (tablero[fila][col] == 0 && esSegura(fila, col)) {
                    reinasColocadas++;
                    tablero[fila][col] = colorJugador1;
                    cout << "APosicion valida! Ganas 1 punto." << endl;
                    puntuacionJugador1++;
                } else {
                    cout << "APosicion invalida! Pierdes 1 punto." << endl;
                    puntuacionJugador1--;
                }
            } else {
                cout << "Coordenadas fuera de rango. Pierdes 1 punto." << endl;
                puntuacionJugador1--;
            }
            cout << "Presiona una tecla para continuar...";
            getch();
            turnoActual = 2; // Pasa el turno a la IA

        } else { // Turno de la IA
            cout << "\n--- Turno de la IA ---" << endl;
            cout << "Puntuacion - " << nombreJugador1 << ": " << puntuacionJugador1 << " | IA: " << puntuacionJugador2 << endl;
            
            bool movidaValidaEncontrada = false;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (tablero[i][j] == 0 && esSegura(i, j)) {
                        reinasColocadas++;
                        tablero[i][j] = colorJugador2;
                        cout << "La IA ha colocado una reina en (" << i << ", " << j << "). Gana 1 punto." << endl;
                        puntuacionJugador2++;
                        movidaValidaEncontrada = true;
                        break;
                    }
                }
                if (movidaValidaEncontrada) break;
            }

            if (!movidaValidaEncontrada) {
                cout << "La IA no pudo encontrar una posicion valida. Pierde 1 punto." << endl;
                puntuacionJugador2--;
            }

            cout << "Presiona una tecla para continuar...";
            getch();
            turnoActual = 1; // Pasa el turno al jugador
        }
    }

    imprimirTablero();
    cout << "\nAFin del juego! Se han colocado 8 reinas." << endl;
    cout << "Puntuacion final:" << endl;
    cout << nombreJugador1 << ": " << puntuacionJugador1 << " puntos." << endl;
    cout << "IA: " << puntuacionJugador2 << " puntos." << endl;
    if (puntuacionJugador1 > puntuacionJugador2) {
        cout << "AEl ganador es " << nombreJugador1 << "!" << endl;
    } else if (puntuacionJugador2 > puntuacionJugador1) {
        cout << "AEl ganador es la IA!" << endl;
    } else {
        cout << "AEs un empate!" << endl;
    }
}


// Función para mostrar las instrucciones
void mostrarInstrucciones() {
    system("cls");
    cout << "--- Instrucciones de Uso ---" << endl;
    cout << "Este programa resuelve el Problema de las 8 Reinas." << endl;
    cout << "1. Elige la opcion 'Resolver' para ver una de las 92 soluciones unicas al problema." << endl;
    cout << "2. Elige la opcion 'Modo de dos jugadores' para un juego competitivo." << endl;
    cout << "   - Cada jugador comienza con 10 puntos." << endl;
    cout << "   - El objetivo es colocar 8 reinas en el tablero sin que se maten." << endl;
    cout << "   - Ganas 1 punto por cada reina bien colocada, pierdes 1 si la posicion es incorrecta." << endl;
    cout << "   - Puedes elegir un color para tus reinas." << endl;
    cout << "   - En cualquier momento de tu turno, puedes escribir 'S' para ver la puntuacion." << endl;
    cout << "3. En el 'Modo de un jugador contra la IA', compites contra el programa." << endl;
    cout << "4. En la opcion de prediccion, puedes ingresar una o dos posiciones iniciales y el programa te dira si es posible completar el tablero a partir de ahi." << endl;
    cout << "5. Las reinas se representan con la letra 'Q' y cada una tiene un color diferente para distinguirlas." << endl;
    cout << "\nPresiona una tecla para volver al menu...";
    getch();
}

// Función para mostrar la información del grupo
void mostrarAcercaDe() {
    system("cls");
    cout << "--- Acerca de... ---" << endl;
    cout << "Algoritmo para el Problema de las 8 Reinas" << endl;
    cout << "Desarrollado por:" << endl;
    for (int i = 0; i < NUM_PARTICIPANTES; ++i) {
        cout << "- " << PARTICIPANTES[i] << endl;
    }
    cout << "\nEste proyecto fue creado como parte de la tarea de Programacion." << endl;
    cout << "Utiliza un algoritmo de backtracking para encontrar una solucion al problema." << endl;
    cout << "\nPresiona una tecla para volver al menu...";
    getch();
}

// Función para mostrar una de las 92 soluciones predefinidas
void mostrarSoluciones() {
    system("cls");
    cout << "--- Modo de Un Jugador - Soluciones ---" << endl;
    cout << "Mostrando las 92 soluciones unicas para el Problema de las 8 Reinas." << endl;

    int indiceSolucion = 0;
    while (true) {
        // Reiniciar el tablero
        for (int row = 0; row < N; ++row) {
            for (int col = 0; col < N; ++col) {
                tablero[row][col] = 0;
            }
        }
        
        // Cargar la solución actual
        for (int j = 0; j < N; ++j) {
            tablero[j][SOLUCIONES[indiceSolucion][j]] = 1;
        }

        cout << "\nSolucion #" << indiceSolucion + 1 << " de " << NUM_SOLUCIONES << ":" << endl;
        imprimirTablero();
        cout << "\nReinas en posiciones (fila, columna):" << endl;
        for (int j = 0; j < N; ++j) {
            cout << "(" << j << ", " << SOLUCIONES[indiceSolucion][j] << ") ";
        }
        cout << "\nPresiona 'N' para la siguiente, 'A' para la anterior, o 'Q' para salir...";
        char key = getch();
        if (toupper(key) == 'Q') {
            break;
        } else if (toupper(key) == 'N') {
            indiceSolucion = (indiceSolucion + 1) % NUM_SOLUCIONES;
        } else if (toupper(key) == 'A') {
            indiceSolucion = (indiceSolucion - 1 + NUM_SOLUCIONES) % NUM_SOLUCIONES;
        }
    }
}

int main() {
    int opcion;

    do {
        system("cls");
        cout << "--- Problema de las 8 Reinas ---" << endl;
        cout << "1. Resolver el problema (Ver soluciones)" << endl;
        cout << "2. Modo de dos jugadores" << endl;
        cout << "3. Modo de un jugador contra la IA" << endl;
        cout << "4. Prediccion y posiciones" << endl;
        cout << "5. Instrucciones de uso" << endl;
        cout << "6. Acerca de..." << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opcion: ";
        
        while (!(cin >> opcion)) {
            cout << "Entrada no valida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                mostrarSoluciones();
                break;
            case 2:
                modoDosJugadores();
                cout << "\nPresiona una tecla para volver al menu...";
                getch();
                break;
            case 3:
                modoContraIA();
                cout << "\nPresiona una tecla para volver al menu...";
                getch();
                break;
            case 4: {
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        tablero[i][j] = 0;
                    }
                }
                predecir();
                cout << "\nPresiona una tecla para volver al menu...";
                getch();
                break;
            }
            case 5:
                mostrarInstrucciones();
                break;
            case 6:
                mostrarAcercaDe();
                break;
            case 7:
                cout << "Saliendo del programa. Hasta luego!" << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                cout << "Presiona una tecla para continuar...";
                getch();
                break;
        }

    } while (opcion != 7);

    return 0;
}

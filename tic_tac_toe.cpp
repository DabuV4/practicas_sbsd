#include <iostream> // Para entrada (cin) y salida (cout)
#include <vector>   // Aunque no se usa vector aquí, es útil conocerlo. Usaremos array C++.
#include <limits>   // Para limpiar el buffer de entrada (cin.ignore)

// Usamos el espacio de nombres std para no escribir std::cout, std::cin, etc.
using namespace std;

// --- Constantes ---
const int TAMANO_TABLERO = 3; // Define el tamaño del tablero (3x3)

// --- Prototipos de Funciones ---
// Anunciamos las funciones que usaremos antes de definirlas.

/**
 * @brief Inicializa el tablero con números del 1 al 9.
 * @param tablero El array 2D que representa el tablero.
 */
void inicializarTablero(char tablero[TAMANO_TABLERO][TAMANO_TABLERO]);

/**
 * @brief Muestra el estado actual del tablero en la consola.
 * @param tablero El array 2D que representa el tablero.
 */
void mostrarTablero(const char tablero[TAMANO_TABLERO][TAMANO_TABLERO]);

/**
 * @brief Obtiene la jugada del usuario (el número de la casilla).
 * @param jugadorActual El símbolo del jugador ('X' o 'O').
 * @return El número de la casilla elegida por el jugador (1-9).
 */
int obtenerJugada(char jugadorActual);

/**
 * @brief Valida si una jugada es válida.
 * Verifica si el número está entre 1 y 9 y si la casilla está libre.
 * @param tablero El array 2D que representa el tablero.
 * @param casilla El número de la casilla elegida (1-9).
 * @return true si la jugada es válida, false en caso contrario.
 */
bool validarJugada(const char tablero[TAMANO_TABLERO][TAMANO_TABLERO], int casilla);

/**
 * @brief Coloca la marca del jugador en la casilla elegida del tablero.
 * @param tablero El array 2D que representa el tablero.
 * @param casilla El número de la casilla elegida (1-9).
 * @param jugadorActual El símbolo del jugador ('X' o 'O').
 */
void realizarJugada(char tablero[TAMANO_TABLERO][TAMANO_TABLERO], int casilla, char jugadorActual);

/**
 * @brief Cambia el turno al otro jugador.
 * @param jugadorActual El símbolo del jugador actual ('X' o 'O'). Se pasa por referencia para modificarlo.
 */
void cambiarTurno(char &jugadorActual);

/**
 * @brief Verifica si el jugador actual ha ganado.
 * Revisa filas, columnas y diagonales.
 * @param tablero El array 2D que representa el tablero.
 * @param jugadorActual El símbolo del jugador ('X' o 'O') que acaba de jugar.
 * @return true si el jugador actual ganó, false en caso contrario.
 */
bool verificarGanador(const char tablero[TAMANO_TABLERO][TAMANO_TABLERO], char jugadorActual);

/**
 * @brief Verifica si el juego ha terminado en empate.
 * Revisa si todas las casillas están ocupadas y no hay ganador.
 * @param tablero El array 2D que representa el tablero.
 * @return true si es empate, false en caso contrario.
 */
bool verificarEmpate(const char tablero[TAMANO_TABLERO][TAMANO_TABLERO]);

/**
 * @brief Contiene el bucle principal del juego para una partida.
 * @param tablero El array 2D que representa el tablero.
 */
void jugarPartida(char tablero[TAMANO_TABLERO][TAMANO_TABLERO]);

// --- Función Principal ---
int main() {
    // Se declara el tablero como un array 2D de caracteres
    char tablero[TAMANO_TABLERO][TAMANO_TABLERO];
    // Variable para controlar si el usuario quiere jugar de nuevo
    char jugarDeNuevo;

    // Bucle principal para permitir jugar varias partidas
    do {
        // Llama a la función que inicia y controla una partida
        jugarPartida(tablero);

        // Pregunta al usuario si desea jugar otra vez
        cout << "\n¿Quieren jugar de nuevo? (s/n): ";
        cin >> jugarDeNuevo;

        // Limpia el buffer de entrada por si el usuario escribió más de un caracter
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // El bucle se repite si el usuario ingresa 's' o 'S'
    } while (jugarDeNuevo == 's' || jugarDeNuevo == 'S');

    // Mensaje de despedida
    cout << "\n¡Gracias por jugar! Adios." << endl;

    // Indica que el programa terminó correctamente
    return 0;
}

// --- Implementación de Funciones ---

/**
 * @brief Inicializa el tablero con números del 1 al 9.
 */
void inicializarTablero(char tablero[TAMANO_TABLERO][TAMANO_TABLERO]) {
    // Variable para llevar la cuenta del número de casilla
    char contadorCasilla = '1';
    // Bucle anidado para recorrer filas (i) y columnas (j)
    for (int i = 0; i < TAMANO_TABLERO; ++i) {
        for (int j = 0; j < TAMANO_TABLERO; ++j) {
            // Asigna el número actual a la casilla
            tablero[i][j] = contadorCasilla;
            // Incrementa el número para la siguiente casilla
            contadorCasilla++;
        }
    }
}

/**
 * @brief Muestra el estado actual del tablero en la consola.
 */
void mostrarTablero(const char tablero[TAMANO_TABLERO][TAMANO_TABLERO]) {
    // Limpia la consola para mostrar el tablero actualizado (opcional)
    // system("cls"); // Para Windows
    system("clear"); // Para Linux/Mac

    cout << "\n--- Juego del Gato (Tic Tac Toe) ---" << endl;
    // Bucle anidado para recorrer filas (i) y columnas (j)
    for (int i = 0; i < TAMANO_TABLERO; ++i) {
        cout << " "; // Espacio inicial para alinear
        for (int j = 0; j < TAMANO_TABLERO; ++j) {
            // Imprime el contenido de la casilla
            cout << tablero[i][j];
            // Si no es la última columna, imprime una barra vertical
            if (j < TAMANO_TABLERO - 1) {
                cout << " | ";
            }
        }
        cout << endl; // Salto de línea al final de la fila
        // Si no es la última fila, imprime una línea separadora horizontal
        if (i < TAMANO_TABLERO - 1) {
            cout << "---|---|---" << endl;
        }
    }
    cout << "---------------------------------" << endl;
}

/**
 * @brief Obtiene la jugada del usuario (el número de la casilla).
 */
int obtenerJugada(char jugadorActual) {
    int casilla;
    // Pide al jugador actual que ingrese el número de la casilla
    cout << "Turno del jugador '" << jugadorActual << "'. Elige una casilla (1-9): ";
    // Lee el número ingresado por el usuario
    cin >> casilla;

    // --- Validación básica de entrada ---
    // Mientras la entrada falle (no sea un número) o el número esté fuera del rango 1-9
    while (cin.fail() || casilla < 1 || casilla > 9) {
        cout << "Entrada invalida. Por favor, elige un numero entre 1 y 9: ";
        // Limpia el estado de error de cin
        cin.clear();
        // Descarta la entrada incorrecta del buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Vuelve a leer la entrada
        cin >> casilla;
    }
     // Descarta cualquier caracter extra introducido después del número (ej: si escribe "5abc")
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Devuelve el número de casilla válido
    return casilla;
}

/**
 * @brief Valida si una jugada es válida.
 */
bool validarJugada(const char tablero[TAMANO_TABLERO][TAMANO_TABLERO], int casilla) {
    // Calcula la fila y columna correspondiente a la casilla (1-9)
    // (casilla - 1) convierte 1-9 a 0-8
    // / TAMANO_TABLERO da la fila (0, 1 o 2)
    // % TAMANO_TABLERO da la columna (0, 1 o 2)
    int fila = (casilla - 1) / TAMANO_TABLERO;
    int col = (casilla - 1) % TAMANO_TABLERO;

    // Verifica si la casilla está libre (no contiene 'X' ni 'O')
    if (tablero[fila][col] != 'X' && tablero[fila][col] != 'O') {
        // La casilla está libre, la jugada es válida
        return true;
    } else {
        // La casilla está ocupada, la jugada no es válida
        cout << "Casilla ocupada. Intenta de nuevo." << endl;
        return false;
    }
}

/**
 * @brief Coloca la marca del jugador en la casilla elegida del tablero.
 */
void realizarJugada(char tablero[TAMANO_TABLERO][TAMANO_TABLERO], int casilla, char jugadorActual) {
    // Calcula la fila y columna
    int fila = (casilla - 1) / TAMANO_TABLERO;
    int col = (casilla - 1) % TAMANO_TABLERO;
    // Coloca el símbolo del jugador ('X' o 'O') en esa posición
    tablero[fila][col] = jugadorActual;
}

/**
 * @brief Cambia el turno al otro jugador.
 */
void cambiarTurno(char &jugadorActual) {
    // Si el jugador actual es 'X'...
    if (jugadorActual == 'X') {
        // ...cambia a 'O'.
        jugadorActual = 'O';
    } else {
        // ...si no (era 'O'), cambia a 'X'.
        jugadorActual = 'X';
    }
}

/**
 * @brief Verifica si el jugador actual ha ganado.
 */
bool verificarGanador(const char tablero[TAMANO_TABLERO][TAMANO_TABLERO], char jugadorActual) {
    // --- Verificar Filas ---
    for (int i = 0; i < TAMANO_TABLERO; ++i) {
        // Si todas las casillas de la fila 'i' son iguales al jugador actual
        if (tablero[i][0] == jugadorActual && tablero[i][1] == jugadorActual && tablero[i][2] == jugadorActual) {
            return true; // Ganó
        }
    }

    // --- Verificar Columnas ---
    for (int j = 0; j < TAMANO_TABLERO; ++j) {
        // Si todas las casillas de la columna 'j' son iguales al jugador actual
        if (tablero[0][j] == jugadorActual && tablero[1][j] == jugadorActual && tablero[2][j] == jugadorActual) {
            return true; // Ganó
        }
    }

    // --- Verificar Diagonales ---
    // Diagonal principal (esquina superior izquierda a inferior derecha)
    if (tablero[0][0] == jugadorActual && tablero[1][1] == jugadorActual && tablero[2][2] == jugadorActual) {
        return true; // Ganó
    }
    // Diagonal secundaria (esquina superior derecha a inferior izquierda)
    if (tablero[0][2] == jugadorActual && tablero[1][1] == jugadorActual && tablero[2][0] == jugadorActual) {
        return true; // Ganó
    }

    // Si no se encontró ninguna línea ganadora
    return false; // No ganó (todavía)
}

/**
 * @brief Verifica si el juego ha terminado en empate.
 */
bool verificarEmpate(const char tablero[TAMANO_TABLERO][TAMANO_TABLERO]) {
    // Recorre todas las casillas del tablero
    for (int i = 0; i < TAMANO_TABLERO; ++i) {
        for (int j = 0; j < TAMANO_TABLERO; ++j) {
            // Si encuentra una casilla que NO sea 'X' y NO sea 'O'
            // (o sea, si encuentra un número del 1 al 9)
            if (tablero[i][j] != 'X' && tablero[i][j] != 'O') {
                // Significa que aún hay casillas libres, no es empate
                return false;
            }
        }
    }
    // Si el bucle termina sin encontrar casillas libres, es empate
    // (Asumiendo que ya se verificó que no hay ganador antes)
    return true;
}

/**
 * @brief Contiene el bucle principal del juego para una partida.
 */


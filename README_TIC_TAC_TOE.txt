Descripción del programa: "Este programa implementa el clásico juego Tic Tac Toe (Gato) para dos jugadores en una interfaz de consola. Utiliza un tablero de 3x3 representado por un array bidimensional. El programa alterna los turnos entre 'X' y 'O', valida las jugadas para asegurar que sean números entre 1 y 9 y que la casilla esté libre, detecta automáticamente cuando un jugador gana (completando una fila, columna o diagonal) o cuando se produce un empate (tablero lleno sin ganador). El código está modularizado en funciones para mayor claridad y permite reiniciar la partida al finalizar."

Instrucciones de uso:
Compilación: Guarda el código en un archivo llamado (por ejemplo) gato.cpp. Ábrelo en una terminal o símbolo del sistema y compílalo usando un compilador de C++ (como g++): g++ gato.cpp -o gato
Ejecución: En la misma terminal, ejecuta el programa compilado: ./gato (en Linux/Mac) o gato.exe (en Windows).
Jugar: El programa mostrará el tablero con casillas numeradas del 1 al 9. El jugador 'X' empieza. Ingresa el número de la casilla donde quieres jugar y presiona Enter. El programa validará tu jugada. Los turnos se alternarán hasta que alguien gane o haya un empate.

Reiniciar: Al final de la partida, el programa te preguntará si quieres jugar de nuevo. Escribe 's' (o 'S') y presiona Enter para empezar una nueva partida, o cualquier otra letra para salir.
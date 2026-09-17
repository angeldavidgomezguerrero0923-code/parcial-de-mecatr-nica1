/*
  Contador Binario de 4 bits - Programa Original
  -----------------------------------------------
  Cuenta en binario desde 0 hasta 15 utilizando 4 LEDs.
  Cada LED representa un bit del número:
    pinesLED[0] -> bit 0 (LSB)
    pinesLED[1] -> bit 1
    pinesLED[2] -> bit 2
    pinesLED[3] -> bit 3 (MSB)

  Se utiliza un arreglo (array) para guardar los pines de los LEDs,
  y operadores bit a bit (& y <<) para saber si un bit está en 1 o en 0.
*/

// Arreglo con los pines digitales usados para los 4 LEDs
const int pinesLED[4] = {2, 3, 4, 5};

// Cantidad de bits (y de LEDs) que se van a manejar
const int NUM_BITS = 4;

// Variable que controla el tiempo de espera entre cada número
// (en vez de escribir delay(500) varias veces en el código)
int waitDelay = 1000;

void setup() {
  // Configuramos cada pin de LED como salida
  for (int i = 0; i < NUM_BITS; i++) {
    pinMode(pinesLED[i], OUTPUT);
  }
}

void loop() {
  // Recorremos todos los números decimales de 0 a 15
  for (int numero = 0; numero <= 15; numero++) {
    mostrarBinario(numero);
    delay(waitDelay);
  }
}

// Función que recibe un número decimal y enciende/apaga los LEDs
// según su representación en binario
void mostrarBinario(int numero) {
  for (int bit = 0; bit < NUM_BITS; bit++) {
    // numero & (1 << bit) desplaza un 1 hacia la posición "bit"
    // y compara ese bit específico del número con una máscara.
    // Si el resultado es distinto de 0, ese bit está encendido (1).
    int estadoBit = numero & (1 << bit);

    if (estadoBit != 0) {
      digitalWrite(pinesLED[bit], HIGH);
    } else {
      digitalWrite(pinesLED[bit], LOW);
    }
  }
}

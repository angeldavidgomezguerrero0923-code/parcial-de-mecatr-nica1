/*
  Reto 4 - Mostrar solamente números pares
  -----------------------------------------
  Solo se deben mostrar: 0, 2, 4, 6, 8, 10, 12, 14

  La modificación clave está en el ciclo for del loop():
  en vez de aumentar de 1 en 1, aumentamos de 2 en 2 (numero += 2).

  También se puede verificar que un número es par usando el
  operador % (módulo): si (numero % 2 == 0) significa que el
  residuo de dividir entre 2 es cero, es decir, es par.
*/

const int pinesLED[4] = {2, 3, 4, 5};
const int NUM_BITS = 4;

int waitDelay = 500;

void setup() {
  for (int i = 0; i < NUM_BITS; i++) {
    pinMode(pinesLED[i], OUTPUT);
  }
}

void loop() {
  // Empezamos en 0 y aumentamos de 2 en 2 hasta 14
  for (int numero = 0; numero <= 14; numero += 2) {
    mostrarBinario(numero);
    delay(waitDelay);
  }
}

void mostrarBinario(int numero) {
  for (int bit = 0; bit < NUM_BITS; bit++) {
    int estadoBit = numero & (1 << bit);

    if (estadoBit != 0) {
      digitalWrite(pinesLED[bit], HIGH);
    } else {
      digitalWrite(pinesLED[bit], LOW);
    }
  }
}

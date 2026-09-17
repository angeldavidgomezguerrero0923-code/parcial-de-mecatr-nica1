/*
  Reto 2 - Contador Descendente
  -----------------------------
  Modificación del contador original para que la secuencia sea:
  15, 14, 13, ... 1, 0 y luego reinicie nuevamente desde 15.

  El cambio principal respecto al programa original está en el
  ciclo for del loop(): en vez de aumentar la variable "numero",
  ahora se decrementa.
*/

const int pinesLED[4] = {2, 3, 4, 5};
const int NUM_BITS = 4;

int waitDelay = 500; // Reto 1: tiempo entre cada número en 500 ms

void setup() {
  for (int i = 0; i < NUM_BITS; i++) {
    pinMode(pinesLED[i], OUTPUT);
  }
}

void loop() {
  // Ciclo descendente: empieza en 15 y termina en 0
  for (int numero = 15; numero >= 0; numero--) {
    mostrarBinario(numero);
    delay(waitDelay);
  }
  // Al terminar el for, el loop() vuelve a ejecutarse
  // y el conteo reinicia automáticamente desde 15.
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

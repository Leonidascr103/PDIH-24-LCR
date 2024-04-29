void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  
}

void loop() {
    // Encendido secuencial del 13 al 1
  for (int pin = 13; pin >= 6; pin--) {
    digitalWrite(pin, HIGH); // Encender el LED
    delay(100); // Esperar un poco antes de encender el siguiente LED
    digitalWrite(pin, LOW); // Apagar el LED para el próximo ciclo
  }
  
  // Encendido secuencial del 1 al 13
  for (int pin = 6; pin <= 13; pin++) {
    digitalWrite(pin, HIGH); // Encender el LED
    delay(100); // Esperar un poco antes de encender el siguiente LED
    digitalWrite(pin, LOW); // Apagar el LED para el próximo ciclo
  }
}


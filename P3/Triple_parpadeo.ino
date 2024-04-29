void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);   // encender el LED (voltaje a HIGH)
  digitalWrite(12, LOW);   // encender el LED (voltaje a HIGH)
  digitalWrite(11, LOW);   // encender el LED (voltaje a HIGH)
  delay(1500);              // esperar encendido durante 1 segundo (1000 milisegundos)
  digitalWrite(12, HIGH);    // apagar el LED (voltaje a LOW)
  digitalWrite(13, LOW);    // apagar el LED (voltaje a LOW)
  digitalWrite(11, LOW);   // encender el LED (voltaje a HIGH)
  delay(1500);              // esperar encendido durante 1 segundo (1000 milisegundos)
  digitalWrite(11, HIGH);    // apagar el LED (voltaje a LOW)
  digitalWrite(13, LOW);    // apagar el LED (voltaje a LOW)
  digitalWrite(12, LOW);   // encender el LED (voltaje a HIGH)
  delay(1500);              // esperar apagado durante 500 milisegundos
}

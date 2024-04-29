const int pinTrigger = 7;
const int pinEcho = 6;
const int pinBuzzer = 8;
float tiempo = 0;
float distancia = 0;

void setup()
{
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinBuzzer, OUTPUT);
  //Serial.begin(9600);
}

void loop()
{
  digitalWrite(pinTrigger, OUTPUT);
  delayMicroseconds(4);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  tiempo=pulseIn(pinEcho, HIGH);
  distancia=0.0172*tiempo;
 /* Serial.println("distancia (cm)");
  Serial.println(distancia);
  delay(500);*/
  if(distancia>100){
    noTone(pinBuzzer);
  }
  else{
    tone(pinBuzzer,1000);
    delay(distancia*10);
    noTone(pinBuzzer);
    delay(distancia*10);
  }
}
  
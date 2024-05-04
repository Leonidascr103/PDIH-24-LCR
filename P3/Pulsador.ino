// Práctica encender y apagar un LED a través de botón pulsador 
const int LED=13;
const int BOTON=7;
const int LED2=12;
const int LED3=11;
int val; 

void setup(){
  pinMode(LED,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(BOTON,INPUT); 
}

void loop(){
  val=digitalRead(BOTON); 
  if(val==HIGH){
    digitalWrite(LED,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
  }else{
    digitalWrite(LED,LOW);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,HIGH);
  }
}

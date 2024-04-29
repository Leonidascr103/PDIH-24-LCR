
int status = 0;

int unnamed = 0;

int i = 0;

void setup() {
// put your setup code here, to run once:
pinMode(A0, INPUT);
pinMode(13, OUTPUT);
pinMode(12, OUTPUT);
pinMode(11, OUTPUT);
pinMode(10, OUTPUT);
pinMode(9, OUTPUT);
pinMode(8, OUTPUT);
pinMode(7, OUTPUT);
}

void loop(){
status = analogRead(A0);
if (status < 20) {
digitalWrite(13, HIGH);
digitalWrite(12, LOW);
digitalWrite(11, LOW);
digitalWrite(10, LOW);
digitalWrite(9, LOW);
digitalWrite(8, LOW);
digitalWrite(7, LOW);
} else {
  if (status < 140) {
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  } else {
    if (status < 260) {
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    } else {
      if (status < 380) {
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      } else {
        if (status < 500) {
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(11, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        }else {
          if (status < 620) {
          digitalWrite(13, HIGH);
          digitalWrite(12, HIGH);
          digitalWrite(11, HIGH);
          digitalWrite(10, HIGH);
          digitalWrite(9, HIGH);
          digitalWrite(8, HIGH);
          digitalWrite(7, LOW);
          } else {
            digitalWrite(13, HIGH);
            digitalWrite(12, HIGH);
            digitalWrite(11, HIGH);
            digitalWrite(10, HIGH);
            digitalWrite(9, HIGH);
            digitalWrite(8, HIGH);
            digitalWrite(7, HIGH);
            }
          }
        }
      }
    }
  }
delay(10); // Delay a little bit to improve simulation performance
}
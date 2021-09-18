int RED = 11 ;
int YELLOW = 12 ;
int GREEN = 13 ;

int distance ;
long duration ;


const int trigPin = 9;
const int echoPin = 10;

void setup() {
  pinMode ( RED , OUTPUT ) ;
  pinMode ( YELLOW , OUTPUT ) ;
  pinMode ( GREEN , OUTPUT ) ;

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(RED , HIGH ) ;
  digitalWrite(YELLOW , LOW ) ;
  delay(1000) ;
  Serial.println("STOP - 1 sec") ;
  digitalWrite(RED , HIGH ) ;
  delay(1000) ;
  Serial.println("STOP - 2 sec") ;
  digitalWrite(RED , HIGH ) ;
  delay(1000) ;
  Serial.println("STOP - 3 sec") ;
  digitalWrite(RED , HIGH ) ;
  delay(1000) ;
  Serial.println("STOP - 4 sec") ;
  digitalWrite(RED , HIGH ) ;
  delay(1000) ;
  Serial.println("STOP - 5 sec") ;
  digitalWrite(RED , HIGH ) ;
  delay(1000) ;
  digitalWrite(RED , LOW ) ;
  digitalWrite(YELLOW , HIGH ) ;
  Serial.println("HALT - 1 sec") ;
  delay(1000) ;
  Serial.println("HALT - 2 sec") ;
  digitalWrite(YELLOW , HIGH ) ;
  digitalWrite(RED , LOW ) ;
  delay(1000) ;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if ( distance <=10 ){
    digitalWrite(YELLOW , LOW ) ;
    digitalWrite(RED , LOW ) ;

    Serial.println("DENSITY - HIGH" ) ;
    digitalWrite(GREEN , HIGH ) ;
    delay(10*3*1000) ;
  }
    else if ( distance <= 30 && distance >10 ){
        digitalWrite(YELLOW , LOW ) ;
    digitalWrite(RED , LOW ) ;

    Serial.println("DENSITY - MEDIUM" ) ;
    digitalWrite(GREEN , HIGH ) ;
    delay(5*3*1000) ;
    }else if ( distance <=60 && distance >= 30 ) {
      digitalWrite(YELLOW , LOW ) ;
    digitalWrite(RED , LOW ) ;

    Serial.println("DENSITY - LOW" ) ;
    digitalWrite(GREEN , HIGH ) ;
    delay(2*3*1000) ;
    }
    digitalWrite(GREEN , LOW ) ;
    digitalWrite(YELLOW,HIGH) ;
    delay(1000) ;
    digitalWrite(YELLOW,HIGH) ;
    delay(1000) ;

}

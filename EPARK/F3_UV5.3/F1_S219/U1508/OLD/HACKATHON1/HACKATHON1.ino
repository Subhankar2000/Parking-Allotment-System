/* ARD-U-KNOW */

long time_ry , time_g , time_y ;

int d = 130;
int counter_car , counter_ry = 1, counter_g = 1  , counter_y = 1  ;

int distance ;
long duration ;

int RED = 11 , YELLOW = 12 , GREEN = 13 ;
int SWITCH = 8 ;

const int trigPin = 9;
const int echoPin = 10;

void setup() {
  pinMode ( SWITCH , INPUT ) ;

  pinMode ( RED , OUTPUT ) ;
  pinMode ( YELLOW , OUTPUT ) ;
  pinMode ( GREEN , OUTPUT ) ;

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  time_ry = millis() ;
  if ( time_ry <= 994 ) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    if ( distance < d )
      counter_car = counter_car + 1 ;
  }
  if ( time_ry == 995 && counter_ry <= 8 ) {
    if ( counter_ry <= 5) {
      digitalWrite( RED , HIGH ) ;
      Serial.println("") ;
      Serial.print ("STOP - ") ;
      Serial.print (counter_ry) ;
      Serial.print (" sec") ;
      Serial.println("") ;
      time_ry = 0 ;
      counter_ry = counter_ry + 1 ;

    }

    else if ( counter_ry == 5 && counter_y <= 2 ) {
      digitalWrite( RED , LOW ) ;
      digitalWrite( YELLOW , HIGH ) ;
      time_y = millis() ;
      Serial.println("") ;
      Serial.print("HALT - ") ;
      Serial.print(counter_y) ;
      Serial.print(" sec" ) ;
      Serial.println("") ;
      time_y = 0 ;
      counter_y = counter_y + 1 ;
    }
  }
}

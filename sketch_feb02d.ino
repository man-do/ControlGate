#include <Servo.h>

Servo myservo; 
//number of pin connections
const int trigPin = 10;
int pos =0;
const int echoPin = 9;
const int greenPin = 4;
const int redPin = 11;

void setup() {

    Serial.begin(9600);

    //atach the servo at pin 7
    myservo.attach(7); 
    
    //we set the red and green pins to output
    pinMode(redPin,OUTPUT);
    pinMode(greenPin , OUTPUT);

}

void loop() {

    long duration, cm;
    //we send and recieve the signal at the ultrasonic sensor
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    //the duration of the return signal
    duration = pulseIn(echoPin, HIGH);
    
    // convert time into a distance
    cm = microsecondsToCentimeters(duration);

    if ( cm > 7 && cm < 14)
    {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    //move the servo smoothly in increments of one
    while(myservo.read() <= 100)
    {
      myservo.write(pos++);
      delay(10);
      }

    delay(4000);
    }
    else if ( cm < 8)
    {
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
    //move the servo smoothly in decrements of one
    while(myservo.read() > 0)
    {
      myservo.write(pos--);
      delay(10);
      }
    delay(100);
    }
    else
    {
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
    //move the servo smoothly in decrements of one
    while(myservo.read() > 0)
    {
      myservo.write(pos--);
      delay(10);
      }
    delay(100);
    }
    
    Serial.print(cm);
    
    Serial.print("cm");
    
    Serial.println();
    
    delay(100);

}

long microsecondsToCentimeters(long microseconds) {

    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    
    // The ping travels out and back, so to find the distance of the
    
    // object we take half of the distance travelled.
    
    return microseconds / 29 / 2;

}

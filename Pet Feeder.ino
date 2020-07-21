#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <Servo.h>
BlynkTimer timer; // Announcing the timer.
BlynkTimer timer1;
WidgetLED led1(V5);  //Announcing the Blynk LED Widgets for the Alarm light.
WidgetLED led2(V3);  // For the food low LED light.
WidgetRTC rtc;  // Announcing variable for Real Time Clock.

Servo myservo;  // create servo object to control a servo

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "<Your_Auth_Code>";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "<Wifi_Name>";
char pass[] = "<Password>";

int ledPin = 13;                // choose the pin for the LED
int inputPin = 8;               // choose the input pin (for PIR sensor)
int val = 0;                    // variable for reading the pin status
int t1;
String time1;
String time2;
String currentTime;
int trigPin = (11); // Add the Trig pin on pin 10.
int echoPin = (10); // Add the ECHO pin on pin 9.
int duration, distance; // Add types 'duration' and 'distance'.
int count = 0;

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial1

// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200  //You can change the baud rate according to your esp8266 module

ESP8266 wifi(&EspSerial);

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode (trigPin, OUTPUT);// Same as above, the TRIG pin will send the ultrasonic wave.
  pinMode (echoPin, INPUT); // The ECHO pin will recieve the rebounded wave, so it must be an input type.+
  pinMode (7 , OUTPUT);
  digitalWrite(7, HIGH);  //Using this pin as VCC for Ultrasonic Sensor
  pinMode (6 , OUTPUT);
  digitalWrite(6, HIGH);  //Using this pin as PIR for Ultrasonic Sensor
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);
  EspSerial.begin(ESP8266_BAUD);  // Set ESP8266 baud rate
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass); //Here it takes all the required parameters for it to connect to the blynk server.
  rtc.begin(); //Here it connects to Real Time Clock on the server, if it doesn't connect it starts from 00:00
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);
  timer.setInterval(2000, runn);  //Here it will run the function 'runn' for the PIR sensor every 2 seconds.
}



void up() {
  myservo.write(0);
  timer.setTimeout(2000, down); // After 2 seconds it will the run the 'down' function and make the servo go back to its original position.
}

void down() {
  myservo.write(180);
}

void runn() {
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON

    Blynk.notify("Alex detected"); //sends a notifications to the app.
    timer.setTimeout(10, up); // After 10ms it will run the function 'up' which will make the servor to pour the food.
  } else {

    digitalWrite(ledPin, LOW); // turn LED OFF
  }
}

//The function BLYNK_WRITE reads data from the app and writes it in a variable in the system.
//The function BLYNK_READ reads data from the variable in the system and sends it to the app.

BLYNK_WRITE(V0) { //This function is linked to the the "Drop Food" button on the app.
  int buttonState = param.asInt(); //Reads the state of the button '0=off or 1=on'
  if (buttonState == 1) {
    timer.setTimeout(100, up);  // After 100ms it will run the function 'up' which will make the servor to pour the food.
  }
}

BLYNK_WRITE(V6) {  //This function sets the system into 'Manual' or 'Automatic' through the app.
  switch (param.asInt()) {
    case 1: {
        Serial.println("Automatic");
        inputPin = 8; // This basically just changes the input pin for the PIR sensor to an empty pin slot so can not detect any motion, which in this case is 8. 
        break;
      }
    case 2: {
        Serial.println("Manual");
        inputPin = 3; // IN this it changes the pin back to 3 where it can detect motion.
        break;
      }
  }
}

void check() { //In this function at specified time 

  currentTime = String(hour()) + ":" + minute(); //Here it is taking the current time form the server.
  Serial.println(currentTime);
  if (time1 == currentTime) {

    if (timer.isEnabled(t1) ) {//Checks if the timer is running.
      timer1.setTimeout(10, up); 
      led1.off(); //Turns the LED in the app off.
      timer.disable(t1); //It closes the timer.
      Serial.println("disable");
    }
  } else {
    Serial.print("Bad");
  }
}

BLYNK_WRITE(V4) {  // This is the timer function used to drop the food at a specific time.
  TimeInputParam t(param); //With the variable 't' we can read the time from the timer on the app.

  if (t.hasStartTime()) // It will run only if a time is set on the timer.
  {
    time1 = String(t.getStartHour()) + ":" + String(t.getStartMinute());
    Serial.println(time1);
    led1.on(); //Turns the LED on the app to turn on.
    t1 = timer.setInterval(5000, check); // Every 5 seconds it will run the 'check' function
  }
}

BLYNK_READ(V1){ //This function displays the real time on the app which is taken from the server.
  time2 = String(hour()) + ":" + minute() + ":" + second();
  Blynk.virtualWrite(V1, time2); //Sends the data of variable to the app widget which is set to Virtual Pin 1(V1).
}

BLYNK_READ(V2) //This function checks the food level in the container.
{
  int distance = ultra(); //Gives output if the the function 'ultra'.
  int level = distance;

  Blynk.virtualWrite(V2, level); //This send the level of the food in the container to the graph in the app.
  if (distance >= 7) {
    if (count == 0) {
      Blynk.notify("Food is low"); //If the level drops to a certain point it will send a notification.
    }
    led2.on(); // This will light up the Food Low LED on the app.
    count = 1; 
  }
  else {
    led2.off();  //This block is used when food id refilled, then it turns off the LED.
    count = 0;
  }
}


int ultra()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;  // Calculating the distance

  return distance;

}

void loop()
{
  Blynk.run(); //This connects the system to the blynk server when it connects it will show on the ap that the system is online.
  timer.run(); //Running the timer variable so it can be used above.
  timer1.run();
}

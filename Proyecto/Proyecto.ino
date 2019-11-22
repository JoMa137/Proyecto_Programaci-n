#include <IRremote.h>
#include <DHT.h>
#include <DHT_U.h>

#include <SoftwareSerial.h>
#include <BlynkSimpleStream.h>
SoftwareSerial SwSerial(10, 11);
#define BLYNK_PRINT SwSerial

//Este código establece la conexión entre arduino y Blynk
char auth[] = "tsEP71ujoIjXvQ_su2_CR2K56_mkhux2";


int SensorT = A2;

const int pinLed1=2;
const int pinLed2=3;
const int pinLed3=4;
const int pinLed4=5;
const int pinLed5=8;
int sensor = 11;



DHT dht(SensorT, DHT11);
IRrecv irrecv(sensor);
decode_results valores;

// Se le asigna un pin virtual para los widgets de los LEDs en Blynk
  WidgetLED led1(V1);
  WidgetLED led2(V2);
  WidgetLED led3(V3);
  WidgetLED led4(V4);
  WidgetLED led5(V7);

// Timers para establecer la frecuencia con la que Blynk leerá la información
BlynkTimer timer;
BlynkTimer timerT;


//Función para que los LEDs de Blynk se enciendan o se apaguen dependiendo del sensor IR
void estadoLeds()
{
  if (digitalRead(pinLed1)== HIGH) {
    led1.on();
  } 
  else {
    led1.off();
  }

    if (digitalRead(pinLed2)== HIGH) {
    led2.on();
    
  } else {
    led2.off();
  }

    if (digitalRead(pinLed3)== HIGH) {
    led3.on();
    
  } else {
    led3.off();
  }

    if (digitalRead(pinLed4)== HIGH) {
    led4.on();
    
  } else {
    led4.off();
  }
    
    if (digitalRead(pinLed5)== HIGH) {
    led5.on();
    
  } else {
    led5.off();
  }
}

//Función para la lectura del sensor de temperatura
void sendSensor()
{
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(hum) || isnan(temp)) {
    SwSerial.println("Failed to read from DHT sensor!");
    return;
  }
  // Pines virtuales para temperatura y humedad
  Blynk.virtualWrite(V5, hum);
  Blynk.virtualWrite(V6, temp);
}



void setup() {

  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(pinLed1,OUTPUT);
  pinMode(pinLed2,OUTPUT);
  pinMode(pinLed3,OUTPUT);
  pinMode(pinLed4,OUTPUT);

  pinMode(SensorT,INPUT);
  dht.begin();

// Se inicializa software serial y la conexión con Blynk
  SwSerial.begin(9600);

  Blynk.begin(Serial, auth);

// Se establece la duración de los timers
  timer.setInterval(500L, estadoLeds);
  timerT.setInterval(1000L, sendSensor);
}

void loop() {

    Blynk.run();
  
    timer.run();
    timerT.run();
  
  if (irrecv.decode(&valores)){
      switch(valores.value){

    case 0xFF6897: 
    digitalWrite(pinLed1,LOW);
    digitalWrite(pinLed2,LOW);
    digitalWrite(pinLed3,LOW);
    digitalWrite(pinLed4,LOW);

    break;

    case 0xFF30CF: //Serial.println("1");
    digitalWrite(pinLed1,HIGH);
    digitalWrite(pinLed2,LOW);
    digitalWrite(pinLed3,LOW);
    digitalWrite(pinLed4,LOW);

    break;

    case 0xFF18E7: //Serial.println("2");
    digitalWrite(pinLed1,LOW);
    digitalWrite(pinLed2,HIGH);
    digitalWrite(pinLed3,LOW);
    digitalWrite(pinLed4,LOW);
    break;

    case 0xFF7A85: //Serial.println("3");
    digitalWrite(pinLed1,LOW);
    digitalWrite(pinLed2,LOW);
    digitalWrite(pinLed3,HIGH);
    digitalWrite(pinLed4,LOW);
    break;

    case 0xFF10EF: //Serial.println ("4");
    digitalWrite(pinLed1,LOW);
    digitalWrite(pinLed2,LOW);
    digitalWrite(pinLed3,LOW);
    digitalWrite(pinLed4,HIGH);
    break;

    case 0xff38c7: //Serial.println ("5");
    digitalWrite(pinLed1,HIGH);
    digitalWrite(pinLed2,HIGH);
    digitalWrite(pinLed3,LOW);
    digitalWrite(pinLed4,LOW);
    break;

    case 0xFF5AA5:
    digitalWrite(pinLed1,LOW);
    digitalWrite(pinLed2,LOW);
    digitalWrite(pinLed3,HIGH);
    digitalWrite(pinLed4,HIGH);
    break;

    case 0xFF42BD:
    digitalWrite(pinLed1,HIGH);
    digitalWrite(pinLed2,HIGH);
    digitalWrite(pinLed3,HIGH);
    digitalWrite(pinLed4,HIGH);
    break;

    case 0xFFFFFFFF: Serial.println("Error"); break;

    default:
    Serial.println("Otro boton");
    
  }

  delay(500);
    irrecv.resume();

  }

}

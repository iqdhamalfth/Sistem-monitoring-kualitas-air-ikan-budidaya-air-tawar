#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <DallasTemperature.h>
#include <OneWire.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "jZPlsJ2pcL91XMwk18QDJeCzadlKcW35";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Godam";
char pass[] = "samadenganx";
char server[] = "prakitblog.com";
const int port = 8181;

const int ph_Pin = A0;
int sensorPin = A1;
const int RELAY_PIN = A2;

#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
double suhu;
int sensorValue;
int turbidity;


// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial1

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);
BlynkTimer timer;

float Po = 0;
float PH_step;
int nilai_analog_PH;
double TeganganPh;

//untuk kalibrasi pH
float PH4 = 3.19;
float PH7 = 2.60;

BLYNK_CONNECTED () {
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
}

void senstoBlynk() {
  Blynk.virtualWrite(V0, turbidity);
  Blynk.virtualWrite(V1, Po);
  Blynk.virtualWrite(V2, suhu);

  if (Po > 8 && turbidity > 100) {
    Blynk.notify("Air dalam kondisi kotor, air akan segera diganti!");
    delay (1000);
  }
}

void setup()
{
  Serial.begin(9600);
  sensors.begin();
  pinMode(RELAY_PIN, OUTPUT);
  delay(10);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass, server, port);
  timer.setInterval(3000L, senstoBlynk);
}

void loop()
{
  sensors.requestTemperatures();                // Send the command to get temperatures
  Serial.println("Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0));   // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  suhu = sensors.getTempCByIndex(0);

  sensorValue = analogRead(sensorPin);
  turbidity = map(sensorValue, 9, 747, 250, 0);
  delay(100);
  Serial.print("turbidity:");
  Serial.print("   ");
  Serial.println(turbidity);
  delay(100);

  if (turbidity > 100) {
    digitalWrite(RELAY_PIN, LOW);
  }
  else if (turbidity < 50) {
    digitalWrite(RELAY_PIN, HIGH);
  }

  Blynk.run();
  timer.run();
  nilaiPH();
}

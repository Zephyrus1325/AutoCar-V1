#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>
Adafruit_MPU6050 mpu;

const char* ssid = "Marco Filho";
const char* pass = "MarcoFilho12";

const uint16_t port = 5204;
const char* host = "192.168.1.101";


// defines pins numbers
const int trigPin = 14;
const int echoPin = 27;
// defines variables
long duration;
int distance;

float threshold = 0.02;  //threshold for acceleration

float angleX = 0;
float angleY = 0;
float angleZ = 0;

int deltaTime = 50;
WiFiClient client;

void setup(void) {
  WiFi.begin(ssid, pass);
  Serial.print("Connecting.");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  if(client.connect(host, port)){
    Serial.println("OK!");
  }
  Serial.print("WiFi connected - IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);



  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  Serial.begin(115200);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {
  // Use WiFiClient class to create TCP connections
  
  //------------------------------------------------
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  calculateAngles((g.gyro.x + 0.05f), (g.gyro.y), (g.gyro.z - 0.05f));
  /* Print out the values */
        /
        Serial.print(a.acceleration.x + 0.29f);
        Serial.print(",");
        Serial.print(a.acceleration.y - 0.27f);
        Serial.print(",");
        Serial.print(a.acceleration.z - 0.46f);
        Serial.print(",");
        Serial.print(angleX);
        Serial.print(",");
        Serial.print(angleY);
        Serial.print(",");
        Serial.print(angleZ);
        Serial.print(",");
        Serial.println(distance);
        //---------------------------------------
        client.print(a.acceleration.x + 0.29f);
        client.print(",");
        client.print(a.acceleration.y - 0.27f);
        client.print(",");
        client.print(a.acceleration.z - 0.46f);
        client.print(",");
        client.print(angleX);
        client.print(",");
        client.print(angleY);
        client.print(",");
        client.print(angleZ);
        client.print(",");
        client.println(distance);
        delay(deltaTime);


}



void calculateAngles(float x, float y, float z) {
  //integrate angles
  angleX += ((x > threshold) || (x < (-threshold))) ? 1.29f * x * (deltaTime / 1000.0) : 0;
  angleY += ((y > threshold) || (y < (-threshold))) ? y * (deltaTime / 1000.0) : 0;
  angleZ += ((z > threshold) || (z < (-threshold))) ? 1.29f * z * (deltaTime / 1000.0) : 0;
}
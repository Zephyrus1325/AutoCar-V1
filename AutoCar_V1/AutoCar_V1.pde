import processing.net.*;

Server myServer;


String val1 = "0";
String val2 = "0";
String val3 = "0";
String val4 = "0";
String val5 = "0";
String val6 = "0";
String val7 = "0";

float accX;
float accY;
float accZ;

float angleX; //angle in radians
float angleY; //angle in radians
float angleZ; //angle in radians



double speedX; //speed in m/s
double speedY; //speed in m/s
double speedZ; //speed in m/s

double posX; //position in meters
double posY; //position in meters
double posZ; //position in meters

int distance;

String input;


void setup() {
  myServer = new Server(this, 5204);
  size(400, 400);
}


void draw() {
  drawStuff();
}

void getValue(String input){
        String[] Split = input.split(",");
   
        val1 = Split[0];
        val2 = Split[1]; 
        val3 = Split[2];
        val4 = Split[3];
        val5 = Split[4];
        val6 = Split[5];
        val7 = Split[6];
        println(val1, val2, val3, val4, val5, val6, val7);
        val1 = removeLastChar(val1);
        val2 = removeLastChar(val2);
        val3 = removeLastChar(val3);
        val4 = removeLastChar(val4);
        val5 = removeLastChar(val5);
        val6 = removeLastChar(val6);
        val7 = removeLastChar(val7);
        val7 = removeLastChar(val7);
        distance = Integer.valueOf(val7);
        angleX = Float.parseFloat(val4);
        angleY = Float.parseFloat(val5);
        angleZ = Float.parseFloat(val6);
}


void keyPressed() {
 if(key == 'r'){
    angleX = 0;
    angleY = 0;
    angleZ = 0;
 }
}

void clientEvent(Client someClient) {
  if(someClient.available() > 0){
  input = someClient.readStringUntil('\n');
  if(input != null){
  getValue(input);
    }
  }
}

void serverEvent(Server someServer, Client someClient) {
  println("We have a new client: " + someClient.ip());
}

public static String removeLastChar(String s) {
  return (s == null || s.length() == 0)
    ? "0" 
    : (s.substring(0, s.length() - 1));
}

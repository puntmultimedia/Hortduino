/*****
 
 All the resources for this project:
  https://randomnerdtutorials.com/esp8266-and-node-red-with-mqtt/
*****/
//-------------------------------------LIBRERIAS----------------------------------------------

#include <WiFi.h>
#include <PubSubClient.h>
// -----------------------------------VARIABLES Y PINES----------------------------------------------

const int sensorPin = A0;
const int lamp = 4;       //(D2 en nodemcu)

// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

//---------------------------------WIFI - SERVER -----------------------------------
// Change the credentials below, so your ESP8266 connects to your router
const char* ssid =  "hort"; // "Punt Multimedia Aula 2_4GHz";   "MOVISTAR_CE11";
const char* password =  "puntmultimedia314";//  "jDQYJ5HhyyBf2iHmicGz";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "192.168.2.94"; //"192.168.1.55";

//-------------------------------INICIO DE ESP-CLIENT-----------------------------------
WiFiClient espClient2;           // Initializes the espClient. CAMBIAR DE NOMBRE PARA MULTIPLES CONEXIONES
PubSubClient client(espClient2); //  You should change the espClient name if you have multiple ESPs running in your home automation system

void setup_wifi();   //----------This functions connects your ESP8266 to your router, si ESP se conecta a WIFI

void reconnect();   //----------FUNCIÓN CONEXIÓN AL BROQUER-MQTT-----------------------------

//-------------------------------SETUP - ENTRADAS - SALIDAS - INICIALIZACIÓN DHT - SERIAL - FUNCIONES-----------
// The setup function sets your ESP GPIOs to Outputs, starts the serial communication at a baud rate of 115200

void setup() {
  pinMode(lamp, OUTPUT);
  
  //dht.begin();
  
  Serial.begin(115200);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);  //Configura su broker mqtt y establece la función de devolución de llamada
  client.setCallback(callback);         //La función de devolución de llamada es lo que recibe mensajes y realmente controla los LED
}

void callback(); //-----------FUNCIÓN LLAMADA:NODE-DASHBOARD(API) MANDA UN MENSAJE. BROQUER ALMACENA MENSAJE Y ENVIA A ESP---------------------------------------

void loop() {  //-------------------------------VOID LOOP - PUBLICACIÓN TEMPERATURA --------------------
                //no necesita cambiar nada en la función de bucle. Básicamente, asegura que su ESP está conectado a su broker
 
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Moisture");    //CAMBIAR DE NOMBRE PARA MULTIPLES CONEXIONES??

  now = millis();  // Y si probamos a quitarla¿?¿?
  // Publishes new temperature and humidity every 30 seconds
  if (now - lastMeasure > 3000) {
    lastMeasure = now;
        
    int lect_sec = analogRead(sensorPin); // SensorPin mide bytes de sequedad,
    float humedad = (4095-lect_sec)*(100.0/4095);//100 - lect_h*(100.0/ 1023);
        
    static char humidityTemp[7];
    dtostrf(humedad, 6, 2, humidityTemp); // Pasar datos a string char* dtostrf(float number, int tamanyo, int decimales, char* buffer);
    /*for(int i=0; i= humidityTemp[7]; i++ ) { // imprime los....
      Serial.println((char)humidityTemp[i]);
      delay(500);*/
                            // Publishes Temperature and Humidity values
    client.publish("room/humidity2", humidityTemp); //client.publish("room/temperature", temperatureTemp);
                                                  
    Serial.print("Humidity: ");
    Serial.println(humedad);
    Serial.print("Rango Bytes: ");
    Serial.println(lect_sec);
     
  }
} 

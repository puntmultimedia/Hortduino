// Don't change the function below. This functions connects your ESP8266 to your router, si ESP se conecta a WIFI
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  // IMPRIME PUNTITOS SI NO SE CONECTA, SI SÍ, ENTONCES CONTINUA Y 
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

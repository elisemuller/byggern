#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

//const char* ssid = "EliseM";
//const char* password = "xe8vci82z4i4x";

const char* ssid = "AndroidAP_6064";
const char* password = "mttp1234";

//const char* ssid = "OnePlus Nord";
//const char* password = "passord321";

const char* PARAM_MESSAGE = "message";

String message = "Highscore\r\n";
int i = 1;
int highscore = 0;

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup() {

    Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    message += "  ____                                    _ \r\n";
    message += " | __ ) _   _  __ _  __ _  ___ _ __ _ __ | |\r\n";
    message += " |  _ \| | | |/ _` |/ _` |/ _ \ '__| '_ \| |\r\n";
    message += " | |_) | |_| | (_| | (_| |  __/ |  | | | |_|\r\n";
    message += " |____/ \__, |\__, |\__, |\___|_|  |_| |_(_)\r\n";
    message += "        |___/ |___/ |___/                   \r\n";
    message += "\r\n";

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        message += "Player";
        message += i;
        message += ": ";
        highscore = digitalRead(16) | digitalRead(5) << 1 | digitalRead(4) << 2 | digitalRead(0) << 3 | digitalRead(2) << 4 | digitalRead(14) << 5;
        message += highscore;
        message += "\r\n";
        request->send(200, "text/plain", message);
        i += 1;
    });

    server.onNotFound(notFound);

    server.begin();
}

void loop() {
}

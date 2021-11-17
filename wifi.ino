#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const char* ssid = "EliseM";
const char* password = "xe8vci82z4i4x";

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

    message += " ____                                       \r\n";
    message += "|  _ \                                      \r\n";
    message += "| |_) |_   _  __ _  __ _  ___ _ __ _ __     \r\n";
    message += "|  _ <| | | |/ _` |/ _` |/ _ \ '__| '_ \    \r\n";
    message += "| |_) | |_| | (_| | (_| |  __/ |  | | | |   \r\n";
    message += "|____/ \__, |\__, |\__, |\___|_|  |_| |_|   \r\n";
    message += " _      __/ | __/ | __/ |     _                         _ \r\n";
    message += "| |    |___/ |___/ |___/     | |                       | |\r\n";
    message += "| | ___  __ _  __| | ___ _ __| |__   ___   __ _ _ __ __| |\r\n";
    message += "| |/ _ \/ _` |/ _` |/ _ \ '__| '_ \ / _ \ / _` | '__/ _` |\r\n";
    message += "| |  __/ (_| | (_| |  __/ |  | |_) | (_) | (_| | | | (_| |\r\n";
    message += "|_|\___|\__,_|\__,_|\___|_|  |_.__/ \___/ \__,_|_|  \__,_|\r\n";
    message += "\r\n";

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        message += "Player";
        message += i;
        message += ": ";
        highscore = analogRead(A0);
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
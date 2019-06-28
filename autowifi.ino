#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <AutoConnect.h>

class AutoConnect2 : public AutoConnect {
  public:
    using AutoConnect::AutoConnect;
    using AutoConnect::_startDNSServer;
};


ESP8266WebServer  server;
AutoConnect2       portal(server);
AutoConnectConfig acConfig;


void initWifi() {
  String mac = WiFi.macAddress();
  String apSSID = "ESP-" + String(mac[9]) + String(mac[10]) + String(mac[12]) + String(mac[13]) + String(mac[15]) + String(mac[16]);
  char softApssid[18];
  apSSID.toCharArray(softApssid, apSSID.length() + 1);
  acConfig.apid = softApssid;
  acConfig.psk = "88888888";
  acConfig.portalTimeout = 5000;
  portal.config(acConfig);

  if (portal.begin()) {
    Serial.println("HTTP server:" + WiFi.localIP().toString());
  }

  WiFi.softAP(softApssid, "88888888");
  portal._startDNSServer();

}

void loopWifi() {
  portal.handleClient();
}

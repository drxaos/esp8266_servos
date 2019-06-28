#include <FS.h>
#include "PageBuilder.h"

String _s1 = "0", _s2 = "0";

PageElement HOME_ELM("file:/root.html", {
  { "S1", [](PageArgument & args) {
      return _s1;
    }
  },
  { "S2", [](PageArgument & args) {
      return _s2;
    }
  }
});
PageBuilder HOME_PAGE("/", { HOME_ELM });

void initWeb() {
  HOME_PAGE.insert(server);
  server.on("/sdrive/s1", sdrive1);
  server.on("/sdrive/s2", sdrive2);
  server.serveStatic("/nouislider.min.css", SPIFFS, "/nouislider.min.css");
  server.serveStatic("/nouislider.min.js", SPIFFS, "/nouislider.min.js");
  portal.onNotFound(handleNotFound);
}

void sdriveApply() {
  _s1 = server.arg("s1");
  _s2 = server.arg("s2");
  mov(_s1.toInt(), _s2.toInt());
  server.send ( 200, "text/plain", "ok");
}

void sdrive1() {
  _s1 = server.arg("v");
  mov(_s1.toInt(), _s2.toInt());
  server.send ( 200, "text/plain", "ok");
}

void sdrive2() {
  _s2 = server.arg("v");
  mov(_s1.toInt(), _s2.toInt());
  server.send ( 200, "text/plain", "ok");
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found " + server.uri());
}

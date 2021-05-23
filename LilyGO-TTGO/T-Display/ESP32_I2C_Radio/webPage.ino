//https://github.com/me-no-dev/ESPAsyncWebServer#body-data-handling

#if defined(DEBUG_CONSOLE)
void logRequest(AsyncWebServerRequest *request) {
  //List all parameters
  int params = request->params();
  for(int i=0;i<params;i++){
    AsyncWebParameter* p = request->getParam(i);
    if(p->isFile()){ //p->isPost() is also true
      debug_printf("FILE[%s]: %s, size: %u\r\n", p->name().c_str(), p->value().c_str(), p->size());
    } else if(p->isPost()){
      debug_printf("POST[%s]: %s\r\n", p->name().c_str(), p->value().c_str());
    } else {
      debug_printf("GET[%s]: %s\r\n", p->name().c_str(), p->value().c_str());
    }
  }
  debug_printf("\r\n");
}
#endif

void page400(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Bad Request");
}

void page404(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void page507(AsyncWebServerRequest *request) {
  request->send(507, "text/plain", "Not enough memory");
}

String checkedString = String(" checked=\"checked\"");
String selectedString = String(" selected=\"selected\"");

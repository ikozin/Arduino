
void pageRadioListGet(AsyncWebServerRequest* request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("GET: %s\r\n", fileRadio);
  logRequest(request);
#endif
  File f = SPIFFS.open(fileRadio, FILE_WRITE);
  if (f) {
    f.write((uint8_t*)radioList, sizeof(radioList));
    f.close();
    return request->send(SPIFFS, fileRadio, emptyString, true);
  } else {
    return page404(request);
  }
}

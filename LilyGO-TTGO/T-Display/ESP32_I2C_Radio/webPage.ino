void page404(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}


void pageIndex(AsyncWebServerRequest *request) {
  AsyncResponseStream *response = request->beginResponseStream("text/plain");
  listDir("/", response);
  request->send(response);
  //request->send(200, "text/plain", "Hello, world");
}

void pageUploadPost(AsyncWebServerRequest* request) {
#if defined(DEBUG_CONSOLE)
  debug_printf("Post: Index\r\n");
  logRequest(request);
#endif
  request->redirect("/rda5807m.html");
}

void handleUpload(AsyncWebServerRequest* request, String fileName, size_t index, uint8_t* data, size_t len, bool final) {
  debug_printf("Upload: %s, %u, %u\r\n", fileName.c_str(), index, len);
  if (!index) {
    request->_tempFile = SPIFFS.open("/" + fileName, "w");
  }
  if (len) {
    request->_tempFile.write(data,len);
  }
  if (final) {
    request->_tempFile.close();
    debug_printf("UploadEnd: %s\r\n", fileName.c_str());
  }
}

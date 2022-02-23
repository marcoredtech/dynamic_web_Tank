String getContentType(String filename){
  if(filename.endsWith(F(".htm")))          return F("text/html");
  else if(filename.endsWith(F(".html")))    return F("text/html");
  else if(filename.endsWith(F(".css")))     return F("text/css");
  else if(filename.endsWith(F(".js")))      return F("application/javascript");
  else if(filename.endsWith(F(".json")))    return F("application/json");
  else if(filename.endsWith(F(".png")))     return F("image/png");
  else if(filename.endsWith(F(".gif")))     return F("image/gif");
  else if(filename.endsWith(F(".jpg")))     return F("image/jpeg");
  else if(filename.endsWith(F(".jpeg")))    return F("image/jpeg");
  else if(filename.endsWith(F(".ico")))     return F("image/x-icon");
  else if(filename.endsWith(F(".xml")))     return F("text/xml");
  else if(filename.endsWith(F(".pdf")))     return F("application/x-pdf");
  else if(filename.endsWith(F(".zip")))     return F("application/x-zip");
  else if(filename.endsWith(F(".gz")))      return F("application/x-gzip");
  return F("text/plain");
}
 
bool handleFileRead(AsyncWebServerRequest *request, String path){
  Serial.print(F("handleFileRead: "));
  Serial.println(path);
 
  if(path.endsWith("/")) path += F("index.html");           // If a folder is requested, send the index file
  String contentType = getContentType(path);                // Get the MIME type
  String pathWithGz = path + F(".gz");
  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){     // If the file exists, either as a compressed archive, or normal
    bool gzipped = false;
 
    if(SPIFFS.exists(pathWithGz)) {                         // If there's a compressed version available
      path += F(".gz");                                     // Use the compressed version
      gzipped = true;
    }
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, path, contentType);
    if (gzipped){
        response->addHeader("Content-Encoding", "gzip");
    }
    Serial.print("Real file path: ");
    Serial.println(path);
 
    request->send(response);
 
    return true;
  }
  Serial.println(String(F("\tFile Not Found: ")) + path);
  return false;                                             // If the file doesn't exist, return false
}
 
void handleNotFound(AsyncWebServerRequest *request) {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += request->url();
  message += "\nMethod: ";
  message += (request->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += request->args();
  message += "\n";
 
  for (uint8_t i = 0; i < request->args(); i++) {
    message += " " + request->argName(i) + ": " + request->arg(i) + "\n";
  }
 
  request->send(200, "text/plain", message);
}
 
void serverRouting() {
      httpServer.onNotFound([](AsyncWebServerRequest *request) {                              // If the client requests any URI
          Serial.println(F("On not found"));
        if (!handleFileRead(request, request->url())){                  // send it if it exists
            handleNotFound(request); // otherwise, respond with a 404 (Not Found) error
        }
      });
 
      Serial.println(F("Set cache!"));
      // Serve a file with no cache so every tile It's downloaded
      httpServer.serveStatic("/configuration.json", SPIFFS, "/configuration.json","no-cache, no-store, must-revalidate");
      // Server all other page with long cache so browser chaching they
      httpServer.serveStatic("/", SPIFFS, "/","max-age=31536000");
}

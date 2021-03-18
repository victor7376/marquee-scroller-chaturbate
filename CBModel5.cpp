
/** The MIT License (MIT)

Copyright (c) 2021 victor7376@github

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "CBModel5.h"

#define CHATURBATE_FINGERPRINT "16 a5 01 0d a1 67 f5 f1 4f 99 9c dd 00 16 18 c5 97 9b b9 44"

CBModel5::CBModel5(String username5)
{
  myUsername5 = username5;
}

void CBModel5::updateDetails5(String username5){

  myUsername5 = username5;
}

void CBModel5::getDetails5(){

      WiFiClientSecure modelClient;
      #ifdef ESP32
      #else
        modelClient.setFingerprint(CHATURBATE_FINGERPRINT);
      #endif
      
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println(F("Connecting to Chaturbate..."));
      if (!modelClient.connect("chaturbate.com", 443)) {
        Serial.println(F("Failed to connect to Chaturbate"));
        
        resetData5(); // reset data
        return;
      }
      Serial.println(F("Connected to Chaturbate"));
    
      Serial.println(F("Sending request to Chaturbate..."));
      // Send HTTP request
      modelClient.println("GET /api/chatvideocontext/" + myUsername5 + "/" + " HTTP/1.0");
      Serial.println("GET /api/chatvideocontext/" + myUsername5 + "/" + " HTTP/1.1");
      modelClient.println(F("Host: chaturbate.com"));
      modelClient.println(F("User-Agent: Arduino"));
      modelClient.println(F("Connection: close"));
      modelClient.println();

  
      //Check the returning code                                                                  
        char status[32] = {0};
      modelClient.readBytesUntil('\r', status, sizeof(status));
      Serial.println("Response Header: " + String(status));
      if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
        Serial.print("Unexpected HTTP status: ");
        Serial.println(status);
        CBModel5Data.error = String(status);
        
        resetData5(); // reset data
        return;
      }

      Serial.println(F("Receive response from chaturbate..."));

      // Skip response headers
      modelClient.find("\r\n\r\n");
      
      resetData5(); // reset data

      // CB v5
      const size_t bufferSize = 2*JSON_ARRAY_SIZE(0) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(16) + JSON_OBJECT_SIZE(58) + 2748;
      
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(modelClient);
      // Parameters
      if (!root.success()) {
        Serial.println(F("Chaturbate Data Parsing failed!"));
        return;
      }

      const char* CBModel5 = root["broadcaster_username"];
      const char* CBModel5Status = root["room_status"];
      const char* CBModel5code = root["code"];
      int CBModel5NumViewers = root["num_viewers"];

      CBModel5Data.CBModel5 = (const char*)root["broadcaster_username"];
      CBModel5Data.CBModel5Status = (const char*)root["room_status"];
      CBModel5Data.CBModel5code = (const char*)root["code"];
      CBModel5Data.CBModel5NumViewers = (const char*)root["num_viewers"];

      Serial.print("Model (5): ");
      Serial.println(CBModel5);
      Serial.print("Status (5): ");
      Serial.println(CBModel5Status);
      Serial.print("Viewers (5): ");
      Serial.println(CBModel5NumViewers);
      
    }
    modelClient.stop();
}


String CBModel5::getCBModel5(){
  return CBModel5Data.CBModel5;
}

String CBModel5::getCBModel5Status(){
  return CBModel5Data.CBModel5Status;
}

String CBModel5::getCBModel5code(){
  return CBModel5Data.CBModel5code;
}

String CBModel5::getCBModel5NumViewers(){
  return CBModel5Data.CBModel5NumViewers;
}

String CBModel5::getError() {
  return CBModel5Data.error;
}

boolean CBModel5::isPassword() {
  boolean password = false;
  if (CBModel5Data.error == "HTTP/1.1 401 Unauthorized") {
    password = true;
  }
  return password;
}

// Reset all ChaturbateData
void CBModel5::resetData5() {
  CBModel5Data.CBModel5 = "";
  CBModel5Data.CBModel5Status = "";
  CBModel5Data.CBModel5code = "";
  CBModel5Data.CBModel5NumViewers = "";
}
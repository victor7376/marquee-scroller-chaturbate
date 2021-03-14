
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

#include "CBModel3.h"

#define CHATURBATE_FINGERPRINT "16 a5 01 0d a1 67 f5 f1 4f 99 9c dd 00 16 18 c5 97 9b b9 44"

CBModel3::CBModel3(String username3)
{
  myUsername3 = username3;
}

void CBModel3::updateDetails3(String username3){

  myUsername3 = username3;
}

void CBModel3::getDetails3(){

      WiFiClientSecure modelClient;
      #ifdef ESP32
      #else
        modelClient.setFingerprint(CHATURBATE_FINGERPRINT);
      #endif
      
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println(F("Connecting to Chaturbate..."));
      if (!modelClient.connect("chaturbate.com", 443)) {
        Serial.println(F("Failed to connect to Chaturbate"));
        resetData3();
        return;
      }
      Serial.println(F("Connected to Chaturbate"));
    
      Serial.println(F("Sending request to Chaturbate..."));
      // Send HTTP request
      modelClient.println("GET /api/chatvideocontext/" + myUsername3 + "/" + " HTTP/1.0");
      Serial.println("GET /api/chatvideocontext/" + myUsername3 + "/" + " HTTP/1.1");
      modelClient.println(F("Host: chaturbate.com"));
      modelClient.println(F("User-Agent: Arduino"));
      modelClient.println(F("Connection: close"));
      modelClient.println();

  
      //Check the returning code                                                                  
        char status[32] = {0};
      modelClient.readBytesUntil('\r', status, sizeof(status));
      Serial.println("Response Header: " + String(status));
      if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
        Serial.print("Unexpected HTTP status");
        Serial.println(status);
        resetData3();
        return;
      }

      Serial.println(F("Receive response from chaturbate..."));

      // Skip response headers
      modelClient.find("\r\n\r\n");
      resetData3();

      // CB v5
      const size_t bufferSize = 2*JSON_ARRAY_SIZE(0) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(16) + JSON_OBJECT_SIZE(58) + 2748;
      
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(modelClient);
      // Parameters
      if (!root.success()) {
        Serial.println(F("Chaturbate Data Parsing failed!"));
        return;
      }

      const char* CBModel3 = root["broadcaster_username"];
      const char* CBModel3Status = root["room_status"];

      CBModel3Data.CBModel3 = (const char*)root["broadcaster_username"];
      CBModel3Data.CBModel3Status = (const char*)root["room_status"];

      Serial.print("Model (3):");
      Serial.println(CBModel3);
      Serial.print("Status (3):");
      Serial.println(CBModel3Status);
      
    }
    modelClient.stop();
}


String CBModel3::getCBModel3(){
  return CBModel3Data.CBModel3;
}

String CBModel3::getCBModel3Status(){
  return CBModel3Data.CBModel3Status;
}


// Reset all ChaturbateData
void CBModel3::resetData3() {
  CBModel3Data.CBModel3 = "";
  CBModel3Data.CBModel3Status = "";
}
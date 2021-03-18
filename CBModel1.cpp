
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

#include "CBModel1.h"

#define CHATURBATE_FINGERPRINT "16 a5 01 0d a1 67 f5 f1 4f 99 9c dd 00 16 18 c5 97 9b b9 44"

CBModel1::CBModel1(String username)
{
  myUsername = username;
}

void CBModel1::updateDetails(String username){

  myUsername = username;
}

void CBModel1::getDetails(){

      WiFiClientSecure modelClient;
      #ifdef ESP32
      #else
        modelClient.setFingerprint(CHATURBATE_FINGERPRINT);
      #endif
      
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println(F("Connecting to Chaturbate..."));
      if (!modelClient.connect("chaturbate.com", 443)) {
        Serial.println(F("Failed to connect to Chaturbate"));
        resetCBModel1Data();
        return;
      }
      Serial.println(F("Connected to Chaturbate"));
    
      Serial.println(F("Sending request to Chaturbate..."));
      // Send HTTP request
      modelClient.println("GET /api/chatvideocontext/" + myUsername + "/" + " HTTP/1.0");
      Serial.println("GET /api/chatvideocontext/" + myUsername + "/" + " HTTP/1.1");
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
        CBModel1Data.error = String(status);
        
        resetCBModel1Data();
        return;
      }

      Serial.println(F("Receive response from chaturbate..."));

      // Skip response headers
      modelClient.find("\r\n\r\n");
      resetCBModel1Data();

      // CB v5
      const size_t bufferSize = 2*JSON_ARRAY_SIZE(0) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(16) + JSON_OBJECT_SIZE(58) + 2748;
      
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(modelClient);
      // Parameters
      if (!root.success()) {
        Serial.println(F("Chaturbate Data Parsing failed!"));
        return;
      }

      const char* CBModel1 = root["broadcaster_username"];
      const char* CBModel1Status = root["room_status"];
      const char* CBModel1code = root["code"];
      int CBModel1NumViewers = root["num_viewers"];

      CBModel1Data.CBModel1 = (const char*)root["broadcaster_username"];
      CBModel1Data.CBModel1Status = (const char*)root["room_status"];
      CBModel1Data.CBModel1code = (const char*)root["code"];
      CBModel1Data.CBModel1NumViewers = (const char*)root["num_viewers"];

      Serial.print("Model (1):");
      Serial.println(CBModel1);
      Serial.print("Status (1):");
      Serial.println(CBModel1Status);
      Serial.print("Viewers (1): ");
      Serial.println(CBModel1NumViewers);

    }
    modelClient.stop();
}


String CBModel1::getCBModel1(){
  return CBModel1Data.CBModel1;
}

String CBModel1::getCBModel1Status(){
  return CBModel1Data.CBModel1Status;
}

String CBModel1::getCBModel1code(){
  return CBModel1Data.CBModel1code;
}

String CBModel1::getCBModel1NumViewers(){
  return CBModel1Data.CBModel1NumViewers;
}

String CBModel1::getError() {
  return CBModel1Data.error;
}

boolean CBModel1::isPassword() {
  boolean password = false;
  if (CBModel1Data.error == "HTTP/1.1 401 Unauthorized") {
    password = true;
  }
  return password;
}

// Reset all ChaturbateData
void CBModel1::resetCBModel1Data() {
  CBModel1Data.CBModel1 = "";
  CBModel1Data.CBModel1Status = "";
  CBModel1Data.CBModel1code = "";
}
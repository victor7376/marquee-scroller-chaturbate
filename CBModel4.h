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

#pragma once
#include "libs/ArduinoJson/ArduinoJson.h"
#include <WiFiClientSecure.h>
//#include "Chaturbate_fingerprint.h"

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif


class CBModel4
{
  
  public:
    CBModel4(String username4);
    void updateDetails4(String username4);
    void getDetails4();
    String getCBModel4();
    String getCBModel4Status();
    String getCBModel4code();
    String getCBModel4NumViewers();
    String getError();
    boolean isPassword();
   

  private:
    const char* servername = "chaturbate.com";
    String myUsername4;

    void resetData4();

  typedef struct {
    String CBModel4;
    String CBModel4Status;
    String CBModel4code;
    String CBModel4NumViewers;
    String error;
  } CBModel4Struct;

  CBModel4Struct CBModel4Data;
};
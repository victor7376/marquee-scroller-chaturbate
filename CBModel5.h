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


class CBModel5
{
  
  public:
    CBModel5(String username5);
    void updateDetails5(String username5);
    void getDetails5();
    String getCBModel5();
    String getCBModel5Status();
    String getCBModel5code();
    String getCBModel5NumViewers();
    String getError();
    boolean isPassword();

  private:
    const char* servername = "chaturbate.com";
    String myUsername5;

    void resetData5();

  typedef struct {
    String CBModel5;
    String CBModel5Status;
    String CBModel5code;
    String CBModel5NumViewers;
    String error;
  } CBModel5Struct;

  CBModel5Struct CBModel5Data;
};
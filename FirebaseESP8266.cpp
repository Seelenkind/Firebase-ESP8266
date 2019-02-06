/*
 * Google's Firebase real time database - ESP8266 library for Arduino, version 1.0
 * 
 * This library provides ESP8266 to perform REST API by GET PUT, POST, PATCH, DELETE data from/to with Google's Firebase database using get, set, update
 * and delete calls. 
 * 
 * The library was test and work well with ESP8266s based module and add support for multiple stream event path.
 * 
 * The MIT License (MIT)
 * Copyright (c) 2019 K. Suwatchai (Mobizt)
 * 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef FirebaseESP8266_CPP
#define FirebaseESP8266_CPP

#include "FirebaseESP8266.h"

typedef struct FirebaseESP8266::FirebaseDataType {
  static const uint8_t NULL_ = 1;
  static const uint8_t INTEGER = 2;
  static const uint8_t FLOAT = 3;
  static const uint8_t STRING = 4;
  static const uint8_t JSON = 5;
};


typedef struct FirebaseESP8266::FirebaseMethod {
  static const uint8_t PUT = 0;
  static const uint8_t POST = 1;
  static const uint8_t GET = 2;
  static const uint8_t STREAM = 3;
  static const uint8_t PATCH = 4;
  static const uint8_t DELETE = 5;
};

FirebaseESP8266::FirebaseESP8266() {}
FirebaseESP8266::~FirebaseESP8266() {}


void FirebaseESP8266::begin(const String host, const String auth) {
  begin(host.c_str(), auth.c_str());
}

void FirebaseESP8266::begin(const char* host, const char* auth) {
  firebaseBegin(host, auth, FIEBASE_PORT);
}

void FirebaseESP8266::reconnectWiFi(bool reconnect) {
  _reconnectWiFi = reconnect;
}

bool FirebaseESP8266::pathExist(FirebaseData &dataObj, const String path) {
   return pathExist(dataObj, path.c_str());
}

bool FirebaseESP8266::pathExist(FirebaseData &dataObj, const char* path){
  if (sendRequest(dataObj, path, FirebaseMethod::GET, FirebaseDataType::STRING, ""))
    return !dataObj._pathNotExist;
  else
    return false;
}

bool FirebaseESP8266::pushInt(FirebaseData &dataObj, const String path, int intValue) {
   return pushInt(dataObj, path.c_str(), intValue);
}

bool FirebaseESP8266::pushInt(FirebaseData &dataObj, const char* path, int intValue){
  char buf[50];
  memset(buf, 0, sizeof buf);
  itoa(intValue, buf, 10);
  return sendRequest(dataObj, path, FirebaseMethod::POST, FirebaseDataType::INTEGER, buf);	
}


bool FirebaseESP8266::pushFloat(FirebaseData &dataObj, const String path, float floatValue) {
  return pushFloat(dataObj, path.c_str(), floatValue);
}

bool FirebaseESP8266::pushFloat(FirebaseData &dataObj, const char* path, float floatValue){
  char buf[50];
  memset(buf, 0, sizeof buf);
  dtostrf(floatValue, 7, 6, buf);
  return sendRequest(dataObj, path, FirebaseMethod::POST, FirebaseDataType::FLOAT, buf);	
}
 
bool pushString(FirebaseData &dataObj, const String path, const String stringValue){
  return pushString(dataObj, path.c_str(), stringValue.c_str());
}

bool FirebaseESP8266::pushString(FirebaseData &dataObj, const char* path, const char* stringValue) {
  return sendRequest(dataObj, path, FirebaseMethod::POST, FirebaseDataType::STRING, stringValue);
}


bool FirebaseESP8266::pushJSON(FirebaseData &dataObj, const String path, const String jsonString){
  return pushJSON(dataObj, path.c_str(), jsonString.c_str());
}

bool FirebaseESP8266::pushJSON(FirebaseData &dataObj, const char* path, const char* jsonString) {
  return sendRequest(dataObj, path, FirebaseMethod::POST, FirebaseDataType::JSON, jsonString);
}

bool FirebaseESP8266::setInt(FirebaseData &dataObj, const String path, int intValue) {
  return setInt(dataObj, path.c_str(), intValue);
}

bool FirebaseESP8266::setInt(FirebaseData &dataObj, const char* path, int intValue) {
  char buf[50];
  memset(buf, 0, sizeof buf);
  itoa(intValue, buf, 10);
  return sendRequest(dataObj, path, FirebaseMethod::PUT, FirebaseDataType::INTEGER, buf);
}

bool FirebaseESP8266::setFloat(FirebaseData &dataObj, const String path, float floatValue) {
  return setFloat(dataObj, path.c_str(), floatValue);
}

bool FirebaseESP8266::setFloat(FirebaseData &dataObj, const char* path, float floatValue) {
  char buf[50];
  memset(buf, 0, sizeof buf);
  dtostrf(floatValue, 7, 6, buf);
  return sendRequest(dataObj, path, FirebaseMethod::PUT, FirebaseDataType::FLOAT, buf);
}

bool FirebaseESP8266::setString(FirebaseData &dataObj, const String path, const String stringValue) {
  return setString(dataObj, path.c_str(), stringValue.c_str());
}

bool FirebaseESP8266::setString(FirebaseData &dataObj, const char* path, const char* stringValue) {
  return sendRequest(dataObj, path, FirebaseMethod::PUT, FirebaseDataType::STRING, stringValue);
}

bool FirebaseESP8266::setJSON(FirebaseData &dataObj, const String path, const String jsonString) {
  return setJSON(dataObj, path.c_str(), jsonString.c_str());
}

bool FirebaseESP8266::setJSON(FirebaseData &dataObj, const char* path, const char* jsonString) {
  return sendRequest(dataObj, path, FirebaseMethod::PUT, FirebaseDataType::JSON, jsonString);
}

bool FirebaseESP8266::updateNode(FirebaseData &dataObj, const String path, const String jsonString) {
  return updateNode(dataObj, path.c_str(), jsonString.c_str());
}

bool FirebaseESP8266::updateNode(FirebaseData &dataObj, const char* path, const char* jsonString) {
  return sendRequest(dataObj, path, FirebaseMethod::PATCH, FirebaseDataType::JSON, jsonString);
}

bool FirebaseESP8266::getInt(FirebaseData &dataObj, const String path) {
  return getInt(dataObj, path.c_str());
}

bool FirebaseESP8266::getInt(FirebaseData &dataObj, const char* path) {
  return getFloat(dataObj, path);
}

bool FirebaseESP8266::getFloat(FirebaseData &dataObj, const String path) {
  return getFloat(dataObj, path.c_str());
}

bool FirebaseESP8266::getFloat(FirebaseData &dataObj, const char* path) {
  bool flag = sendRequest(dataObj, path, FirebaseMethod::GET, FirebaseDataType::FLOAT, "");
  if (dataObj._dataType != FirebaseDataType::INTEGER && dataObj._dataType != FirebaseDataType::FLOAT) flag = false;
  return flag;
}

bool FirebaseESP8266::getString(FirebaseData &dataObj, const String path) {
  return getString(dataObj, path.c_str());;
}

bool FirebaseESP8266::getString(FirebaseData &dataObj, const char* path) {
  bool flag = sendRequest(dataObj, path, FirebaseMethod::GET, FirebaseDataType::STRING, "");
  if (dataObj._dataType != FirebaseDataType::STRING) flag = false;
  return flag;
}

bool FirebaseESP8266::getJSON(FirebaseData &dataObj, const String path) {
  return getJSON(dataObj, path.c_str());
}

bool FirebaseESP8266::getJSON(FirebaseData &dataObj, const char* path) {
  bool flag = sendRequest(dataObj, path, FirebaseMethod::GET, FirebaseDataType::JSON, "");
  if (dataObj._dataType != FirebaseDataType::JSON) flag = false;
  return flag;
}

bool FirebaseESP8266::deleteNode(FirebaseData &dataObj, const String path) {
  return deleteNode(dataObj, path.c_str());
}

bool FirebaseESP8266::deleteNode(FirebaseData &dataObj, const char* path) {
  return sendRequest(dataObj, path, FirebaseMethod::DELETE, FirebaseDataType::STRING, "");
}

bool FirebaseESP8266::beginStream(FirebaseData &dataObj, const String path) {
  return beginStream(dataObj, path.c_str());
}

bool FirebaseESP8266::beginStream(FirebaseData &dataObj, const char* path) {
  return firebaseConnectStream(dataObj, path);
}

bool FirebaseESP8266::readStream(FirebaseData &dataObj) {
  if (dataObj._streamStop) return true;
  return getServerStreamResponse(dataObj);
}

bool FirebaseESP8266::endStream(FirebaseData &dataObj) {
  bool flag = false;
  memset(dataObj._streamPath, 0, sizeof dataObj._streamPath);
  forceEndHTTP(dataObj);
  flag = dataObj._http.http_connected();
  if (!flag) {
    dataObj._isStream = false;
    dataObj._streamStop = true;
  }
  return !flag;
}

void FirebaseESP8266::firebaseBegin(const char* host, const char* auth, uint16_t port) {
  memset(_host, 0, sizeof _host);
  memset(_auth, 0, sizeof _auth);
  strcpy(_host, host);
  strcpy(_auth, auth);
  _port = port;
}



int FirebaseESP8266::firebaseConnect(FirebaseData &dataObj, const char* path, const uint8_t method, uint8_t dataType, const char* payload) {

  if (dataObj._pause) return 0;


  if (strlen(path) == 0 || strlen(_host) == 0 || strlen(_auth) == 0) {
    dataObj._httpCode = _HTTP_CODE_BAD_REQUEST;
    return _HTTP_CODE_BAD_REQUEST;
  }
  //build requested uri
  char payloadStr[strlen(payload) + 10];
  memset(payloadStr, 0, sizeof payloadStr);
  char uri[200];
  memset(uri, 0, sizeof uri);
  if (path[0] != '/') strcpy(uri, "/");
  strcat(uri, path);
  if (method == FirebaseMethod::PATCH)
    strcat_P(uri, (char*)F("/"));

  strcat_P(uri, (char*)F(".json?auth="));
  strcat(uri, _auth);

  //init the firebase data
  resetFirebasedataFlag(dataObj);
  memset(dataObj._data, 0, sizeof dataObj._data);
  memset(dataObj._path, 0, sizeof dataObj._path);

  if (method == FirebaseMethod::STREAM) {
    //stream path change? reset the current (keep alive) connection
    if (strcmp(path, dataObj._streamPath) != 0) dataObj._streamPathChanged = true;
    if (!dataObj._isStream || dataObj._streamPathChanged) {
      if (dataObj._http.http_connected())
        forceEndHTTP(dataObj);
    }

    memset(dataObj._streamPath, 0, sizeof dataObj._streamPath);
    strcpy(dataObj._streamPath, path);

  } else {
    //last requested method was stream?, reset the connection
    if (dataObj._isStream) forceEndHTTP(dataObj);

    strcpy(dataObj._path, path);
    dataObj._isStreamTimeout = false;

  }


  dataObj._http.http_begin(_host, _port, uri);


  //Prepare for string and JSON payloads
  if (method != FirebaseMethod::GET && method != FirebaseMethod::STREAM && method != FirebaseMethod::DELETE) {
    memset(payloadStr, 0, sizeof payloadStr);
    if (dataType == FirebaseDataType::STRING) strcpy(payloadStr, "\"");
    strcat(payloadStr, payload);  
    if (dataType == FirebaseDataType::STRING) strcat(payloadStr, "\"");
  }
  

  //Prepare request header
  char header[FIREBASE_REQ_BUFFER_SIZE];

  buildFirebaseRequest(dataObj, _host, method, path, _auth,  payloadStr, header);

  //Send request w/wo payload
  int httpCode = dataObj._http.http_sendRequest(header, payloadStr);


  return httpCode;
}

bool FirebaseESP8266::sendRequest(FirebaseData &dataObj, const char* path, const uint8_t method, uint8_t dataType, const char* payload ) {

  bool flag = false;

  if (dataObj._pause) return true;

  if (strlen(path) == 0 || strlen(_host) == 0 || strlen(_auth) == 0) {
    dataObj._httpCode = _HTTP_CODE_BAD_REQUEST;
    return false;
  }
	
  if ((method == FirebaseMethod::PUT || method == FirebaseMethod::POST || method == FirebaseMethod::PATCH) && strlen(payload)==0 && dataType!=FirebaseDataType::STRING) { 
    dataObj._httpCode = _HTTP_CODE_BAD_REQUEST;
    return false;
  }



  //Try to reconnect WiFi if lost connection without waiting
  if (_reconnectWiFi && WiFi.status() != WL_CONNECTED) WiFi.reconnect();

  //If WiFi is not connected, return false
  if (WiFi.status() != WL_CONNECTED) {
    dataObj._httpCode = HTTPC_ERROR_CONNECTION_LOST;
    return false;
  }

  //Get the current WiFi client from current firebase data
  //Check for connection status

  if (dataObj._http.http_connected()) dataObj._httpConnected = true;
  else dataObj._httpConnected = false;


  if (dataObj._httpConnected) {
    if (method == FirebaseMethod::STREAM) {

      dataObj._streamMillis = millis();
      return false;

    } else {
      if (!dataObj._keepAlive) {
        dataObj._streamMillis = millis() + 50;
        dataObj._interruptRequest = true;
        delay(20);
        if (dataObj._http.http_connected()) {
          delay(20);
          forceEndHTTP(dataObj);
          if (dataObj._http.http_connected()) return false;
        }
        dataObj._httpConnected = false;
      }
    }
  }

  if (!dataObj._keepAlive && dataObj._httpConnected) return false;

  dataObj._httpConnected = true;
  dataObj._interruptRequest = false;

  dataObj._httpConnected = true;

  int httpCode = firebaseConnect(dataObj, path, method, dataType, payload);

  if (httpCode == 0) {
    dataObj._dataType2 = dataType;
    memset(dataObj._data, 0, sizeof dataObj._data);
    if (method == FirebaseMethod::STREAM) {
      dataObj._dataMillis = millis();
      flag = getServerStreamResponse(dataObj);
      if (!flag) forceEndHTTP(dataObj);
    } else {
      strcpy(dataObj._path, path);
      flag = getServerResponse(dataObj);
      dataObj._dataAvailable = strlen(dataObj._data) > 0;
    }

    if (!flag) forceEndHTTP(dataObj);

  } else {
    //can't establish connection
    dataObj._httpCode = httpCode;
    dataObj._httpConnected = false;
    delay(100);
    return false;
  }


  return flag;
}
bool FirebaseESP8266::getServerResponse(FirebaseData &dataObj) {

  if (dataObj._pause) return true;

  if (WiFi.status() != WL_CONNECTED) {
    dataObj._httpCode = HTTPC_ERROR_CONNECTION_LOST;
    return false;
  }



  WiFiClientSecure client = dataObj._http.client;
  if (!dataObj._http.http_connected() || dataObj._interruptRequest) return cancelCurrentResponse(dataObj);
  if (!handleTCPNotConnected(dataObj) || !dataObj._httpConnected) return false;


  bool flag = false;
  memset(dataObj._data, 0, sizeof dataObj._data);
  char response[FIREBASE_RESPONSE_SIZE];
  memset(response, 0, sizeof response);
  char res[FIREBASE_RESPONSE_SIZE];
  uint16_t count = 0;
  char c;
  int p1, p2, len;
  bool isStream = false;
  dataObj._httpCode = -1000;
  dataObj._contentLength = -1;
  dataObj._bufferOverflow = false;
  memset(dataObj._pushName, 0, sizeof dataObj._pushName);

  bool hasEvent = false;
  bool hasEventData = false;
  char eventType[30];
  memset(eventType, 0, sizeof eventType);
  unsigned long dataTime = millis();

  if (!dataObj._isStream)
    while (client.connected() && !client.available() && millis() - dataTime < dataObj._http.tcpTimeout) delay(1);


  dataTime = millis();
  if (client.connected() && client.available()) {

    while (client.available() &&  millis() - dataTime < dataObj._http.tcpTimeout) {
      if (dataObj._interruptRequest) return cancelCurrentResponse(dataObj);
      c = client.read();
      if (count < FIREBASE_RESPONSE_SIZE - 1 && c != '\n') {
        strcat_c(response, c);
        count++;
      } else {
        if (strlen(response) == FIREBASE_RESPONSE_SIZE - 1) dataObj._bufferOverflow = true;
        dataTime = millis();
        if (strlen(response) > 0) {
          if (strpos(response, "HTTP/1.1", 0) != -1) {
            p1 = strpos(response, " ", 0);
            len = rstrpos(response, " ", 0) - p1 - 1;
            memset(res, 0, sizeof res);
            strncpy(res, response + p1, len);
            dataObj._httpCode = atoi(res);
          } else if (strpos(response, ":", 0) != -1) {
            p1 = strpos(response, ":", 0);
            if (p1 < strlen(response) - 1) {
              len = strlen(response) - p1;
              memset(res, 0, sizeof res);
              strncpy(res, response + p1, len);

              //Parses for headers and payload
              if (strpos(response, "Content-Type", 0) != -1 && strpos(res, "text/event-stream", 0) != -1) isStream = true;
              else if (strpos(response, "Connection", 0) != -1) {
                if (strpos(res, "keep-alive", 0) != -1) dataObj._keepAlive = true;
                else dataObj._keepAlive = false;
              }
              else if (strpos(response, "Content-Length", 0) != -1) dataObj._contentLength = atoi(res);
              else if (strpos(response, "event:", 0) != -1) {
                strcpy(eventType, res);
                hasEvent = true;
                isStream = true;
                dataObj._httpCode = _HTTP_CODE_OK;
              } else if (strpos(response, "data:", 0) != -1) {
                memset(response, 0, sizeof response);
                strcpy (response, res);
                hasEventData = true;
                isStream = true;
                dataObj._httpCode = _HTTP_CODE_OK;
              }
            }
          }
        }
        if (!hasEventData || !hasEvent) {
          memset(response, 0, sizeof response);
          count = 0;
        }
      }
    }
    if (millis() - dataTime > dataObj._http.tcpTimeout)
      dataObj._httpCode = HTTPC_ERROR_READ_TIMEOUT;

    if (dataObj._httpCode == _HTTP_CODE_OK) {
      //JSON stream data?
      if (isStream) {
        if (hasEventData && hasEvent) {
          if (strpos(eventType, "put", 0) != -1 || strpos(eventType, "patch", 0) != -1) {

            //Parses json response for path
            p1 = strpos(response, "\"path\":\"", 0);
            if (p1 != -1 && p1 < sizeof response)
            {
              p1 = p1 + 6;
              p2 = strpos(response, "\"", p1 + 1);
              if (p2 != -1 && p2 < sizeof response && p1 < p2) {
                len = p2 - p1 - 2;
                memset(dataObj._path, 0, sizeof dataObj._path);
                strncpy(dataObj._path, response + p1 + 1, len);
                dataObj._path[strlen(dataObj._path)] = '\0';
              }
            }

            //Parses json response for data
            p1 = strpos(response, "\"data\":", 0);
            if (p1 != -1 && p1 < sizeof response)
            {
              p1 = p1 + 5;
              p2 = strlen(response) - 1;
              if (p1 < p2) {

                len = p2 - p1 - 1;
                memset(dataObj._data, 0, sizeof dataObj._data);
                strncpy(dataObj._data, response + p1 + 1, len);

                memset(response, 0, sizeof response);
                strcpy(response, dataObj._data);
                setDataType(dataObj, response);

                bool samePath = strcmp(dataObj._path, dataObj._path2) == 0;
                bool rootPath = strcmp(dataObj._path, "/") == 0;
                bool emptyPath = strlen(dataObj._path2) == 0;
                bool sameData = strcmp(dataObj._data, dataObj._data2) == 0;
                //Any stream update?
                if ((!samePath  && (!rootPath || emptyPath)) || (samePath && !sameData && !dataObj._streamPathChanged)) {
                  dataObj._streamDataChanged = true;
                  memset(dataObj._data2, 0, sizeof dataObj._data2);
                  strcpy(dataObj._data2, dataObj._data);
                  memset(dataObj._path2, 0, sizeof dataObj._path2);
                  strcpy(dataObj._path2, dataObj._path);
                } else dataObj._streamDataChanged = false;
                dataObj._dataMillis = millis();
                flag = true;
                dataObj._dataAvailable = flag;
                dataObj._isStreamTimeout = false;
              }
            }
            dataObj._streamPathChanged = false;
          } else {
            //Firebase keep alive data
            if (strpos(eventType, "keep-alive", 0) != -1) {
              dataObj._isStreamTimeout = false;
              dataObj._dataMillis = millis();
            }
          }
        }
        dataObj._streamMillis = millis();
      } else {
        //Just text payload
        setDataType(dataObj, response);

        //Push (POST) data?
        p1 = strpos(response, "{\"name\":\"", 0);
        if (p1 != -1 && p1 < sizeof response) {
          p1 = p1 + 8;
          p2 = strlen(response) - 1;
          len = p2 - p1 - 1;
          strncpy(dataObj._pushName, response + p1, len);
          dataObj._dataType = -1;
          dataObj._dataType2 = -1;
          memset(dataObj._data, 0, sizeof dataObj._data);
        }

      }
    } else {
      dataObj._contentLength = -1;
    }



    if (dataObj._dataType == FirebaseDataType::NULL_) {
      dataObj._pathNotExist = true;
    } else {
      dataObj._pathNotExist = false;
      bool _n1 = dataObj._dataType == FirebaseDataType::FLOAT || dataObj._dataType == FirebaseDataType::INTEGER;
      bool _n2 = dataObj._dataType2 == FirebaseDataType::FLOAT || dataObj._dataType2 == FirebaseDataType::INTEGER;

      if (dataObj._dataType2 == dataObj._dataType || (_n1 && _n2))
        dataObj._mismatchDataType = false;
      else
        dataObj._mismatchDataType = true;
    }

    if (!dataObj._httpCode) {
      dataObj._contentLength = -1;
      dataObj._httpCode = HTTPC_ERROR_NO_HTTP_SERVER;
    }
    dataObj._httpConnected = false;
    dataObj._streamMillis =  millis();

    if ( dataObj._httpCode == HTTPC_ERROR_READ_TIMEOUT) return false;
    return dataObj._httpCode == _HTTP_CODE_OK;
  }
  if (dataObj._httpCode == -1000) flag = true;
  dataObj._httpConnected =  false;
  dataObj._streamMillis = millis();

  return flag;
}
bool FirebaseESP8266::firebaseConnectStream(FirebaseData &dataObj, const char* path) {

  if (dataObj._pause) return true;

  dataObj._streamStop = false;

  if (dataObj._isStream && strcmp(path, dataObj._streamPath) == 0) return true;

  if (strlen(path) == 0 || strlen(_host) == 0 || strlen(_auth) == 0) {
    dataObj._httpCode = _HTTP_CODE_BAD_REQUEST;
    return false;
  }


  if (millis() - dataObj._streamResetMillis > 50) delay(50);
  bool flag;
  flag = strlen(dataObj._streamPath) == 0;
  flag |= firebaseConnect(dataObj, path, FirebaseMethod::STREAM, FirebaseDataType::STRING, "") == 0;
  dataObj._dataMillis = millis();
  return flag;
}

bool FirebaseESP8266::getServerStreamResponse(FirebaseData &dataObj) {

  if (dataObj._pause) return true;

  if (dataObj._streamStop) return true;

  unsigned long ml = millis();
  if (dataObj._streamMillis == 0) dataObj._streamMillis = ml;
  if (dataObj._streamResetMillis == 0) dataObj._streamResetMillis = ml;

  //Reset firebase data every 50 ms and extend delay for 50 ms before stream response checking
  //to allow other http connection that may happen
  if (ml - dataObj._streamResetMillis > 50) {
    dataObj._streamResetMillis = ml;
    dataObj._streamDataChanged = false;
    memset(dataObj._data2, 0, sizeof dataObj._data2);
    memset(dataObj._path2, 0, sizeof dataObj._path2);
    dataObj._dataAvailable = false;
    dataObj._isStreamTimeout = false;
    delay(50);
    return true;
  }

  if (ml - dataObj._streamMillis > 50) {
    dataObj._streamMillis = ml;
    bool flag = false;
    char path[FIREBASE_PATH_SIZE];
    memset(path, 0, sizeof path);
    if (dataObj._dataMillis > 0 && millis() - dataObj._dataMillis > KEEP_ALIVE_TIMEOUT) {
      dataObj._dataMillis = millis();
      dataObj._isStreamTimeout = true;
      strcpy(path, dataObj._streamPath);
      firebaseConnectStream(dataObj, path);
      return false;
    }
    if (dataObj._httpConnected) return false;
    dataObj._httpConnected = true;
    resetFirebasedataFlag(dataObj);
    memset(dataObj._data, 0, sizeof dataObj._data);


    if (dataObj._http.http_connected() && !dataObj._isStream) forceEndHTTP(dataObj);
    if ( !dataObj._http.http_connected()) {
      strcpy(path, dataObj._streamPath);
      firebaseConnectStream(dataObj, path);
    }

    return getServerResponse(dataObj);
  }
}
void FirebaseESP8266::forceEndHTTP(FirebaseData &dataObj) {
  WiFiClientSecure client = dataObj._http.client;

  if (client.available() > 0) {
    client.flush();
    delay(50);
  }
  client.stop();
  delay(50);

}
void FirebaseESP8266::buildFirebaseRequest(FirebaseData &dataObj, const char* host, uint8_t method, const char* path, const char* auth, const char* payload, char* request) {
  const char newline[10] = "\r\n";
  char contentLength[20];
  memset(contentLength, 0, sizeof contentLength);
  memset(request, 0, sizeof request);
  if (method == FirebaseMethod::STREAM) {
    strcpy_P(request, (char*)F("GET "));
    dataObj._isStream = true;
  } else {
    if (method == FirebaseMethod::PUT)  strcpy(request, "PUT");
    else if (method == FirebaseMethod::POST)  strcpy(request, "POST");
    else if (method == FirebaseMethod::GET)  strcpy(request, "GET");
    else if (method == FirebaseMethod::PATCH)  strcpy(request, "PATCH");
    else if (method == FirebaseMethod::DELETE)  strcpy(request, "DELETE");
    strcat(request, " ");
    dataObj._isStream = false;
  }

  strcat(request, path);

  if (method == FirebaseMethod::PATCH)
    strcat_P(request, (char*)F("/"));

  strcat_P(request, (char*)F(".json?auth="));
  strcat(request, auth);
  strcat_P(request, (char*)F(" HTTP/1.1\r\n"));
  strcat_P(request, (char*)F("Host: "));
  strcat(request, host);
  strcat(request, newline);
  strcat_P(request, (char*)F("User-Agent: ESP8266\r\n"));
  strcat_P(request, (char*)F("X-Firebase-Decoding: 1\r\n"));

  if (method == FirebaseMethod::STREAM) {
    strcat_P(request, (char*)F("Connection: close\r\n"));
    strcat_P(request, (char*)F("Accept: text/event-stream\r\n"));
  } else {
    strcat_P(request, (char*)F("Connection: keep-alive\r\n"));
    strcat_P(request, (char*)F("Keep-Alive:timeout=30, max=100\r\n"));
  }

  strcat_P(request, (char*)F("Accept-Encoding: identity;q=1,chunked;q=0.1,*;q=0\r\n"));
  if (method == FirebaseMethod::PUT || method == FirebaseMethod::POST || method == FirebaseMethod::PATCH) {
    strcat_P(request, (char*)F("Content-Length: "));
    itoa(strlen(payload), contentLength, 10);
    strcat(request, contentLength);
  }
  strcat(request, newline);
  strcat(request, newline);

}
bool FirebaseESP8266::cancelCurrentResponse(FirebaseData &dataObj) {
  forceEndHTTP(dataObj);
  dataObj._isStream = false;
  dataObj._streamDataChanged = false;
  dataObj._dataMillis = millis();
  memset(dataObj._data, 0, sizeof dataObj._data);
  memset(dataObj._path, 0, sizeof dataObj._path);
  memset(dataObj._data2, 0, sizeof dataObj._data2);
  memset(dataObj._path2, 0, sizeof dataObj._path2);
  dataObj._dataAvailable = false;
  dataObj._isStreamTimeout = false;
  dataObj._httpCode = HTTPC_ERROR_CONNECTION_REFUSED;
  return false;
}

void FirebaseESP8266::setDataType(FirebaseData &dataObj, const char* response) {
  memset(dataObj._data, 0, sizeof dataObj._data);
  if (strlen(response) > 0) {
    if (response[0] == '{')
      dataObj._dataType = FirebaseDataType::JSON;
    else if (response[0] == '"')
      dataObj._dataType = FirebaseDataType::STRING;
    else if (strpos(response, ".", 0) != -1)
      dataObj._dataType = FirebaseDataType::FLOAT;
    else if (strcmp(response, "null") == 0)
      dataObj._dataType = FirebaseDataType::NULL_;
    else  dataObj._dataType = FirebaseDataType::INTEGER;
    if (strcmp(response, "null") != 0) strcpy(dataObj._data, response);
    dataObj._data[strlen(dataObj._data)] = '\0';
  } else {
    dataObj._dataType = FirebaseDataType::NULL_;
  }
}

void FirebaseESP8266::resetFirebasedataFlag(FirebaseData &dataObj) {
  dataObj._bufferOverflow = false;
  dataObj._streamDataChanged = false;
  dataObj._streamPathChanged = false;
  dataObj._dataAvailable = false;
  memset(dataObj._pushName, 0, sizeof dataObj._pushName);
}
bool FirebaseESP8266::handleTCPNotConnected(FirebaseData &dataObj) {
  if (!dataObj._http.http_connected()) {
    dataObj._contentLength = -1;
    dataObj._dataType = FirebaseDataType::NULL_;
    dataObj._httpCode = HTTPC_ERROR_NOT_CONNECTED;
    memset(dataObj._data, 0, sizeof dataObj._data);
    memset(dataObj._path, 0, sizeof dataObj._path);
    resetFirebasedataFlag(dataObj);
    return false;
  }
  return true;
}

void FirebaseESP8266::errorToString(int httpCode, char* buf) {
  memset(buf, 0, sizeof buf);
  switch (httpCode) {
    case HTTPC_ERROR_CONNECTION_REFUSED:
      strcpy(buf, (char*)F("connection refused"));
      return;
    case HTTPC_ERROR_SEND_HEADER_FAILED:
      strcpy(buf, (char*)F("send header failed"));
      return;
    case HTTPC_ERROR_SEND_PAYLOAD_FAILED:
      strcpy(buf, (char*)F("send payload failed"));
      return;
    case HTTPC_ERROR_NOT_CONNECTED:
      strcpy(buf, (char*)F("not connected"));
      return;
    case HTTPC_ERROR_CONNECTION_LOST:
      strcpy(buf, (char*)F("connection lost"));
      return;
    case HTTPC_ERROR_NO_HTTP_SERVER:
      strcpy(buf, (char*)F("no HTTP server"));
      return;
    case _HTTP_CODE_BAD_REQUEST:
      strcpy(buf, (char*)F("bad request"));
      return;
    case _HTTP_CODE_NON_AUTHORITATIVE_INFORMATION:
      strcpy(buf, (char*)F("non-authoriative information"));
      return;
    case _HTTP_CODE_NO_CONTENT:
      strcpy(buf, (char*)F("no content"));
      return;
    case _HTTP_CODE_MOVED_PERMANENTLY:
      strcpy(buf, (char*)F("moved permanently"));
      return;
    case _HTTP_CODE_USE_PROXY:
      strcpy(buf, (char*)F("use proxy"));
      return;
    case _HTTP_CODE_TEMPORARY_REDIRECT:
      strcpy(buf, (char*)F("temporary redirect"));
      return;
    case _HTTP_CODE_PERMANENT_REDIRECT:
      strcpy(buf, (char*)F("permanent redirect"));
      return;
    case _HTTP_CODE_UNAUTHORIZED:
      strcpy(buf, (char*)F("unauthorized"));
      return;
    case _HTTP_CODE_FORBIDDEN:
      strcpy(buf, (char*)F("forbidden"));
      return;
    case _HTTP_CODE_NOT_FOUND:
      strcpy(buf, (char*)F("not found"));
      return;
    case _HTTP_CODE_METHOD_NOT_ALLOWED:
      strcpy(buf, (char*)F("method not allow"));
      return;
    case _HTTP_CODE_NOT_ACCEPTABLE:
      strcpy(buf, (char*)F("not acceptable"));
      return;
    case _HTTP_CODE_PROXY_AUTHENTICATION_REQUIRED:
      strcpy(buf, (char*)F("proxy authentication required"));
      return;
    case _HTTP_CODE_REQUEST_TIMEOUT:
      strcpy(buf, (char*)F("request timeout"));
      return;
    case _HTTP_CODE_LENGTH_REQUIRED:
      strcpy(buf, (char*)F("length required"));
      return;
    case _HTTP_CODE_PAYLOAD_TOO_LARGE:
      strcpy(buf, (char*)F("payload too large"));
      return;
    case _HTTP_CODE_MISDIRECTED_REQUEST:
      strcpy(buf, (char*)F("mis-directed request"));
      return;
    case _HTTP_CODE_UNPROCESSABLE_ENTITY:
      strcpy(buf, (char*)F("unprocessable entity"));
      return;
    case _HTTP_CODE_URI_TOO_LONG:
      strcpy(buf, (char*)F("uri too long"));
      return;
    case _HTTP_CODE_TOO_MANY_REQUESTS:
      strcpy(buf, (char*)F("too many requests"));
      return;
    case _HTTP_CODE_REQUEST_HEADER_FIELDS_TOO_LARGE:
      strcpy(buf, (char*)F("request header fields too larg"));
      return;
    case _HTTP_CODE_INTERNAL_SERVER_ERROR:
      strcpy(buf, (char*)F("internal server error"));
      return;
    case _HTTP_CODE_BAD_GATEWAY:
      strcpy(buf, (char*)F("bad gateway"));
      return;
    case _HTTP_CODE_SERVICE_UNAVAILABLE:
      strcpy(buf, (char*)F("service unavailable"));
      return;
    case _HTTP_CODE_GATEWAY_TIMEOUT:
      strcpy(buf, (char*)F("gateway timeout"));
      return;
    case _HTTP_CODE_HTTP_VERSION_NOT_SUPPORTED:
      strcpy(buf, (char*)F("http version not support"));
      return;
    case _HTTP_CODE_NETWORK_AUTHENTICATION_REQUIRED:
      strcpy(buf, (char*)F("network authentication required"));
      return;
    case _HTTP_CODE_LOOP_DETECTED:
      strcpy(buf, (char*)F("loop detected"));
      return;
    case FIREBASE_ERROR_BUFFER_OVERFLOW:
      strcpy(buf, (char*)F("data buffer overflow"));
      return;
    case HTTPC_ERROR_READ_TIMEOUT:
      strcpy(buf, (char*)F("read Timeout"));
      return;
    case FIREBASE_ERROR_DATA_TYPE_MISMATCH:
      strcpy(buf, (char*)F("data type mismatch"));
      return;
    case FIREBASE_ERROR_PATH_NOT_EXIST:
      strcpy(buf, (char*)F("path not exist"));
      return;
    default:
      return;
  }
}
void FirebaseESP8266::strcat_c (char *str, char c)
{
  for (; *str; str++);
  *str++ = c;
  *str++ = 0;
}
int FirebaseESP8266::strpos(const char *haystack, const char *needle, int offset)
{
  char _haystack[strlen(haystack)];
  strncpy(_haystack, haystack + offset, strlen(haystack) - offset);
  char *p = strstr(_haystack, needle);
  if (p)
    return p - _haystack + offset + 1;
  return -1;
}

int FirebaseESP8266::rstrpos(const char *haystack, const char *needle, int offset)
{
  char _haystack[strlen(haystack)];
  strncpy(_haystack, haystack + offset, strlen(haystack) - offset);
  char *p = rstrstr(_haystack, needle);
  if (p)
    return p - _haystack + offset + 1;
  return -1;
}
char* FirebaseESP8266::rstrstr(const char* haystack, const char* needle)
{
  int needle_length = strlen(needle);
  const char* haystack_end = haystack + strlen(haystack) - needle_length;
  const char* p;
  size_t i;
  for (p = haystack_end; p >= haystack; --p)
  {
    for (i = 0; i < needle_length; ++i) {
      if (p[i] != needle[i])
        goto next;
    }
    return (char*)p;
next:;
  }
  return 0;
}

void FirebaseESP8266::replace_char(char* str, char in, char out) {
  char buf[strlen(str)];
  memset(buf,0, sizeof buf);
  int k=0; 
  if(out !='\0'){
    for(int i=0;i<strlen(str);i++)
      if(str[i]==in) str[i]=out;
	}else{
	  for(int i=0;i<strlen(str);i++)
	  if(str[i]!=in) {
        buf[k] = str[i];
		k++;
	  }
	  memset(str,0, sizeof str);
	  strcpy(str,buf);	  
  }
}


FirebaseData::FirebaseData() {}

WiFiClientSecure FirebaseData::getWiFiClient() {
  return _http.client;
}

bool FirebaseData::pauseFirebase(bool pause) {

  if (_http.http_connected() && pause != _pause) {
    if (_http.client.available() > 0) {
      _http.client.flush();
      delay(50);
    }
    _http.client.stop();
    delay(50);
    if (!_http.http_connected()) {
      _pause = pause;
      return true;
    }
    return false;
  } else {
    _pause = pause;
    return true;
  }


}


String FirebaseData::dataType() {

  if (_dataType == FirebaseESP8266::FirebaseDataType::JSON) return "json";
  if (_dataType == FirebaseESP8266::FirebaseDataType::STRING) return "string";
  if (_dataType == FirebaseESP8266::FirebaseDataType::FLOAT) return "float";
  if (_dataType == FirebaseESP8266::FirebaseDataType::INTEGER) return "int";
  if (_dataType == FirebaseESP8266::FirebaseDataType::NULL_) return "null";
  return String();
}

uint8_t FirebaseData::dataTypeInt() {
  return _dataType;
}

String FirebaseData::streamPath() {
  return String(_streamPath);
}

void FirebaseData::streamPathBuf(char* buf) {
  memset(buf, 0, sizeof buf);
  strcpy(buf, _streamPath);
}

String FirebaseData::dataPath() {
  return String(_path);
}

void FirebaseData::dataPathBuf(char* buf) {
  memset(buf, 0, sizeof buf);
  strcpy(buf, _path);
}

int FirebaseData::intData() {
  if (strlen(_data) > 0  && _dataType == FirebaseESP8266::FirebaseDataType::INTEGER || _dataType == FirebaseESP8266::FirebaseDataType::FLOAT) return atoi(_data);
  else return 0;
}

float FirebaseData::floatData() {
  if (strlen(_data) > 0  && (_dataType == FirebaseESP8266::FirebaseDataType::INTEGER || _dataType == FirebaseESP8266::FirebaseDataType::FLOAT)) return atof(_data);
  else return 0.0;
}

String FirebaseData::stringData() {
  char buf[FIREBASE_DATA_SIZE];
  memset(buf, 0, sizeof buf);  
  strcpy(buf, _data);
  removeDQ(buf);
  if (strlen(_data) > 0  && _dataType == FirebaseESP8266::FirebaseDataType::STRING) return String(buf);
  else return String();
}

void FirebaseData::stringDataBuf(char* buf) {
  memset(buf, 0, sizeof buf);  
  if (strlen(_data) > 0  && _dataType == FirebaseESP8266::FirebaseDataType::STRING) {
	  strcpy(buf, _data);
	  removeDQ(buf);
  }
}

String FirebaseData::jsonData() {
  if (strlen(_data) > 0  && _dataType == FirebaseESP8266::FirebaseDataType::JSON) return String(_data);
  else return String();
}

void FirebaseData::jsonDataBuf(char* buf) {
  memset(buf, 0, sizeof buf);
  if (strlen(_data) > 0  && _dataType == FirebaseESP8266::FirebaseDataType::JSON) strcpy(buf,_data);
}

String FirebaseData::pushName() {
  char buf[30];
  memset(buf, 0, sizeof buf);
  strcpy(buf, _pushName);
  if (strlen(buf) > 0) return String(buf);
  else return String();
}

void FirebaseData::pushNameBuf(char* buf) {
  memset(buf, 0, sizeof buf);  
  if (strlen(buf) > 0) strcpy(buf, _pushName);
}

bool FirebaseData::isStream() {
  return _isStream;
}

bool FirebaseData::httpConnected() {
  return _httpConnected;
}

bool FirebaseData::streamTimeout() {
  return _isStreamTimeout;
}

bool FirebaseData::dataAvailable() {
  return _dataAvailable;
}

bool FirebaseData::streamAvailable() {
  return !_httpConnected && _dataAvailable && _streamDataChanged;
}

bool FirebaseData::mismatchDataType() {
  return _mismatchDataType;
}
bool FirebaseData::bufferOverflow() {
  return _bufferOverflow;
}
String FirebaseData::errorReason() {
  char buf[50];

  if (_httpCode == _HTTP_CODE_OK) {
    if (_bufferOverflow)
      _httpCode = FIREBASE_ERROR_BUFFER_OVERFLOW;
    if (_mismatchDataType)
      _httpCode = FIREBASE_ERROR_DATA_TYPE_MISMATCH;
    else if (_pathNotExist)
      _httpCode = FIREBASE_ERROR_PATH_NOT_EXIST;
  }

  Firebase.errorToString(_httpCode, buf);

  if (strlen(buf) == 0 && _httpCode > 0)itoa(_httpCode, buf, 10);

  return String(buf);
}

void FirebaseData::errorReasonBuf(char* buf) {
	
  memset(buf, 0, sizeof buf);
  
  if (_httpCode == _HTTP_CODE_OK) {
    if (_bufferOverflow)
      _httpCode = FIREBASE_ERROR_BUFFER_OVERFLOW;
    if (_mismatchDataType)
      _httpCode = FIREBASE_ERROR_DATA_TYPE_MISMATCH;
    else if (_pathNotExist)
      _httpCode = FIREBASE_ERROR_PATH_NOT_EXIST;
  }

  Firebase.errorToString(_httpCode, buf);

  if (strlen(buf) == 0 && _httpCode > 0)itoa(_httpCode, buf, 10);

}

int FirebaseData::httpCode() {
  return _httpCode;
}



void FirebaseData::removeDQ(char* str) {
  char buf[strlen(str)];
  memset(buf,0, sizeof buf);
  for(int i=1;i<strlen(str)-1;i++)
	buf[i-1]=str[i];

  memset(str,0, sizeof str);
  strcpy(str,buf);
}

FirebaseESP8266 Firebase = FirebaseESP8266();

#endif

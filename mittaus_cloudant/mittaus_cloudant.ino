/**
 * Based on:
 * BasicHTTPClient.ino
 *
 */
#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>

#include <ArduinoJson.h>

/************************* WiFi Access Point *********************************/
const char* ssid = "";
const char* password = "";
const char* iamEndpoint = "https://iam.cloud.ibm.com/identity/token?grant_type=urn:ibm:params:oauth:grant-type:apikey&apikey=APIKEYTAHAN";
const char* sendEndpoint = "https://5dbdfbf9-61d8-46d1-a127-d3bd471efad2-bluemix.cloudantnosqldb.appdomain.cloud/testing";

String token;
bool loggedIn = false;

String getBearer() {
  String bearer = "Bearer ";
  bearer.concat(token);
  return bearer;
}


String postRequest(String endpoint, String payload) {
  /**
   * One way to send json:
   * https://arduinojson.org/
  */
  
  HTTPClient http;
  String responseData;
  
  Serial.print("[HTTP] begin...\n");
  // configure traged server and url
  http.begin(endpoint); //HTTP

  // If payload is empty string, dont add content type header.
  // IBM Cloudant POST login is done with empty payload. Content type causes error
  if (payload.length() != 0) {
    http.addHeader("Content-Type", "application/json");
  }

  // Add authorization header if logged in.
  // Prevent authorization header when logging in.
  if (loggedIn) {
    http.addHeader("authorization", getBearer());
  }
  
  Serial.print("[HTTP] POST...\n");
  // start connection and send HTTP header
  int httpCode = http.POST(payload);
  
  // httpCode will be negative on error
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);

    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      responseData = http.getString();
      Serial.println(responseData);
    } else {
      /// Print error response, payload length and bearer string
      String errorResponseData = http.getString();
      Serial.print(payload.length());
      Serial.print(getBearer());
      Serial.println(errorResponseData);
    }

  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  
  http.end();
  return responseData;
}


String getRequest(char* endpoint) {
  HTTPClient http;
  String responseData;
  
  Serial.print("[HTTP] begin...\n");
  // configure traged server and url
  http.begin(endpoint); //HTTP
  
  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  
  // httpCode will be negative on error
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if(httpCode == HTTP_CODE_OK) {
        responseData = http.getString();
        Serial.println(responseData);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  
  http.end();
  return responseData;
}


void postMeasure(int num) {
  /**
   * Create json String payload to POST
   */
  String jsonData = "{\"measure\": ";
  jsonData.concat(num);
  jsonData.concat("}");
  Serial.print("Json data: ");
  Serial.println(jsonData);
  postRequest(sendEndpoint, jsonData);
}


void iamLogin() {
  /**
   * Login IBM IAM. Get token
   */
  StaticJsonDocument<2000> doc;
  String response = postRequest(iamEndpoint, "");
  DeserializationError error = deserializeJson(doc, response);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  const char* accessToken = doc["access_token"];
  token = accessToken;
  Serial.print(F("Access token: "));
  Serial.println(token);
  loggedIn = true;
}


void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println("HTTP request demo");

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  delay(2000);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  iamLogin();
  delay(2000);
  postMeasure(5);
}


void loop() {

}



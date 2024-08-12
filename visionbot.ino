#include "esp_camera.h"          // ESP Camera Library
#include <Arduino.h>             // Arduino Library
#include <WiFi.h>                // WiFi Library for ESP32
#include <HTTPClient.h>          // HTTP Client Library
#include <base64.h>              // Base64 Library for ESP32

// Define the camera model
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// Wi-Fi credentials
const char* ssid = "**********";
const char* password = "************";

// API URL
const char* url = "https://gemini-flask-api.vercel.app/generate";

// Prompt
const char* prompt = "Describe the image";

// Button pin configuration
const int buttonPin = 15; // GPIO pin for the push button

// Setup function to initialize the camera, Wi-Fi, and button pin
void setup() {
  Serial.begin(115200); // Starting Serial Communication

  // Configuring the button pin as an input
  pinMode(buttonPin, INPUT_PULLUP); // Use the internal pull-up resistor

  // Configuring camera settings
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA; // Set a smaller frame size
  config.jpeg_quality = 10;
  config.fb_count = 2;

  // Initialize the camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x\n", err);
    return;
  }
  Serial.println("Camera initialized");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected!");
}

// Function to capture, encode, and send the image
void captureAndSendImage() {
  // Capture a single frame
  camera_fb_t *fb = esp_camera_fb_get(); // Captures the image
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  // Encode the image to base64
  String encoded = base64::encode(fb->buf, fb->len);

  // Prepare the JSON payload
  String payload = "{\"prompt\":\"" + String(prompt) + "\",\"image\":\"" + encoded + "\"}";

  // Send the POST request
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(payload);

  if (httpResponseCode == 200) {
    String response = http.getString();
    Serial.println("Generated Content:");
    Serial.println(response);
  } else {
    Serial.print("Request failed with status code ");
    Serial.println(httpResponseCode);
  }

  http.end();

  // Return the frame buffer back to the driver
  esp_camera_fb_return(fb);
}

// Loop function to check button state and trigger image capture
void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Button pressed. Capturing and sending image...");
    captureAndSendImage();
    
    // Wait for the button to be released to avoid multiple captures
    while (digitalRead(buttonPin) == LOW) {
      delay(100);
    }
  }
}

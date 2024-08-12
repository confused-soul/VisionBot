# VisionBot: AI Visual Assistance System

**VisionBot** is an AI-powered visual assistance system designed to help visually impaired individuals by providing real-time descriptions of their surroundings. The system uses an ESP32-CAM microcontroller to capture images, which are processed by a custom Flask-based web API. The API utilizes the Gemini LLM to generate detailed descriptions of the images.

## Features

- **Image Capture**: Captures images with an ESP32-CAM when a button is pressed.
- **Real-Time Descriptions**: Provides accurate and detailed descriptions of images using the Gemini LLM.
- **Custom Flask API**: A Flask-based web server handles image processing and communicates with the Gemini Python API.
- **AI Integration**: Leverages the power of the Gemini LLM for natural language processing and image description generation.

## System Components

1. **ESP32-CAM MCU**: A microcontroller unit that captures images upon button press.
2. **Flask Web API**: A server that receives the captured image, processes it, and returns a description.
3. **Gemini LLM**: A language model that generates descriptions of the images received by the server.

## Installation

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/yourusername/VisionBot.git
   cd VisionBot
   ```

2. **Set Up the Flask Server:**

   - Install required dependencies:

     ```bash
     pip install -r requirements.txt
     ```

   - Start the Flask server:

     ```bash
     python web_api.py
     ```

3. **Configure ESP32-CAM:**

   - Flash the provided firmware to the ESP32-CAM.
   - Ensure the MCU is connected to the correct Wi-Fi network and can communicate with the Flask server.

## Usage

1. **Capture Image**: Press the button on the ESP32-CAM to capture an image.
2. **Process Image**: The image is sent to the Flask API, which processes it using the Gemini LLM.
3. **Receive Description**: The system returns a detailed description of the captured image, providing visual assistance.

## Potential Applications

VisionBot can be used to assist visually impaired individuals by providing real-time descriptions of their environment, helping them navigate and understand their surroundings better.

## Contributing

Contributions are welcome! Please fork this repository and submit a pull request for any feature enhancements or bug fixes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

For any inquiries or support, please contact **Md Yasir Khan** at [mdyasirkhan2003@gmail.com].

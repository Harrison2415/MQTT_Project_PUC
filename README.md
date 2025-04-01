# MQTT Project - Automated Model with ESP

This project was developed as part of a college course. It consists of an automated model that uses an **ESP** to control various components, such as **LEDs** and **motors**, through the **MQTT protocol**.

## 🔧 How It Works?

- The model includes **LEDs**, which simulate lighting, and **motors**, which control doors and gates.
- Communication is carried out via **MQTT**, using a **public broker**.
- An **ESP** receives MQTT commands to activate or deactivate the devices in the model.
- A **ready-made MQTT app** from the Play Store was used to send commands, making it easy to control the model without developing a custom application.

## 🚀 Technologies Used

- **ESP8266/ESP32** (for Wi-Fi communication)
- **MQTT** (communication protocol)
- **Public MQTT broker** (to receive and send commands)

## 📌 Requirements

To run this project, you will need:
- An **ESP8266 or ESP32** module
- Sensors, LEDs, and **servos** according to your model design
- An **MQTT client** to send commands (such as MQTT Explorer or a mobile app). There are many **ready-made apps** available in the Play Store that can be used for this purpose.

## 📜 Usage

1. **Upload the code to the ESP** using the Arduino IDE.
2. **Configure the ESP** to connect to Wi-Fi and the MQTT broker.
3. **Use a ready-made MQTT app** to send MQTT commands to turn LEDs on/off, open/close gates, etc.

## 🤝 Contributing

If this project is useful to you, feel free to contribute! Fork the repository, improve the code, and submit a pull request. 😃

---

Hope this project helps you in some way!

**Happy coding! 🚀**

# 🤖ArduiNodon🎮
An interactive HTML user interface and **Arduino** firmware designed for the 2021 Nintendo Switch game **Game Builder Garage** (a.k.a. **GBG** in English, a.k.a. **はじプロ** in Japan). This tool allows users to easily create, simulate, and share code schematics for GBG on any browser, and then automatically re-draw those schematics in the actual game using an Arduino. (No Switch or game modification required!)

🎥 **[Trailer](https://youtu.be/OXWpxESW4e8?si=QSbBM4nZ4uQ_vH3S)**

🚀 **[Launch the Live Web UI](https://your-username.github.io/gbg-arduinodon/)**

---

## ⚙️ How it Works

Within the *Programming Screen* of **Game Builder Garage**, USB mouse controls are natively supported.

The **Arduino** is a programmable microcontroller, and there are a few models that can pretend to be a USB mouse.

Through careful scripting and automation, we can reverse-engineer any Nodon with any setting into a long list of mouse movements and clicks. This project simply automates the entire process of converting a bunch of Nodons into a series of mouse commands that would result in the same configuration of Nodons within GBG.

Since this only sends a one-way string of mouse commands, it cannot react to anything unexpected that happens within the game like the user accidentally nudging the mouse, nor can it make anything the player cannot make themselves, such as modded objects.

---

## 📂 Repository Structure

* **`ArduiNodon-UI.html`** — The standalone web user interface (downloadable for offline use).
* **`ArduiNodon-Importer.ino`** — The script to paste your schematics into and then upload to your Arduino board to import into GBG.
* **`ArduiNodon-Documentation.md`** — The documentation for all the Arduino functions used across ArduiNodon.
* **`docs/index.html`** — The internal file used to host the live web application via GitHub Pages.

---

## 🛠️ Getting Started

**[If you are unfamiliar with GBG Arduino Tools in general, it is recommended to watch this video first about the GBG Arduino Texture Tools, which has a very similar process. (presented by VideoDojo, script made by Borri and Scrubz)](https://youtu.be/PTDiTS-Exjk?si=7BVb8NnknOZa9iBn)**

Follow these steps to import code from your browser into GBG itself!:

### 1. Build with ArduiNodon UI
1. Open the **[Live Web UI](https://zertolurian.github.io/gbg-arduinodon/)** or your local copy of `ArduiNodon-UI.html` in a compatible browser.
2. Build your code from scratch, or import `.ndnx` schematics from others.
3. *(Optional)* Simulate how your code will work in GBG from within the UI itself!
4. Export your code into a `.ndnx` file to easily share with others, or *Copy to Clipboard* to paste it later into the Arduino script for importing into GBG.

### 2. Hardware Preparation
1. Connect your Arduino board to your computer using a USB cable. **(This script only works for boards that natively support mouse emulation, such as the Arduino Leonardo with its ATmega32u4; Arduino UNO is *NOT* supported)**
2. *(Optional)* Connect a button that connects GND to *any* pin from 8-13.

### 3. Upload to the Arduino
1. Open the `ArduiNodon-Importer.ino` file inside the Arduino IDE.
2. Select your correct Board and Port from the IDE tools menu.
3. Ensure that **HID-Project** by NicoHood is installed in your libraries. Go to Tools -> Manage Libraries -> Search for "HID-Project" -> Install if you haven't yet.
4. *(Optional)* Change the settings within the Config at the top of the script based on your preferences, such as Delay, Overwrite Mode, and the position on the programming screen you want the code to execute in.
5. *(If you didn't connect a button)* Enable *No Button Mode* from within the Config.
6. Paste your code exported from ArduiNodon UI into the **NODON CODE SPACE** around line 200 (just scroll down; it's hard to miss!).
7. Click **Upload** to flash the code to your microcontroller. Ensure that the console says that the sketch has been uploaded successfully, and then unplug the Arduino from your computer.

### 3. Importing into GBG
1. Connect your Arduino to your Switch through the Dock's USB-A port (or directly to the Switch's USB-C port, if you have a USB-A to USB-C adapter; this is required if you are using a Switch Lite).
5. *(If you didn't connect a button)* Wait for 30 seconds (or whichever delay you put into the config), and then the script should start running automatically. Once it is finished, unplug the Arduino or else it will run the script again after another set delay.
6. *(If you connected a button)* Press the button, and the script should start running immediately. Once it is finished, you may re-press the button to run it again if it made any mistakes.
7. Wait for the script to finish, and make sure that none of the controls are disturbed during this process or else the script will make a mistake, and you would need to re-run the script again.
8. Voila! Your code is now in GBG!🎉

---

## 📜 License & Support

**AI Disclosure:** ArduiNodon UI was mostly built using AI.
This project is open-source and free to use, modify, and share within the Game Builder Garage community. If you run into issues or have ideas for new features, feel free to DM @zertolurian on Discord!

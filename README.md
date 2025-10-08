# 🧪 ESP32-P4 Hello World (JC4880P443C LCD)

This is a minimal **ESP-IDF** project for the **ESP32-P4** that initializes the **JC4880P443C LCD panel** and displays a simple "Hello World" screen using **LVGL**.


## 🚀 Build & Flash

```bash
# Set up ESP-IDF environment
. $HOME/esp/esp-idf/export.sh

# Configure the project
idf.py set-target esp32p4

# Build, flash, and monitor
idf.py build flash monitor
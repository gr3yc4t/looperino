# 🎹 Looperino 🎸
MIDI Looper based on Sooperlooper and Arduino.
## Requirements
#### Arduino
The following libraries are required
- [Bounce2](https://github.com/thomasfredericks/Bounce2)
- TapTempo
- [MIDI Library](https://github.com/FortySevenEffects/arduino_midi_library)
- [Jled](https://github.com/jandelgado/jled)

Each of them can be easily installed through the Library Manager present in Arduino IDE
#### Linux
- [SooperLooper](https://github.com/essej/sooperlooper)
- [ttymydi](https://launchpad.net/ttymidi) or [Hairless Midi Serial](https://projectgus.github.io/hairless-midiserial/)
## Installation
The code includes conditional compilation to include supports for Button inputs (`INPUTS`) Bluetooth remote control(`BLUETOOTH`) and a OLED display (`DISPLAY_OLED`)
## Usage
First of all, you have to figure out if you need ttymidi by checking if your board version supports "MIDI over USB" in this [page](https://github.com/tttapa/MIDI_controller/wiki/MIDI-over-USB).

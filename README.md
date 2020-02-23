# 🎹 Looperino 🎸
MIDI Looper based on Sooperlooper and Arduino.
## Features
- MIDI command can be associated either when an input button is pressed or holded
- Display showing looper info (Selected loop, Recording/Overdubbing status)
- Input tempo (looper bmp) by tapping on an input button
- Supports for effect knob
- Supports for bluetooth communication (e.g. flanger or volume control via mobile app)
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
The code includes conditional compilation to support for Button inputs (`INPUTS`), Bluetooth remote control(`BLUETOOTH`) and a OLED display (`DISPLAY_OLED`)
## Usage
First of all, you have to figure out if your board version supports "*MIDI over USB*" in this [page](https://github.com/tttapa/MIDI_controller/wiki/MIDI-over-USB). Otherwise, you have to launch *ttymidi* in order to convert your Arduino serial comminication into a MIDI data.

After that, you have to configure *Sooperlooper* in order to associate MIDI commands to actions (a sample configuration can be found [here](https://github.com/gr3yc4t/looperino/blob/master/sooperlooper_config/loop_station_mapping.slb))


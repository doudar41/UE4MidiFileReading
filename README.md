# UE4MidiFileReading
This is c++ class that makes Blueprints in UE4 allowing to read essential midi info ticks, notes durations and pitches

Thanks to https://github.com/OneLoneCoder who wrote this piece of code
https://github.com/OneLoneCoder/olcPixelGameEngine/blob/master/Videos/OneLoneCoder_PGE_MIDI.cpp
I wrote small class to create blueprint inside UE4 to read essential midi data. Note properties delta time, NoteOn NoteOff, pitch. 

1. Make UE4 C++ project
2. Download files https://github.com/doudar41/UE4MidiFileReading
3. Create a c++ Actor class with the same name as files from repository (Midireading)
4. Open it in IDE of your choice
5. Open and copy all code from downloaded Midireading.h and paste it into newly created one.
6. Change name of project in string 33
7. Open and copy all code from downloaded Midireading.cpp and paste it into newly created one.
8. Return to UE and press compile

9. Now you can open any public function from this class in any blueprint


Depend on your needs you might need different functions

BytesToHexFixed, BytesToBinaryStringFixed and BytesToCharFixed - These are utilities to convert byte to strings

Hex represents different parts of midi file and info that it contains. Sorry for sending you to midi documentation https://people.carleton.edu/~jellinge/m208w14/pdf/02MIDIBasics_doc.pdf but it is really necessary to understand what different hex lines are doing if you are going to use it. 

LoadMidiFileToArray – do exactly what it called to convert them later

AddingBytes – read three bytes after hex number 51 to read tempo in microseconds

MidiReadStruct – generate struct FtempoBytesArray that returns arrays of notes data from midi file. Notes On/Off commands, time between them and pitch.

#ifndef EFFECTS_H
#define EFFECTS_H

#define Effect const uint8_t PROGMEM

Effect crash[] = {
0x06,      // Number of tracks
0x00, 0x00,   // Address of track 0
0x01, 0x00,   // Address of track 1
0x02, 0x00,   // Address of track 2
0x07, 0x00,   // Address of track 3
0x0a, 0x00,   // Address of track 4
0x11, 0x00,   // Address of track 5
0x00,     // Channel 0 entry track
0x01,     // Channel 1 entry track
0x02,     // Channel 2 entry track
0x03,     // Channel 3 entry track
//"Track channel 0"
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 1"
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 2"
0x40, 20,   // FX: SET VOLUME: volume = 20
0x9D, 24,   // FX: SET TEMPO: tempo = 24
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 3"
0xFC, 5,    // GOTO track 5
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track short crash"
0x40, 32,   // FX: SET VOLUME: volume = 32
0x41, -4,   // FX: VOLUME SLIDE ON: steps = -4
0x9F + 8,   // DELAY: ticks = 8
0x43,     // FX: VOLUME SLIDE OFF
0xFE,     // RETURN
//"Track Track 1"
0xFC, 4,    // GOTO track 4
0xFE,     // RETURN

};



#endif

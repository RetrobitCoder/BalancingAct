#ifndef SONGS_H
#define SONGS_H

#define Song const uint8_t PROGMEM

Song opening_tune[] = {
0x05,      // Number of tracks
0x00, 0x00,   // Address of track 0
0x01, 0x00,   // Address of track 1
0x02, 0x00,   // Address of track 2
0x09, 0x00,   // Address of track 3
0x0a, 0x00,   // Address of track 4
0x00,     // Channel 0 entry track
0x01,     // Channel 1 entry track
0x02,     // Channel 2 entry track
0x03,     // Channel 3 entry track
//"Track channel 0"
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 1"
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 2"
0x40, 48,   // FX: SET VOLUME: volume = 48
0x9D, 24,   // FX: SET TEMPO: tempo = 24
0xFC, 4,    // GOTO track 4
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 3"
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track Openingtune"
0x00 + 47,    // NOTE ON: note = 47
0x9F + 8,   // DELAY: ticks = 8
0x00 + 55,    // NOTE ON: note = 55
0x9F + 8,   // DELAY: ticks = 8
0x00 + 51,    // NOTE ON: note = 51
0x9F + 4,   // DELAY: ticks = 4
0x00 + 49,    // NOTE ON: note = 49
0x9F + 8,   // DELAY: ticks = 8
0x00 + 46,    // NOTE ON: note = 46
0x9F + 4,   // DELAY: ticks = 4
0x00 + 50,    // NOTE ON: note = 50
0x9F + 4,   // DELAY: ticks = 4
0x00 + 51,    // NOTE ON: note = 51
0x9F + 3,   // DELAY: ticks = 3
0x00 + 46,    // NOTE ON: note = 46
0x9F + 2,   // DELAY: ticks = 2
0x00 + 48,    // NOTE ON: note = 48
0x9F + 3,   // DELAY: ticks = 3
0x00 + 51,    // NOTE ON: note = 51
0x9F + 4,   // DELAY: ticks = 4
0x00 + 56,    // NOTE ON: note = 56
0x9F + 4,   // DELAY: ticks = 4
0x00 + 52,    // NOTE ON: note = 52
0x9F + 4,   // DELAY: ticks = 4
0x00 + 53,    // NOTE ON: note = 53
0x9F + 4,   // DELAY: ticks = 4
0x00 + 49,    // NOTE ON: note = 49
0x9F + 4,   // DELAY: ticks = 4
0xFE,     // RETURN

};

Song win_tune[] = {
0x05,      // Number of tracks
0x00, 0x00,   // Address of track 0
0x01, 0x00,   // Address of track 1
0x04, 0x00,   // Address of track 2
0x0b, 0x00,   // Address of track 3
0x0c, 0x00,   // Address of track 4
0x00,     // Channel 0 entry track
0x01,     // Channel 1 entry track
0x02,     // Channel 2 entry track
0x03,     // Channel 3 entry track
//"Track channel 0"
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 1"
0x40, 48,   // FX: SET VOLUME: volume = 48
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 2"
0x40, 20,   // FX: SET VOLUME: volume = 20
0x9D, 24,   // FX: SET TEMPO: tempo = 24
0xFC, 4,    // GOTO track 4
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 3"
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track Win"
0x00 + 48,    // NOTE ON: note = 48
0x9F + 4,   // DELAY: ticks = 4
0x00 + 53,    // NOTE ON: note = 53
0x9F + 4,   // DELAY: ticks = 4
0xFE,     // RETURN

};

Song lose_tune[] = {
0x05,      // Number of tracks
0x00, 0x00,   // Address of track 0
0x01, 0x00,   // Address of track 1
0x06, 0x00,   // Address of track 2
0x0b, 0x00,   // Address of track 3
0x0c, 0x00,   // Address of track 4
0x00,     // Channel 0 entry track
0x01,     // Channel 1 entry track
0x02,     // Channel 2 entry track
0x03,     // Channel 3 entry track
//"Track channel 0"
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 1"
0x40, 48,   // FX: SET VOLUME: volume = 48
0xFC, 4,    // GOTO track 4
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 2"
0x40, 20,   // FX: SET VOLUME: volume = 20
0x9D, 24,   // FX: SET TEMPO: tempo = 24
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 3"
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track Lose"
0x00 + 17,    // NOTE ON: note = 17
0x9F + 4,   // DELAY: ticks = 4
0x00 + 10,    // NOTE ON: note = 10
0x9F + 4,   // DELAY: ticks = 4
0xFE,     // RETURN

};
#endif

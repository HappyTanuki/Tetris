#ifndef _MIDI_H
#define _MIDI_H

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#pragma pack(push,1)

typedef struct {
    BYTE byteState;
    BYTE byteNote;
    BYTE byteVelocity;
    BYTE byteNULL;
}MJGRShortMidiMSG_ST;

typedef union {
    DWORD                dwMidi_Data;
    MJGRShortMidiMSG_ST  stMidi_Data;
}MJGRShortMidiMSG;

#pragma pack(pop)

HMIDIOUT     m_DevHandle;
MMRESULT     m_MMErrCode;
MIDIOUTCAPS  m_NowMidiOutCaps;

#endif
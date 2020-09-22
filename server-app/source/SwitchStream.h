#pragma once

#include <iostream>
#include <winsock2.h>
#include <string>
#include <thread>
#include <atomic>

enum STREAM_MODE
{
    LOW_LATENCY_30_FPS = 0,
    OK_LATENCY_60_FPS,
    LOW_LATENCY_V_FPS,
    STREAM_MODE_COUNT
};

struct alignas(16) FFMPEG_Config 
{
    int16_t     desiredFrameRate;
    int16_t     videoX;
    int16_t     videoY;
    int16_t     scaleX;
    int16_t     scaleY;
    uint16_t    bitrateKB;
    int8_t      vsyncMode;
    int8_t      padding[3];
};

enum Command : int16_t
{
    SHUTDOWN = 0xEEE,
    UPDATE_FFMPEG_CONFIG = 0xADD,
    START_STREAM = 0xCAD,
    START_STREAM_LOW_LATENCY_30FPS = 0x030,
    START_STREAM_LOW_LATENCY_VFPS = 0xA60,
    START_STREAM_OK_LATENCY_60FPS = 0x060,
    STOP_STREAM = 0xBAB,
    CLOSE_SERVER = 0xAAA,
    SHUTDOWN_PC = 0x0FF,
    IGNORE_COMMAND = 0xFFF
};

struct alignas(32) CommandPayload
{
    //for now only add ffmpeg-config as an extra data member
    FFMPEG_Config   configData;
    Command         commandCode;
    //fill the struct to pad it out to 32 bytes
    int8_t          padding[32-sizeof(FFMPEG_Config)-sizeof(Command)];

    // int16_t dataBufferSize;
    // char dataBuffer[255];
};

const int COMMAND_PAYLOAD_SIZE = sizeof(CommandPayload);
const int COMMAND_CODE_SIZE = sizeof(Command);
const int FFMPEG_CONFIG_SIZE = sizeof(FFMPEG_Config);

extern FFMPEG_Config receivedConfig;

const FFMPEG_Config DEFAULT_CONFIGS[] = {
    {60, 1920, 1080, 1280, 720, 5000, 2}, //good performance, gets clamped to 30fps (low latency)
    {60, 1920, 1080, 1280, 720, 5000, 1}, //good performance, tries to stay at 60fps (OK latency)
    {60, 1920, 1080, 1280, 720, 5000, 1} //can be very good, almost similar to mode 1 (low latency)
};

void ListenForStreamStart();

void ReadCommandsFromSwitch(SOCKET& switchSocket);

bool ListenForConnection(const SOCKET listenSock, SOCKET& connectedSocket, sockaddr_in& connectionInfo);

bool CreateListenerSocket(SOCKET& sock, uint16_t portNo);

PROCESS_INFORMATION StartStream(FFMPEG_Config config, bool& started);

std::string CreateCommandLineArg(FFMPEG_Config config);

std::string ConfigToString(FFMPEG_Config config);

#ifndef VoiceDet_H_
#define VoiceDet_H_
#ifdef _WIN64
#pragma comment(lib,"lib/msc_x64.lib") //x64
#else
#pragma comment(lib,"lib/msc.lib") //x86
#endif
/*
* 语音听写(iFly Auto Transform)技术能够实时地将语音转换成对应的文字。
*/

#include<string>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <errno.h>
#include<iostream>
#include "qisr.h"
#include "msp_cmn.h"
#include "msp_errors.h"
#include<tchar.h>
#include <mmsystem.h>


#pragma comment(lib, "winmm.lib")
#define WIN32_LEAN_AND_MEAN	  
#define __T(x) L ## x
#define _T(x) __T(x)





using namespace std;

#define	BUFFER_SIZE	4096
#define FRAME_LEN	640 
#define HINTS_SIZE  100

class VoiceDet
{
public :
	VoiceDet();
	DWORD FCC(LPSTR lpStr);
	bool getVoiceStr(std::string& retd);
	bool startEveryting(std::string& retd);
	void cleanBuffer();
	bool run_iat(const char* audio_file, const char* session_begin_params);
	char rec_result[BUFFER_SIZE] = {NULL};
	char *IpTemp;

	//char rec_result[BUFFER_SIZE] = { NULL };
	//char lpTemp[256] = "";
};

#endif
#include"iat_sample.h"

VoiceDet::VoiceDet()
{
	IpTemp = new char[256];
	IpTemp = "";
}

DWORD VoiceDet::FCC(LPSTR lpStr)
{
	DWORD Number = lpStr[0] + lpStr[1] * 0x100 + lpStr[2] * 0x10000 + lpStr[3] * 0x1000000;
	return Number;
}
bool VoiceDet::getVoiceStr(std::string& retd)
{
	return startEveryting(retd);
}
bool VoiceDet::startEveryting(std::string& retd)
{
	bool        pa;
	
	int			ret = MSP_SUCCESS;
	char		result[BUFFER_SIZE] = { NULL };
	char* login_params = new char[40];
	login_params = "appid = 5735c7a1, work_dir = .\0";  // 登录参数，appid与msc库绑定,请勿随意改动

													  /*
													  * sub:				请求业务类型
													  * domain:			领域
													  * language:			语言
													  * accent:			方言
													  * sample_rate:		音频采样率
													  * result_type:		识别结果格式
													  * result_encoding:	结果编码格式
													  *
													  * 详细参数说明请参阅《iFlytek MSC Reference Manual》
													  */
	
	const char* session_begin_params = "sub = iat, domain = iat, language = zh_ch, accent = mandarin, sample_rate = 16000, result_type = plain, result_encoding = gb2312";
	
	/* 用户登录 */
	
	ret =MSPLogin(nullptr, nullptr, login_params); //第一个参数是用户名，第二个参数是密码，均传NULL即可，第三个参数是登录参数	
	if (MSP_SUCCESS != ret)
	{
		goto exit; //登录失败，退出登录
		return false;
	}
	
	CreateMutex(NULL, false, _T("MyMutex"));

	DWORD datasize = 224000;//语音长度
	WAVEFORMATEX waveformat;
	waveformat.wFormatTag = WAVE_FORMAT_PCM;
	waveformat.nChannels = 1;
	waveformat.nSamplesPerSec = 16000;
	waveformat.nAvgBytesPerSec = 32000;
	waveformat.nBlockAlign = 2;// 最小块单元，wBitsPerSample×nChannels/8
	waveformat.wBitsPerSample = 16; //指定录音格式
	waveformat.cbSize = 0;

	//printf(lpTemp, "WAVEFORMATEX size = %lu", sizeof(WAVEFORMATEX));



	HWAVEIN  m_hWaveIn;

	if (!waveInGetNumDevs())
		return false;

	int res = waveInOpen(&m_hWaveIn, WAVE_MAPPER, &waveformat, (DWORD)NULL, 0L, CALLBACK_WINDOW); //打开录音设备

	if (res != MMSYSERR_NOERROR)
		return false;


	WAVEHDR m_pWaveHdr;

	m_pWaveHdr.lpData = (char *)GlobalLock(GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, datasize));
	memset(m_pWaveHdr.lpData, 0, datasize);
	m_pWaveHdr.dwBufferLength = datasize;
	m_pWaveHdr.dwBytesRecorded = 0;
	m_pWaveHdr.dwUser = 0;
	m_pWaveHdr.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	m_pWaveHdr.dwLoops = 1;
	m_pWaveHdr.lpNext = NULL;
	m_pWaveHdr.reserved = 0;

	int resPrepare = waveInPrepareHeader(m_hWaveIn, &m_pWaveHdr, sizeof(WAVEHDR)); //准备内存块录音

	if (resPrepare != MMSYSERR_NOERROR)
		return false;

	resPrepare = waveInAddBuffer(m_hWaveIn, &m_pWaveHdr, sizeof(WAVEHDR));

	if (resPrepare != MMSYSERR_NOERROR)
		return false;


	if (waveInStart(m_hWaveIn))
		return false;

	Sleep(5000);


	MMTIME mmt;
	mmt.wType = TIME_BYTES;

	if (waveInGetPosition(m_hWaveIn, &mmt, sizeof(MMTIME)))
		return false;

	waveInReset(m_hWaveIn);
	m_pWaveHdr.dwBytesRecorded = mmt.u.cb;



	DWORD NumToWrite = 0;  DWORD dwNumber = 0;
	HANDLE FileHandle = CreateFile(_T("myTest.wav"), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//  memset(m_pWaveHdr.lpData, 0, datasize);

	dwNumber = FCC("RIFF");
	WriteFile(FileHandle, &dwNumber, 4, &NumToWrite, NULL);

	dwNumber = m_pWaveHdr.dwBytesRecorded + 18 + 20;
	WriteFile(FileHandle, &dwNumber, 4, &NumToWrite, NULL);

	dwNumber = FCC("WAVE");
	WriteFile(FileHandle, &dwNumber, 4, &NumToWrite, NULL);

	dwNumber = FCC("fmt ");
	WriteFile(FileHandle, &dwNumber, 4, &NumToWrite, NULL);

	dwNumber = 18L;
	WriteFile(FileHandle, &dwNumber, 4, &NumToWrite, NULL);

	WriteFile(FileHandle, &waveformat, sizeof(WAVEFORMATEX), &NumToWrite, NULL);

	dwNumber = FCC("data");
	WriteFile(FileHandle, &dwNumber, 4, &NumToWrite, NULL);

	dwNumber = m_pWaveHdr.dwBytesRecorded;
	WriteFile(FileHandle, &dwNumber, 4, &NumToWrite, NULL);

	WriteFile(FileHandle, m_pWaveHdr.lpData, m_pWaveHdr.dwBytesRecorded, &NumToWrite, NULL);

	SetEndOfFile(FileHandle);
	CloseHandle(FileHandle);    FileHandle = INVALID_HANDLE_VALUE;
	if (waveInUnprepareHeader(m_hWaveIn, &m_pWaveHdr, sizeof(WAVEHDR)))
		return false;
	if (GlobalFree(GlobalHandle(m_pWaveHdr.lpData)))
		return false;

	if (res == MMSYSERR_NOERROR)  //关闭录音设备
		waveInClose(m_hWaveIn) == MMSYSERR_NOERROR;
	pa = run_iat("myTest.wav", session_begin_params);
	if (!pa) return false;
	retd = rec_result;
	MSPLogout(); //退出登录
	return true;
exit:
	_getch();
	MSPLogout(); //退出登录
}
bool VoiceDet::run_iat(const char* audio_file, const char* session_begin_params)
{
	const char*		session_id = NULL;
	char			hints[HINTS_SIZE] = { NULL }; //hints为结束本次会话的原因描述，由用户自定义
	unsigned int	total_len = 0;
	int				aud_stat = MSP_AUDIO_SAMPLE_CONTINUE;		//音频状态
	int				ep_stat = MSP_EP_LOOKING_FOR_SPEECH;		//端点检测
	int				rec_stat = MSP_REC_STATUS_SUCCESS;			//识别状态
	int				errcode = MSP_SUCCESS;

	FILE*			f_pcm = NULL;
	char*			p_pcm = NULL;
	long			pcm_count = 0;
	long			pcm_size = 0;
	long			read_size = 0;


	if (NULL == audio_file)
		goto iat_exit;

	f_pcm = fopen(audio_file, "rb");
	if (NULL == f_pcm)
	{
		goto iat_exit;
		return false;
	}

	fseek(f_pcm, 0, SEEK_END);
	pcm_size = ftell(f_pcm); //获取音频文件大小 
	fseek(f_pcm, 0, SEEK_SET);

	p_pcm = (char *)malloc(pcm_size);
	if (NULL == p_pcm)
	{
		goto iat_exit;
		return false;
	}

	read_size = fread((void *)p_pcm, 1, pcm_size, f_pcm); //读取音频文件内容
	if (read_size != pcm_size)
	{
		goto iat_exit;
		return false;
	}
	session_id = QISRSessionBegin(NULL, session_begin_params, &errcode); //听写不需要语法，第一个参数为NULL
	if (MSP_SUCCESS != errcode)
	{
		goto iat_exit;
		return false;
	}

	while (1)
	{
		unsigned int len = 10 * FRAME_LEN; // 每次写入200ms音频(16k，16bit)：1帧音频20ms，10帧=200ms。16k采样率的16位音频，一帧的大小为640Byte
		int ret = 0;

		if (pcm_size < 2 * len)
			len = pcm_size;
		if (len <= 0)
			break;

		aud_stat = MSP_AUDIO_SAMPLE_CONTINUE;
		if (0 == pcm_count)
			aud_stat = MSP_AUDIO_SAMPLE_FIRST;
		ret = QISRAudioWrite(session_id, (const void *)&p_pcm[pcm_count], len, aud_stat, &ep_stat, &rec_stat);
		if (MSP_SUCCESS != ret)
		{
			goto iat_exit;
			return false;
		}

		pcm_count += (long)len;
		pcm_size -= (long)len;

		if (MSP_REC_STATUS_SUCCESS == rec_stat) //已经有部分听写结果
		{
			const char *rslt = QISRGetResult(session_id, &rec_stat, 0, &errcode);
			if (MSP_SUCCESS != errcode)
			{

				goto iat_exit;
				return false;
			}
			if (NULL != rslt)
			{
				unsigned int rslt_len = strlen(rslt);
				total_len += rslt_len;
				if (total_len >= BUFFER_SIZE)
				{
					goto iat_exit;
					return false;
				}
				strncat(rec_result, rslt, rslt_len);
			}
		}

		if (MSP_EP_AFTER_SPEECH == ep_stat)
			break;
		Sleep(200); //模拟人说话时间间隙。200ms对应10帧的音频
	}
	errcode = QISRAudioWrite(session_id, NULL, 0, MSP_AUDIO_SAMPLE_LAST, &ep_stat, &rec_stat);
	if (MSP_SUCCESS != errcode)
	{
		goto iat_exit;
		return false;
	}

	while (MSP_REC_STATUS_COMPLETE != rec_stat)
	{
		const char *rslt = QISRGetResult(session_id, &rec_stat, 0, &errcode);
		if (MSP_SUCCESS != errcode)
		{
			goto iat_exit;
			return false;
		}
		if (NULL != rslt)
		{
			unsigned int rslt_len = strlen(rslt);
			total_len += rslt_len;
			if (total_len >= BUFFER_SIZE)
			{
				goto iat_exit;
			}
			strncat(rec_result, rslt, rslt_len);
		}
		Sleep(150); //防止频繁占用CPU
	}
	QISRSessionEnd(session_id, hints);
	return true;
iat_exit:
	if (NULL != f_pcm)
	{
		fclose(f_pcm);
		f_pcm = NULL;
	}
	if (NULL != p_pcm)
	{
		free(p_pcm);
		p_pcm = NULL;
	}

	QISRSessionEnd(session_id, hints);
}
void  VoiceDet::cleanBuffer()
{
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		rec_result[i] = NULL;
	}

}
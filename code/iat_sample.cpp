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
	login_params = "appid = 5735c7a1, work_dir = .\0";  // ��¼������appid��msc���,��������Ķ�

													  /*
													  * sub:				����ҵ������
													  * domain:			����
													  * language:			����
													  * accent:			����
													  * sample_rate:		��Ƶ������
													  * result_type:		ʶ������ʽ
													  * result_encoding:	��������ʽ
													  *
													  * ��ϸ����˵������ġ�iFlytek MSC Reference Manual��
													  */
	
	const char* session_begin_params = "sub = iat, domain = iat, language = zh_ch, accent = mandarin, sample_rate = 16000, result_type = plain, result_encoding = gb2312";
	
	/* �û���¼ */
	
	ret =MSPLogin(nullptr, nullptr, login_params); //��һ���������û������ڶ������������룬����NULL���ɣ������������ǵ�¼����	
	if (MSP_SUCCESS != ret)
	{
		goto exit; //��¼ʧ�ܣ��˳���¼
		return false;
	}
	
	CreateMutex(NULL, false, _T("MyMutex"));

	DWORD datasize = 224000;//��������
	WAVEFORMATEX waveformat;
	waveformat.wFormatTag = WAVE_FORMAT_PCM;
	waveformat.nChannels = 1;
	waveformat.nSamplesPerSec = 16000;
	waveformat.nAvgBytesPerSec = 32000;
	waveformat.nBlockAlign = 2;// ��С�鵥Ԫ��wBitsPerSample��nChannels/8
	waveformat.wBitsPerSample = 16; //ָ��¼����ʽ
	waveformat.cbSize = 0;

	//printf(lpTemp, "WAVEFORMATEX size = %lu", sizeof(WAVEFORMATEX));



	HWAVEIN  m_hWaveIn;

	if (!waveInGetNumDevs())
		return false;

	int res = waveInOpen(&m_hWaveIn, WAVE_MAPPER, &waveformat, (DWORD)NULL, 0L, CALLBACK_WINDOW); //��¼���豸

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

	int resPrepare = waveInPrepareHeader(m_hWaveIn, &m_pWaveHdr, sizeof(WAVEHDR)); //׼���ڴ��¼��

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

	if (res == MMSYSERR_NOERROR)  //�ر�¼���豸
		waveInClose(m_hWaveIn) == MMSYSERR_NOERROR;
	pa = run_iat("myTest.wav", session_begin_params);
	if (!pa) return false;
	retd = rec_result;
	MSPLogout(); //�˳���¼
	return true;
exit:
	_getch();
	MSPLogout(); //�˳���¼
}
bool VoiceDet::run_iat(const char* audio_file, const char* session_begin_params)
{
	const char*		session_id = NULL;
	char			hints[HINTS_SIZE] = { NULL }; //hintsΪ�������λỰ��ԭ�����������û��Զ���
	unsigned int	total_len = 0;
	int				aud_stat = MSP_AUDIO_SAMPLE_CONTINUE;		//��Ƶ״̬
	int				ep_stat = MSP_EP_LOOKING_FOR_SPEECH;		//�˵���
	int				rec_stat = MSP_REC_STATUS_SUCCESS;			//ʶ��״̬
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
	pcm_size = ftell(f_pcm); //��ȡ��Ƶ�ļ���С 
	fseek(f_pcm, 0, SEEK_SET);

	p_pcm = (char *)malloc(pcm_size);
	if (NULL == p_pcm)
	{
		goto iat_exit;
		return false;
	}

	read_size = fread((void *)p_pcm, 1, pcm_size, f_pcm); //��ȡ��Ƶ�ļ�����
	if (read_size != pcm_size)
	{
		goto iat_exit;
		return false;
	}
	session_id = QISRSessionBegin(NULL, session_begin_params, &errcode); //��д����Ҫ�﷨����һ������ΪNULL
	if (MSP_SUCCESS != errcode)
	{
		goto iat_exit;
		return false;
	}

	while (1)
	{
		unsigned int len = 10 * FRAME_LEN; // ÿ��д��200ms��Ƶ(16k��16bit)��1֡��Ƶ20ms��10֡=200ms��16k�����ʵ�16λ��Ƶ��һ֡�Ĵ�СΪ640Byte
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

		if (MSP_REC_STATUS_SUCCESS == rec_stat) //�Ѿ��в�����д���
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
		Sleep(200); //ģ����˵��ʱ���϶��200ms��Ӧ10֡����Ƶ
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
		Sleep(150); //��ֹƵ��ռ��CPU
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
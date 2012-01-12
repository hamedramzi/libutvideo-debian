/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id: Thread.h 789 2011-10-25 14:08:55Z umezawa $ */

#pragma once

class CThreadManager;

class CThreadJob
{
	friend class CThreadManager;

private:
#ifdef _WIN32
	HANDLE m_hCompletionEvent;
#endif

public:
	CThreadJob(void);
	virtual ~CThreadJob(void) = 0;

public:
	virtual void JobProc(CThreadManager *pManager) = 0;
};

class CThreadManager
{
private:
	static const int MAX_THREAD = 32;
	static const int MAX_JOB = 256;

private:
	int m_nNumThreads;
	int m_nNumJobs;
#ifdef _WIN32
	queue<CThreadJob *> m_queueJob[MAX_THREAD];
	HANDLE m_hThread[MAX_THREAD];
	DWORD m_dwThreadId[MAX_THREAD];
	HANDLE m_hThreadSemaphore[MAX_THREAD];
	CRITICAL_SECTION m_csJob;
	HANDLE m_hCompletionEvent[MAX_JOB];
#endif
#if defined(__APPLE__) || defined(__unix__)
	queue<CThreadJob *> m_queueJob;
	pthread_t m_ptidThread[MAX_THREAD];
	pthread_mutex_t m_ptmJobMutex;
	pthread_cond_t m_ptcJobCond;
	int m_nNumCompleteJobs;
#endif

public:
	static int GetNumProcessors(void);

public:
	CThreadManager(void);
	~CThreadManager(void);
	void SubmitJob(CThreadJob *pJob, uint32_t dwAffinityHint);
	void WaitForJobCompletion(void);

private:
#ifdef _WIN32
	static DWORD WINAPI StaticThreadProc(LPVOID lpParameter);
	DWORD ThreadProc(int nThreadIndex);
#endif
#if defined(__APPLE__) || defined(__unix__)
	static void *StaticThreadProc(void *);
	void *ThreadProc(int nThreadIndex);
#endif
};

#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <ctime>
#include <algorithm>

#define THREAD_FAILED			-99

struct SMART_THREAD
{
	char* tName;
	time_t tTime;
	HANDLE tHandle;
	bool isSuspended;
};
typedef std::vector<SMART_THREAD*> SThreadVector;

class SThread
{

private:

	bool ThreadExists(char* thread_name);
	void AddToActiveThreads(SMART_THREAD);
	void RemoveFromActiveThreads(SMART_THREAD);
	SMART_THREAD* GetThread(char* thread_name);
	SMART_THREAD* GetThread(HANDLE thread_handle);

public:
	SThreadVector ActiveThreads;
	BOOL StartThread(char* thread_name, LPTHREAD_START_ROUTINE start_function);
	int TerminateRunningThread(char* thread_name);
	int PauseThread(char* thread_name);
	int ResumeSuspendedThread(char* thread_name);
	int ActiveThreadCount();
	double GetThreadDuration(char* thread_name);
	double GetThreadDuration(HANDLE thread_handle);

};


BOOL SThread::StartThread(char* thread_name, LPTHREAD_START_ROUTINE start_function)
{
	if (ThreadExists(thread_name)) return THREAD_FAILED;
	SMART_THREAD smart_thread;
	HANDLE thread_handle = CreateThread(0, 0, start_function, 0, 0, 0);
	if (thread_handle == INVALID_HANDLE_VALUE) return THREAD_FAILED;
	smart_thread.tName = thread_name;
	smart_thread.tTime = clock();
	smart_thread.tHandle = thread_handle;
	smart_thread.isSuspended = false;
	AddToActiveThreads(smart_thread);
}

bool SThread::ThreadExists(char* thread_name)
{
	bool exists = false;
	
	for each (SMART_THREAD* smart_thread in ActiveThreads)
	{
		if (strcmp(smart_thread->tName, thread_name) == 0)
		{
			exists = true;
			break;
		}
	}

	return exists;
}

int SThread::ActiveThreadCount()
{
	return ActiveThreads.size();
}

void SThread::AddToActiveThreads(SMART_THREAD smart_thread)
{
	SMART_THREAD* pSmartThread = &smart_thread;
	ActiveThreads.push_back(pSmartThread);
}

int SThread::TerminateRunningThread(char* thread_name)
{
	SMART_THREAD* w_thread = GetThread(thread_name); 
	if (w_thread == NULL) return NULL;
	DWORD dwExit;
	GetExitCodeThread(w_thread->tHandle, &dwExit);
	TerminateThread(w_thread->tHandle, dwExit);
	return 1;
}

int SThread::PauseThread(char* thread_name)
{
	SMART_THREAD* w_thread = GetThread(thread_name);
	if (w_thread == NULL) return NULL;
	if (!w_thread->isSuspended) SuspendThread(w_thread->tHandle);
	w_thread->isSuspended = true;
	return 1;
}

int SThread::ResumeSuspendedThread(char* thread_name)
{
	SMART_THREAD* w_thread = GetThread(thread_name);
	if (w_thread == NULL) return NULL;
	if (w_thread->isSuspended) ResumeThread(w_thread->tHandle);
	w_thread->isSuspended = false;
	return 1;
}


SMART_THREAD* SThread::GetThread(char* thread_name)
{
	for each (SMART_THREAD* s_thread in ActiveThreads)
	{
		if (strcmp(s_thread->tName, thread_name) == 0)
		{
			return s_thread;
		}
	}
}

SMART_THREAD* SThread::GetThread(HANDLE thread_handle)
{
	for each (SMART_THREAD* s_thread in ActiveThreads)
	{
		if (s_thread->tHandle == thread_handle)
		{
			return s_thread;
		}
	}
}


double SThread::GetThreadDuration(char* thread_name)
{
	SMART_THREAD* s_thread = GetThread(thread_name);
	if (s_thread == NULL) return 0;
	return (std::clock() - s_thread->tTime / CLOCKS_PER_SEC);
}

double SThread::GetThreadDuration(HANDLE thread_handle)
{
	SMART_THREAD* s_thread = GetThread(thread_handle);
	if (s_thread == NULL) return 0;
	return (std::clock() - s_thread->tTime / CLOCKS_PER_SEC);
}
#pragma once
class CTimer
{
public:
	CTimer();

	float TotalTIme() const;
	float DeltaTime() const;

	void Reset();	// call before message loop
	void Start();	// call when unpaused.
	void Stop();	// call when paused
	void Tick();	// call every frame

	__int64 GetCurTime();
	__int64 GetPrevTime();
private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};


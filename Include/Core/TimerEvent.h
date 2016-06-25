/***********************************************************************
*FileName	:  TimerEvent
*Author		:  fz
*Date		:  2016.1.17
*Description:  ��ʱ���¼�
************************************************************************/
#pragma once
#include <event2/event.h>
#include <event2/event_struct.h>
#include <memory>

class TimerEvent
{
public:
	TimerEvent(event_base* evBase, int milliSecs, bool repeated);
	virtual~TimerEvent();
	virtual void OnTimer() = 0;

	event m_event;
	timeval m_timeval;
// private:
// 	friend bool AddTimer(TimerEvent* te);
// 	friend void RemoveTimer(TimerEvent* te);
// 	friend bool ResetTimer(TimerEvent* te, int milliSecs);
};

//����ʹ������ģ��,Ҳ����ֱ�Ӽ̳�TimerEvent,��дOnTimer����
bool AddTimer(TimerEvent* te);
void RemoveTimer(TimerEvent* te);
bool ResetTimer(TimerEvent* te, int milliSecs = 0);
//std::shared_ptr�汾
bool AddTimer(std::shared_ptr<TimerEvent> te);
void RemoveTimer(std::shared_ptr<TimerEvent> te);
bool ResetTimer(std::shared_ptr<TimerEvent> te, int milliSecs = 0);

//C:�� Fn:��ĺ��� R:������������
template<class C, class R>
class Timer : public TimerEvent
{
	typedef R(C::*Fn)();
	C* m_class;
	Fn m_fn;
public:
	Timer(C* pClass, Fn fn, event_base* evBase, int milliSecs, bool repeated = false) :
		TimerEvent(evBase, milliSecs, repeated), m_class(pClass), m_fn(fn){}
	virtual void OnTimer(){ (m_class->*m_fn)(); }
};

//C:�� Fn:��ĺ��� R:������������ P1:��������1
template<class C, class R, class P1>
class Timer1 : public TimerEvent
{
	typedef R(C::*Fn)(P1 p1);
	C* m_class;
	Fn m_fn;
	P1 m_p1;
public:
	Timer1(C* pClass, Fn fn, P1 p1, event_base* evBase, int milliSecs, bool repeated = false) :
		TimerEvent(evBase, milliSecs, repeated), m_class(pClass), m_fn(fn), m_p1(p1){}
	virtual void OnTimer(){ (m_class->*m_fn)(m_p1); }
};

//C:�� Fn:��ĺ��� R:������������ P1:��������1 P2:��������2
template<class C, class R, class P1, class P2>
class Timer2 : public TimerEvent
{
	typedef R(C::*Fn)(P1 p1, P2 p2);
	C* m_class;
	Fn m_fn;
	P1 m_p1;
	P2 m_p2;
public:
	Timer2(C* pClass, Fn fn, P1 p1, P2 p2, event_base* evBase, int milliSecs, bool repeated = false) :
		TimerEvent(evBase, milliSecs, repeated), m_class(pClass), m_fn(fn), m_p1(p1), m_p2(p2){}
	virtual void OnTimer(){ (m_class->*m_fn)(m_p1, m_p2); }
};

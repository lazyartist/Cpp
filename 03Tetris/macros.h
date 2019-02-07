#pragma once

#define DeclareSingleton(T)\
private:\
	static T* m_Inst;\
/*빈줄에서 \해주지 않으면 매크로 블록으로 인식하지 못한다.*/\
\
public:\
	static T* GetInst() {\
		if(m_Inst == NULL){\
			m_Inst = new T;\
		}\
		return m_Inst;\
	}\
\
	static void DestroyInst(){\
		if(m_Inst){\
			delete m_Inst;\
			m_Inst = NULL;\
		}\
	}

#define DefinitionSingleton(T) \
T* T::m_Inst = NULL;

#define SafeDelete(p) if(p) delete p; p = NULL;
/***********************************************************************
*FileName	:  PoolObject
*Author		:  fz
*Date		:  2016.4.9
*Description:  ����� 
	
	�ɶ�����󼯹���,��ʼ��Ϊһ������,ÿ������,����ͬ�Ĵ�С�Ķ����Ա
	
	ʹ��ʱע����Ҫ�ֶ�����������
************************************************************************/
#pragma once

template<class T>
class ObjectPool
{
private:
	/*��Ա����*/
	struct Object
	{
		T			obj;            //��Ա  
		Object*		next;			//���µ�ָ��
		Object*		pre;			//���ϵ�ָ��
		bool		isAlloc;
	};
	/*����*/
	struct Objects
	{
		Object*		curObj;			//��ǰ����
		Objects*	nextObjs;		//�¸�����
	};

	int				m_maxObjCnt;		//�����ж���������
	int				m_objCnt;			//�ѷ����������
	int				m_objsCnt;			//��������	
	Object*			m_unusedObjs;		//���ö����б�
	Objects*		m_objs;				//����
public:
	ObjectPool(void) : m_objs(NULL), m_unusedObjs(NULL){}
	virtual ~ObjectPool(void){}

	int	GetAllocatedSize(){ return m_objCnt; }
	int	GetPoolSize(){ return m_maxObjCnt * m_objsCnt; }
	bool IsCreated(){ return m_unusedObjs != NULL; }

	virtual bool Create(unsigned int maxCnt)
	{
		m_maxObjCnt = maxCnt;
		m_objsCnt = 1;

		m_objs = new Objects;
		m_objs->nextObjs = NULL;
		m_objs->curObj = new Object[m_maxObjCnt];

		//���������Ա
		for (int i = 0; i < m_maxObjCnt; i++)
		{
			if (i > 0)
			{
				m_objs->curObj[i].pre = &m_objs->curObj[i - 1];
				m_objs->curObj[i - 1].next = &m_objs->curObj[i];
			}
			m_objs->curObj[i].isAlloc = false;
		}
		m_objs->curObj[0].pre = NULL;
		m_objs->curObj[m_maxObjCnt - 1].next = NULL;

		m_unusedObjs = m_objs->curObj;
		m_objCnt = 0;
		return true;
	}

	virtual void Destroy()
	{
		while (m_objs)
		{
			if (m_objs->curObj)
			{
				delete[] m_objs->curObj;
				m_objs->curObj = NULL;
			}

			Objects* pOld = m_objs;
			m_objs = m_objs->nextObjs;
			delete pOld;
		}
	}

	virtual T* Alloc()
	{
		if (!m_unusedObjs)
		{
			Objects* pSet = new Objects;
			pSet->nextObjs = m_objs;
			pSet->curObj = new Object[m_maxObjCnt];

			for (int i = 0; i < m_maxObjCnt; i++)
			{
				if (i > 0)
				{
					pSet->curObj[i].pre = &pSet->curObj[i - 1];
					pSet->curObj[i - 1].next = &pSet->curObj[i];
				}
				pSet->curObj[i].isAlloc = false;
			}
			pSet->curObj[0].pre = NULL;
			pSet->curObj[m_maxObjCnt - 1].next = NULL;

			m_unusedObjs = pSet->curObj;
			m_objs = pSet;
			m_objsCnt++;
		}

		Object* pFreeObj;
		pFreeObj = m_unusedObjs;
		m_unusedObjs = m_unusedObjs->next;
		if (m_unusedObjs)
			m_unusedObjs->pre = NULL;

		pFreeObj->isAlloc = true;
		m_objCnt++;

		return (T*)&(pFreeObj->obj);
	}

	void Free(T* pElement)
	{
		Object* pObject = (Object*)pElement;

		if (!pObject->isAlloc)
			return;

		pObject->next = m_unusedObjs;
		pObject->pre = NULL;
		if (m_unusedObjs)
			m_unusedObjs->pre = pObject;
		m_unusedObjs = pObject;

		m_objCnt--;

		pObject->isAlloc = false;
	}
};




/*
//c11
#pragma once
#include <boost/pool/object_pool.hpp>
#include <memory>

using namespace std;
template<class obj_type>
class enable_obj_pool
{
	static boost::object_pool<obj_type> _pool;
public:
	static std::shared_ptr<obj_type> alloc()
	{
		//����shared_ptr�Ӷ�����л�ȡ����һ������,(���캯��,�������õķ���),placeholdersռλ�����bind,��ʾfree����������һ������
		return std::shared_ptr<obj_type>(_pool.construct(), bind(&obj_type::free, std::placeholders::_1));
	}

	static void free(obj_type* o)
	{
		_pool.destroy(o);
	}
};

#define enable_obj_pool_entity(thing) boost::object_pool<thing> enable_obj_pool<thing>::_pool;*/

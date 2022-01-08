#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef TPOBJECTHEADER_H
#define TPOBJECTHEADER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QMetaType>
#include "ITPObjectMgr.h"
#include "TPGlobalInfoMgr.h"

#define safeCallInterface(ITPInterface, desc)   \
{ \
    ObjectPtr<IRztInterface> irzt; \
    if(irzt) \
    { \
        irzt->desc; \
    } \
} \

#define safeCallInterfaceIndex(IRztInterface, type, desc)   \
{ \
    ObjectPtr<IRztInterface> irzt(type); \
    if(irzt) \
    { \
        irzt->desc; \
    } \
} \

//ST转Variant
template <class T>
inline QVector<QVariant> stToVariant(QVector<T> vec)
{
    QVector<QVariant> vecRet;
    for (auto& a: vec)
    {
        vecRet.push_back(QVariant::fromValue(a));
    }
    return vecRet;
}

//Variant转ST
template <class T>
inline QVector<T> variantToST(QVector<QVariant> vec)
{
    QVector<T> vecRet;
    for (auto& a: vec)
    {
        vecRet.push_back(a.value<T>());
    }
    return vecRet;
}


//ObjPtr
template <class T> inline const char * TP_obj_iid()
{ return Q_NULLPTR; }

#define TP_DECLARE_OBJ(IFace, IID) \
    template <> inline const char *TP_obj_iid<IFace*>() \
    { return IID; } \

#define toIID(IFace) (TP_obj_iid<IFace*>())
#define iidToObject(iid) (TPGlobalInfoMgr::getObjectMgr()->getObject(iid))
#define iidIndexToObject(iid, index) (TPGlobalInfoMgr::getObjectMgr()->getObject(iid, index))

//获取一个未使用的对象索引
#define mallocObjectPtr(IFace) (TPGlobalInfoMgr::getObjectMgr()->mallocObject(toIID(IFace)))
//获取所有对象index
#define getAllObjectPtrIndex(IFace) (TPGlobalInfoMgr::getObjectMgr()->getObjectsIndex(toIID(IFace)))

#define TP_ADDOBJECT_CLASS(IFace, objClassName) TPGlobalInfoMgr::getObjectMgr()->addObject(TPObjKey(toIID(IFace), OBJDEFAULT), new objClassName())
#define TP_ADDOBJECT_CLASS2(IFace, objClassName, index) TPGlobalInfoMgr::getObjectMgr()->addObject(TPObjKey(toIID(IFace), index), new objClassName(index))
#define TP_ADDOBJECT_CLASS3(IFace, objClassName, index) TPGlobalInfoMgr::getObjectMgr()->addObject(TPObjKey(toIID(IFace), index), new objClassName())
//批量增加未使用的对象
#define TP_ADDOBJECT_CLASS4(IFace, objClassName, count) for (int i = 0; i < count; i++) TPFrameworkMgr::getObjectMgr()->addObject(TPObjKey(toIID(IFace), i + 1), new objClassName(i + 1), false)

#define TP_ADDOBJECT_PTR(IFace, ptr) TPGlobalInfoMgr::getObjectMgr()->addObject(TPObjKey(toIID(IFace), OBJDEFAULT), ptr)
#define TP_ADDOBJECT_PTR2(IFace, ptr, index) TPGlobalInfoMgr::getObjectMgr()->addObject(TPObjKey(toIID(IFace), index), ptr)


template <typename T>
class ObjectPtr
{
public:
    ObjectPtr(const int& nIndex = OBJDEFAULT)
    {
        t = getPointer(nIndex);
    }
    ~ObjectPtr()
    {
    }
    T* operator ->()
    {
        if (Q_NULLPTR == t)
        {
            qRztInfo() << "->NULL ptr";
        }
        return t;
    }

    operator bool ()
    {
        return t != Q_NULLPTR;
    }

    static T* getPointer(const int& nIndex = OBJDEFAULT)
    {
       return dynamic_cast<T*>(TPGlobalInfoMgr::getObjectMgr()->getObject(TP_obj_iid<T*>(), nIndex));
    }

private:
    ObjectPtr(const ObjectPtr &) = delete;
    ObjectPtr &operator=(ObjectPtr &) = delete;
    bool operator ==(const ObjectPtr& ptr) = delete;
    bool operator !=(const ObjectPtr& ptr) = delete;

private:
    T* t = Q_NULLPTR;
};

template <typename T1, typename T2>
class ObjectPtr2
{
public:
    ObjectPtr2(const int& nIndex = OBJDEFAULT)
    {
        t2 = getPointer(nIndex);
    }
    ~ObjectPtr2()
    {
    }
    T2* operator ->()
    {
        if (Q_NULLPTR == t2)
        {
            qRztInfo() << "->NULL ptr";
        }
        return t2;
    }

    operator bool ()
    {
        return t2 != Q_NULLPTR;
    }

    static T2* getPointer(const int& nIndex = OBJDEFAULT)
    {
       return dynamic_cast<T2*>(TPGlobalInfoMgr::getObjectMgr()->getObject(TP_obj_iid<T1*>(), nIndex));
    }

private:
    ObjectPtr2(const ObjectPtr2 &) = delete;
    ObjectPtr2 &operator=(ObjectPtr2 &) = delete;
    bool operator ==(const ObjectPtr2& ptr) = delete;
    bool operator !=(const ObjectPtr2& ptr) = delete;

private:
    T2* t2 = Q_NULLPTR;
};

#endif //RZTOBJECTHEADER_H

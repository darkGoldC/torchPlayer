#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef TP_DataDefine_H
#define TP_DataDefine_H

#include <QtCore/qglobal.h>


#if defined(TPDATASHARED_LIBRARY)
#  define TPDATASHARED_EXPORT Q_DECL_EXPORT
#else
#  define TPDATASHARED_EXPORT Q_DECL_IMPORT
#endif



#endif

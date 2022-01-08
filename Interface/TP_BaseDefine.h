#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef TP_BaseDefine_H
#define TP_BaseDefine_H

#include <QtCore/qglobal.h>


#if defined(TPBASESHARED_LIBRARY)
#  define TPBASESHARED_EXPORT Q_DECL_EXPORT
#else
#  define TPBASESHARED_EXPORT Q_DECL_IMPORT
#endif



#endif

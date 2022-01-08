#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef TP_NetDefine_H
#define TP_NetDefine_H

#include <QtCore/qglobal.h>


#if defined(TPNETSHARED_LIBRARY)
#  define TPNETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TPNETSHARED_EXPORT Q_DECL_IMPORT
#endif



#endif

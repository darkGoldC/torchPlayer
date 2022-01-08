#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef TP_UIDefine_H
#define TP_UIDefine_H

#include <QtCore/qglobal.h>


#if defined(TPUISHARED_LIBRARY)
#  define TPUISHARED_EXPORT Q_DECL_EXPORT
#else
#  define TPUISHARED_EXPORT Q_DECL_IMPORT
#endif



#endif

#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef TP_ControllerDefine_h
#define TP_ControllerDefine_h

#include <QtCore/qglobal.h>


#if defined(TPCONTROLLERSHARED_LIBRARY)
#  define TPCONTROLLERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TPCONTROLLERSHARED_EXPORT Q_DECL_IMPORT
#endif



#endif

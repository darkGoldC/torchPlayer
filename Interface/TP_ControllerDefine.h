#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef TP_ControllerDefine_H
#define TP_ControllerDefine_H

#include <QtCore/qglobal.h>


#if defined(TPCONTROLLERSHARED_LIBRARY)
#  define TPCONTROLLERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TPCONTROLLERSHARED_EXPORT Q_DECL_IMPORT
#endif



#endif

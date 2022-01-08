#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef TP_CoreDefine_H
#define TP_CoreDefine_H

#include <QtCore/qglobal.h>


#if defined(TPCORESHARED_LIBRARY)
#  define TPCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define TPCORESHARED_EXPORT Q_DECL_IMPORT
#endif



#endif

#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef Chj_UIDefine_H
#define Chj_UIDefine_H

#include <QtCore/qglobal.h>


#if defined(CHJUISHARED_LIBRARY)
#  define CHJUISHARED_EXPORT Q_DECL_EXPORT
#else
#  define CHJUISHARED_EXPORT Q_DECL_IMPORT
#endif



#endif

#ifndef TPCOMMONDEFINE_H
#define TPCOMMONDEFINE_H

#include <QtGlobal>
#include <QString>
#include <QDebug>
#include "TPNanoLog.h"

#define INVALID_ID -1

#define NANO_LOG(LEVEL) TPNanolog::NanoLog() == TPNanolog::TPNanoLogLine(LEVEL, __FILE__, __FUNCTION__, __LINE__)
#define qTPInfo()      TPNanolog::is_logged(TPNanolog::LogLevel::INFO) && NANO_LOG(TPNanolog::LogLevel::INFO)
#define qTPDebug()     TPNanolog::is_logged(TPNanolog::LogLevel::DEBUG) && NANO_LOG(TPNanolog::LogLevel::DEBUG)
#define qTPWarning()   TPNanolog::is_logged(TPNanolog::LogLevel::WARN) && NANO_LOG(TPNanolog::LogLevel::WARN)
#define qTPCrit()      TPNanolog::is_logged(TPNanolog::LogLevel::CRIT) && NANO_LOG(TPNanolog::LogLevel::CRIT)

#define qTPOparaLog() TPNanolog::NanoLog() += TPNanolog::TPNanoLogLine(TPNanolog::LogLevel::INFO, __FILE__, __FUNCTION__, __LINE__)

#define NANOSCOPE_LOG(no, LEVEL, STATE) TPNanolog::TPNanoLogScope type##no(STATE); type##no == TPNanolog::TPNanoLogLine(LEVEL, __FILE__, __FUNCTION__, __LINE__)
#define qTPInfoScope(no)     NANOSCOPE_LOG(no##1, TPNanolog::LogLevel::INFO, true) << "begin"; \
                            NANOSCOPE_LOG(no##2, TPNanolog::LogLevel::INFO, false) << "end"

#define qTPDebugScope(no)     NANOSCOPE_LOG(no##1, TPNanolog::LogLevel::DEBUG, true) << "begin"; \
                            NANOSCOPE_LOG(no##2, TPNanolog::LogLevel::DEBUG, false) << "end"

#define qTPWarningScope(no)     NANOSCOPE_LOG(no##1, TPNanolog::LogLevel::WARN, true) << "begin"; \
                            NANOSCOPE_LOG(no##2, TPNanolog::LogLevel::WARN, false) << "end"

#define INVALID 0

typedef long long nTime_t;

#endif // TPCOMMONDEFINE_H

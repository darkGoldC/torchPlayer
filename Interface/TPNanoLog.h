#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

/*

Distributed under the MIT License (MIT)

    Copyright (c) 2016 Karthik Iyengar

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in the 
Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished 
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS 
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef NANO_LOG_HEADER_GUARD
#define NANO_LOG_HEADER_GUARD

#include <cstdint>
#include <memory>
#include <string>
#include <iosfwd>
#include <atomic>
#include <type_traits>
#include <QString>
#include <functional>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include <QRect>
#include <QPoint>
#include "TP_BaseDefine.h"

namespace TPNanolog
{
    enum  LogLevel  :uint8_t { INFO, DEBUG, WARN, CRIT };
    typedef std::function<void (std::string )> TPLogCallBack;

    struct STTPLogConfig
    {
        int nLogFlushTime = 3;
        int nLogFlushSize = 10; //kb
        int nLogFileCount = 30;
        int nLogOutputMinLevel = 0;
    };

    class TPBASESHARED_EXPORT TPNanoLogLine
    {
    public:
    TPNanoLogLine(LogLevel level, char const * file, char const * function, uint32_t line);
    ~TPNanoLogLine();

    TPNanoLogLine(TPNanoLogLine &&) = default;
    TPNanoLogLine& operator=(TPNanoLogLine &&) = default;

    size_t getLevel();
	void stringify(std::ostream & os);
    std::string getLineLogInfo();

    TPNanoLogLine& operator<<(char arg);
    TPNanoLogLine& operator<<(int32_t arg);
    TPNanoLogLine& operator<<(uint32_t arg);
    TPNanoLogLine& operator<<(int64_t arg);
    TPNanoLogLine& operator<<(uint64_t arg);
    TPNanoLogLine& operator<<(double arg);
    TPNanoLogLine& operator<<(std::string const & arg);
    TPNanoLogLine& operator<<(QString const &arg);
    TPNanoLogLine& operator<<(QByteArray const &arg);

	template < size_t N >
    TPNanoLogLine& operator<<(const char (&arg)[N])
	{
	    encode(string_literal_t(arg));
	    return *this;
	}

	template < typename Arg >
    typename std::enable_if < std::is_same < Arg, char const * >::value, TPNanoLogLine& >::type
	operator<<(Arg const & arg)
	{
	    encode(arg);
	    return *this;
	}

	template < typename Arg >
    typename std::enable_if < std::is_same < Arg, char * >::value, TPNanoLogLine& >::type
	operator<<(Arg const & arg)
	{
	    encode(arg);
	    return *this;
	}

    template<typename Arg>
    typename std::enable_if<std::is_same < Arg, QRect >::value, TPNanoLogLine& >::type
    operator<<(const Arg &rect)
    {
        encode < uint32_t >(rect.x());
        encode < char >(',');
        encode < uint32_t >(rect.y());
        encode < uint32_t >(rect.width());
        encode < char >('x');
        encode < uint32_t >(rect.height());
        return *this;
    }

    template<typename Arg>
    typename std::enable_if<std::is_same < Arg, QSize >::value, TPNanoLogLine& >::type
    operator<<(const Arg &size)
    {
        encode < uint32_t >(size.width());
        encode < char >('x');
        encode < uint32_t >(size.height());
        return *this;
    }

    template<typename Arg>
    typename std::enable_if<std::is_same < Arg, QPoint >::value, TPNanoLogLine& >::type
    operator<<(const Arg &point)
    {
        encode < uint32_t >(point.x());
        encode < char >(',');
        encode < uint32_t >(point.y());
        return *this;
    }

    template<typename Arg>
    typename std::enable_if<std::is_same < Arg, QJsonObject >::value, TPNanoLogLine& >::type
    operator<<(Arg value)
    {
        const char *name = "QJsonObject";
        std::string strDebug =  name + std::string("::") + '(';

        QJsonDocument doc(value);
        strDebug += QString(doc.toJson(QJsonDocument::Compact)).toStdString() + ") ";
        encode_c_string(strDebug.c_str(), strDebug.size());
        return *this;
    }

    template<typename Arg>
    typename std::enable_if<std::is_same < Arg, QJsonArray >::value, TPNanoLogLine& >::type
    operator<<(Arg value)
    {
        const char *name = "QJsonArray";
        std::string strDebug =  name + std::string("::") + '(';

        QJsonDocument doc(value);
        strDebug += QString(doc.toJson(QJsonDocument::Compact)).toStdString() + ") ";
        encode_c_string(strDebug.c_str(), strDebug.size());
        return *this;
    }

    template <typename SequentialContainer>
    inline TPNanoLogLine&  printSequentialContainer(const char *which, const SequentialContainer &c)
    {
        *this << which << '(';
        typename SequentialContainer::const_iterator it = c.begin(), end = c.end();
        if (it != end) {
            *this << *it;
            ++it;
        }
        while (it != end) {
            *this << ", " << *it;
            ++it;
        }
        *this << ") ";
        return *this;
    }

    template<typename T>
    TPNanoLogLine& operator<<(QVector<T> value)
    {
//        QString strContent;
//        for(auto &item : value)
//        {
//            strContent += item + ", ";
//        }

//        std::string strDebug = "QVector<QString>::(" + strContent.toStdString() + ") ";
//        encode_c_string(strDebug.c_str(), strDebug.size());
        return printSequentialContainer("QVector<QString>", value);
    }

    template<typename Arg>
    typename std::enable_if<std::is_same < Arg, QStringList>::value, TPNanoLogLine& >::type
    operator<<(Arg value)
    {
        QString strContent;
        for(auto &item : value)
        {
            strContent += item + ", ";
        }

        std::string strDebug = "QVector<QString>::(" + strContent.toStdString() + ") ";
        encode_c_string(strDebug.c_str(), strDebug.size());
        return *this;
    }

    template<typename Arg>
    typename std::enable_if<std::is_same < Arg, QList<int> >::value, TPNanoLogLine& >::type
    operator<<(Arg value)
    {
        QString strContent;
        for(auto &item : value)
        {
            strContent += QString::number(item) + ", ";
        }

        std::string strDebug = "QVector<QString>::(" + strContent.toStdString() + ") ";
        encode_c_string(strDebug.c_str(), strDebug.size());
        return *this;
    }

    template<typename Arg>
    typename std::enable_if<std::is_same < Arg, QDateTime >::value, TPNanoLogLine& >::type
    operator<<(Arg value)
    {
        QString strContent = value.toString();

        std::string strDebug = "QDateTime::(" + strContent.toStdString() + ") ";
        encode_c_string(strDebug.c_str(), strDebug.size());
        return *this;
    }

	struct string_literal_t
	{
	    explicit string_literal_t(char const * s) : m_s(s) {}
	    char const * m_s;
	};

    private:	
	char * buffer();

    template < typename Arg >
    void encode(Arg arg)
    {
        *reinterpret_cast<Arg*>(buffer()) = arg;
        m_bytes_used += sizeof(Arg);
    }

	template < typename Arg >
	void encode(Arg arg, uint8_t type_id);

	void encode(char * arg);
	void encode(char const * arg);
	void encode(string_literal_t arg);
    void encode(QString type_id);
	void encode_c_string(char const * arg, size_t length);
	void resize_buffer_if_needed(size_t additional_bytes);
	void stringify(std::ostream & os, char * start, char const * const end);

    private:
	size_t m_bytes_used;
	size_t m_buffer_size;
    size_t m_level;
    std::unique_ptr < char [] > m_heap_buffer;
    char m_stack_buffer[256 - 3 * sizeof(size_t) - sizeof(decltype(m_heap_buffer)) - 8 /* Reserved */];
    };
    
    struct TPBASESHARED_EXPORT NanoLog
    {
        /*
         * Ideally this should have been operator+=
         * Could not get that to compile, so here we are...
         */
        bool operator==(TPNanoLogLine &);
        bool operator+=(TPNanoLogLine &);
    };

    struct TPBASESHARED_EXPORT TPNanoLogScope
    {
        public:
            explicit TPNanoLogScope(bool bPos);
            bool operator==(TPNanoLogLine &);
            ~TPNanoLogScope();
        private:
            TPNanoLogLine m_logLine;
            std::atomic_bool m_bBegin = {true};
    };

    TPBASESHARED_EXPORT void    set_log_level(LogLevel level);
    
    TPBASESHARED_EXPORT bool    is_logged(LogLevel level);
    TPBASESHARED_EXPORT void    set_oparate_log(bool blog);
    TPBASESHARED_EXPORT void    setLogCallback(TPLogCallBack func);

    /*
     * Non guaranteed logging. Uses a ring buffer to hold log lines.
     * When the ring gets full, the previous log line in the slot will be dropped.
     * Does not block producer even if the ring buffer is full.
     * ring_buffer_size_mb - LogLines are pushed into a mpsc ring buffer whose size
     * is determined by this parameter. Since each LogLine is 256 bytes, 
     * ring_buffer_size = ring_buffer_size_mb * 1024 * 1024 / 256
     */
    struct TPBASESHARED_EXPORT NonGuaranteedLogger
    {
        NonGuaranteedLogger(uint32_t ring_buffer_size_mb_) : ring_buffer_size_mb(ring_buffer_size_mb_) {}
        uint32_t ring_buffer_size_mb;
    };

    /*
     * Provides a guarantee log lines will not be dropped. 
     */
    struct GuaranteedLogger
    {
    };
    
    /*
     * Ensure initialize() is called prior to any log statements.
     * log_directory - where to create the logs. For example - "/tmp/"
     * log_file_name - root of the file name. For example - "nanolog"
     * This will create log files of the form -
     * /tmp/nanolog.1.txt
     * /tmp/nanolog.2.txt
     * etc.
     * log_file_roll_size_mb - mega bytes after which we roll to next log file.
     */

    TPBASESHARED_EXPORT void    initialize(GuaranteedLogger gl, std::string const & log_directory, std::string const & log_file_name, uint32_t log_file_roll_size_mb, bool bOparate = false);
    TPBASESHARED_EXPORT void    initialize(NonGuaranteedLogger ngl, std::string const & log_directory, std::string const & log_file_name, uint32_t log_file_roll_size_mb);
    TPBASESHARED_EXPORT void    flush();
    TPBASESHARED_EXPORT void    setLogConfig(STTPLogConfig logConfig);
} // namespace nanolog

#endif /* NANO_LOG_HEADER_GUARD */


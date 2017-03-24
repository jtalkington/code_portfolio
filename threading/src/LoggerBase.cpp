/*
 * Copyright 2017 Jerry Talkington
 *
 * No license is granted to use this software. This is provided for skill
 * evaluation only. Do not copy or reuse this software for any purpose.
 */
#include "../include/LoggerBase.hpp"

#include <iostream>
#include <mutex>
#include <atomic>

namespace jtalkington {

static const std::string emergency = "EMERGENCY";
static const std::string alert = "ALERT";
static const std::string critical = "CRITICAL";
static const std::string error = "ERROR";
static const std::string warning = "WARNING";
static const std::string notice = "NOTICE";
static const std::string info = "INFO";
static const std::string debug = "DEBUG";
static const std::string none = "";
static const std::string unknown = "Unkown";

class LoggerBase::LoggerBaseData {
    public:
        /// Constructor
        LoggerBaseData() :
            m_Severity(NONE) {}
        
        /// The current severity level.
        std::atomic<Severity_t> m_Severity;

        /// The stream we write to.
        StreamPtr_t m_Stream;

        /// The lock for thread safety.
        std::mutex m_Mutex;
};

LoggerBase::LoggerBase() :
    m_Data(std::unique_ptr<LoggerBaseData>(new LoggerBaseData()))
{
    reset_stream();
}

LoggerBase::~LoggerBase() {}

void LoggerBase::open(std::shared_ptr<std::ostream> stream, Severity_t level) {
    m_Data->m_Severity = level;
	
    std::lock_guard<std::mutex> guard(m_Data->m_Mutex);
    m_Data->m_Stream = stream;
}

void LoggerBase::open(Severity_t level) {
    m_Data->m_Severity = level;
    open();
}

void LoggerBase::open() {
    reset_stream();
}


void LoggerBase::log(Severity_t level, const std::string& eventMessage) {
    if (level <= m_Data->m_Severity) {
        std::lock_guard<std::mutex> guard(m_Data->m_Mutex);

        if (level != NONE) {
            *(m_Data->m_Stream) << describe_severity(level) << ": ";
        }

        *(m_Data->m_Stream) << eventMessage << std::endl << std::flush;
    }
}

void LoggerBase::log(const std::string& eventMessage) {
    log(NONE, eventMessage);
}

void LoggerBase::set_severity(Severity_t level) {
    m_Data->m_Severity = level;
}

LoggerBase::Severity_t LoggerBase::get_severity() {
    return m_Data->m_Severity;
}
const std::string& LoggerBase::describe_severity(Severity_t level) {
   
    switch (level) {
        case EMERGENCY: { return emergency; } break;
        case ALERT: { return alert; } break;
        case CRITICAL: { return critical; } break;
        case ERROR: { return error; } break;
        case WARNING: { return warning; } break;
        case NOTICE: { return notice; } break;
        case INFO: { return info; } break;
        case DEBUG: { return debug; } break;
        case NONE: { return none; } break;
        default: { return unknown; } break;
    }
}

void LoggerBase::reset_stream() {
    std::lock_guard<std::mutex> guard(m_Data->m_Mutex);
    m_Data->m_Stream = StreamPtr_t(&std::cerr, [](void*) {});
}


} // namespace jtalkington


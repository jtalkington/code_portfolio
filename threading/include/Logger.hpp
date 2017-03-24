/*
 * Copyright 2017 Jerry Talkington
 *
 * No license is granted to use this software. This is provided for skill
 * evaluation only. Do not copy or reuse this software for any purpose.
 */
#ifndef jtalkington_Logger_hpp
#define jtalkington_Logger_hpp

#include <LoggerBase.hpp>

#include <string>

namespace jtalkington {

/**
 * A template class for logging messages.
 *
 * This class allows for creating any number of unique loggers that are shared
 * across the program. Templated to allow a unique logger for each file or stream
 * that is being written to. The default stream/file to write to is stderr.
 *
@code
#include <Logger.hpp>
#include <sstream>

class MyNewLogger {};
typedef Logger<MyNewLogger> MyLogger_t;

std::shared_ptr<std::stringstream> myLogStream(new std::stringstream());
MyLogger_t::open(std::static_pointer_cast<std::ostream>(myLogStream));
MyLogger_t::log(MyLogger_t::NOTICE, "This goes to myLogStream!");

@endcode
 *
 * @TODO copydoc from LoggerBase instead of repeating it
 */
template<class T>
class Logger : public LoggerBase {
    public:
        /**
         * A pointer type for an instance of Logger<T>.
         */
        typedef std::shared_ptr< Logger<T> > ptr_t;

        /**
         * Redirect all logs to the specified stream.
         *
         * @param stream The new stream to send logging to.
         * @param level The minimum severity level to log.
         */
        static void open(std::shared_ptr<std::ostream> stream, Severity_t level = NONE);

        /**
         * Reset the output stream to stderr while changing the Severity level.
         *
         * @param level The minimum severity level to log.
         */
        static void open(Severity_t level);

        /**
         * Reset the output stream to stderr without changing the Severity level.
         *
         * @param level The minimum severity level to log.
         */
        static void open(void);

        // @TODO
        // void open(std::string filename);

        /**
         * Log an event message.
         *
         * @param level The Severity_t logging level.
         * @param eventMessage The event message to log.
         */
        static void log(Severity_t level, const std::string& eventMessage);

        /**
         * Log an event message without reporting severity.
         *
         * @param eventMessage The event message to log.
         */
        static void log(const std::string& eventMessage);

        /**
         * Set the logging severity level.
         *
         * Sets the severity level for this logger. Messages less severe than
         * this setting are not logged.
         *
         * @param level The minimum severity for messages to be logged.
         */
        static void set_severity(Severity_t level);

        /**
         * Get the severity level.
         *
         * @returns The current severity level.
         */
        static Severity_t get_severity(void);

        /*
         * Get the instance of this logger.
         */
        static Logger<T>::ptr_t get_instance(void);

    private:
        // Private constructor to prevent instantiation outside of this class.
        Logger() {};

        /// The singleton for this instance.
        static Logger<T>::ptr_t m_InstancePtr;
};

template<class T>
inline
typename Logger<T>::ptr_t Logger<T>::get_instance(void) {
    if (!m_InstancePtr) {
        m_InstancePtr = Logger<T>::ptr_t(new Logger<T>());
    }

    return m_InstancePtr;
}

template<class T>
typename Logger<T>::ptr_t Logger<T>::m_InstancePtr;

template<class T>
inline
void Logger<T>::open(std::shared_ptr<std::ostream> stream, Severity_t level) {
    Logger<T>::ptr_t log = get_instance();
    static_cast<LoggerBase*>(log.get())->open(stream, level);
}

template<class T>
inline
void Logger<T>::open(Severity_t level) {
    Logger<T>::ptr_t log = get_instance();
    static_cast<LoggerBase*>(log.get())->open(level);
}

template<class T>
inline
void Logger<T>::open() {
    Logger<T>::ptr_t log = get_instance();
    static_cast<LoggerBase*>(log.get())->open();
}


template<class T>
inline
void Logger<T>::log(Severity_t level, const std::string& eventMessage) {
    Logger<T>::ptr_t log = get_instance();
    static_cast<LoggerBase*>(log.get())->log(level, eventMessage);
}

template<class T>
inline
void Logger<T>::log(const std::string& eventMessage) {
    Logger<T>::ptr_t log = get_instance();
    static_cast<LoggerBase*>(log.get())->log(eventMessage);
}

template<class T>
inline
void Logger<T>::set_severity(Severity_t level) {
    Logger<T>::ptr_t log = get_instance();
    static_cast<LoggerBase*>(log.get())->set_severity(level);
}
 
/**
 * An empty class to instantiate the default logger.
 */
class LoggerDefault {};

/**
 * The default logger.
 */
typedef Logger<LoggerDefault> DefaultLogger;


} // namespace jtalkington

#endif // jtalkington_Logger_hpp

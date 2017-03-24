/*
 * Copyright 2017 Jerry Talkington
 *
 * No license is granted to use this software. This is provided for skill
 * evaluation only. Do not copy or reuse this software for any purpose.
 */
#ifndef jtalkington_LoggerBase_hpp
#define jtalkington_LoggerBase_hpp

#include <string>
#include <memory>

namespace jtalkington {

/**
 * A base class for logger templates. This allows us to declare common types
 * in a single place.
 *
 * @TODO allow logging to a file
 * @TODO enable optional timestamps
 * @TODO allow disabling of newline
 */
class LoggerBase {
    public:
        /**
         * The types of events that can be logged. Per syslog, the lower the
         * level, the more severe.
         */
        typedef enum {
            EMERGENCY,
            ALERT,
            CRITICAL,
            ERROR,
            WARNING,
            NOTICE,
            INFO,
            DEBUG,
            NONE
        } Severity_t;

        /**
         * A pointer type to a stream.
         */
        typedef std::shared_ptr<std::ostream> StreamPtr_t;

        /// Constructor
        LoggerBase();

        /// Destructor
        virtual ~LoggerBase();

        /**
         * Redirect all logs to the specified stream.
         *
         * @param stream The new stream to send logging to.
         * @param level The minimum severity level to log.
         */
        void open(std::shared_ptr<std::ostream> stream, Severity_t level = NONE);

        /**
         * Reset the output stream to stderr while chainging the severity level.
         *
         * @param level The minimum severity level to log.
         */
        void open(Severity_t level);

        /**
         * Reset the output stream to stderr without chainging the severity level.
         *
         * @param level The minimum severity level to log.
         */
        void open();

        // @TODO
        // void open(std::string filename);

        /**
         * Log an event message.
         *
         * @param level The Severity_t logging level.
         * @param eventMessage The event message to log.
         */
        void log(Severity_t level, const std::string& eventMessage);

        /**
         * Log an event message without reporting severity.
         *
         * @param eventMessage The event message to log.
         */
        void log(const std::string& eventMessage);

        /**
         * Set the logging severity level.
         *
         * Sets the severity level for this logger. Messages less severe than
         * this setting are not logged.
         *
         * @param level The minimum severity for messages to be logged.
         */
        void set_severity(Severity_t level);

        /**
         * Get the severity level.
         *
         * @returns The current severity level.
         */
        Severity_t get_severity(void);
        
        /**
         * Return a string describing the provided severity level.
         *
         * @param level The level to describe.
         * @returns A textual description of the security level.
         */
        static const std::string& describe_severity(Severity_t level);

    private:
		// Resets the stream to stderr
		void reset_stream(void);

		// A class for holding data
        class LoggerBaseData;
        // The pointer to the data
        std::unique_ptr<LoggerBaseData> m_Data;
};

} // namespace jtalkington

#endif //jtalkington_LoggerBase_hpp

/*
 * Copyright 2017 Jerry Talkington
 *
 * No license is granted to use this software. This is provided for skill
 * evaluation only. Do not copy or reuse this software for any purpose.
 */
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include "../include/Logger.hpp"

#include <sstream>
#include <memory>
#include <iostream>

using namespace jtalkington;


namespace test_jtalkington_Logger {
struct CerrRedirect {
    CerrRedirect(std::streambuf* newBuffer)
        : m_OriginalBuffer(std::cerr.rdbuf(newBuffer)) {}

    ~CerrRedirect() {
        std::cerr.rdbuf(m_OriginalBuffer);
    }

    private:
        std::streambuf* m_OriginalBuffer;
};

BOOST_AUTO_TEST_SUITE( jtalkington_Logger )

BOOST_AUTO_TEST_CASE( test_DefaultLogger )
{
    boost::test_tools::output_test_stream output;
    CerrRedirect redir(output.rdbuf());

    std::string testString = "This is a test.";
    std::string expected;
    
    DefaultLogger::log(DefaultLogger::EMERGENCY, testString);
    expected = "EMERGENCY: " + testString + "\n";
    BOOST_CHECK(output.is_equal(expected));
    output.flush();

    DefaultLogger::log(DefaultLogger::ALERT, testString);
    expected = "ALERT: " + testString + "\n";
    BOOST_CHECK(output.is_equal(expected));
    output.flush();

    DefaultLogger::log(DefaultLogger::CRITICAL, testString);
    expected = "CRITICAL: " + testString + "\n";
    BOOST_CHECK(output.is_equal(expected));
    output.flush();

    DefaultLogger::log(DefaultLogger::ERROR, testString);
    expected = "ERROR: " + testString + "\n";
    BOOST_CHECK(output.is_equal(expected));
    output.flush();

    DefaultLogger::log(DefaultLogger::WARNING, testString);
    expected = "WARNING: " + testString + "\n";
    BOOST_CHECK(output.is_equal(expected));
    output.flush();

    DefaultLogger::log(DefaultLogger::NOTICE, testString);
    expected = "NOTICE: " + testString + "\n";
    BOOST_CHECK(output.is_equal(expected));
    output.flush();

    DefaultLogger::log(DefaultLogger::INFO, testString);
    expected = "INFO: " + testString + "\n";
    BOOST_CHECK(output.is_equal(expected));
    output.flush();

    DefaultLogger::log(DefaultLogger::DEBUG, testString);
    expected = "DEBUG: " + testString + "\n";
    BOOST_CHECK(output.is_equal(expected));
    output.flush();

    DefaultLogger::log(DefaultLogger::NONE, testString);
    expected = testString + "\n";
    BOOST_CHECK(output.is_equal(expected));
    output.flush();

    DefaultLogger::log(testString);
    expected = testString + "\n";
    BOOST_CHECK(output.is_equal(expected));
    output.flush();

    DefaultLogger::set_severity(DefaultLogger::INFO);
    DefaultLogger::log(DefaultLogger::DEBUG, testString);
    expected = "";
    BOOST_CHECK(output.is_equal(expected));
    output.flush();

    DefaultLogger::log(DefaultLogger::INFO, testString);
    expected = "INFO: " + testString + "\n";
    BOOST_CHECK(output.is_equal(expected));
    output.flush();
}

BOOST_AUTO_TEST_CASE( test_Logger_Stream )
{
    std::shared_ptr<std::stringstream> ss(new std::stringstream());
    std::string testString = "This is a test.";
    std::string expected = testString + "\n";

    DefaultLogger::open(std::static_pointer_cast<std::ostream>(ss));

    DefaultLogger::log(testString);

    BOOST_CHECK(ss->str() == expected);

}

BOOST_AUTO_TEST_SUITE_END()

} // namespace test_jtalkington_Logger

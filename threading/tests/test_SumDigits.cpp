/*
 * Copyright 2017 Jerry Talkington
 *
 * No license is granted to use this software. This is provided for skill
 * evaluation only. Do not copy or reuse this software for any purpose.
 */
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include "../include/SumDigits.hpp"
#include "../include/Logger.hpp"

#include <sstream>
#include <memory>
#include <iostream>
#include <thread>

using namespace jtalkington;

namespace test_jtalkington_SumDigits {

BOOST_AUTO_TEST_SUITE( jtalkington_SumDigits )

BOOST_AUTO_TEST_CASE( test_SumDigits )
{
    std::shared_ptr<std::stringstream> ss(new std::stringstream());
    DefaultLogger::open(std::static_pointer_cast<std::ostream>(ss));

    std::string expected;
    std::string result;
    
    {
        SumDigits::ptr_t sd = SumDigits::create();
        sd->perform_sum("12345", 0);
        SumDigits::destroy(sd);
        expected = "Sum of digit string \"12345\" is \"15\".\n";
    }
    result = ss->str();
    BOOST_CHECK_MESSAGE(result == expected, result);
    ss->str(std::string());
    ss->clear();
    
    {
        SumDigits::ptr_t sd = SumDigits::create();
        sd->perform_sum("a2345", 0);
        SumDigits::destroy(sd);
        expected = "ERROR: String \"a2345\" is not just digits.\n";
    }
    result = ss->str();
    BOOST_CHECK_MESSAGE(result == expected, result);
    ss->str(std::string());
    ss->clear();
}


BOOST_AUTO_TEST_SUITE_END()

} //namespace test_jtalkington_SumDigits

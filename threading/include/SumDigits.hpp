/*
 * Copyright 2017 Jerry Talkington
 *
 * No license is granted to use this software. This is provided for skill
 * evaluation only. Do not copy or reuse this software for any purpose.
 */
#ifndef SumDigits_hpp
#define SumDigits_hpp

#include <memory>

namespace jtalkington {

/**
 * A simple class to sum the digits of a string and log the results.
 */
class SumDigits {
    public:
        /// A shared pointer to an instance of SumDigits.
        typedef std::shared_ptr<SumDigits> ptr_t;

        /// Destructor
        virtual ~SumDigits();
        
        /**
         * Create an instance of SumDigits.
         *
         * Creates and returns a shared point to an instance of SumDigits. This
         * can either be allowed to go out of scope, or destroyed with the
         * destroy() method.
         *
         * @param numThreads The number of threads to start.
         */
        static ptr_t create(unsigned short numThreads = 3);

        /**
         * Destroy a SumDigits instance in a synchronized way.
         *
         * This will shutdown all threads and destroy the instance before
         * returning. Allows the caller to ensure that there are no more jobs
         * pending.
         *
         * N.B. The pointer will no longer have a valid object after this call.
         *
         * @param instance A pointer to a SumDigits instance.
         * @throws std::invalid_argument If the pointer is not valid.
         */
        static void destroy(ptr_t& instance);

        /**
         * Sums the digits present in a string of digits, and prints a result to the
         * DefaultLogger.
         *
         * @param dely The number of seconds to wait before performing that sum.
         */ 
        void perform_sum(const std::string& data, uint64_t delay = 0); 

    private:
        // Private constructor.
        SumDigits(unsigned short numThreads);

        // A class that holds the data members for SumDigits.
        class SumDigitsImpl;
        // A pointer to an instance of that class.
        std::unique_ptr<SumDigitsImpl> m_Impl;
};

} // namespace jtalkington
#endif // SumDigits_hpp


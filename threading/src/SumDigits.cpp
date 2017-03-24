/*
 * Copyright 2017 Jerry Talkington
 *
 * No license is granted to use this software. This is provided for skill
 * evaluation only. Do not copy or reuse this software for any purpose.
 */

#include "../include/SumDigits.hpp"
#include "SumDigitsImpl.hpp"

#include <stdexcept>
#include <queue>
#include <mutex>
#include <thread>

namespace jtalkington {

SumDigits::SumDigits(unsigned short numThreads) 
    : m_Impl(std::unique_ptr<SumDigitsImpl>(new SumDigitsImpl(numThreads)))
{
}

SumDigits::~SumDigits() {}

SumDigits::ptr_t SumDigits::create(unsigned short numThreads) {
    ptr_t newPtr(new SumDigits(numThreads));
    return newPtr;
}

void SumDigits::destroy(ptr_t& instance) {
    if (!instance) {
        throw std::invalid_argument("Attempted to destroy() a nonexistent instance.");
    }
    
    instance->m_Impl->shutdown();
    instance.reset();
}

void SumDigits::perform_sum(const std::string& data, uint64_t delay) {
    m_Impl->perform_sum(data, delay);
}

} // namespace jtalkington

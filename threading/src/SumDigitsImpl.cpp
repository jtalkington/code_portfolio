/*
 * Copyright 2017 Jerry Talkington
 *
 * No license is granted to use this software. This is provided for skill
 * evaluation only. Do not copy or reuse this software for any purpose.
 */

#include "../include/Logger.hpp"
#include "SumDigitsImpl.hpp"
#include <functional>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <iostream>

namespace jtalkington {

SumDigits::SumDigitsImpl::SumDigitsImpl(unsigned short numThreads) :
    m_TaskQueue(),
    m_Mutex(),
    m_Threads(),
    m_Notifier(),
    m_Shutdown(false)
{
    if (numThreads < 1) {
        numThreads = 1;
    }

    for (unsigned short i = 0; i < numThreads; ++i) {
        m_Threads.push_back(std::thread(&SumDigits::SumDigitsImpl::worker_thread, this));
    }
}

SumDigits::SumDigitsImpl::~SumDigitsImpl() {
    shutdown();
}

void SumDigits::SumDigitsImpl::shutdown() {
    std::unique_lock<std::mutex> lock(m_Mutex);
    if (!m_Threads.empty()) {
        m_Shutdown = true;
        m_Notifier.notify_all();

        lock.unlock();
        
        for (std::thread& t : m_Threads) {
            t.join();
        }
        m_Threads.clear();
    }
}

// @TODO Add threads if we are above a certain threshold
void SumDigits::SumDigitsImpl::perform_sum(const std::string& data, uint64_t delay) {
    if (m_Shutdown) {
        DefaultLogger::log(DefaultLogger::ERROR, "Unable to add task, shutting down");
        return;
    }
    
    Task_t task(std::make_pair(data, delay));
    
    std::lock_guard<std::mutex> guard(m_Mutex);
    m_TaskQueue.push(std::move(task));
    m_Notifier.notify_one();
}

/// @TODO move this into a more usable location
static std::string add_digits(const std::string& input) {

    uint64_t sum = 0;

    for (auto i : input) {
        if (!std::isdigit(i)) {
            throw std::invalid_argument("String \"" + input + "\" is not just digits.");
        }

        sum += std::atoi(&i);
    }

    return std::to_string(sum);
}

void SumDigits::SumDigitsImpl::worker_thread() {

    while(true) {
        Task_t task;
        bool empty;
        
        {
            std::unique_lock<std::mutex> lock(m_Mutex);

            // Keep draining until all of the queued jobs have completed.
            if (m_TaskQueue.empty()) {
                if (m_Shutdown) {
                    return;
                }
                
                m_Notifier.wait(lock);
                empty = m_TaskQueue.empty();
                
                if (m_Shutdown && empty) {
                    return;
                } else if (empty) {
                    continue;
                }

            }

            task = std::move(m_TaskQueue.front());
            m_TaskQueue.pop();
        }

        // Sleep the specified number of seconds.
        std::this_thread::sleep_for(std::chrono::seconds(task.second));

        std::string sum;
        try {
            sum = add_digits(task.first);
        } catch (std::exception& e) {
            DefaultLogger::log(DefaultLogger::ERROR, e.what());
            continue;
        } catch (...) {
            DefaultLogger::log(DefaultLogger::ERROR, "Undefined exception thrown.");
            continue;
        }

        DefaultLogger::log("Sum of digit string \"" + task.first + "\" is \"" + sum + "\".");

    }
}

} // namespace jtalkington

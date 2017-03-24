/*
 * Copyright 2017 Jerry Talkington
 *
 * No license is granted to use this software. This is provided for skill
 * evaluation only. Do not copy or reuse this software for any purpose.
 */

#include <stdexcept>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <memory>
#include <condition_variable>

#include "../include/SumDigits.hpp"

namespace jtalkington {

class SumDigits::SumDigitsImpl {
    public:
        // Constructor
        SumDigitsImpl(unsigned short numThreads);

        // Destructor
        virtual ~SumDigitsImpl();

        // Stop and join all threads.
        void shutdown(void);

        // Enqueue the task.
        void perform_sum(const std::string& data, uint64_t delay);

    private:
        // A type for the tasks
        typedef std::pair<std::string, uint64_t> Task_t;

        // The function that performs the work
        void worker_thread(void);

        // The actual task queue.
        std::queue<Task_t> m_TaskQueue;
        
        // The mutex for locking
        std::mutex m_Mutex;

        // The vector of all running threads.
        std::vector<std::thread> m_Threads;
        
        // The condition variable for the worker threads
        std::condition_variable m_Notifier;

        // true when shutting down
        std::atomic<bool> m_Shutdown;

};

} // namespace jtalkington

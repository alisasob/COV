#pragma once
#include <iostream>
#include <chrono>
#include <list>
#include <mutex>
#include "QueuedRequest.h"

// Класс для работы с очередью запросов
class RequestQueue {
public:
    QueuedRequest* pushRequest(const Request& p_request_data, const int N, std::string& pushStatus) {
        QueuedRequest* queuedRequest = new QueuedRequest();
        if (requestQueue.size() < N) {
            std::lock_guard<std::mutex> lock(queue_mutex);
            requestQueue.push_back(queuedRequest); 
        }
        else pushStatus = "overload";
        return queuedRequest;
    }

    QueuedRequest* pullRequest() {
        std::lock_guard<std::mutex> lock(queue_mutex);
        QueuedRequest* frontRequest;
        if (!requestQueue.empty()) {
            frontRequest = requestQueue.front();
            requestQueue.pop_front();
        }
        else {
            frontRequest = new QueuedRequest("empty");
        }
        return frontRequest;
    }

private:
    std::list<QueuedRequest*> requestQueue;
    std::mutex queue_mutex;
};

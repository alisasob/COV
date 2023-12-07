#pragma once
#include <iostream>
#include <chrono>
#include <list>
#include <vector>
#include <thread>
#include <mutex>
#include "RequestQueue.h"

//  ласс дл€ представлени€ операторского потока
class OperatorThread {
public:
    static void operatorThreadFunc(RequestQueue& requestQueue, int opId) {
        while (true) {
            QueuedRequest* queuedRequest = requestQueue.pullRequest();
            if (queuedRequest->status == "empty") {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            else {
                if (!queuedRequest->expired()) {
                    queuedRequest->answerTime = std::chrono::system_clock::now();
                    queuedRequest->opId = opId;
                    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 5000 + 3000));
                    queuedRequest->status = "200 OK";
                }
                else {
                    queuedRequest->status = "timeout";
                }
            }
        }
    }
};

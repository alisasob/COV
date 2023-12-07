#include <stdio.h>
#include <iostream>
#include <iomanip>
////#include <fstream>
#include <string>
#include <list>
#include "include/nlohmann/json.hpp"
#include <time.h>
#include "httplib.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"
#include "CDR.h"
#include "OperatorThread.h"
#include "QueuedRequest.h"
#include "Request.h"
#include "RequestQueue.h"
//#include <windows.h>
#include <cstring>
#include <semaphore.h>

pthread_mutex_t cout_mutex;

const int N = 3; // максимальная длина очереди
const int NumOfOp = 2; // количество операторов

using json = nlohmann::json;

time_t getDT();
std::string DTToStr(time_t);

int main()
{
    setlocale(LC_CTYPE, "rus");

    Model model;
    View view;
    Controller controller(model, view);
    httplib::Server server;
    int LastCDRID = 0;

    RequestQueue requestQueue;
    
    std::vector<std::thread> operatorThreads;// Создание и запуск операторских потоков
    for (int i = 0; i < NumOfOp; ++i) {
        operatorThreads.emplace_back(OperatorThread::operatorThreadFunc, std::ref(requestQueue), i);
    }
    
    pthread_mutex_init(&cout_mutex, NULL);

    server.Post("/calls", [&](const httplib::Request& req, httplib::Response& res) {
        __int64_t come, ans, end;
        int opID, min, max, i, t;
        bool b = false;
        std::string message;
        CDR cdr;
        come = getDT();
        cdr.comeCallDT = DTToStr(come);
        Request request;
        std::string push_status;

        std::string id = req.matches[1];
        json r = json::parse(req.body);
        request.abonentNumber = r["abonent"];
        cdr.abonentNumber = request.abonentNumber;
        QueuedRequest* queuedRequest;
        queuedRequest = requestQueue.pushRequest(request, N, push_status);
        if (push_status == "overload") {
            end = getDT();
            cdr.endCallDT = DTToStr(end);
            cdr.callID = queuedRequest->id;
            cdr.status = push_status;
            message = cdr.getLine(0);
        }
        else {
            ans = getDT();
            cdr.answerCallDT = DTToStr(ans);
            while (queuedRequest->status == "pending") {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            end = getDT();
            cdr.endCallDT = DTToStr(end);
            cdr.callID = queuedRequest->id;
            cdr.status = queuedRequest->status;
            if (queuedRequest->status == "timeout") {
                message = cdr.getLine(0);
            }
            else {
                cdr.operatorID = queuedRequest->opId;
                ans = std::chrono::system_clock::to_time_t(queuedRequest->answerTime);
                cdr.answerCallDT = DTToStr(ans);
                cdr.durationCall = end - ans;
                message = cdr.getLine();
            };
        };
     
        pthread_mutex_lock(&cout_mutex);
        std::cout << message << "\n";
        pthread_mutex_unlock(&cout_mutex);
        });
    server.listen("localhost", 8080);

	return 0;
}


time_t getDT() {
    time_t rawtime;
    time(&rawtime);
    return rawtime;
};

std::string DTToStr(time_t rawtime) {
    struct tm timeinfo;
    char buffer[80];
    localtime_r(&rawtime, &timeinfo);
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeinfo);
    std::string str(buffer);
    return str;
};

#pragma once
#include <iostream>
#include <chrono>
#include "Request.h"

int ID = 0;

// Структура для представления запроса в очереди
class QueuedRequest {
public:
    int id; // id поступившего вызова
    int opId; // id оператора принявшего вызов
    Request requestData; // поступивший запрос
    std::string status; // статус вызова
    std::chrono::system_clock::time_point answerTime; // время ответа оператора
    std::chrono::steady_clock::time_point expiryTime; // время до которого абонент готов ожидать в очереди
    bool expired() {
        if (std::chrono::steady_clock::now() > expiryTime) return true;
        return false;
    }
public:
    QueuedRequest(std::string);
};

QueuedRequest::QueuedRequest(std::string status = "pending") {
    requestData = Request();
    this->status = status;
    expiryTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(rand() % 5000 + 1000);
    if (this->status != "empty") {
        this->id = ++ID;
    }
};
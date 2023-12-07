#pragma once
#include <iostream>
#include <chrono>
#include "Request.h"

int ID = 0;

// ��������� ��� ������������� ������� � �������
class QueuedRequest {
public:
    int id; // id ������������ ������
    int opId; // id ��������� ���������� �����
    Request requestData; // ����������� ������
    std::string status; // ������ ������
    std::chrono::system_clock::time_point answerTime; // ����� ������ ���������
    std::chrono::steady_clock::time_point expiryTime; // ����� �� �������� ������� ����� ������� � �������
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
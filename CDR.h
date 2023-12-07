#pragma once
#include <iostream>
#include <string>
class CDR
{
public:
    std::string comeCallDT; //DT поступления вызова.
    int callID;//Идентификатор входящего вызова(Call ID)
    std::string abonentNumber; //Номер абонента А
    std::string endCallDT; //DT завершения вызова
    std::string status;//Статус вызова(OK или причина ошибки, например timeout)
    std::string answerCallDT;//DT ответа оператора(если был или пустое значение)
    int operatorID;//Идентификатор оператора(пустое значение если соединение не состоялось)
    double durationCall;//Длительность разговора(пустое значение если соединение не состоялось)

public:
    std::string getLine();
    std::string getLine(int);
    ~CDR();
};

std::string CDR::getLine() {
    std::string s = "";
    s += comeCallDT + ";";
    s += std::to_string(callID) + ";";
    s += abonentNumber + ";";
    s += endCallDT + ";";
    s += status + ";";
    s += answerCallDT + ";";
    s += std::to_string(operatorID) + ";";
    s += std::to_string(durationCall) + ";";
    return s;
};

std::string CDR::getLine(int a) {
    std::string s = "";
    s += comeCallDT + ";";
    s += std::to_string(callID) + ";";
    s += abonentNumber + ";";
    s += endCallDT + ";";
    s += status + ";";
    return s;
};

CDR::~CDR() {};
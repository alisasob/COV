#pragma once
#include <iostream>
#include <string>
class CDR
{
public:
    std::string comeCallDT; //DT ����������� ������.
    int callID;//������������� ��������� ������(Call ID)
    std::string abonentNumber; //����� �������� �
    std::string endCallDT; //DT ���������� ������
    std::string status;//������ ������(OK ��� ������� ������, �������� timeout)
    std::string answerCallDT;//DT ������ ���������(���� ��� ��� ������ ��������)
    int operatorID;//������������� ���������(������ �������� ���� ���������� �� ����������)
    double durationCall;//������������ ���������(������ �������� ���� ���������� �� ����������)

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
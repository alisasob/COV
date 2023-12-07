#pragma once
#include <string>
class View {
public:
    std::string render(const std::string& message) {
        return "<html><body>" + message + "</body></html>";
    }
};
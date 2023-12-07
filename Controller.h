#pragma once
#include "View.h"
#include "Model.h"
class Controller {
public:
    Controller(Model& model, View& view) : model(model), view(view) {}

    std::string handleRequest(std::string message) {
        return view.render(message);
    }

private:
    Model& model;
    View& view;
};

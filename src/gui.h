#pragma once

#include "datagrid.h"
#include "statusbar.h"
#include "graph.h"
#include "rocket.h"

class GUI {
public:
    void draw(int posX, int posY, int width, int height);

private:
    StatusBar status_bar;
    DataGrid data_grid;
    Graph graph;
    Rocket rocket;
};

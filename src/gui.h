#pragma once

#include "datagrid.h"
#include "statusbar.h"
#include "graph.h"
#include "rocket.h"
#include "gps.h"

class GUI {
public:
    void processEvents();
    void draw(int posX, int posY, int width, int height);
    ~GUI();

private:
    StatusBar status_bar;
    DataGrid data_grid;
    Graph graph;
    Rocket rocket;
    GPS gps;
};

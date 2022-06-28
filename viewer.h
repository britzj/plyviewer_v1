#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_viewer.h"

using std::vector;
using std::array;

class viewer : public QMainWindow
{
    Q_OBJECT

public:
    viewer(QWidget *parent = nullptr);
    ~viewer();

private slots:
    void openfile();
    void unloadfile();
    void calculatebounds();
    void viewAbout();


private:
    Ui::viewerClass ui;
    QString currentFile;
    double xpair[2] = { 0 }; // min, max, index min, index max
    double ypair[2] = { 0 };
    double zpair[2] = { 0 };
    int indexlist[6] = {0};
    std::vector<std::array<double, 3>> abounds;

public:
    vector<array<double, 3>> vertexPos;
    vector<vector<size_t>> faceInd;

};

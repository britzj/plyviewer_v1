#include "viewer.h"
#include <QFileDialog>
#include <qmessagebox.h>
#include <qtextstream.h>
#include <happly.h>


using std::vector;
using std::array;
using happly::PLYData;
using std::string;

viewer::viewer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QObject::connect(ui.actionOpen, &QAction::triggered, this, &viewer::openfile); // slot: browsing for file
    QObject::connect(ui.actionUnload, &QAction::triggered, this, &viewer::unloadfile); //slot: clear workspace
    QObject::connect(ui.buttCalcBound, &QPushButton::clicked, this, &viewer::calculatebounds); //slot: clear workspace
    QObject::connect(ui.actionAbout, &QAction::triggered, this, &viewer::viewAbout); //slot: view about
}

viewer::~viewer()
{}

void viewer::openfile() {  
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file"); //browse from directory
    QFile file(fileName);
    currentFile = fileName;

    // check if error opening file
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

     setWindowTitle("plyViewer: " + fileName);  

    //QTextStream in(&file);
    //QString text = in.readAll();
    //ui.textEdit->setText(text);
    file.close();
}

void viewer::unloadfile() {
    // clear memory and workspace
    setWindowTitle("plyViewer");
    ui.textEdit->clear();
    currentFile = " ";
}

void viewer::calculatebounds() {

    string filename = currentFile.toStdString();
    PLYData plyIn(filename, true);
    plyIn.validate();
    
    // Get vertex and indices
    vertexPos = plyIn.getVertexPositions();
    faceInd = plyIn.getFaceIndices();

    int n = vertexPos.size();
    int i, j;
    
    for (i = 0; i < n; i++) {
    
        // if the array only contains 1 coordinate
        if (i == 0) {
            xpair[0] = vertexPos[i][0];
            xpair[1] = xpair[0];

            ypair[0] = vertexPos[i][1];
            ypair[1] = ypair[0];

            zpair[0] = vertexPos[i][2];
            zpair[1] = zpair[0];
        }
        else {
            // find min and max x:
            if (vertexPos[i][0] < xpair[0]) { // min
                xpair[0] = vertexPos[i][0];
                indexlist[0] = i; // get index at which this has occured
                
            }
            if (vertexPos[i][0] > xpair[1]) { // max
                xpair[1] = vertexPos[i][0];
                indexlist[1] = i; //index
            }
            // y-coordinate
            if (vertexPos[i][1] < ypair[0]) { // min
                ypair[0] = vertexPos[i][1];
                indexlist[2] = i;
            }
            if (vertexPos[i][1] > ypair[1]) { // max
                ypair[1] = vertexPos[i][1];
                indexlist[3] = i;
            }
            // z-coordinate
            if (vertexPos[i][2] < zpair[0]) { // min
                zpair[0] = vertexPos[i][2];
                indexlist[4] = i;
            }
            if (vertexPos[i][2] > zpair[1]) { // max
                zpair[1] = vertexPos[i][2];
                indexlist[5] = i;
            }
        }
    }

    // assigning the xyz values from vertex array at min/max boundary points
    array<double, 3> a;
    for (j = 0; j < 6; j++) {

        a[0] = vertexPos[indexlist[j]][0];
        a[1] = vertexPos[indexlist[j]][1];
        a[2] = vertexPos[indexlist[j]][2];

        abounds.push_back(a);
    }

    ui.textEdit->clear();
    //ui.textEdit->setText();
    ui.textEdit->append("x, min: (" + QString::number(abounds[0][0]) + ", " + QString::number(abounds[0][1]) + ", " + QString::number(abounds[0][2]) + ")");
    ui.textEdit->append("x, max: (" + QString::number(abounds[1][0]) + ", " + QString::number(abounds[1][1]) + ", " + QString::number(abounds[1][2]) + ") \n");
    ui.textEdit->append("y, min: (" + QString::number(abounds[2][0]) + ", " + QString::number(abounds[2][1]) + ", " + QString::number(abounds[2][2]) + ")");
    ui.textEdit->append("y, max: (" + QString::number(abounds[3][0]) + ", " + QString::number(abounds[3][1]) + ", " + QString::number(abounds[3][2]) + ") \n");
    ui.textEdit->append("z, min: (" + QString::number(abounds[4][0]) + ", " + QString::number(abounds[4][1]) + ", " + QString::number(abounds[4][2]) + ")");
    ui.textEdit->append("z, max: (" + QString::number(abounds[5][0]) + ", " + QString::number(abounds[5][1]) + ", " + QString::number(abounds[5][2]) + ")");

}

void viewer::viewAbout() {

    QMessageBox::information(this, "To Ixus:", "Juan made this program and he thinks its cool!");
}

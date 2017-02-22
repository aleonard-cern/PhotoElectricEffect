#include "graph.h"

graph::graph(QCustomPlot *qcp_, const QString &title_, const QString& xLabel_, const QString &yLabel_):
    qcp(qcp_)
{
    qcp->addGraph();
    qcp->graph(0)->setPen(QPen(Qt::blue));
    qcp->graph(0)->setLineStyle(QCPGraph::lsNone);
    qcp->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
    qcp->graph(0)->setErrorType(QCPGraph::etValue);
    qcp->graph(0)->setErrorPen(QPen(Qt::black));
    qcp->graph(0)->setName("Efficiency");

    init(title_, xLabel_, yLabel_);

}

void graph::init(const QString &title_, const QString& xLabel_, const QString &yLabel_)
{

    max = 1;
    xMin = -1;
    xMax = 1;
    nPoints = 0;
    title = title_;
    xLabel = xLabel_;
    yLabel = yLabel_;

    qcp->graph(0)->setDataValueError(x, y, ey);
    qcp->rescaleAxes();
    qcp->xAxis->setLabel(xLabel);
    qcp->yAxis->setLabel(yLabel);
    qcp->xAxis->setRange(xMin*1.1, xMax*1.1);
    qcp->yAxis->setRange(-1.1, 1.1);
    qcp->axisRect()->setupFullAxesBox();

    // title
    qcp->plotLayout()->insertRow(0);
    qcp->plotLayout()->addElement(0, 0, new QCPPlotTitle(qcp, title));


    /*
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(180, 180, 180));
    plotGradient.setColorAt(1, QColor(150, 150, 150));
    qcp->setBackground(plotGradient);
    */
}


void graph::clearXY()
{

    x.clear();
    y.clear();
    ey.clear();
    nPoints = 0;

}

void graph::adjustPlot(double xMin_, double xMax_)
{

    xMin = xMin_;
    xMax = xMax_;

    qcp->graph(0)->setDataValueError(x, y, ey);

    qcp->rescaleAxes();
    qcp->xAxis->setRange(xMin*1.01, xMax*1.01);
    qcp->replot();

}

void graph::addPoint(double x_, double y_, double ey_)
{

    nPoints++;
    x.push_back(x_);
    y.push_back(y_);
    ey.push_back(ey_);


    if (nPoints == 1) {
        xMin = x_ - 0.15 * fabs(x_);
        xMax = x_ + 0.15 * fabs(x_);

        yMin = y_ - 0.15 * fabs(y_);
        yMax = y_ + 0.15 * fabs(y_);
    }
    else {
        if (xMin > x_) xMin = x_ - 0.15 * fabs(x_);
        if (xMax < x_) xMax = x_ + 0.15 * fabs(x_);
        if (yMin > y_) yMin = y_ - 0.15 * fabs(y_);
        if (yMax < y_) yMax = y_ + 0.15 * fabs(y_);
    }




    qcp->graph(0)->clearData();
    qcp->graph(0)->setDataValueError(x, y, ey);
    qcp->xAxis->setRange(xMin, xMax);
    qcp->yAxis->setRange(yMin, yMax);
    qcp->replot();
}

void graph::addEfficiencyPoint(double x_, uint num_, uint den_)
{
    if (den_ != 0) {
        addPoint(x_, num_*1.0/den_, sqrt(num_)*1.0/den_);
    }
    else {
        qDebug() << "Division by 0, denominator was null, skipin this point";
    }
}

void graph::clear()
{
    clearXY();
    adjustPlot(xMin, xMax);
}

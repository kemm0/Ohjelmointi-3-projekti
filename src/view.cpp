#include "view.hh"

View::View(QObject* parent) :
    QObject{parent},
    lineSeries_{} {
}

View::~View(){
    delete lineSeries_;
}

QtCharts::QLineSeries* View::getLineSeries() const{
    return lineSeries_;
}

void View::setLineSeries(QtCharts::QLineSeries *lineSeries){
    if (lineSeries_ == lineSeries) return;
    if (lineSeries_ && lineSeries_->parent() == this) delete lineSeries_;
    lineSeries_ = lineSeries;

    emit lineSeriesSignal();
}

void View::addData(){
    // tää varmaan yhdistetään jotenkin APIin :-D
    if (lineSeries_)
    {
        lineSeries_->append(
            x,
            y
        );
        x += 0.1;
        y += 0.01;
    }
}

void View::clearData(){
    if (lineSeries_)
    {
        lineSeries_->clear();
    }
}

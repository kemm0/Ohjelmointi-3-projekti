#include "appcontroller.hh"

AppController::AppController(QObject *parent) :
    QObject(parent),
    backend_(nullptr),
    gui_(nullptr)
{

}

void AppController::init(Backend *backend, QObject *gui)
{
    backend_ = backend;
    gui_ = gui;

    QObject::connect(gui_, SIGNAL(dataAdded(QVariant)), backend_, SLOT(fetchNewData(QVariant)));
    QObject::connect(gui_, SIGNAL(dataRemoved(QVariant)),backend_, SLOT(removeData(QVariant)));
    QObject::connect(gui_, SIGNAL(savePreferences(QVariant,QVariant)),backend_,SLOT(savePreferences(QVariant,QVariant)));
    QObject::connect(gui_, SIGNAL(loadPreferences(QVariant)),backend_,SLOT(loadPreferences(QVariant)));
    QObject::connect(gui_,SIGNAL(saveData(QVariant,QVariant,QVariant)),backend_,SLOT(saveData(QVariant,QVariant,QVariant)));
    QObject::connect(gui_,SIGNAL(loadData(QVariant)),backend_,SLOT(loadData(QVariant)));

    QObject::connect(backend_, SIGNAL(dataAdded(QVariant)), gui_,SLOT(addData(QVariant)));
    QObject::connect(backend_, SIGNAL(error(QVariant)), gui_,SLOT(showErrorMessage(QVariant)));
}

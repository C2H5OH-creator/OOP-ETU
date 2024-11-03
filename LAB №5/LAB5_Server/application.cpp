#include "application.h"

Application::Application(int argc, char *argv[])
    : QCoreApplication(argc, argv) {
    connect(communicator, &UDPCommunicator::messageReceived, this, &Application::handleMessage);
}

void Application::handleMessage(const QString &message){


/*
    if (changeRootButton->isChecked()){
        number root = Complex(changeInputRootReal->text().toDouble(),changeInputRootImaginary->text().toDouble());
        if(polynom.SetValue(0,->text().toUInt(),root)){
            QMessageBox::information(this, "Подтверждено", "Корень успешно изменён!");
        }
    }
    else{
        number value = Complex(changeInputAnReal->text().toDouble(),changeInputAnImaginary->text().toDouble());
        if(polynom.SetValue(1,0,value)){
            QMessageBox::information(this, "Подтверждено", "An успешно изменён!");
        }

    }
*/
}

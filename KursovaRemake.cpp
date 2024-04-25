#include "KursovaRemake.h"

#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>

#include "Engine.h"
#include "ICEngine.h"
#include "JetEngine.h"

KursovaRemake::KursovaRemake(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.EngineButton, SIGNAL(clicked()), this, SLOT(pressEngineButton()));
    connect(ui.ICEngine_button, SIGNAL(clicked()), this, SLOT(pressEngineButton()));
    connect(ui.JetEngine_button, SIGNAL(clicked()), this, SLOT(pressEngineButton()));

    connect(ui.Delete_button, SIGNAL(clicked()), this, SLOT(pressDelete()));

    connect(ui.radioButton_name, SIGNAL(clicked()), this, SLOT(radioButtons()));
    connect(ui.radioButton_power, SIGNAL(clicked()), this, SLOT(radioButtons()));
    connect(ui.radioButton_type, SIGNAL(clicked()), this, SLOT(radioButtons()));

    connect(ui.ready_button, SIGNAL(clicked()), this, SLOT(pressReady()));
    connect(ui.lineEdit, SIGNAL(editingFinished()), this, SLOT(lineEditCheck()));

    connect(ui.verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderChange()));


    //member initialization
    enginetype = EngineType::Engine;
    ui.EngineButton->setDisabled(true);
}


KursovaRemake::~KursovaRemake()
{
    ui.tableWidget->clear();

    qDeleteAll(engines);
    engines.clear();
}

void KursovaRemake::pressReady()
{
    const std::string temp = ui.lineEdit->text().toStdString();
    
    if (enginetype == EngineType::Engine)
    {
        engines.emplace_back(new Engine{ temp, (unsigned int)ui.spinBox->value()});
    }
    else if (enginetype == EngineType::ICEngine)
    {
        engines.emplace_back(new ICEngine{ temp, (unsigned int)ui.spinBox->value() });
    }
    else if (enginetype == EngineType::JetEngine)
    {
        engines.emplace_back(new JetEngine{ temp, (unsigned int)ui.spinBox->value() });
    }

    ui.tableWidget->setRowCount(ui.tableWidget->rowCount() + 1);

    ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 0,
        new QTableWidgetItem(engines[engines.size() - 1]->getName()
            .c_str()));

    ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 1,
        new QTableWidgetItem(std::to_string(engines[engines.size() - 1]->getPower())
            .c_str()));

    ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 2,
        new QTableWidgetItem(engines[engines.size() - 1]->getClassName()));

    QMessageBox messageBox;
    messageBox.setText("Engine has been created");
    messageBox.exec();

    ui.lineEdit->clear();
    ui.ready_button->setDisabled(true);

}

void KursovaRemake::pressDelete()
{
    ui.tableWidget->removeRow(ui.tableWidget->currentRow());
}

void KursovaRemake::radioButtons()
{
    if (ui.radioButton_name->isChecked())
    {
        ui.tableWidget->sortItems(0);
    }
    else if (ui.radioButton_power->isChecked())
    {
        //sort alghoritm should be implemented by yourself
        //By default it does not work
    }
    else if (ui.radioButton_type->isChecked())
    {
        ui.tableWidget->sortItems(2);
    }
}

void KursovaRemake::lineEditCheck()
{
    if (!ui.lineEdit->text().toStdString().empty())
    {
        ui.ready_button->setEnabled(true);
    }
    else
    {
        ui.ready_button->setDisabled(true);
    }
}

void KursovaRemake::sliderChange()
{
    if (!isRunning)
    {
        ui.sleeping_label->setText("RUNNING");
        isRunning = true;
    }
    else
    {
        ui.sleeping_label->setText("Sleeping");
        isRunning = false;
    }
        

}

void KursovaRemake::pressEngineButton()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString buttonLabel = button->text();


    if (buttonLabel.toStdString() == "Engine")
    {
        enginetype = EngineType::Engine;
        ui.EngineButton->setDisabled(true);
    
        ui.ICEngine_button->setEnabled(true);
        ui.JetEngine_button->setEnabled(true);
    }
    else if (buttonLabel.toStdString() == "ICEngine")
    {
        enginetype = EngineType::ICEngine;
        ui.ICEngine_button->setDisabled(true);

        ui.EngineButton->setEnabled(true);
        ui.JetEngine_button->setEnabled(true);
    }
    else if (buttonLabel.toStdString() == "JetEngine")
    {
        enginetype = EngineType::JetEngine;
        ui.JetEngine_button->setDisabled(true);

        ui.EngineButton->setEnabled(true);
        ui.ICEngine_button->setEnabled(true);
    }
}

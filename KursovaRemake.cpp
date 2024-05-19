#include "KursovaRemake.h"

#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>

#include "Engine.h"
#include "ICEngine.h"
#include "JetEngine.h"
#include <QFileDialog>
#include <iostream>

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

    connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFileAction()));
    connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveFileAction()));

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
    

    addEngine(temp, enginetype, (unsigned int)ui.spinBox->value());
    updateTable();

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

void KursovaRemake::saveFileAction()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "File Type (*.dat)");

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) 
        {
            QMessageBox::information(this, tr("Unable to save file"),
                file.errorString());
            return;
        }
        else
        {
            QTextStream out(&file);
            for (int i{ 0 }; i < engines.size(); ++i)
            {
                out << engines[i]->getName().c_str() << "," << engines[i]->getPower() << "," << engines[i]->getClassName() << '\n';
            }
            file.close();
        }
    }
}

void KursovaRemake::openFileAction()
{
    EngineMap engine = openFile();
    
    for (auto const& [key, value] : engine)
    {
        addEngine(key, value.second, value.first);
        updateTable();
    }

}

EngineMap KursovaRemake::openFile()
{
    QFile file(QFileDialog::getOpenFileName(this, "Select file", "", "Save files (*.dat)"));


    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "ErrorMessage", "Couldn't open the file");
        return {};
    }

    {
        qDeleteAll(engines);
        engines.clear();
        for (int i{ ui.tableWidget->rowCount() }; i >= 0; --i)
        {
            ui.tableWidget->removeRow(i);
        }
    }

    QTextStream in(&file);
    EngineMap engineLF;
    while (!in.atEnd())
    {
        QString temp;
        in >> temp;
        QStringList list = temp.split(",");
        if(list.size() >= 3)
        {
            engineLF[list[0].toStdString()] = std::make_pair(list[1].toInt(), toEngineType(list[2].toStdString()));
        }
    }
    
    file.flush();
    file.close();

    return engineLF;
}

inline EngineType KursovaRemake::toEngineType(std::string name) const
{
    if (name == "Engine")
    {
        return EngineType::Engine;
    }
    else if (name == "ICEngine")
    {
        return EngineType::ICEngine;
    }
    else if (name == "JetEngine")
    {
        return EngineType::JetEngine;
    }
    else
    {
        return EngineType::MAX_ENGINE;
    }
}

void KursovaRemake::addEngine(const std::string name, EngineType type, unsigned int value)
{
    if (type == EngineType::Engine)
    {
        engines.emplace_back(new Engine{ name, value });
    }
    else if (type == EngineType::ICEngine)
    {
        engines.emplace_back(new ICEngine{ name, value });
    }
    else if (type == EngineType::JetEngine)
    {
        engines.emplace_back(new JetEngine{ name, value });
    }
}

void KursovaRemake::updateTable()
{
    ui.tableWidget->setRowCount(ui.tableWidget->rowCount() + 1);

    ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 0,
        new QTableWidgetItem(engines[engines.size() - 1]->getName()
            .c_str()));

    ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 1,
        new QTableWidgetItem(std::to_string(engines[engines.size() - 1]->getPower())
            .c_str()));

    ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 2,
        new QTableWidgetItem(engines[engines.size() - 1]->getClassName()));
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

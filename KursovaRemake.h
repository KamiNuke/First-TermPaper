#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_KursovaRemake.h"

#include <qlist.h>
#include <qstring.h>

#include "IEngine.h"
#include "overloadFunctions.h"

using EngineMap = std::map<std::string, std::pair<unsigned int, EngineType>>;

class KursovaRemake : public QMainWindow
{
    Q_OBJECT

public:
    KursovaRemake(QWidget *parent = nullptr);
    ~KursovaRemake();

private slots:
    void pressEngineButton();
    void pressReady();
    void pressDelete();
    void radioButtons();
    void lineEditCheck();

    void sliderChange();
    
    void saveFileAction();
    void openFileAction();

private:
    EngineMap openFile();

    inline EngineType toEngineType(std::string name) const;

    void addEngine(const std::string name, EngineType type, unsigned int value);
    void updateTable();
private:
    bool isRunning{ false };

    QList<IEngine*> engines;
    EngineType enginetype;
    Ui::KursovaRemakeClass ui;
};

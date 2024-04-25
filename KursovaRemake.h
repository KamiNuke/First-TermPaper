#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_KursovaRemake.h"

#include <qlist.h>

#include "IEngine.h"

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
private:
    bool isRunning{ false };

    QList<IEngine*> engines;
    EngineType enginetype{ EngineType::MAX_ENGINE };
    Ui::KursovaRemakeClass ui;
};

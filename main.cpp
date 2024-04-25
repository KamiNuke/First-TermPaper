#include "KursovaRemake.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KursovaRemake w;
    w.show();
    return a.exec();
}

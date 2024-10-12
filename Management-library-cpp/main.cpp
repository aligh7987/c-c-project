#include "Login.h"
#include "LibraryManager.h"
#include "Member.h"
#include "Admin.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QFontDatabase>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //import manager in file
LibraryManager wm ;
QFile fi("manager.txt");
fi.open(QFile::ReadOnly);
if(fi.size() ==0){
    wm.writeInManagerFile("HelloWorld","1",1);
}
fi.close();

    //for design app
    QPalette pal =a.palette();
    pal.setColor(QPalette::Window, Qt::white);
    a.setPalette(pal);
    int id = QFontDatabase::addApplicationFont(":/font/fonts/Shabnam-Bold.ttf");
    if(id != -1){
        QStringList font_families = QFontDatabase::applicationFontFamilies(id);
    a.setFont(QFont(font_families,14,QFont::Normal),nullptr);
    }
    //ta inja.
    Login w;
    w.exec();

return a.exec();
}

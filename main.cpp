#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QtSql>
#include <ui_mainwindow.h>
//#include "seconnectermysql.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "NotreProjet_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow NotreInterface;
    NotreInterface.show();
//    if(!NotreConnection())
//       exit(-1);
//    NotreTableHache Table(100);
//    Table.charger();
//   // Table.sauvegarder();
//    Table.affiche();
//    std::cout<<Table.size();
//    QString c, q;
//    c="Toyota";
//    q="v001";
//    Table.suppression(c,q);
//    Table.affiche();
//    std::cout<< Table.size();
    return a.exec();
}

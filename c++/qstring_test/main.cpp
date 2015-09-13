#include <iostream>

//#include <QCoreApplication>
#include <QString>

using namespace std;

int main(int argc, char *argv[])
{
    QString hello = QString("%1 %2").arg("hello", "world");
    //QCoreApplication a(argc, argv);

    cout << hello.toStdString() << endl;
    //exit(a.exec());
    exit(EXIT_SUCCESS);
}


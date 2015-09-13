#include <iostream>

#include <QCoreApplication>

#include <QString>
#include <QStringList>

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	QCoreApplication::setApplicationName("Hello World!");
	QCoreApplication::setApplicationVersion("0.0");

	QStringList args = app.arguments();

	cout << "Command line: " << args.join(" ").toStdString() << endl;
	cout << "PID: " << app.applicationPid() << endl;

	// app.exec(); // main loop
	app.exit(0);
}


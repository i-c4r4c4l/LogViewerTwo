#ifndef LOGVIEWERTWO_H
#define LOGVIEWERTWO_H

#include <QMainWindow>
#include <QDir>

const QString LOGS_PATH = "C:\\DEV\\Qt\\LogViewerTwo\\settings.ini";
const QString RESOURCE_PATH = "C:\\DEV\\Qt\\LogViewerTwo\\icons\\";

QT_BEGIN_NAMESPACE
namespace Ui { class LogViewerTwo; }
QT_END_NAMESPACE

class LogViewerTwo : public QMainWindow
{
    Q_OBJECT

public:
    LogViewerTwo(QWidget *parent = nullptr);
    ~LogViewerTwo();


private slots:
    void on_chkLog_stateChanged(int state);

    void on_chkMilling_stateChanged(int state);

    void on_chkAll_stateChanged(int state);

    void on_btnExit_clicked();

    void on_btnSearch_clicked();

private:
    Ui::LogViewerTwo *ui;

    QStringList openedFilePaths;
    QString lastOpenedDir = QDir::homePath();

    void filterFileList();
    void autoLoadFolder();
};
#endif // LOGVIEWERTWO_H

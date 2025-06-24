#include "logviewertwo.h"
#include "ui_logviewertwo.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QListWidget>
#include <QTextEdit>
#include <QApplication>
#include <QFileDialog>
#include <QTextStream>
#include <QScrollBar>
#include <QIcon>
#include <QTimer>
#include <QSettings>
#include <QDebug>

LogViewerTwo::LogViewerTwo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogViewerTwo)
{

    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground, false);
    setAutoFillBackground(true);

    QPalette pal;
    pal.setColor(QPalette::Window, QColor("#f0f0f0"));  // light grey
    setPalette(pal);



    ui->centralwidget->setFixedSize(1204, 768);
    setWindowTitle("Log Viewer");
    setWindowIcon(QIcon(RESOURCE_PATH + "log.png"));

    QFont defaultFont("Segoe UI", 10);
    QApplication::setFont(defaultFont);

    QTimer::singleShot(0, this, &LogViewerTwo::autoLoadFolder);



    QWidget *central = ui->centralwidget;

    QWidget *header = ui->wgtHeader;
    header->setStyleSheet("background-color: #0d1a4a; border-radius: 8px;");
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    ui->lblTitle->setStyleSheet("color: white; font-size: 30px; font-weight: bold; font-style: italic;");

    ui->btnExit->setFixedSize(60, 60);
    ui->btnExit->setIcon(QIcon(RESOURCE_PATH + "exit.png"));
    ui->btnExit->setIconSize(QSize(60, 60));

    ui->btnExit->setStyleSheet(R"(
        QPushButton {
            background-color: transparent;
            border: none;
        }
        QPushButton:hover {
            background-color: rgba(44, 125, 125, 0.1);
            border-radius: 8px;
        }
    )");

    headerLayout->addWidget(ui->lblTitle);
    headerLayout->addStretch();
    headerLayout->addWidget(ui->btnExit);

    // Filter Row
    QWidget *filterBar = ui->wgtFilter;
    QHBoxLayout *filterLayout = new QHBoxLayout(filterBar);
    filterLayout->setContentsMargins(10, 10, 10, 10);
    filterLayout->setSpacing(15);

    QString checkBoxStyle = R"(
        QCheckBox {
            spacing: 10px;
            font-size: 24px;
            font-weight: bold;
            color: #1a237e;
            padding: 6px 20px 6px 12px; /* extra right padding to prevent clipping */
            border-radius: 8px;
            background-color: transparent;
            min-width: 70px; /* ensure label fits like "All" */
        }

        QCheckBox::indicator {
            width: 18px;
            height: 18px;
        }

        QCheckBox::indicator:unchecked {
            border: 2px solid #1a237e;
            background-color: transparent;
            border-radius: 4px;
        }

        QCheckBox::indicator:checked {
            background-color: #1a237e;
            border-radius: 4px;
        }

        QCheckBox:hover {
            background-color: #e3f2fd;
        }
    )";

    ui->chkLog->setStyleSheet(checkBoxStyle);
    ui->chkMilling->setStyleSheet(checkBoxStyle);
    ui->chkAll->setStyleSheet(checkBoxStyle);

    ui->fromDateEdit->setDate(QDate::currentDate());
    ui->toDateEdit->setDate(QDate::currentDate());

    ui->fromDateEdit->setDisplayFormat("yy/MM/dd");
    ui->fromDateEdit->setCalendarPopup(true);
    ui->fromDateEdit->setFixedWidth(150);

    ui->toDateEdit->setDisplayFormat("yy/MM/dd");
    ui->toDateEdit->setCalendarPopup(true);
    ui->toDateEdit->setFixedWidth(150);

    ui->fromDateEdit->setStyleSheet(R"(
        QDateEdit {
            font-size: 13px;
            padding: 6px 10px;
            border: 1px solid #;
            border-radius: 6px;
            background-color: #1a237e;
        }
    )");

    ui->toDateEdit->setStyleSheet(R"(
        QDateEdit {
            font-size: 13px;
            padding: 6px 10px;
            border: 1px solid #ccc;
            border-radius: 6px;
            background-color: #1a237e;
        }
    )");

    QString dateEditStyle = R"(
        QLineEdit {
            font-size: 15px;
            padding: 4px 8px;
            border: 1px solid #ccc;
            border-radius: 4px;
        }
    )";

    QString calendarStyle = R"(
        QDateEdit {
            font-size: 18px;
            padding: 6px 10px;
            border: 1px solid #ccc;
            border-radius: 6px;
            color: #0d1a4a;
        }

        QCalendarWidget QWidget {
            color: #0d1a4a;  /* Default text color (placeholder-like) */
        }

        QCalendarWidget QAbstractItemView {
            selection-background-color: #1a237e;
            selection-color: white;
            font-weight: bold;
        }

        QCalendarWidget QToolButton {
            color: white;
            background-color: transparent;
        }

        QCalendarWidget QWidget#qt_calendar_navigationbar {
            background-color: #0d1a4a;
            color: white;
        }
    )";


    ui->fromDateEdit->setStyleSheet(calendarStyle);
    ui->toDateEdit->setStyleSheet(calendarStyle);
    //ui->fromDateEdit->setStyleSheet(dateEditStyle);
    //ui->toDateEdit->setStyleSheet(dateEditStyle);

    ui->btnSearch->setFixedSize(95, 45);
    ui->btnSearch->setStyleSheet(R"(
        QPushButton {
            font-size: 22px;
            font-weight: bold;
            padding: 6px 14px;
            background-color: #0d1a4a;
            color: white;
            border-radius: 5px;
        }
        QPushButton:hover {
            background-color: #1a237e;
        }
    )");

    QSpacerItem *spaceBetweenButtonsAndCheckboxes = new QSpacerItem(
        40, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);
    filterLayout->addItem(spaceBetweenButtonsAndCheckboxes);




    filterLayout->addWidget(ui->chkLog);
    filterLayout->addWidget(ui->chkMilling);
    filterLayout->addWidget(ui->chkAll);
    ui->chkAll->setChecked(true);
    filterLayout->addStretch();

    filterLayout->addWidget(ui->fromDateEdit);
    filterLayout->addWidget(ui->toDateEdit);
    filterLayout->addWidget(ui->btnSearch);

    // Split View
    QHBoxLayout *splitLayout = new QHBoxLayout;
    ui->fileContentViewer->setReadOnly(true);

    splitLayout->addWidget(ui->fileListWidget, 3);
    splitLayout->addWidget(ui->fileContentViewer, 6);

    ui->fileListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->fileListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->fileListWidget->setWordWrap(true);
    ui->fileListWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->fileContentViewer->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->fileContentViewer->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->fileContentViewer->setLineWrapMode(QTextEdit::NoWrap);

    ui->fileListWidget->setStyleSheet(R"(
        QListWidget {
            border-radius: 8px;
            border: 1px solid rgba(44, 125, 125, 0.8);
        }

        QListWidget::item {
            padding: 6px 14px;
            margin: 4px 0;
            border-radius: 6px;
        }

        QListWidget::item:selected {
            background-color: #2c7d7d;
            color: white;
        }

        QListWidget::item:hover {
            background-color: #379f9f;
        }
    )");

    ui->fileContentViewer->setStyleSheet(R"(
        QTextEdit {
            border: 1px solid rgba(44, 125, 125, 0.8);
            border-radius: 6px;
            padding: 6px;
        }
    )");

     QString scrollStyle = R"(
        QScrollBar:vertical {
            background: #f5f5f5;
            width: 25px;
            height: 40px;
            margin: 0px;
            border-radius: 10px;
        }

        QScrollBar::handle:vertical {
            background: rgba(44, 125, 125, 0.2);
            height: 40px;
            border-radius: 10px;
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }

        QScrollBar:horizontal {
            background: #f5f5f5;
            height: 25px;
            margin: 0px;
            border-radius: 10px;
        }

        QScrollBar::handle:horizontal {
            background: rgba(44, 125, 125, 0.2);
            max-width: 40px;
            border-radius: 10px;
        }

        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
            width: 0px;
        }

        QScrollBar::handle:vertical:hover {
            background: rgba(44, 125, 125, 0.4);
        }

        QScrollBar::handle:horizontal:hover {
             background: rgba(44, 125, 125, 0.4);
        }
    )";

    ui->fileListWidget->verticalScrollBar()->setStyleSheet(scrollStyle);
    ui->fileListWidget->horizontalScrollBar()->setStyleSheet(scrollStyle);
    ui->fileContentViewer->verticalScrollBar()->setStyleSheet(scrollStyle);
    ui->fileContentViewer->horizontalScrollBar()->setStyleSheet(scrollStyle);

    ui->lblFileList->setStyleSheet(R"(
                                        color: #1e3c40;
                                        font-weight: bold;
                                   )");
    ui->lblFileContents->setStyleSheet(R"(
                                        color: #1e3c40;
                                        font-weight: bold;
                                   )");


    connect(ui->fileListWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        QString clickedFileName = item->text();

        for (const QString &path : openedFilePaths)
        {
            if (QFileInfo(path).fileName() == clickedFileName)
            {
                QFile file(path);
                if (file.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    QTextStream in(&file);
                    ui->fileContentViewer->clear();
                    ui->fileContentViewer->setCurrentFont(QFont("Segoe UI", 10));
                    ui->fileContentViewer->setPlainText(in.readAll());
                }
                break;
            }
        }
    });

    setCentralWidget(central);

}

LogViewerTwo::~LogViewerTwo()
{
    delete ui;
}

void LogViewerTwo::filterFileList()
{
    ui->fileListWidget->clear();
    for (const QString &path : openedFilePaths)
    {
        QString fileName = QFileInfo(path).fileName();

        if (ui->chkAll->isChecked())
        {
            ui->fileListWidget->addItem(fileName);
        }
        else if (ui->chkLog->isChecked() && fileName.endsWith(".csv", Qt::CaseSensitive))
        {
            ui->fileListWidget->addItem(fileName);
        }
        else if (ui->chkMilling->isChecked() && fileName.endsWith(".ini", Qt::CaseSensitive))
        {
            ui->fileListWidget->addItem(fileName);
        }
    }

    ui->fileContentViewer->clear();
}

void LogViewerTwo::on_btnExit_clicked()
{
    close();
}

void LogViewerTwo::on_chkLog_stateChanged(int state)
{
    if (state == Qt::Checked)
    {
        ui->chkMilling->setChecked(false);
        ui->chkAll->setChecked(false);
    }
    else if (!ui->chkMilling->isChecked() && !ui->chkAll->isChecked())
    {
        ui->chkLog->setChecked(true);
    }

    filterFileList();
}

void LogViewerTwo::on_chkMilling_stateChanged(int state)
{
    if (state == Qt::Checked)
    {
        ui->chkLog->setChecked(false);
        ui->chkAll->setChecked(false);
    }
    else if (!ui->chkLog->isChecked() && !ui->chkAll->isChecked())
    {
        ui->chkMilling->setChecked(true);
    }

    filterFileList();
}

void LogViewerTwo::on_chkAll_stateChanged(int state)
{
    if (state == Qt::Checked)
    {
        ui->chkLog->setChecked(false);
        ui->chkMilling->setChecked(false);
    }
    else if (!ui->chkLog->isChecked() && !ui->chkMilling->isChecked())
    {
        ui->chkAll->setChecked(true);
    }

    filterFileList();
}

void LogViewerTwo::autoLoadFolder()
{
    QSettings settings(LOGS_PATH, QSettings::IniFormat);
    QString logsFolder = settings.value("LOGS_PATH").toString();

    QDir dir(logsFolder);
    if (!dir.exists())
    {
        qDebug() << "Folder does not exist: " + logsFolder;
        return;
    }

    QStringList filters;
    filters << "*.csv" << "*.ini";

    QStringList files = dir.entryList(filters, QDir::Files, QDir::Time);

    openedFilePaths.clear();
    ui->fileListWidget->clear();

    for (const QString &file : files)
    {
        QString fullPath = dir.absoluteFilePath(file);
        openedFilePaths.append(fullPath);
        ui->fileListWidget->addItem(file);
    }

    filterFileList();

    ui->fileContentViewer->clear();
    qDebug() << "Loaded from settings.ini path: " << logsFolder;

}

void LogViewerTwo::on_btnSearch_clicked()
{
    QDate fromDate = ui->fromDateEdit->date();
    QDate toDate = ui->toDateEdit->date();

    QStringList dateStrings;
    for (QDate d = fromDate; d <= toDate; d = d.addDays(1))
    {
        dateStrings.append(d.toString("yyMMdd"));
        dateStrings.append(d.toString("yyyy-MM-dd"));
        dateStrings.append(d.toString("yy/MM/dd"));
        dateStrings.append(d.toString("yyyy/MM/dd"));
    }

    ui->fileListWidget->clear();
    ui->fileContentViewer->clear();

    for (const QString &path : openedFilePaths)
    {
        QString fileName = QFileInfo(path).fileName();

        if (ui->chkLog->isChecked() && !fileName.endsWith(".csv", Qt::CaseSensitive))
            continue;
        if (ui->chkMilling->isChecked() && !fileName.endsWith(".ini", Qt::CaseSensitive))
            continue;

        bool matches = std::any_of(dateStrings.begin(), dateStrings.end(),
            [&] (const QString &dateStr) { return fileName.contains(dateStr); });

        if (matches)
        {
            ui->fileListWidget->addItem(fileName);
        }

    }

    qDebug() << "Filtered & searched files: " + QString::number(ui->fileListWidget->count());
}

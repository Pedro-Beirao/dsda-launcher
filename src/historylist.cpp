#include "historylist.h"
#include "mainwindow.h"
#include "states.h"
#include "ui_historylist.h"

historyList::historyList(QWidget *parent) : QWidget(parent), ui(new Ui::historyList)
{
    ui->setupUi(this);

    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(fooo3()));
    shortcut3->setAutoRepeat(false);

    init_historyPath();
}

historyList::~historyList() { delete ui; }

void historyList::init_historyPath()
{
#if defined Q_OS_WIN
    historyPath = QCoreApplication::applicationDirPath() + "\\history.states";
#else
    historyPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.dsda-doom/history.states";
#endif
}

void historyList::getHistory()
{
    ui->history_listWidget->clear();

    QFile file(historyPath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;

    QTextStream stream(&file);
    QString buffer;

    stream.readLineInto(&buffer);
    if (buffer != HISTORY_HEADER)
    {
        file.close();
        return;
    }

    while (buffer != "-" && !stream.atEnd())
    {
        stream.readLineInto(&buffer);
    }

    while (!stream.atEnd())
    {
        stream.readLineInto(&buffer);
        QString iwad;
        QString warp_1;
        QString warp_2;
        QString pwads;
        QString recordDemo;
        QString playbackDemo;
        QString playbackDemoType;
        while (buffer != "-" && !stream.atEnd())
        {
            buffer = buffer.trimmed();

            QString buffer_name;
            QString buffer_value;

            int pos = buffer.indexOf(' ');
            if (pos != -1)
            {
                buffer_name = buffer.mid(0, pos).trimmed();
                buffer_value = buffer.mid(pos + 1).trimmed();
            }

            if (buffer_name == "iwad") iwad = buffer_value;
            else if (buffer_name == "warp1") warp_1 = buffer_value;
            else if (buffer_name == "warp2") warp_2 = buffer_value;
            else if (buffer_name == "pwad") pwads += getFileName(buffer_value) + " ";
            else if (buffer_name == "record") recordDemo = buffer_value;
            else if (buffer_name == "playback") playbackDemo = buffer_value;
            else if (buffer_name == "demodropdown")
            {
                if (buffer_value == '0') playbackDemoType = "Playdemo ";
                else if (buffer_value == '1') playbackDemoType = "Timedemo ";
                else if (buffer_value == '2') playbackDemoType = "Fastdemo ";
            }

            stream.readLineInto(&buffer);
        }

        QString title = iwad;

        QString level = createLevelString(warp_1, warp_2);

        if (!level.isEmpty()) title += " - " + level;
        if (!pwads.isEmpty()) title += "\n" + pwads;
        if (!recordDemo.isEmpty()) title += "\nRecord " + getFileName(recordDemo);
        if (!playbackDemo.isEmpty()) title += "\n" + playbackDemoType + getFileName(playbackDemo);

        ui->history_listWidget->insertItem(0, title);
    }

    file.close();

    ui->history_listWidget->setCurrentRow(0);
}

void historyList::on_history_listWidget_currentRowChanged(int currentRow)
{
    ui->iwad_label->clear();
    ui->complevel_label->clear();
    ui->difficulty_label->clear();
    ui->level_label->clear();
    ui->pwads_label->clear();
    ui->demo_label->clear();
    ui->extra_label->clear();
    ui->timestamp_label->clear();

    QFile file(historyPath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;

    QTextStream stream(&file);
    QString buffer;
    while (buffer != "-" && !stream.atEnd())
    {
        stream.readLineInto(&buffer);
    }

    int count = 0;
    QString warp1, warp2, recordDemo_s, playbackDemo_s, playbackDemo_t;

    while (!stream.atEnd())
    {
        stream.readLineInto(&buffer);

        if (buffer == "-") count++;
        if (count != ui->history_listWidget->count() - 1 - currentRow) continue;

        buffer = buffer.trimmed();

        QString buffer_name, buffer_value;

        int pos = buffer.indexOf(' ');
        if (pos != -1)
        {
            buffer_name = buffer.mid(0, pos).trimmed();
            buffer_value = buffer.mid(pos + 1).trimmed();
        }

        if (buffer_name == "iwad") ui->iwad_label->setText(buffer_value);
        else if (buffer_name == "complevel") ui->complevel_label->setText(buffer_value);
        else if (buffer_name == "warp1") warp1 = buffer_value;
        else if (buffer_name == "warp2") warp2 = buffer_value;
        else if (buffer_name == "skill") ui->difficulty_label->setText("Skill " + buffer_value);
        else if (buffer_name == "pwad") ui->pwads_label->setText(ui->pwads_label->text() + getFileName(buffer_value) + "\n");
        else if (buffer_name == "record") recordDemo_s = "Record\n" + getFileName(buffer_value) + "\n";
        else if (buffer_name == "playback") playbackDemo_s = getFileName(buffer_value) + "\n";
        else if (buffer_name == "demodropdown")
        {
            if (buffer_value == '0') playbackDemo_t = "Playdemo\n";
            else if (buffer_value == '1') playbackDemo_t = "Timedemo\n";
            else if (buffer_value == '2') playbackDemo_t = "Fastdemo\n";
        }
        else if (buffer_name == "box1" && buffer_value == "true") ui->extra_label->setText(ui->extra_label->text() + " " + MainWindow::pMainWindow->toggle1_checkBox()->toolTip());
        else if (buffer_name == "box2" && buffer_value == "true") ui->extra_label->setText(ui->extra_label->text() + " " + MainWindow::pMainWindow->toggle2_checkBox()->toolTip());
        else if (buffer_name == "box3" && buffer_value == "true") ui->extra_label->setText(ui->extra_label->text() + " " + MainWindow::pMainWindow->toggle3_checkBox()->toolTip());
        else if (buffer_name == "box4" && buffer_value == "true") ui->extra_label->setText(ui->extra_label->text() + " " + MainWindow::pMainWindow->toggle4_checkBox()->toolTip());
        else if (buffer_name == "additional") ui->extra_label->setText(ui->extra_label->text() + " " + buffer_value);
        else if (buffer_name == "timestamp") ui->timestamp_label->setText(buffer_value);
    }

    ui->level_label->setText(createLevelString(warp1, warp2));
    if (ui->level_label->text().isEmpty()) ui->difficulty_label->clear();

    if (!recordDemo_s.isEmpty()) ui->demo_label->setText(recordDemo_s);
    else if (!playbackDemo_s.isEmpty()) ui->demo_label->setText(playbackDemo_t + playbackDemo_s);

    file.close();
}

void historyList::fooo3() // CTRL+W runs this function close the active window
{
    QWidget *currentWindow = QApplication::activeWindow();
    currentWindow->close();
}

void historyList::on_load_pushButton_clicked()
{
    QFile file(historyPath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;

    int c = -1;

    QTextStream stream(&file);
    QString buffer;
    while (!stream.atEnd())
    {
        stream.readLineInto(&buffer);
        if (buffer == "-")
        {
            c++;
        }
        if (c == ui->history_listWidget->count()-1-ui->history_listWidget->currentRow())
        {
            states::loadStateNew(stream);
            break;
        }
    }

    file.close();
}

// Removed this feature, for now atleast
void historyList::on_launch_pushButton_clicked()
{
    QStringList argList;

    QFile file(historyPath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;

    QTextStream stream(&file);
    QString buffer;

    while (!stream.atEnd())
    {
        stream.readLineInto(&buffer);
        buffer = buffer.trimmed();

        QString buffer_name;
        QString buffer_value;

        int pos = buffer.indexOf(' ');
        if (pos != -1)
        {
            buffer_name = buffer.mid(0, pos).trimmed();
            buffer_value = buffer.mid(pos + 1).trimmed();
        }

        if (buffer_name == "iwad") // iwad
        {
            argList.append("-iwad");
            argList.append(MainWindow::pMainWindow->iwad_comboBox()->itemData(MainWindow::pMainWindow->iwad_comboBox()->findText(buffer_value), Qt::ToolTip).toString());
        }
        else if (buffer_name == "complevel") // complevel
        {
            if (buffer_value == "Default") continue;

            int cl_pos = buffer_value.indexOf(' ');
            if (cl_pos != -1)
            {
                argList.append("-complevel");
                argList.append(buffer_value.mid(0, cl_pos));
            }
        }
        else if (buffer_name == "warp1") // warp 1
        {
            argList.append("-warp");
            argList.append(buffer_value);
        }
        else if (buffer_name == "warp2") // warp 2
        {
            if (argList.at(argList.count() - 2) != "-warp") continue;

            argList.append(buffer_value);
        }
        else if (buffer_name == "skill") // skill
        {
            if (buffer_value == '0') continue;

            argList.append("-warp");
            argList.append(buffer_value);
        }
        else if (buffer_name == "box1") // box1
        {
            if (string_to_bool(buffer_value)) argList.append(MainWindow::pMainWindow->toggle1_checkBox()->toolTip().split(';'));
        }
        else if (buffer_name == "box2") // box2
        {
            if (string_to_bool(buffer_value)) argList.append(MainWindow::pMainWindow->toggle2_checkBox()->toolTip().split(';'));
        }
        else if (buffer_name == "box3") // box3
        {
            if (string_to_bool(buffer_value)) argList.append(MainWindow::pMainWindow->toggle3_checkBox()->toolTip().split(';'));
        }
        else if (buffer_name == "box4") // box4
        {
            if (string_to_bool(buffer_value)) argList.append(MainWindow::pMainWindow->toggle4_checkBox()->toolTip().split(';'));
        }
        else if (buffer_name == "resolution") // resolution
        {
        }
        else if (buffer_name == "fullscreen") // fullscreen
        {
        }
        else if (buffer_name == "hud") // hud
        {
        }
        else if (buffer_name == "config") // config
        {
        }
        else if (buffer_name == "track") // track
        {
        }
        else if (buffer_name == "time") // time
        {
        }
        else if (buffer_name == "pwad") // pwad
        {
        }
        else if (buffer_name == "record") // record demo
        {
        }
        else if (buffer_name == "playback") // playback demo
        {
        }
        else if (buffer_name == "demodropdown") // demo drop down
        {
        }
        else if (buffer_name == "viddump") // demo drop down
        {
        }
        else if (buffer_name == "additional") // additional arguments
        {
        }
        else if (buffer_name == "-")
        {
            return;
        }
    }

    file.close();

    MainWindow::pMainWindow->Launch(argList);
}

#include "mainwindow.h"

QSettings *settings;
MainWindow *MainWindow::pMainWindow = nullptr;

void MainWindow::changeExeName(QString newName) { exeName = newName; }

void MainWindow::showSSLDialog()
{
    QMessageBox msgBox;
    msgBox.setText("SSL library not found. Network features not available.");
    msgBox.setInformativeText("It should have been packaged with the Launcher.\nIf reinstalling does not fix this, try manually installing OpenSSL.\n\nlibssl-1_1-x64.dll + libcrypto-1_1-x64.dll");
    msgBox.addButton(tr("Ok"), QMessageBox::NoRole);
    msgBox.exec();
}

void MainWindow::changeButtonColor(bool isDark)
{
#ifdef __APPLE__
    if (isDark)
    {
        ui->showCommandLine_pushButton->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                                      "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");
        ui->tooltip_pushButton->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                              "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");
        ui->additionalArguments_pushButton->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); border-radius:5px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                                          "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); border-radius:5px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");
        ui->nextPage_pushButton->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); border-radius:5px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                               "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); border-radius:5px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");
        ui->previousPage_pushButton->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); border-radius:5px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                                   "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); border-radius:5px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");
    }
    else
    {
        ui->showCommandLine_pushButton->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                                      "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(223,223,223); color: rgb(13,13,13)}");
        ui->tooltip_pushButton->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                              "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(223,223,223); color: rgb(13,13,13)}");
        ui->additionalArguments_pushButton->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); border-radius:5px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                                          "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); border-radius:5px; background-color: rgb(223,223,223); color: rgb(13, 13, 13)}");
        ui->nextPage_pushButton->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); border-radius:5px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                               "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); border-radius:5px; background-color: rgb(223,223,223); color: rgb(13, 13, 13)}");
        ui->previousPage_pushButton->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); border-radius:5px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                                   "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); border-radius:5px; background-color: rgb(223,223,223); color: rgb(13, 13, 13)}");
    }
#endif
}

// Prevents launching the game twice if the button "Launch" is pressed twice quickly
void MainWindow::delayLaunch() { canLaunch = true; }

// MainWindow
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::pMainWindow = this;

    execPath = QCoreApplication::applicationDirPath();

    // Allow files to be droped in the launcher (*.wad *.lmp *.deh *.bex)
    setAcceptDrops(true);

    // Add event filter to the "additional arguments" box
    ui->additionalArguments_textEdit->installEventFilter(this);

    // Add event filter to the Launch button. This will allow you to see the current parameters when you hover your mouse
    ui->launchGame_pushButton->installEventFilter(this);

    // set the settings and console windows
    settingsWindow = new Settings;
    consoleWindow = new Console;
    historyListWindow = new historyList;
    endoomWindow = new endoom;

    // The "episode" and "level" boxes can only take 2 numbers
    // This approach also prevents a problem where Qt tried to add spaces to those boxes if no numbers were added
    QRegularExpression rgx("[0-9]{2}");
    QValidator *comValidator = new QRegularExpressionValidator(rgx, this);
    ui->episode_lineEdit->setValidator(comValidator);
    ui->level_lineEdit->setValidator(comValidator);

    ui->stackedWidget->setAttribute(Qt::WA_TranslucentBackground);

#ifdef _WIN32
    ui->tooltip_textBrowser->setHtml(
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:8pt; font-weight:400; font-style:normal;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" "
        "font-size:8pt;\">Don't see any IWAD?     ^</span></p><p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Go to the settings and add the folder you have your IWADs in, to the </span><span style=\" font-size:9pt; "
        "font-weight:700;\">IWAD Folders</span><span style=\" font-size:8pt;\"> list.</span></p><p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Then restart the Launcher</span></p></body></html>");
#endif

    // Keyboard shortcut
    // Qt::CTRL is the CTRL key for Windows/Linux and is the CMD key for MacOS

    // Closes the active window
    QShortcut *shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL), this, SLOT(close()));
    shortcut3->setAutoRepeat(false);

    findIwads();

    loadSettings();

    setStyles();

    QStringList arguments = qApp->arguments();
    for (int i = 1; i < arguments.count(); i++)
    {
        dropFile(arguments.at(i));
    }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::loadSettings()
{
    // Set the parameters text correctly
    if (!settings->value("toggle1a").isNull())
    {
        setToggles(settings->value("toggle1t").toString(), settings->value("toggle1a").toString(), settings->value("toggle2t").toString(), settings->value("toggle2a").toString(), settings->value("toggle3t").toString(), settings->value("toggle3a").toString(), settings->value("toggle4t").toString(), settings->value("toggle4a").toString());
    }
    else
    {
        setToggles(DEFAULT_TOGGLE1ARG, DEFAULT_TOGGLE1TEXT, DEFAULT_TOGGLE2ARG, DEFAULT_TOGGLE2TEXT, DEFAULT_TOGGLE3ARG, DEFAULT_TOGGLE3TEXT, DEFAULT_TOGGLE4ARG, DEFAULT_TOGGLE4TEXT);
    }

    // Load settings and apply them
    if (settings->value("remember").toBool())
    {
        // Top
        ui->iwad_comboBox->setCurrentIndex(settings->value("iwad").toInt());
        ui->complevel_comboBox->setCurrentIndex(settings->value("complevel").toInt());
        ui->difficulty_comboBox->setCurrentIndex(settings->value("skill").toInt());
        ui->episode_lineEdit->setText(settings->value("warp1").toString());
        ui->level_lineEdit->setText(settings->value("warp2").toString());
        if (!settings->value("maxskilllevel").isNull()) setMaxSkillLevel(settings->value("maxskilllevel").toInt());

        // Options
        ui->toggle1_checkBox->setChecked(settings->value("fast").toBool());
        ui->toggle2_checkBox->setChecked(settings->value("nomo").toBool());
        ui->toggle3_checkBox->setChecked(settings->value("respawn").toBool());
        ui->toggle4_checkBox->setChecked(settings->value("solonet").toBool());
        ui->fullscreen_checkBox->setChecked(settings->value("fullscreen").toBool());
        ui->resolution_comboBox->setCurrentIndex(settings->value("geom").toInt());
        ui->hud_lineEdit->setText(settings->value("hud").toString());
        ui->config_lineEdit->setText(settings->value("config").toString());
        ui->track_comboBox->setCurrentIndex(settings->value("track").toInt());
        ui->time_comboBox->setCurrentIndex(settings->value("time").toInt());

        // Wads
        int pwadCount = settings->beginReadArray("pwads");
        for (int i = 0; i < pwadCount; i++)
        {
            settings->setArrayIndex(i);
            QString filePath = settings->value("pwad").toString();

            ui->wads_listWidget->addItem(getFileName(filePath));
            ui->wads_listWidget->item(ui->wads_listWidget->count() - 1)->setToolTip(filePath);
        }
        settings->endArray();

        // Demos
        ui->record_lineEdit->setText(settings->value("recorddemo").toString());
        ui->playback_lineEdit->setText(settings->value("playdemo").toString());
        ui->viddump_lineEdit->setText(settings->value("viddump").toString());
        ui->playback_comboBox->setCurrentIndex(settings->value("demoplaybox").toInt());

        // Bottom
        ui->additionalArguments_textEdit->append(settings->value("argumentText").toString());
    }
}

void MainWindow::setStyles()
{
    // Top
    enable_disable_skill_comboBox();

    // Options
    if (ui->hud_lineEdit->text().isEmpty()) ui->hud_lineEdit->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    else ui->hud_lineEdit->setStyleSheet(STYLE_TEXT_NORMAL);

    if (ui->config_lineEdit->text().isEmpty()) ui->config_lineEdit->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    else ui->config_lineEdit->setStyleSheet(STYLE_TEXT_NORMAL);

    // Demos
    if (ui->viddump_lineEdit->text().isEmpty()) ui->viddump_lineEdit->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    else ui->viddump_lineEdit->setStyleSheet(STYLE_TEXT_NORMAL);

    if (ui->playback_comboBox->currentIndex() != 1)
    {
        ui->viddump_lineEdit->setHidden(true);
        ui->viddump_pushButton->setHidden(true);
    }
}
// Drag Event for *.wad *.lmp *.state *.deh *.bex
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }
}

void MainWindow::dropLmp(QString filePath)
{
    ui->tabs->setCurrentIndex(2);
    ui->playback_lineEdit->setText(filePath);

    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

    QTextStream stream(&file);
    QString buffer;

    bool found_footer = false;
    while (stream.readLineInto(&buffer))
    {
        if (buffer.mid(0, 5) == "-iwad")
        {
            found_footer = true;
            ui->wads_listWidget->clear();

            QStringList argList;
            QString tmp;
            for (qsizetype i = 0; i < buffer.size(); i++)
            {
                if (buffer[i] != ' ' && buffer[i] != '\"')
                {
                    tmp += buffer[i];
                }
                else if (!tmp.isEmpty())
                {
                    argList.push_back(tmp);
                    tmp.clear();
                }
            }
            if (!tmp.isEmpty())
            {
                argList.push_back(tmp);
                tmp.clear();
            }

            for (int i = 0; i < argList.count() - 1; i++)
            {
                if (argList[i] == "-iwad")
                {
                    int iwad_dot_pos = argList[i + 1].lastIndexOf('.');
                    iwad_dot_pos = iwad_dot_pos == -1 ? argList[i + 1].size() : iwad_dot_pos;

                    int iwad_index = ui->iwad_comboBox->findText(argList[i + 1].left(iwad_dot_pos));
                    if (iwad_index != -1)
                    {
                        ui->iwad_comboBox->setCurrentIndex(iwad_index);
                    }
                }
                else if (argList[i] == "-file" || argList[i] == "-deh")
                {
                    QStringList files;
                    for (int ii = i + 1; ii < argList.count(); ii++)
                    {
                        if (argList[ii].size() < 2 || argList[ii][0] == '-')
                        {
                            break;
                        }

                        QString tmp = argList[ii].toLower();

                        // Some old Woof demos don't have the .wad extension on the footer
                        int file_dot_pos = tmp.lastIndexOf('.');
                        if (file_dot_pos == -1) tmp += ".wad";

                        files.append(tmp);
                    }

                    for (int i = 0; i < files.count(); i++)
                    {
                        QString filePath = getFilePath(files[i]);
                        if (filePath.isEmpty()) continue;

                        ui->wads_listWidget->addItem(getFileName(filePath));
                        ui->wads_listWidget->item(ui->wads_listWidget->count() - 1)->setToolTip(filePath);
                    }
                }
            }
        }
    }

    file.close();

    if (!found_footer)
    {
        QStringList iwad_list;
        for (int i = 0; i < ui->iwad_comboBox->count(); i++)
        {
            iwad_list.push_back(ui->iwad_comboBox->itemText(i));
        }
        demodialog *demoDialogNew = new demodialog(iwad_list, this);
        demoDialogNew->open();

        demoDialog = demoDialogNew;
        connect(demoDialog, SIGNAL(accepted()), this, SLOT(demoDialog_accepted()));
    }
}

void MainWindow::dropFile(QString fileName)
{
    int dot_pos = fileName.lastIndexOf('.');
    if (dot_pos == -1) return;

    QString tmp = fileName.mid(dot_pos + 1).toLower();

    if (tmp == "lmp")
    {
        dropLmp(fileName);
    }
    else if (tmp == "wad" || tmp == "bex" || tmp == "deh" || tmp == "zip")
    {
        QStringList wadsToAdd;
        wadsToAdd.append(fileName);
        addPwads(wadsToAdd);
        ui->tabs->setCurrentIndex(1);
    }
    else if (tmp == "state")
    {
        states::loadStateFromFile(fileName);
    }
}

void MainWindow::demoDialog_accepted()
{
    ui->iwad_comboBox->setCurrentIndex(demoDialog->get_iwad_index());
    ui->wads_listWidget->clear();

    QStringList files_list = demoDialog->get_files_list();
    foreach (QString filePath, files_list)
    {
        ui->wads_listWidget->addItem(getFileName(filePath));
        ui->wads_listWidget->item(ui->wads_listWidget->count() - 1)->setToolTip(filePath);
    }
}

// Drop Event for *.wad *.lmp *gfd
void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls())
    {
        QString fileName = url.toLocalFile();
        dropFile(fileName);
    }
}

void MainWindow::error(QProcess::ProcessError error) { qDebug() << "Error: " << error; }

void MainWindow::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QProcess *p = (QProcess *)sender();
    delete p;
    running = false;

    if (exitCode != 0)
    {
        consoleWindow->show();
        consoleWindow->activateWindow();
        consoleWindow->raise();
        return;
    }

    if (settings->value("endoom").toBool())
    {
        endoomWindow->showEndoom(endoomString);

        endoomWindow->show();
        endoomWindow->activateWindow();
        endoomWindow->raise();
    }
}

void MainWindow::readyReadStandardError()
{

    QProcess *p = (QProcess *)sender();
    QByteArray buf = p->readAllStandardError();

    consoleWindow->changeText("<div style='color: red;'>" + buf + "</div>");
}

void MainWindow::readyReadStandardOutput()
{
    QProcess *p = (QProcess *)sender();
    QByteArray buf = p->readAllStandardOutput();

    QString qs = buf;

    if (qs.indexOf("\033") != -1 || endoomString != "")
    {
        endoomString += qs;
    }
    else
    {
        consoleWindow->changeText(buf);
    }
}

void MainWindow::started() { running = true; }

void MainWindow::gameIsRunning()
{
    QMessageBox msgBox;
    msgBox.setText(exeName + " is still running.");
    msgBox.addButton("Ok", QMessageBox::YesRole);
    msgBox.exec();
}

void MainWindow::saveSettings()
{
    // Top
    settings->setValue("iwad", ui->iwad_comboBox->currentIndex());
    settings->setValue("complevel", ui->complevel_comboBox->currentIndex());
    settings->setValue("skill", ui->difficulty_comboBox->currentIndex());
    settings->setValue("warp1", ui->episode_lineEdit->text());
    settings->setValue("warp2", ui->level_lineEdit->text());

    // Bottom
    settings->setValue("fast", ui->toggle1_checkBox->isChecked());
    settings->setValue("nomo", ui->toggle2_checkBox->isChecked());
    settings->setValue("solonet", ui->toggle3_checkBox->isChecked());
    settings->setValue("respawn", ui->toggle4_checkBox->isChecked());
    settings->setValue("fullscreen", ui->fullscreen_checkBox->isChecked());
    settings->setValue("geom", ui->resolution_comboBox->currentIndex());
    settings->setValue("hud", ui->hud_lineEdit->text());
    settings->setValue("config", ui->config_lineEdit->text());
    settings->setValue("track", ui->track_comboBox->currentIndex());
    settings->setValue("time", ui->time_comboBox->currentIndex());

    // Wads
    settings->beginWriteArray("pwads");
    for (int i = 0; i < ui->wads_listWidget->count(); i++)
    {
        settings->setArrayIndex(i);
        settings->setValue("pwad", ui->wads_listWidget->item(i)->toolTip());
    }
    settings->endArray();

    // Demos
    settings->setValue("recorddemo", ui->record_lineEdit->text());
    settings->setValue("playdemo", ui->playback_lineEdit->text());
    settings->setValue("viddump", ui->viddump_lineEdit->text());
    settings->setValue("demoplaybox", ui->playback_comboBox->currentIndex());

    // Bottom
    settings->setValue("argumentText", ui->additionalArguments_textEdit->toPlainText());

    settings->setValue("exeName", exeName);

    settings->setValue("version", version);

    settings->sync();
}

QStringList MainWindow::getArguments()
{
    QStringList arguments;

    // Top
    arguments.append("-iwad");
    arguments.append(ui->iwad_comboBox->currentData(Qt::ToolTipRole).toString());

    QString complevel_string = ui->complevel_comboBox->currentText();
    if (complevel_string != "Default")
    {
        arguments.append("-complevel");
        arguments.append(complevel_string.left(2));
    }

    if (ui->difficulty_comboBox->isEnabled() && ui->difficulty_comboBox->currentIndex() != 0)
    {
        arguments.append("-skill");
        arguments.append(QString::number(ui->difficulty_comboBox->currentIndex()));
    }

    // Warping in Doom takes 2 boxes. 1 for the episode, 1 for the mission
    // Warping in Doom 2 takes 1 box, for the map
    if (!ui->level_lineEdit->text().isEmpty() && !ui->level_lineEdit->isHidden())
    {
        arguments.append("-warp");
        arguments.append(ui->episode_lineEdit->text());
        arguments.append(ui->level_lineEdit->text());
    }
    else if (!ui->episode_lineEdit->text().isEmpty() && ui->level_lineEdit->isHidden())
    {
        arguments.append("-warp");
        arguments.append(ui->episode_lineEdit->text());
    }

    // Options
    if (ui->toggle1_checkBox->isChecked()) arguments.append(ui->toggle1_checkBox->toolTip().split(';'));

    if (ui->toggle2_checkBox->isChecked()) arguments.append(ui->toggle2_checkBox->toolTip().split(';'));

    if (ui->toggle3_checkBox->isChecked()) arguments.append(ui->toggle3_checkBox->toolTip().split(';'));

    if (ui->toggle4_checkBox->isChecked()) arguments.append(ui->toggle4_checkBox->toolTip().split(';'));

    if (ui->resolution_comboBox->currentIndex() == 0)
    {
        if (ui->fullscreen_checkBox->isChecked()) arguments.append("-fullscreen");
        else arguments.append("-window");
    }
    else
    {
        QString geom_char = ui->fullscreen_checkBox->isChecked() ? "f" : "w";

        arguments.append("-geom");
        arguments.append(ui->resolution_comboBox->currentText() + geom_char);
    }

    if (ui->hud_lineEdit->text() != "")
    {
        arguments.append("-hud");
        arguments.append(ui->hud_lineEdit->text());
    }

    if (ui->config_lineEdit->text() != "")
    {
        arguments.append("-config");
        arguments.append(ui->config_lineEdit->text());
    }

    if (ui->track_comboBox->currentIndex() == 1) arguments.append("-track_pacifist");
    else if (ui->track_comboBox->currentIndex() == 2) arguments.append("-track_100k");

    if (ui->time_comboBox->currentIndex() == 1) arguments.append("-time_use");
    else if (ui->time_comboBox->currentIndex() == 2) arguments.append("-time_keys");
    else if (ui->time_comboBox->currentIndex() == 3) arguments.append("-time_secrets");
    else if (ui->time_comboBox->currentIndex() == 4) arguments.append("-time_all");

    // Wads
    if (ui->wads_listWidget->count() > 0)
    {
        arguments.append("-file");
        for (int i = 0; i < ui->wads_listWidget->count(); i++)
        {
            /*
#ifdef _WIN32
            for (int i = 0; i < file.length(); i++)
            {
                if (file[i] == '/') file[i] = '\\';
            }
#endif
            */
            arguments.append(ui->wads_listWidget->item(i)->toolTip());
        }
    }

    // Demos
    if (!ui->record_lineEdit->text().isEmpty())
    {
        arguments.append("-record");
        arguments.append(ui->record_lineEdit->text());
    }

    if (!ui->playback_lineEdit->text().isEmpty())
    {
        if (ui->playback_comboBox->currentIndex() == 0)
        {
            arguments.append("-playdemo"); // Plays demo at normal speed
            arguments.append(ui->playback_lineEdit->text());
        }
        else if (ui->playback_comboBox->currentIndex() == 1)
        {
            arguments.append("-timedemo"); // Used for viddumping
            arguments.append(ui->playback_lineEdit->text());

            if (!ui->viddump_lineEdit->text().isEmpty())
            {
                arguments.append("-viddump");
                arguments.append(ui->viddump_lineEdit->text());
            }
        }
        else if (ui->playback_comboBox->currentIndex() == 2)
        {
            arguments.append("-fastdemo"); // Used for benchmarks
            arguments.append(ui->playback_lineEdit->text());
        }
    }

    if (ui->additionalArguments_textEdit->toPlainText() != "")
    {
        QString str = ui->additionalArguments_textEdit->toPlainText() + " ";

        QString strToAdd = "";
        for (qsizetype i = 0; i < str.length(); i++)
        {

            QChar c = str[i];
            if (c == ' ')
            {
                if (strToAdd != "")
                {
                    arguments.append(strToAdd);
                    strToAdd = "";
                }
            }
            else if (c == '\"')
            {
                i++;
                while (str[i] != '\"')
                {
                    strToAdd.push_back(str[i]);
                    i++;
                }
            }
            else
            {
                strToAdd.push_back(c);
            }
        }
    }

    return arguments;
}

void MainWindow::on_launchGame_pushButton_clicked(bool returnTooltip, QString exportCmd) // Runs when you click the launch button or when you close the launcher (When closing, it will not run the game, but actually just save the settings)
{
    if (!canLaunch) // Dont allow 2 launchs in the time of 2 sec
        return;

    if (running && !returnTooltip)
    {
        gameIsRunning();
        return;
    }

    int complevelIndex = ui->complevel_comboBox->currentIndex();
    int diffIndex = ui->difficulty_comboBox->currentIndex();

    QStringList argList = getArguments();

    if (returnTooltip)
    {
        QString argStr;
        QString argStrComplete;
        foreach (QString p, argList)
        {
            argStrComplete.append((p + " "));

            int lastBar = 0;
            for (qsizetype i = 0; i < p.length(); i++)
            {
                if (p[i] == QDir::separator())
                {
                    lastBar = i + 1;
                }
            }
            p = p.mid(lastBar);

            if (p.length() > 1 && p[0] != '"' && p[p.length() - 1] == '"')
            {
                p = p.mid(0, p.length() - 1);
            }

            argStr.append((p + " "));
        }

        if (exportCmd != "")
        {
            QFile file(exportCmd);
            if (!file.open(QFile::WriteOnly | QFile::Text))
            {
                return;
            }
            QTextStream out(&file);

#ifdef __APPLE__
            out << "\"" + execPath + "/../Resources/" + exeName + "\" -iwad \"" + ui->iwad_comboBox->itemData(ui->iwad_comboBox->currentIndex(), Qt::ToolTipRole).toString() + "\" " + argStrComplete;
#elif __linux__
            out << "\"" + execPath + "/" + exeName + "\" -iwad \"" + ui->iwad_comboBox->itemData(ui->iwad_comboBox->currentIndex(), Qt::ToolTipRole).toString() + "\" " + argStrComplete;
#else
            std::replace(execPath.begin(), execPath.end(), '/', '\\');
            out << "\"" + execPath + "\\" + exeName + ".exe\" -iwad \"" + ui->iwad_comboBox->itemData(ui->iwad_comboBox->currentIndex(), Qt::ToolTipRole).toString() + "\" " + argStrComplete;
#endif
            file.close();

            return;
        }

        QMessageBox msgBox;
        msgBox.setText("Executable: " + exeName + "\nIWAD: " + ui->iwad_comboBox->currentText() + "\nParameters: " + argStr);
        msgBox.addButton(tr("Copy"), QMessageBox::NoRole);
        QPushButton *pButtonYes = msgBox.addButton(tr("Ok"), QMessageBox::YesRole);
        msgBox.setDefaultButton(pButtonYes);
        msgBox.exec();

        if (msgBox.clickedButton() != pButtonYes)
        {
            QClipboard *clip = QApplication::clipboard();
#ifdef __APPLE__
            clip->setText("\"" + execPath + "/../Resources/" + exeName + "\" -iwad \"" + ui->iwad_comboBox->itemData(ui->iwad_comboBox->currentIndex(), Qt::ToolTipRole).toString() + "\" " + argStrComplete);
#elif __linux__
            clip->setText("\"" + execPath + "/" + exeName + "\" -iwad \"" + ui->iwad_comboBox->itemData(ui->iwad_comboBox->currentIndex(), Qt::ToolTipRole).toString() + "\" " + argStrComplete);
#else
            std::replace(execPath.begin(), execPath.end(), '/', '\\');
            clip->setText("\"" + execPath + "\\" + exeName + ".exe\" -iwad \"" + ui->iwad_comboBox->itemData(ui->iwad_comboBox->currentIndex(), Qt::ToolTipRole).toString() + "\" " + argStrComplete);
#endif
        }

        return;
    }

    Launch(ui->iwad_comboBox->currentText(), argList);

    SaveHistory(ui->iwad_comboBox->currentText(), argList);
}

void MainWindow::Launch(QString iwadName, QStringList argList)
{
    if (!canLaunch) return;

    for (int i = 0; i < argList.count(); i++)
    {
        if (argList.at(i) == "")
        {
            argList.removeAt(i);
        }
    }

    consoleWindow->clearText();
    endoomWindow->clearText();
    endoomString = "";

    if (settings->value("endoom").toBool())
    {
        argList.append({"-assign", "ansi_endoom=2"});
    }

#ifdef __APPLE__
    QFile port = QFile(execPath + "/../Resources/" + exeName + "");
    if (port.exists())
    {
        QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        argList.push_front(ui->iwad_comboBox->itemData(ui->iwad_comboBox->currentIndex(), Qt::ToolTipRole).toString());
        argList.push_front("-iwad");
        QProcess *process = new QProcess;
        process->setWorkingDirectory(homePath);
        process->start(execPath + "/../Resources/" + exeName, argList);
        connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finished(int, QProcess::ExitStatus)));
        connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
        connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
        connect(process, SIGNAL(started()), this, SLOT(started()));
    }
    else
    {
        QMessageBox::warning(this, "dsda-launcher", exeName + " was not found in dsda-launcher.app/Contents/Resources/" + exeName);
    }
#elif __linux__
    QFile port = QFile(execPath + "/" + exeName);
    QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    argList.push_front(ui->iwad_comboBox->itemData(ui->iwad_comboBox->currentIndex(), Qt::ToolTipRole).toString());
    // Run "which" command to check if dsda-doom exists. if it does then no need to specify a path, just run a process with exeName.
    QStringList apar;
    apar << exeName;
    QProcess whichProcess;
    whichProcess.start("which", apar);
    whichProcess.waitForFinished();
    QString processPath;
    // If it finds an executable in the dsda-launcher folder, it will prioritize it over the one installed in a bin folder.
    if (port.exists()) processPath = execPath + "/" + exeName;
    else processPath = exeName;
    if (whichProcess.readAllStandardOutput() != "")
    {
        QProcess *process = new QProcess;
        process->setWorkingDirectory(homePath);
        process->start(processPath, argList);
        connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finished(int, QProcess::ExitStatus)));
        connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
        connect(process, SIGNAL(started()), this, SLOT(started()));
    }
    else QMessageBox::warning(this, "dsda-launcher", ("Failed to launch the application executable.\nMake sure that " + exeName + " is installed correctly through your package manager or installed with the original build instructions.\n\nIf you are sure " + exeName + " exists, symlink it to dsda-launcher's folder."));
#else
    QFile port = QFile(execPath + "/" + exeName + ".exe");
    if (port.exists())
    {
        argList.push_front(ui->iwad_comboBox->itemData(ui->iwad_comboBox->currentIndex(), Qt::ToolTipRole).toString());
        argList.push_front("-iwad");
        QProcess *process = new QProcess;
        process->setWorkingDirectory(execPath);
        process->start(execPath + "/" + exeName + ".exe", argList);
        connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finished(int, QProcess::ExitStatus)));
        connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
        connect(process, SIGNAL(started()), this, SLOT(started()));
    }
    else
    {
        QMessageBox::warning(this, "dsda-launcher", "Failed to launch the application executable.\nMake sure that the launcher is in the same folder as " + exeName + ".exe");
    }
#endif

    // Again, don't allow the launch button to work twice in the space of 2 secs
    canLaunch = false;
    QTimer::singleShot(1000, this, SLOT(delayLaunch()));
}

void MainWindow::SaveHistory(QString iwad, QStringList args)
{
    int checksum = 0;
    int count = 0;
    int needToDelete = 0;

    QString t = iwad;
    for (qsizetype i = 0; i < args.size(); i++)
    {
        t += args.at(i);
    }
    QByteArray arr = t.toLatin1();
    checksum = qChecksum(arr.data(), arr.length());

    QFile file(historyListWindow->historyPath);

    if (!file.isOpen())
    {
        return;
    }

    QTextStream stream(&file);

    QString buffer;

    while (!file.atEnd())
    {
        stream.readLineInto(&buffer);
        if (buffer[0] == '-')
        {
            count++;
        }
    }
    stream.seek(0);

    while (buffer.mid(0, 9) != "checksum=" && !file.atEnd())
    {
        stream.readLineInto(&buffer);
    }

    if (buffer.mid(0, 9) == "checksum=" && buffer.mid(9).length() > 0)
    {
        if (checksum == buffer.mid(9).toInt())
        {
            file.close();
            return;
        }
    }

    file.close();

    int maxhistory = settings->value("maxhistory").toInt();
    if (count >= maxhistory)
    {
        needToDelete = count - maxhistory + 1;
    }

    QString h = "# Do not edit this file manually\n\nchecksum=" + QString::number(checksum) + "\n";
    QString streamstr = stream.readAll();

    QFile file_out(historyListWindow->historyPath);

    if (!file_out.isOpen())
    {
        return;
    }

    QTextStream out(&file_out);

    if (!needToDelete)
    {
        if (streamstr != "")
        {
            h += streamstr + "\n";
        }
        out << h;
    }
    else
    {
        if (streamstr != "")
        {
            int past = 0;
            for (qsizetype i = 0; i < streamstr.length(); i++)
            {
                if (streamstr.mid(i, 2) == "-\n")
                {
                    if (past == needToDelete)
                    {
                        streamstr = streamstr.mid(i);
                    }
                    else
                    {
                        past++;
                    }
                }
            }
            h += streamstr + "\n";
        }
        out << h;
    }
    file_out.close();
    states::saveStateToFile(historyListWindow->historyPath + "s");
    QFile::remove(historyListWindow->historyPath);
    QFile::rename(historyListWindow->historyPath + "s", historyListWindow->historyPath);
}

QString demoFile;

void MainWindow::keyPressEvent(QKeyEvent *event) // ENTER makes the game start
{
    if (event->key() == 0x01000005 || event->key() == 0x01000004) // Key is either ENTER or RETURN
    {
        on_launchGame_pushButton_clicked(false, "");
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *ev) // ENTER does not work on the additional parameters box
{

    if (object == (QObject *)ui->launchGame_pushButton)
    {
        // if (ev->type() == QEvent::Enter)
        //{
        //     on_launchGame_pushButton_clicked(false, true);
        //     return QWidget::eventFilter(object, ev);
        // }
        if (ev->type() == QEvent::MouseButtonPress)
        {
            on_launchGame_pushButton_clicked(false, "");
            return QWidget::eventFilter(object, ev);
        }
    }
    if (ev->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = (QKeyEvent *)ev;

        if (keyEvent->key() == 0x01000005 || keyEvent->key() == 0x01000004) // Key is either ENTER or RETURN
        {
            on_launchGame_pushButton_clicked(false, "");
            return true;
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *event) // When closing the launcher, save the settings
{
    if (running)
    {
        gameIsRunning();
        event->ignore();
        return;
    }

    saveSettings();
    QApplication::quit();
}

void MainWindow::on_showCommandLine_pushButton_clicked() { on_launchGame_pushButton_clicked(true, ""); }

QComboBox *MainWindow::iwad_comboBox() { return ui->iwad_comboBox; }
QComboBox *MainWindow::complevel_comboBox() { return ui->complevel_comboBox; }
QLineEdit *MainWindow::episode_lineEdit() { return ui->episode_lineEdit; }
QLineEdit *MainWindow::level_lineEdit() { return ui->level_lineEdit; }
QComboBox *MainWindow::difficulty_comboBox() { return ui->difficulty_comboBox; }
QCheckBox *MainWindow::toggle1_checkBox() { return ui->toggle1_checkBox; }
QCheckBox *MainWindow::toggle2_checkBox() { return ui->toggle2_checkBox; }
QCheckBox *MainWindow::toggle3_checkBox() { return ui->toggle3_checkBox; }
QCheckBox *MainWindow::toggle4_checkBox() { return ui->toggle4_checkBox; }
QComboBox *MainWindow::resolution_comboBox() { return ui->resolution_comboBox; }
QCheckBox *MainWindow::fullscreen_checkBox() { return ui->fullscreen_checkBox; }
QLineEdit *MainWindow::hud_lineEdit() { return ui->hud_lineEdit; }
QLineEdit *MainWindow::config_lineEdit() { return ui->config_lineEdit; }
QComboBox *MainWindow::track_comboBox() { return ui->track_comboBox; }
QComboBox *MainWindow::time_comboBox() { return ui->time_comboBox; }
QListWidget *MainWindow::wads_listWidget() { return ui->wads_listWidget; }
QLineEdit *MainWindow::record_lineEdit() { return ui->record_lineEdit; }
QLineEdit *MainWindow::playback_lineEdit() { return ui->playback_lineEdit; }
QLineEdit *MainWindow::viddump_lineEdit() { return ui->viddump_lineEdit; }
QComboBox *MainWindow::playback_comboBox() { return ui->playback_comboBox; }
QTextEdit *MainWindow::additionalArguments_textEdit() { return ui->additionalArguments_textEdit; }

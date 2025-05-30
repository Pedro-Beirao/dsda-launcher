#include "mainwindow.h"

QSettings *settings;
MainWindow *MainWindow::pMainWindow = nullptr;

void MainWindow::changeGameName(QString newName) { gameName = newName; }

void MainWindow::showSSLDialog()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Warning");
    msgBox.setText("SSL library not found");
    msgBox.setInformativeText("Network features not available.");
    msgBox.addButton(tr("Ok"), QMessageBox::NoRole);
    msgBox.adjustSize();
    msgBox.exec();
}

// Prevents launching the game twice if the button "Launch" is pressed twice quickly
void MainWindow::delayLaunch() { canLaunch = true; }

// MainWindow
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::pMainWindow = this;

    launcherfolder = QCoreApplication::applicationDirPath();
    findDataFolder();

    // Allow files to be droped in the launcher (*.wad *.lmp *.deh *.bex)
    setAcceptDrops(true);

    // Add event filter to the "additional arguments" box
    ui->additionalArguments_textEdit->installEventFilter(this);

    // Add event filter to the Launch button. This will allow you to see the current parameters when you hover your mouse
    ui->launchGame_pushButton->installEventFilter(this);

    // set the settings and console windows
    aboutWindow = new About;
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

    // Keyboard shortcut
    // Qt::CTRL is the CTRL key for Windows/Linux and is the CMD key for MacOS

    // Closes the active window
    QShortcut *shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL), this, SLOT(close()));
    shortcut3->setAutoRepeat(false);

    QFileInfoList IWADs = findIwads();
    for (int i = 0; i < IWADs.count(); i++)
    {
        ui->iwad_comboBox->addItem(IWADs[i].baseName().toLower());
        ui->iwad_comboBox->setItemData(ui->iwad_comboBox->count() - 1, IWADs[i].absoluteFilePath(), Qt::ToolTipRole);
    }

    // If no IWAD found, show a tool tip
    if (ui->iwad_comboBox->count() == 0) ui->tooltip_textBrowser->show();
    else ui->tooltip_textBrowser->hide();

    loadSelected();

    setStyles();

    initializeIndicators();

    QTimer::singleShot(0, this, SLOT(CheckUpdates()));

    QStringList arguments = qApp->arguments();
    for (int i = 1; i < arguments.count(); i++)
    {
        dropFile(arguments.at(i));
    }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::CheckUpdates()
{
    if (settings->value("updaterStartLauncher").toBool())
    {
        if (updateLauncherDialog(false)) return;
    }
    if (settings->value("updaterStartGame").toBool()) updateGameDialog(false);
}

void MainWindow::loadSelected()
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
        if (ui->iwad_comboBox->currentIndex() == -1 && ui->iwad_comboBox->count() > 0) ui->iwad_comboBox->setCurrentIndex(0);

        ui->complevel_comboBox->setCurrentIndex(settings->value("complevel").toInt());
        ui->skill_comboBox->setCurrentIndex(settings->value("skill").toInt());
        ui->episode_lineEdit->setText(settings->value("warp1").toString());
        ui->level_lineEdit->setText(settings->value("warp2").toString());

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

void MainWindow::saveSelected()
{
    // Top
    settings->setValue("iwad", ui->iwad_comboBox->currentIndex());
    settings->setValue("complevel", ui->complevel_comboBox->currentIndex());
    settings->setValue("skill", ui->skill_comboBox->currentIndex());
    settings->setValue("warp1", ui->episode_lineEdit->text());
    settings->setValue("warp2", ui->level_lineEdit->text());

    // Bottom
    settings->setValue("fast", ui->toggle1_checkBox->isChecked());
    settings->setValue("nomo", ui->toggle2_checkBox->isChecked());
    settings->setValue("respawn", ui->toggle3_checkBox->isChecked());
    settings->setValue("solonet", ui->toggle4_checkBox->isChecked());
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

    settings->setValue("version", version);

    settings->sync();
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

    QString footer_iwad = "";
    QStringList footer_files;

    while (stream.readLineInto(&buffer))
    {
        if (buffer.left(5) == "-iwad")
        {
            QStringList args = QProcess::splitCommand(buffer);
            bool searching_files = false;
            for (int i = 0; i < args.count(); i++)
            {
                if (args[i].isEmpty()) continue;
                if (args[i][0] == '-') searching_files = false;

                if (searching_files)
                {
                    // Some old Woof demos don't have the .wad extension on the footer
                    int file_dot_pos = args[i].lastIndexOf('.');
                    if (file_dot_pos == -1) args[i] += ".wad";

                    footer_files.append(args[i]);
                }

                if (args[i] == "-iwad" && i < args.count() - 1)
                {
                    footer_iwad = args[i + 1];
                }
                else if (args[i] == "-file" || args[i] == "-deh")
                {
                    searching_files = true;
                }
            }
        }
    }

    file.close();

    demodialog *demoDialogNew = new demodialog(footer_iwad, footer_files, this);
    demoDialogNew->setAttribute(Qt::WA_DeleteOnClose);
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
        addPwads({fileName});
        ui->tabs->setCurrentIndex(1);
    }
    else if (tmp == "state")
    {
        states::loadStateFromFile(fileName);
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls())
    {
        QString fileName = url.toLocalFile();
        dropFile(fileName);
    }
}

void MainWindow::error(QProcess::ProcessError error) {}

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
        setWindowTitleBar(consoleWindow->winId());
        return;
    }

    if (settings->value("endoom").toBool() && !endoomString.isEmpty())
    {
        endoomWindow->showEndoom(endoomString);

        endoomWindow->show();
        endoomWindow->activateWindow();
        endoomWindow->raise();
        setWindowTitleBar(endoomWindow->winId());
    }
}

void MainWindow::readyReadStandardError()
{
    QProcess *p = (QProcess *)sender();
    QByteArray buf = p->readAllStandardError();

    consoleWindow->appendText("<div style='color: red;'>" + buf + "</div>");
}

void MainWindow::readyReadStandardOutput()
{
    QProcess *p = (QProcess *)sender();
    QByteArray buf = p->readAllStandardOutput();

    QString qs = buf;

    if (qs.indexOf("\033") != -1 || !endoomString.isEmpty())
    {
        endoomString += qs;
    }
    else
    {
        consoleWindow->appendText(buf);
    }
}

void MainWindow::started() { running = true; }

void MainWindow::gameIsRunningDialog()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("DSDA-Launcher");
    msgBox.setText("dsda-doom is still running.");
    msgBox.addButton("Ok", QMessageBox::YesRole);
    msgBox.adjustSize();
    msgBox.exec();
}

QStringList MainWindow::getArguments()
{
    QStringList arguments;

    // Top
    arguments.append("-iwad");
    arguments.append(ui->iwad_comboBox->currentData(Qt::ToolTipRole).toString());

    if (ui->complevel_comboBox->isEnabled() && ui->complevel_comboBox->currentText() != "Default")
    {
        arguments.append("-complevel");
        arguments.append(ui->complevel_comboBox->currentText().left(2));
    }

    if (ui->skill_comboBox->isEnabled() && ui->skill_comboBox->currentIndex() != 0)
    {
        arguments.append("-skill");
        arguments.append(QString::number(ui->skill_comboBox->currentIndex()));
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

    if (ui->resolution_comboBox->currentIndex() <= 0)
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
    else if (ui->track_comboBox->currentIndex() == 3) arguments.append("-track_reality");

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
#if defined Q_OS_WIN
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

    if (settings->value("endoom").toBool())
    {
        arguments.append({"-assign", "ansi_endoom=2"});
    }

    if (!ui->additionalArguments_textEdit->toPlainText().isEmpty())
    {
        QStringList parsed = parseStringIntoArguments(ui->additionalArguments_textEdit->toPlainText());

        arguments.append(parsed);
    }

    return arguments;
}

void MainWindow::on_launchGame_pushButton_clicked(bool returnTooltip, QString exportCmd) // Runs when you click the launch button or when you close the launcher (When closing, it will not run the game, but actually just save the settings)
{
    if (!canLaunch) // Dont allow 2 launchs in the time of 2 sec
        return;

    if (running && !returnTooltip)
    {
        gameIsRunningDialog();
        return;
    }

    QStringList arguments = getArguments();

    if (returnTooltip)
    {
        QString argStr;
        QString argStrComplete;

        foreach (QString p, arguments)
        {
            if (p.trimmed().contains(' ')) p = "\"" + p + "\"";
            argStrComplete.append((" " + p));
        }

        foreach (QString p, arguments)
        {
            int lastBar = 0;
            for (int i = 0; i < p.length(); i++)
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

#if defined Q_OS_MACOS
            out << "\"" + getGamePath() + "\"" + argStrComplete;
#elif defined Q_OS_LINUX
            out << "\"" + getGamePath() + "\"" + argStrComplete;
#else
            std::replace(launcherfolder.begin(), launcherfolder.end(), '/', '\\');
            out << "\"" + getGamePath() + "\"" + argStrComplete;
#endif
            file.close();

            return;
        }

        QMessageBox msgBox;
        msgBox.setWindowTitle("Parameters");
        msgBox.setText("Executable: " + gameName + "\nIWAD: " + ui->iwad_comboBox->currentText() + "\nParameters: " + argStr);
        msgBox.addButton(tr("Copy"), QMessageBox::NoRole);
        QPushButton *pButtonYes = msgBox.addButton(tr("Ok"), QMessageBox::YesRole);
        msgBox.setDefaultButton(pButtonYes);
        msgBox.adjustSize();
        msgBox.exec();

        if (msgBox.clickedButton() != pButtonYes)
        {
            QClipboard *clip = QApplication::clipboard();
#if defined Q_OS_MACOS
            clip->setText("\"" + getGamePath() + "\"" + argStrComplete);
#elif defined Q_OS_LINUX
            clip->setText("\"" + getGamePath() + "\"" + argStrComplete);
#else
            std::replace(launcherfolder.begin(), launcherfolder.end(), '/', '\\');
            clip->setText("\"" + getGamePath() + "\"" + argStrComplete);
#endif
        }

        return;
    }

    Launch(arguments);

    SaveHistory(arguments);
}

void MainWindow::Launch(QStringList arguments)
{
    if (!canLaunch) return;

    if (running)
    {
        gameIsRunningDialog();
        return;
    }

    consoleWindow->clearText();
    endoomString = "";

    // clang-format off
#if defined Q_OS_MACOS
    QString gamePath = getGamePath();
    QFile port(gamePath);
    if (port.exists())
    {
        QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        QProcess *process = new QProcess;
        process->setWorkingDirectory(homePath);
        process->start(gamePath, arguments);
        connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int,QProcess::ExitStatus)));
        connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
        connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
        connect(process, SIGNAL(started()), this, SLOT(started()));
    }
    else
    {
        QMessageBox::warning(this, "Error", gameName + " was not found in " + APP_NAME + ".app/Contents/Resources/" + gameName);
    }
#elif defined Q_OS_LINUX
    QString gamePath = getGamePath();
    QFile port(gamePath);
    if (port.exists())
    {
        QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        QProcess *process = new QProcess;
        process->setWorkingDirectory(homePath);
        process->start(gamePath, arguments);
        connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int,QProcess::ExitStatus)));
        connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
        connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
        connect(process, SIGNAL(started()), this, SLOT(started()));
    }
    else
    {
        QMessageBox::warning(this, "Error", ("Failed to launch the application executable.\nMake sure that " + gameName + " is installed correctly through your package manager or installed with the original build instructions.\n\nIf you are sure " + gameName + " exists, symlink it to " + APP_NAME + "'s folder."));
    }
#else
    QString gamePath = getGamePath();
    QFile port(gamePath);
    if (port.exists())
    {
        QProcess *process = new QProcess;
        process->setWorkingDirectory(launcherfolder);
        process->start(gamePath, arguments);
        connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int,QProcess::ExitStatus)));
        connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
        connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
        connect(process, SIGNAL(started()), this, SLOT(started()));
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to launch the application executable.\nMake sure that the launcher is in the same folder as " + gameName + ".exe");
    }
#endif
    // clang-format on

    // Again, don't allow the launch button to work twice in the space of 2 secs
    canLaunch = false;
    QTimer::singleShot(1000, this, SLOT(delayLaunch()));
}

void MainWindow::SaveHistory(QStringList args)
{
    int checksum = 0;
    int count = 0;
    int needToDelete = 1;

    QString checksumString = "";
    for (qsizetype i = 0; i < args.size(); i++)
        checksumString += args.at(i);
    QByteArray checksumByteArray = checksumString.toLatin1();

#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    checksum = qChecksum(checksumByteArray.data());
#else
    checksum = qChecksum(checksumByteArray.data(), checksumByteArray.length());
#endif

    QFile file(historyListWindow->historyPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString buffer;

    QTextStream stream(&file);
    if (file.isOpen())
    {
        stream.readLineInto(&buffer);
        if (buffer != HISTORY_HEADER)
        {
            // Outdated history.states file. Remove it
            file.close();
            QFile::remove(historyListWindow->historyPath);
            stream.setString(NULL);
        }

        while (file.isOpen() && !stream.atEnd())
        {
            stream.readLineInto(&buffer);

            if (buffer == '-')
            {
                count++;
                continue;
            }

            if (buffer.left(8) == "checksum" && buffer.mid(8).length() > 0)
            {
                if (checksum == buffer.mid(8).toInt())
                {
                    // Same exact parameters where launched, ignore
                    file.close();
                    return;
                }
            }
        }
        stream.seek(0);
    }

    int maxhistory = settings->value("maxhistory").toInt();
    if (count >= maxhistory)
    {
        needToDelete = count - maxhistory + 2;
    }

    QFile file_out(historyListWindow->historyPath + "_tmp");
    file_out.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    if (!file_out.isOpen()) return;
    QTextStream out(&file_out);
    out << HISTORY_HEADER << "\nchecksum" << QString::number(checksum) << "\n";

    if (needToDelete <= 0) needToDelete = 1;
    while (file.isOpen() && !stream.atEnd())
    {
        stream.readLineInto(&buffer);
        if (buffer == '-' && needToDelete > 0) needToDelete--;
        if (needToDelete <= 0) out << buffer << '\n';
    }
    file.close();
    file_out.close();
    states::saveStateToFile(historyListWindow->historyPath + "_tmp");
    QFile::remove(historyListWindow->historyPath);
    QFile::rename(historyListWindow->historyPath + "_tmp", historyListWindow->historyPath);
}

QString demoFile;

void MainWindow::keyPressEvent(QKeyEvent *event) // ENTER makes the game start
{
    if (event->key() == 0x01000005 || event->key() == 0x01000004) // Key is either ENTER or RETURN
    {
        on_launchGame_pushButton_clicked(false, "");
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *ev) // Make ENTER not work on the additional parameters box
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
        gameIsRunningDialog();
        event->ignore();
        return;
    }

    saveSelected();
    QApplication::quit();
}

void MainWindow::on_showCommandLine_pushButton_clicked() { on_launchGame_pushButton_clicked(true, ""); }

void MainWindow::on_wadsSelected_indicator_clicked() { ui->tabs->setCurrentIndex(1); }
void MainWindow::on_recordingDemo_indicator_clicked() { ui->tabs->setCurrentIndex(2); }
void MainWindow::on_playingDemo_indicator_clicked() { ui->tabs->setCurrentIndex(2); }

QComboBox *MainWindow::iwad_comboBox() { return ui->iwad_comboBox; }
QComboBox *MainWindow::complevel_comboBox() { return ui->complevel_comboBox; }
QLineEdit *MainWindow::episode_lineEdit() { return ui->episode_lineEdit; }
QLineEdit *MainWindow::level_lineEdit() { return ui->level_lineEdit; }
QComboBox *MainWindow::skill_comboBox() { return ui->skill_comboBox; }
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

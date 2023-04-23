#include "mainwindow.h"
#include "./ui_mainwindow.h"

QSettings settings("pedrobeirao","dsda-launcher");
MainWindow * MainWindow::pMainWindow = nullptr;

void MainWindow::changeExeName(QString newName)
{
    exeName = newName;
}

void MainWindow::showSSLDialog()
{
    QMessageBox msgBox;
    msgBox.setText("SSL library not found. Network features not available.");
    msgBox.setInformativeText("It should have been packaged with the Launcher.\nIf reinstalling does not fix this, try manually installing OpenSSL.\n\nlibssl-1_1-x64.dll + libcrypto-1_1-x64.dll");
    msgBox.addButton(tr("Ok"), QMessageBox::NoRole);
    msgBox.exec();
}

void MainWindow::changeMaxSkillLevel(int max)
{
    ui->difficulty_comboBox->clear();
    for(int i=0; i<=max;i++)
    {
        if(i!=0)
            ui->difficulty_comboBox->addItem(std::to_string(i).c_str());
        else
            ui->difficulty_comboBox->addItem(" ");
    }
    ui->difficulty_comboBox->setCurrentIndex(settings.value("skill").toInt());
}

void MainWindow::changeToggles(QString t1, QString a1, QString t2, QString a2, QString t3, QString a3, QString t4, QString a4)
{
    ui->fast_checkBox->setText(t1);
    ui->fast_checkBox->setToolTip(a1);
    ui->nomo_checkBox->setText(t2);
    ui->nomo_checkBox->setToolTip(a2);
    ui->respawn_checkBox->setText(t3);
    ui->respawn_checkBox->setToolTip(a3);
    ui->solonet_checkBox->setText(t4);
    ui->solonet_checkBox->setToolTip(a4);
    fastParam = a1;
    nomoParam = a2;
    respawnParam = a3;
    solonetParam = a4;
}

void MainWindow::changeResolutions(QListWidget *list)
{
    ui->resolution_comboBox->clear();
    ui->resolution_comboBox->addItem(" ");
    for(int i=0;i<list->count();i++)
    {
        ui->resolution_comboBox->addItem(list->item(i)->text());
    }
}

void MainWindow::changeComplevelsList(int i)
{
    if(i==0)
    {
        ui->complevel_comboBox->clear();
        ui->complevel_comboBox->addItems({"Default","2 - Doom / Doom 2","3 - Ultimate Doom","4 - Final Doom","9 - Boom","11 - MBF","21 - MBF 21"});
    }
    else if(i==1)
    {
        ui->complevel_comboBox->clear();
        ui->complevel_comboBox->addItems({"Default","0 - Doom v1.2","1 - Doom v1.666","2 - Doom / Doom 2","3 - Ultimate Doom","4 - Final Doom","5 - DOSDoom","6 - TASDoom","7 - Boom's comp mode","8 - Boom v2.01","9 - Boom","10 - LxDoom","11 - MBF","12 - PrBoom v2.03beta","13 - PrBoom v2.1.0","14 - PrBoom v2.1.1 - 2.2.6","15 - PrBoom v2.3.x","16 - PrBoom v2.4.0","17 - Current PrBoom","21 - MBF 21"});
    }
}

void MainWindow::changeButtonColor(bool isDark)
{
#ifdef __APPLE__
    if(isDark)
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

// Lower case all letters of a string
QString lowerCase(std::string word)
{
    for(size_t i=0;i<word.length();i++)
    {
        word[i]=tolower(word[i]);
    }
    return word.c_str();
}

// Remove file extension
QString removeExtension(QString path)
{
    int dot_pos = path.lastIndexOf('.');

    return lowerCase(path.left(dot_pos).toStdString());
}

// Prevents launching the game twice if the button "Launch" is pressed twice quickly
void MainWindow::delayLaunch()
{
    canLaunch=true;
}

void MainWindow::findIwads(int type)
{
    QFileInfoList imagesInfo;
    QString doomwaddirstr = QString(qgetenv("DOOMWADDIR"));

    // Find the IWADs in the correct folder depending on the OS
#ifdef __APPLE__
        if(!QDir(dotfolder).exists())
            QDir().mkdir(dotfolder);

        QProcess::startDetached("cp", {execPath+"/../Resources/"+exeName+".wad",dotfolder});

        QDir directory(dotfolder);
        imagesInfo = directory.entryInfoList(QStringList() << "*.WAD",QDir::Files);

        doomwaddirstr = doomwaddirstr.split(":")[0];
#elif __linux__
        if(!QDir(dotfolder).exists())
            QDir().mkdir(dotfolder);

        QDir directory(dotfolder);
        imagesInfo = directory.entryInfoList(QStringList() << "*.WAD",QDir::Files);

        doomwaddirstr = doomwaddirstr.split(":")[0];
#else
        QDir directory = execPath;
        imagesInfo = directory.entryInfoList(QStringList() << "*.WAD",QDir::Files);

        doomwaddirstr = doomwaddirstr.split(";")[0];
#endif

    QDir doomwaddir(doomwaddirstr);
    imagesInfo += doomwaddir.entryInfoList(QStringList() << "*.WAD",QDir::Files);

    int size = settings.beginReadArray("iwadfolders");
    if(size!=0)
    {
        for (int i = 0; i < size; i++) {
            settings.setArrayIndex(i);
            QString folder = settings.value("folder").toString();
            if(folder!="")
            {
                QDir folder0(folder);
                imagesInfo += folder0.entryInfoList(QStringList() << "*.WAD",QDir::Files);
            }
        }
    }
    settings.endArray();

    foreach(QFileInfo imageInfo, imagesInfo)
    {
        QString toLow = imageInfo.baseName().toLower();

        bool found = false;
        for (QPair<QString, QString> l : iwads_paths)
        {
            if (l.first == toLow)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            iwads_paths.push_back({toLow, imageInfo.absoluteFilePath()});
        }
    }

    // This makes sure that a logical order to display the IWADs is followed
    // I think doing this is better than having random orders like: Doom 2 -> TNT -> Doom
    QStringList doomIWADs = doom1IWADs + doom2IWADs;

    int cur = 0;
    for(int i = 0; i< doomIWADs.size(); i++)
    {
        for(int j = 0; j < iwads_paths.size(); j++)
        {
            if(doomIWADs.at(i) == iwads_paths[j].first)
            {
                ui->iwad_comboBox->addItem(iwads_paths[j].first);
                iwads_paths.swapItemsAt(j, cur);
                cur++;
                doomIWADs.replace(i, " ");
                break;
            }
        }
    }
}

// MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::pMainWindow = this;

    execPath = QCoreApplication::applicationDirPath();
#ifdef _WIN32
historyPath = QCoreApplication::applicationDirPath()+"\\history.states";
#endif

    // Allow files to be droped in the launcher (*.wad *.lmp *.deh *.bex)
    setAcceptDrops(true);

    ui->reloadLeaderboard_toolButton->hide();

    // Add event filter to the "additional arguments" box
    ui->additionalArguments_textEdit->installEventFilter(this);

    // Add event filter to the Launch button. This will allow you to see the current parameters when you hover your mouse
    ui->launchGame_pushButton->installEventFilter(this);

    enable_disable_skill_comboBox();

    // set the settings and console windows
    settingsWindow = new Settings;
    consoleWindow = new Console;
    historyListWindow = new historyList;
    endoomWindow = new endoom;

    // The "episode" and "level" boxes can only take 2 numbers
    // This approach also prevents a problem where Qt tried to add spaces to those boxes if no numbers were added
    QRegularExpression rgx("[0-9]{2}");
    QValidator *comValidator = new QRegularExpressionValidator (rgx, this);
    ui->episode_lineEdit->setValidator(comValidator);
    ui->level_lineEdit->setValidator(comValidator);

    ui->stackedWidget->setAttribute(Qt::WA_TranslucentBackground);

#ifdef _WIN32
    ui->tooltip_textBrowser->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:8pt; font-weight:400; font-style:normal;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Don't see any IWAD?     ^</span></p><p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Go to the settings and add the folder you have your IWADs in, to the </span><span style=\" font-size:9pt; font-weight:700;\">IWAD Folders</span><span style=\" font-size:8pt;\"> list.</span></p><p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Then restart the Launcher</span></p></body></html>");
#endif

    // Keyboard shortcut
    // Qt::CTRL is the CTRL key for Windows/Linux and is the CMD key for MacOS

    // Closes the active window
    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(foo3()));
    shortcut3->setAutoRepeat(false);

    // Set the parameters text correctly
    if(settings.value("toggle1a").toString()!="")
    {
        fastParam = settings.value("toggle1a").toString();
        nomoParam = settings.value("toggle2a").toString();
        respawnParam = settings.value("toggle3a").toString();
        solonetParam = settings.value("toggle4a").toString();
        ui->fast_checkBox->setText(settings.value("toggle1t").toString());
        ui->fast_checkBox->setToolTip(fastParam);
        ui->nomo_checkBox->setText(settings.value("toggle2t").toString());
        ui->nomo_checkBox->setToolTip(nomoParam);
        ui->respawn_checkBox->setText(settings.value("toggle3t").toString());
        ui->respawn_checkBox->setToolTip(respawnParam);
        ui->solonet_checkBox->setText(settings.value("toggle4t").toString());
        ui->solonet_checkBox->setToolTip(solonetParam);
    }


    findIwads(0);


    // If no IWAD found, show a tool tip
    if(ui->iwad_comboBox->count()==0)
    {
        ui->tooltip_textBrowser->show();
    }
    else
    {
        ui->tooltip_textBrowser->hide();
    }

    // Load settings and apply them
    ui->complevel_comboBox->setCurrentIndex(settings.value("complevel").toInt());
    ui->difficulty_comboBox->setCurrentIndex(settings.value("skill").toInt());
    ui->episode_lineEdit->setText(settings.value("warp1").toString());
    ui->level_lineEdit->setText(settings.value("warp2").toString());
    int pwadCount = settings.value("pwadCount").toInt();
    for(int i=0; i<pwadCount;i++)
    {
        ui->wads_listWidget->addItem(settings.value(("pwad"+std::to_string(i)).c_str()).toString());

    }
    ui->fast_checkBox->setChecked(settings.value("fast").toBool());
    ui->nomo_checkBox->setChecked(settings.value("nomo").toBool());
    ui->respawn_checkBox->setChecked(settings.value("respawn").toBool());
    ui->fullscreen_checkBox->setChecked(settings.value("fullscreen").toBool());
    ui->resolution_comboBox->setCurrentIndex(settings.value("geom").toInt());
    if(ui->iwad_comboBox->count()>=settings.value("iwad").toInt())
    {
        ui->iwad_comboBox->setCurrentIndex(settings.value("iwad").toInt());
    }
    ui->solonet_checkBox->setChecked(settings.value("solonet").toBool());
    ui->additionalArguments_textEdit->append(settings.value("argumentText").toString());

    ui->record_lineEdit->setText(settings.value("recorddemo").toString());
    ui->playback_lineEdit->setText(settings.value("playdemo").toString());
    ui->viddump_lineEdit->setText(settings.value("viddump").toString());
    ui->hud_lineEdit->setText(settings.value("hud").toString());
    ui->config_lineEdit->setText(settings.value("config").toString());

    ui->playback_comboBox->setCurrentIndex(settings.value("demoplaybox").toInt());

    if(ui->playback_comboBox->currentIndex()!=1)
    {
        ui->viddump_lineEdit->setHidden(true);
        ui->viddump_pushButton->setHidden(true);
    }

    if(ui->viddump_lineEdit->text()=="")
        ui->viddump_lineEdit->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    else
        ui->viddump_lineEdit->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");

    if(ui->hud_lineEdit->text()=="")
        ui->hud_lineEdit->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    else
        ui->hud_lineEdit->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");

    if(ui->config_lineEdit->text()=="")
        ui->config_lineEdit->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    else
        ui->config_lineEdit->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");



    if(settings.value("maxskilllevel").toString()!="")
        changeMaxSkillLevel(settings.value("maxskilllevel").toInt());

    if(ui->iwad_comboBox->currentIndex()==-1 && ui->iwad_comboBox->count()!=0)
        ui->iwad_comboBox->setCurrentIndex(0);

    if(ui->episode_lineEdit->text()=="")
    {
        ui->difficulty_comboBox->setEnabled(false);
        ui->difficulty_label->setEnabled(false);
    }

    QStringList arguments = qApp->arguments();
        if(arguments.count() > 1)
        {
             for(int i=1; i<arguments.count(); i++)
             {
                    QString absPath = arguments.at(i);
                    dropFile(absPath);
             }
        }
}

// Drag Event for *.wad *.lmp *.state *.deh *.bex
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::dropFile(QString fileName)
{
    int dot_pos = fileName.lastIndexOf('.');
    if (dot_pos == -1) return;

    QString tmp = lowerCase(fileName.mid(dot_pos+1).toStdString());

    if(tmp=="lmp")
    {
            ui->tabs->setCurrentIndex(2);
            ui->playback_lineEdit->setText(fileName);
            std::ifstream file;
            file.open(fileName.toStdString());
            std::string line;

            bool found_footer = false;
            while(getline(file, line, '\n'))
            {
                if(line.substr(0,5)=="-iwad")
                {
                    found_footer = true;
                    ui->wads_listWidget->clear();

                    QStringList argList;
                    std::string tmp;
                    for (size_t i = 0; i < line.size(); i++)
                    {
                        if (line[i] != ' ' && line[i] != '\"')
                        {
                            tmp += line[i];
                        }
                        else if (!tmp.empty())
                        {
                            argList.push_back(QString::fromStdString(tmp));
                            tmp.clear();
                        }
                    }
                    if (!tmp.empty())
                    {
                        argList.push_back(QString::fromStdString(tmp));
                        tmp.clear();
                    }

                    for(int i=0;i<argList.count()-1;i++)
                    {
                        if(argList[i]=="-iwad")
                        {
                            dot_pos = argList[i+1].lastIndexOf('.');

                            int iwad_index = ui->iwad_comboBox->findText(argList[i+1].left(dot_pos));
                            if (iwad_index != -1)
                            {
                                ui->iwad_comboBox->setCurrentIndex(iwad_index);
                            }
                        }
                        else if(argList[i]=="-file" || argList[i] == "-deh")
                        {
                            QStringList files;
                            for(int ii=i+1; ii < argList.count(); ii++)
                            {
                                if(argList[ii].size() == 0 || argList[ii][0] == '-')
                                {
                                    break;
                                }

                                QString tmp = removeExtension(argList[ii]);
                                files.append(tmp);
                            }

                            int size = settings.beginReadArray("pwadfolders");
                            if(size!=0 && !files.empty())
                            {
                                for (int i = 0; i < size; i++) {
                                    settings.setArrayIndex(i);
                                    QString folder = settings.value("folder").toString();
                                    if(folder!="")
                                    {
                                        QDir path(folder);
                                        QStringList files0 = path.entryList(QDir::Files);
                                        foreach(QString file0, files0)
                                        {
                                            QString tmp = removeExtension(file0);
                                            for(int i=0; i<files.count(); i++)
                                            {
                                                if(files[i].toStdString() == tmp.toStdString())
                                                {
                                                    ui->wads_listWidget->addItem(folder+"/"+file0);
                                                    files.remove(i);
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            settings.endArray();



                            if(files.count()!=0)
                            {
                                QString folder;
#ifdef _WIN32
                                folder = execPath;
#else
                                folder = dotfolder;
#endif
                                QDir path(folder);
                                QStringList files0 = path.entryList(QDir::Files);
                                QString f = QString(qgetenv("DOOMWADPATH"));
                                int prev = 0;
                                int tilDOOMWADPATH = files0.size();
                                for(int j = 0; j<f.length(); j++)
                                {
#ifdef _WIN32
                                    if (f.at(j) == ';' || j+1 == f.length())
#else
                                    if (f.at(j) == ':' || j+1 == f.length())
#endif
                                    {
                                        files0.append(QDir(f.mid(prev, j-prev)).entryList(QDir::Files));
                                        prev = j+1;
                                    }
                                }

                                for(int j=0; j<files0.count(); j++)
                                {
                                    for(int i=0; i<files.count(); i++)
                                    {
                                        if(lowerCase(files[i].toStdString())==lowerCase(files0.at(j).toStdString()))
                                        {
                                            if(j < tilDOOMWADPATH)
                                                ui->wads_listWidget->addItem(folder+"/"+files0.at(j));
                                            else
                                            {
#ifdef _WIN32
                                                ui->wads_listWidget->addItem("%DOOMWADPATH%/"+files0.at(j));
#else
                                                ui->wads_listWidget->addItem("$DOOMWADPATH/"+files0.at(j));
#endif
                                            }
                                            files.remove(i);
                                            break;
                                        }
                                    }
                                }
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
    else if(tmp=="wad" || tmp=="bex" || tmp=="deh" || tmp=="zip")
    {
        QStringList wadsToAdd;
        wadsToAdd.append(fileName);
        addWads(wadsToAdd);
        ui->tabs->setCurrentIndex(1);
    }
    else if(tmp=="state")
    {
           states::LoadState(fileName, 0);
    }
}

void MainWindow::demoDialog_accepted()
{
    ui->iwad_comboBox->setCurrentIndex(demoDialog->get_iwad_index());
    ui->wads_listWidget->clear();
    ui->wads_listWidget->addItems(demoDialog->get_files_list());
}

// Drop Event for *.wad *.lmp *gfd
void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        dropFile(fileName);
    }
}

void MainWindow::on_actionLoad_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Load State"),settings.value("statefile").toString(),tr("state files (*.state)"));
    if(fileNames.length()>0)
    {
        settings.setValue("statefile", fileNames[0]);
        states::LoadState(fileNames[0], 0);
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save State"),settings.value("statefile").toString(),tr("state files (*.state)"));
    if(fileName != "")
    {
        settings.setValue("statefile", fileName);
        states::SaveState(fileName);
    }
}

void MainWindow::on_actionGithub_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Pedro-Beirao/dsda-launcher"));
}

void MainWindow::on_actionGithub_2_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/kraflab/dsda-doom"));
}

void MainWindow::on_actionCheck_for_updates_triggered()
{
            if (!QSslSocket::supportsSsl())
            {
                showSSLDialog();
                return;
            }

            QString launcherV;

            QNetworkRequest req(QUrl("https://api.github.com/repos/Pedro-Beirao/dsda-launcher/releases/latest"));
            req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            QJsonObject json;
            QNetworkAccessManager nam;
            QNetworkReply *reply = nam.get(req);
            while (!reply->isFinished())
            {
                qApp->processEvents();
            }
            QByteArray response_data = reply->readAll();
            QJsonDocument jsondoc = QJsonDocument::fromJson(response_data);
            QJsonObject jsonobj = jsondoc.object();
                foreach(const QString& key, jsonobj.keys()) {
                    QJsonValue value = jsonobj.value(key);
                    if(key=="name")
                    {
                        if(version!=value.toString())
                        {
                            QMessageBox msgBox;
                            msgBox.setText("DSDA-Launcher "+version);
                            msgBox.setInformativeText("Available: "+value.toString());
                            QPushButton* pButtonYes = msgBox.addButton(tr("Update"), QMessageBox::YesRole);
                            msgBox.addButton(tr("Ignore"), QMessageBox::NoRole);
                            msgBox.setDefaultButton(pButtonYes);
                            msgBox.exec();
                            if (msgBox.clickedButton()==pButtonYes)
                            {
                                QDesktopServices::openUrl(QUrl("https://github.com/Pedro-Beirao/dsda-launcher/releases/tag/"+launcherV));
                            }
                        }
                        else
                        {
                            QMessageBox msgBox;
                            msgBox.setText("DSDA-Launcher "+version);
                            msgBox.setInformativeText("Up to Date");
                            msgBox.addButton(tr("Ignore"), QMessageBox::NoRole);
                            msgBox.exec();
                        }
                    }
                }

            reply->deleteLater();
}

void MainWindow::on_actionCheck_for_Updates_triggered()
{
    if (!QSslSocket::supportsSsl())
    {
        showSSLDialog();
        return;
    }

    QString portversion;

    QString path;

#ifdef __APPLE__
        path = execPath+"/../Resources/"+exeName;
#elif __linux__
        path = execPath+"/"+exeName;
#else
        path = execPath+"/"+exeName+".exe";
#endif
    QFile port = QFile(path);
    if(port.exists())
    {
        QProcess *process = new QProcess;
        process->setWorkingDirectory(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
        process->start(path, {"-v"});
        process->waitForStarted();
        std::string data;

        while(process->waitForReadyRead())
            data.append(process->readAll());

        std::stringstream  stream(data);
        stream >> data >> data;
        portversion = data.c_str();
    }

    QNetworkRequest req0(QUrl("https://api.github.com/repos/kraflab/dsda-doom/releases/latest"));
    req0.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json0;
    QNetworkAccessManager nam0;
    QNetworkReply *reply0 = nam0.get(req0);
    while (!reply0->isFinished())
    {
        qApp->processEvents();
    }
    QByteArray response_data = reply0->readAll();
    QJsonDocument jsondoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonobj = jsondoc.object();
        foreach(const QString& key, jsonobj.keys()) {
            QJsonValue value = jsonobj.value(key);
            if(key=="name")
            {
                if(portversion!=value.toString())
                {
                    QMessageBox msgBox;
                    msgBox.setText("DSDA-Doom "+portversion);
                    msgBox.setInformativeText("Available: "+value.toString());
                    QPushButton* pButtonYes;
                    pButtonYes = msgBox.addButton(tr("Update"), QMessageBox::YesRole);
                    msgBox.addButton(tr("Ignore"), QMessageBox::NoRole);
                    msgBox.setDefaultButton(pButtonYes);
                    msgBox.exec();
                    if (msgBox.clickedButton()==pButtonYes)
                    {
                        QDesktopServices::openUrl(QUrl("https://www.doomworld.com/forum/topic/118074-dsda-doom-source-port-v0225/"));
                    }
                }
                else
                {
                    QMessageBox msgBox;
                    msgBox.setText("DSDA-Doom "+portversion);
                    msgBox.setInformativeText("Up to Date");
                    msgBox.addButton(tr("Ignore"), QMessageBox::NoRole);
                    msgBox.exec();
                }
            }
        }

    reply0->deleteLater();
}

void MainWindow::on_actionSet_triggered()
{
    settingsWindow->show();
    settingsWindow->activateWindow();
    settingsWindow->raise();
}

void MainWindow::on_actionTips_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("A few tips you should know:");
    msgBox.setInformativeText("- Drag .wad / .deh files on top of the launcher to add them to the loaded files\n\n- Drag .lmp files on top of the launcher to play the demo and autoselect the correct IWAD, PWADs and complevel\n\n- For the mentioned autoselect to work correctly, go to the settings and set the PWADs folders");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}
void MainWindow::on_actionWhat_is_this_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("State files");
    msgBox.setInformativeText("These .state files save all the parameters selected on the launcher, and lets you load them again whenever you need");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::on_actionCommand_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export command line"),settings.value("batfile").toString(),tr("batch files (*.bat *.sh *.zsh *.command)"));
    if(fileName != "")
    {
        settings.setValue("batfile", fileName);
        on_launchGame_pushButton_clicked(false,true,fileName.toStdString());
    }
}

void MainWindow::on_actionOpen_IWAD_folder_triggered()
{
    foo();
}

void MainWindow::on_actionOpen_Console_triggered()
{
    on_console_pushButton_clicked();
}

void MainWindow::on_actionHistory_triggered()
{
    if (historyListWindow->isHidden())
    {
        historyListWindow->getHistory();
    }
    historyListWindow->show();
    historyListWindow->activateWindow();
    historyListWindow->raise();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::foo() // CTRL+O runs this function to open the folder where the IWADs should be placed in
{
#ifdef __APPLE__
        QProcess::startDetached("open", {dotfolder});
#elif __linux__
        QProcess::startDetached("xdg-open", {dotfolder});
#else
        QProcess::startDetached("explorer.exe", {execPath});
#endif
}


void MainWindow::foo3() // CTRL+W runs this function close the active window
{
    QWidget *currentWindow = QApplication::activeWindow();
    currentWindow->close();
}

void MainWindow::addWads(QStringList fileNames) // Click the + button to add a wad
{
    ui->wads_listWidget->addItems(fileNames);
}


std::string arguments = " ";

void MainWindow::addToArguments(QString string)
{
    if(ui->additionalArguments_textEdit->toPlainText().length()>1 && ui->additionalArguments_textEdit->toPlainText().back()!=' ')
        ui->additionalArguments_textEdit->setText(ui->additionalArguments_textEdit->toPlainText()+" "+string);
    else
        ui->additionalArguments_textEdit->setText(ui->additionalArguments_textEdit->toPlainText()+string);
}

bool isFast=false;
bool isNoMo =false;
bool isRespawn=false;
bool isSoloNet = false;
std::string isFullscreen="w";

void MainWindow::error(QProcess::ProcessError error)
{
  qDebug() << "Error: " << error;
}

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

    endoomWindow->showEndoom(endoomString);

    endoomWindow->show();
    endoomWindow->activateWindow();
    endoomWindow->raise();
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

      if (qs.startsWith("\033"))
      {
         endoomString += qs;
      }
      else
      {
         consoleWindow->changeText(buf);
      }
}

void MainWindow::started()
{
    running = true;
}

void MainWindow::gameIsRunning()
{
    QMessageBox msgBox;
    msgBox.setText(exeName+" is still running.");
    msgBox.addButton("Ok", QMessageBox::YesRole);
    msgBox.exec();
}

void MainWindow::on_launchGame_pushButton_clicked(bool onExit, bool returnTooltip, std::string exportCmd) // Runs when you click the launch button or when you close the launcher (When closing, it will not run the game, but actually just save the settings)
{
    if(!canLaunch) // Dont allow 2 launchs in the time of 2 sec
        return;

    if(running && !returnTooltip)
    {
        gameIsRunning();
        return;
    }

    int complevelIndex = ui->complevel_comboBox->currentIndex();
    int diffIndex = ui->difficulty_comboBox->currentIndex();

    if(onExit)
        {
            settings.setValue("iwad",ui->iwad_comboBox->currentIndex());

            // Again, we need to remove the setting if the additional parameters box is empty so that it does not appear when we open the launcher again
            if(ui->additionalArguments_textEdit->toPlainText().toStdString()!="")
            {
                settings.setValue("argumentText",ui->additionalArguments_textEdit->toPlainText().toStdString().c_str());
            }
            else
            {
                settings.remove("argumentText");
            }
            settings.setValue("fullscreen", ui->fullscreen_checkBox->isChecked());
            settings.setValue("geom",ui->resolution_comboBox->currentIndex());

            settings.setValue("solonet",isSoloNet);
            settings.setValue("respawn",isRespawn);
            settings.setValue("nomo",isNoMo);
            settings.setValue("fast",isFast);

            settings.setValue("complevel",complevelIndex);
            settings.setValue("skill",diffIndex);

            settings.setValue("warp1",ui->episode_lineEdit->text().toStdString().c_str());
            settings.setValue("warp2",ui->level_lineEdit->text().toStdString().c_str());

            // We need to remove the setting if the warp number is deleted so that it does not appear when we open the launcher again
            // gzdoom does not do this for the arguments box (at the time of writing, at least) and it drives me nuts
            if(ui->episode_lineEdit->text().toStdString()=="")
            {
                settings.remove("warp1");
            }
            if(ui->level_lineEdit->text().toStdString()=="")
            {
                settings.remove("warp2");
            }

            if(ui->record_lineEdit->text().toStdString()!="")
            {
                settings.setValue("recorddemo",ui->record_lineEdit->text());
            }
            else
            {
                settings.remove("recorddemo");
            }

            if(ui->playback_lineEdit->text().toStdString()!="")
            {
                settings.setValue("playdemo",ui->playback_lineEdit->text());
            }
            else
            {
                settings.remove("playdemo");
            }

            if(ui->viddump_lineEdit->text().toStdString()!="")
            {
                settings.setValue("viddump",ui->viddump_lineEdit->text());
            }
            else
            {
                settings.remove("viddump");
            }

            if(ui->hud_lineEdit->text().toStdString()!="")
            {
                settings.setValue("hud",ui->hud_lineEdit->text());
            }
            else
            {
                settings.remove("hud");
            }

            if(ui->config_lineEdit->text().toStdString()!="")
            {
                settings.setValue("config",ui->config_lineEdit->text());
            }
            else
            {
                settings.remove("config");
            }

            settings.setValue("demoplaybox", ui->playback_comboBox->currentIndex());

            settings.setValue("pwadCount", ui->wads_listWidget->count());
            for(int i=0; i<ui->wads_listWidget->count();i++)
            {
                settings.setValue(("pwad"+std::to_string(i)).c_str(),ui->wads_listWidget->item(i)->text());
            }

            settings.setValue("exeName", exeName);

            settings.setValue("version", version);

            return;
        }

    QStringList argList;

    /* Complevels:
        Default
        1 - Doom v1.666
        2 - Doom v1.9
        3 - Ultimate Doom & Doom95
        4 - Final Doom
        5 - DOSDoom
        6 - TASDOOM
        7 - Boom's inaccurate vanilla compatibility mode
        8 - Boom v2.01
        9 - Boom v2.02
        10 - LxDoom
        11 - MBF
     12—16 - PrBoom (old versions)
        17 - Current PrBoom
        21 - MBF 21

        If the complevel starts with 'D', then dont use the "-complevel" parameter
        Otherwise, run "-complevel *First+Second char of the string*"
    */
    std::string complevelString = ui->complevel_comboBox->currentText().toStdString();
    if(ui->complevel_comboBox->isEnabled() && complevelString[0]!='D')
    {
        argList.append("-complevel");
        QString complevelNum;
        complevelNum.push_back(complevelString[0]);
        complevelNum.push_back(complevelString[1]);
        argList.append(complevelNum);
    }

    // Difficulty or Skill
    if(ui->difficulty_comboBox->isEnabled() && ui->difficulty_comboBox->currentIndex()!=0)
    {
        argList.append("-skill");
        argList.append((std::to_string(diffIndex)).c_str());
    }

    // Warping in Doom takes 2 boxes. 1 for the episode, 1 for the mission
    // Warping in Doom 2 takes 1 box, for the map
    if(ui->level_lineEdit->text().toStdString()!= "" && !ui->level_lineEdit->isHidden())
    {
        argList.append("-warp");
        argList.append(ui->episode_lineEdit->text());
        argList.append(ui->level_lineEdit->text());
    }
    else if(ui->episode_lineEdit->text().toStdString()!= "" && ui->level_lineEdit->isHidden())
    {
        argList.append("-warp");
        argList.append(ui->episode_lineEdit->text());
    }

    /* You can load 3 types of files.
        *.wad -file
        *.deh -deh
        *.bex -deh
    */
    if(ui->wads_listWidget->count()>0)
    {
        argList.append("-file");
        for(int item=0;item < ui->wads_listWidget->count(); item++)
        {
            std::string fileToAdd = ui->wads_listWidget->item(item)->text().toStdString();
#ifdef _WIN32
            for(int i=0; i<fileToAdd.length();i++)
            {
                if(fileToAdd[i]=='/')
                    fileToAdd[i]='\\';
            }
#endif
            if(fileToAdd.substr(0,5) == "$DOOM")
                fileToAdd = fileToAdd.substr(13);
            else if (fileToAdd.substr(0,5) == "%DOOM")
                fileToAdd = fileToAdd.substr(14);

            if(returnTooltip)
                argList.append(("\""+fileToAdd+"\"").c_str());
            else
                argList.append((fileToAdd).c_str());
        }
    }


    // Again, these are the parameters available on toggles
    if(isFast)
    {
        QString tmp = "";
        for (int i = 0; i < fastParam.length(); i++)
        {
            if (fastParam.at(i) == ';')
            {
                argList.append(tmp);
                tmp = "";
                continue;
            }
            tmp += fastParam.at(i);
        }
        argList.append(tmp);
    }
    if(isNoMo)
    {
        QString tmp = "";
        for (int i = 0; i < nomoParam.length(); i++)
        {
            if (nomoParam.at(i) == ';')
            {
                argList.append(tmp);
                tmp = "";
                continue;
            }
            tmp += nomoParam.at(i);
        }
        argList.append(tmp);
    }
    if(isRespawn)
    {
        QString tmp = "";
        for (int i = 0; i < respawnParam.length(); i++)
        {
            if (respawnParam.at(i) == ';')
            {
                argList.append(tmp);
                tmp = "";
                continue;
            }
            tmp += respawnParam.at(i);
        }
        argList.append(tmp);
    }
    if(isSoloNet)
    {
        QString tmp = "";
        for (int i = 0; i < solonetParam.length(); i++)
        {
            if (solonetParam.at(i) == ';')
            {
                argList.append(tmp);
                tmp = "";
                continue;
            }
            tmp += solonetParam.at(i);
        }
        argList.append(tmp);
    }

    if(ui->resolution_comboBox->currentIndex()==0)
    {
        if(isFullscreen=="w")
        {
            argList.append("-window");
        }
        else
        {
            argList.append("-fullscreen");
        }
    }
    else
    {
        argList.append("-geom");
        argList.append((ui->resolution_comboBox->currentText().toStdString()+isFullscreen).c_str());
    }


    if(ui->record_lineEdit->text()!="")
    {
        argList.append("-record");
        if(returnTooltip)
            argList.append("\""+ui->record_lineEdit->text()+"\"");
        else
            argList.append(ui->record_lineEdit->text());
    }

    if(ui->playback_lineEdit->text()!="")
    {
        if(ui->playback_comboBox->currentIndex()==0)
        {
            argList.append("-playdemo"); // Plays demo at normal speed
            if(returnTooltip)
                argList.append("\""+ui->playback_lineEdit->text()+"\"");
            else
                argList.append(ui->playback_lineEdit->text());
        }
        else if(ui->playback_comboBox->currentIndex()==1)
        {
            argList.append("-timedemo"); // Used for viddumping
            if(returnTooltip)
                argList.append("\""+ui->playback_lineEdit->text()+"\"");
            else
                argList.append(ui->playback_lineEdit->text());
            if(ui->viddump_lineEdit->text().length()>2)
            {
                argList.append("-viddump");
                if(returnTooltip)
                    argList.append("\""+ui->viddump_lineEdit->text()+"\"");
                else
                    argList.append(ui->viddump_lineEdit->text());
            }
        }
        else if(ui->playback_comboBox->currentIndex()==2)
        {
            argList.append("-fastdemo"); // Used for benchmarks
            if(returnTooltip)
                argList.append("\""+ui->playback_lineEdit->text()+"\"");
            else
                argList.append(ui->playback_lineEdit->text());
        }
    }

    if(ui->hud_lineEdit->text()!="")
    {
        argList.append("-hud");
        if(returnTooltip)
            argList.append("\""+ui->hud_lineEdit->text()+"\"");
        else
            argList.append(ui->hud_lineEdit->text());
    }

    if(ui->config_lineEdit->text()!="")
    {
        argList.append("-config");
        if(returnTooltip)
            argList.append("\""+ui->config_lineEdit->text()+"\"");
        else
            argList.append(ui->config_lineEdit->text());
    }

    if (ui->track_comboBox->currentIndex()==1)
        argList.append("-track_pacifist");
    else if(ui->track_comboBox->currentIndex()==2)
        argList.append("-track_100k");

    if (ui->time_comboBox->currentIndex()==1)
        argList.append("-time_use");
    else if(ui->time_comboBox->currentIndex()==2)
        argList.append("-time_keys");
    else if(ui->time_comboBox->currentIndex()==3)
        argList.append("-time_secrets");
    else if(ui->time_comboBox->currentIndex()==4)
        argList.append("-time_all");


    if (ui->additionalArguments_textEdit->toPlainText() != "")
    {
        std::string str = ui->additionalArguments_textEdit->toPlainText().toStdString()+" ";

        std::string strToAdd="";
        for( size_t i=0; i<str.length(); i++){

            char c = str[i];
            if( c == ' '){
                if (strToAdd != "")
                {
                    argList.append(strToAdd.c_str());
                    strToAdd="";
                }
            }else if(c == '\"' ){
                i++;
                while( str[i] != '\"' ){ strToAdd.push_back(str[i]); i++; }
            }else{
                strToAdd.push_back(c);
            }
        }
    }


    if(returnTooltip)
    {
        std::string argStr;
        std::string argStrComplete;
        foreach(QString p, argList)
        {
            argStrComplete.append((p+" ").toStdString());

            int lastBar = 0;
            for(qsizetype i=0; i<p.length(); i++)
            {
                if(p[i]== QDir::separator())
                {
                    lastBar=i+1;
                }
            }
            p = p.toStdString().substr(lastBar).c_str();

            if(p.length()>1 && p[0]!='"' && p[p.length()-1]=='"')
            {
                p = p.toStdString().substr(0,p.length()-1).c_str();
            }

            argStr.append((p+" ").toStdString());
        }

        if(exportCmd!="")
        {
            std::ofstream file_;
            file_.open(exportCmd);
            std::string pwads;
#ifdef __APPLE__
                file_ << ("\""+execPath+"/../Resources/"+exeName+"\" -iwad \""+iwads_paths.at(ui->iwad_comboBox->currentIndex()).second+"\" ").toStdString()+argStrComplete;
#elif __linux__
                file_ << ("\""+execPath+"/"+exeName+"\" -iwad \""+iwads_paths.at(ui->iwad_comboBox->currentIndex()).second+"\" ").toStdString()+argStrComplete;
#else
                std::replace(execPath.begin(),execPath.end(),'/','\\');
                file_ << ("\""+execPath+"\\"+exeName+".exe\" -iwad \""+iwads_paths.at(ui->iwad_comboBox->currentIndex()).second+"\" ").toStdString()+argStrComplete;
#endif
            file_.close();

            return;
        }

        QMessageBox msgBox;
        msgBox.setText("Executable: "+exeName+"\nIWAD: "+ui->iwad_comboBox->currentText()+"\nParameters: "+argStr.c_str());
        msgBox.addButton(tr("Copy"), QMessageBox::NoRole);
        QPushButton* pButtonYes = msgBox.addButton(tr("Ok"), QMessageBox::YesRole);
        msgBox.setDefaultButton(pButtonYes);
        msgBox.exec();

        if (msgBox.clickedButton()!=pButtonYes)
        {
            QClipboard *clip = QApplication::clipboard();
#ifdef __APPLE__
                    clip->setText("\""+execPath+"/../Resources/"+exeName+"\" -iwad \""+iwads_paths.at(ui->iwad_comboBox->currentIndex()).second+"\" "+argStrComplete.c_str());
#elif __linux__
                    clip->setText("\""+execPath+"/"+exeName+"\" -iwad \""+iwads_paths.at(ui->iwad_comboBox->currentIndex()).second+"\" "+argStrComplete.c_str());
#else
                    std::replace(execPath.begin(),execPath.end(),'/','\\');
                    clip->setText("\""+execPath+"\\"+exeName+".exe\" -iwad \""+iwads_paths.at(ui->iwad_comboBox->currentIndex()).second+"\" "+argStrComplete.c_str());
#endif
        }


        return;
    }

    Launch(ui->iwad_comboBox->currentText(), argList);

    SaveHistory(ui->iwad_comboBox->currentText(), argList);
}



void MainWindow::Launch(QString iwadName, QStringList argList)
{
    if (!canLaunch)
        return;

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

#ifdef __APPLE__
        QFile port = QFile(execPath+"/../Resources/"+exeName+"");
        if(port.exists())
        {
            QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
            argList.push_front(iwads_paths.at(ui->iwad_comboBox->findText(iwadName)).second);
            argList.push_front("-iwad");
            QProcess *process = new QProcess;
            process->setWorkingDirectory(homePath);
            process->start(execPath+"/../Resources/"+exeName, argList);
            connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int,QProcess::ExitStatus)));
            connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
            connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
            connect(process, SIGNAL(started()), this, SLOT(started()));
        }
        else
        {
            QMessageBox::warning(this, "dsda-launcher", exeName + " was not found in dsda-launcher.app/Contents/Resources/"+exeName);
        }
#elif __linux__
        QFile port = QFile(execPath+"/"+exeName);
        QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        argList.push_front(iwads_paths.at(ui->iwad_comboBox->findText(iwadName)).second);
        //system(("cd ~/ && " + execPath+"/dsda-doom -iwad '"+homePath+"/.dsda-doom/"+ui->iwad_comboBox->currentText().toStdString()+".wad' "+arguments+" >> "+homePath+"/.dsda-doom/LogFile.txt &").c_str());
        // Run "which" command to check if dsda-doom exists. if it does then no need to specify a path, just run a process with exeName.
        QStringList apar; apar << exeName;
        QProcess whichProcess;
        whichProcess.start("which", apar);
        whichProcess.waitForFinished();
        QString processPath;
        // If it finds an executable in the dsda-launcher folder, it will prioritize it over the one installed in a bin folder.
        if(port.exists()) processPath = execPath + "/" + exeName;
        else processPath = exeName;
        if(whichProcess.readAllStandardOutput() != "")
        {
            QProcess *process = new QProcess;
            process->setWorkingDirectory(homePath);
            process->start(processPath, argList);
            connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int,QProcess::ExitStatus)));
            connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
            connect(process, SIGNAL(started()), this, SLOT(started()));
        }
        else QMessageBox::warning(this, "dsda-launcher", ("Failed to launch the application executable.\nMake sure that "+ exeName+" is installed correctly through your package manager or installed with the original build instructions.\n\nIf you are sure " + exeName + " exists, symlink it to dsda-launcher's folder."));
#else
    /*
        std::string cmd = "\"" + execPath + "\\dsda-doom.exe \" -iwad \"" + execPath + "\\" + ui->iwad_comboBox->currentText().toStdString()+".wad\"" + arguments + " >> \""+ execPath+"\\LogFile.txt\" ";
        for(int i=0; i<cmd.length();i++)
        {
            if(cmd[i]=='/')
                cmd[i]='\\';
        }

        STARTUPINFO si={sizeof(si), NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, STARTF_USESHOWWINDOW, SW_SHOWNORMAL};
        PROCESS_INFORMATION pi={};
        std::wstring cmdline = std::wstring(cmd.begin(), cmd.end());
        if (CreateProcess(NULL, const_cast<wchar_t*>(cmdline.c_str()), NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS|CREATE_UNICODE_ENVIRONMENT|CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
        } else {
                QMessageBox::warning(this, "dsda-launcher", "Failed to launch the application executable.\nMake sure that the launcher is in the same folder as dsda-doom.exe");
        }

        // system() also works fine, but leaves a cmd window in the background, so CreateProcess() is better
        // system(("cmd /c \""+gamePath+"\"").c_str());

        arguments=" ";
    */
        QFile port = QFile(execPath+"/"+exeName+".exe");
        if(port.exists())
        {
            argList.push_front(iwads_paths.at(ui->iwad_comboBox->findText(iwadName)).second);
            argList.push_front("-iwad");
            QProcess *process = new QProcess;
            process->setWorkingDirectory(execPath);
            process->start(execPath+"/"+exeName+".exe", argList);
            connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int,QProcess::ExitStatus)));
            connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
            connect(process, SIGNAL(started()), this, SLOT(started()));
        }
        else
        {
            QMessageBox::warning(this, "dsda-launcher", "Failed to launch the application executable.\nMake sure that the launcher is in the same folder as "+exeName+".exe");
        }
#endif

        // Again, don't allow the launch button to work twice in the space of 2 secs
        canLaunch=false;
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

    std::ostringstream stream;
    if (QFileInfo::exists(historyPath))
    {
        std::ifstream file;
        file.open(historyPath.toStdString());

        if (!file.is_open())
        {
            return;
        }

        std::string buffer;

        while (!file.eof())
        {
            std::getline(file, buffer);
            if (buffer[0]=='-')
            {
                count++;
            }
        }
        file.seekg(0);

        while (buffer.substr(0,9)!="checksum=" && !file.eof())
        {
            std::getline(file, buffer);
        }

        if (buffer.substr(0,9)=="checksum=" && buffer.substr(9).length()>0)
        {
            if (checksum==std::atoi(buffer.substr(9).c_str()))
            {
                file.close();
                return;
            }
        }

        stream << file.rdbuf();

        file.close();
    }

    int maxhistory = settings.value("maxhistory").toInt();
    if (count >= maxhistory)
    {
        needToDelete = count - maxhistory + 1;
    }

    std::string h = "# Do not edit this file manually\n\nchecksum="+std::to_string(checksum)+"\n";
    std::string streamstr = stream.str();

    std::ofstream out(historyPath.toStdString()+"s");
    if (!needToDelete)
    {
        if (streamstr!="")
        {
            h += streamstr+"\n";
        }
        out << h;
    }
    else
    {
        if (streamstr!="")
        {
            int past = 0;
            for (size_t i = 0; i < streamstr.length(); i++)
            {
                if (streamstr.substr(i,2) == "-\n")
                {
                    if (past == needToDelete)
                    {
                        streamstr = streamstr.substr(i);
                    }
                    else
                    {
                        past++;
                    }
                }
            }
            h += streamstr+"\n";
        }
        out << h;
    }
    out.close();
    states::SaveState((historyPath.toStdString()+"s").c_str());
    remove((historyPath.toStdString()).c_str());
    rename((historyPath.toStdString()+"s").c_str(),historyPath.toStdString().c_str());
    // QProcess::startDetached("chmod", {"a-w", historyPath}); windows doesnt have chmod :(


}

// If the IWAD selected changes
void MainWindow::on_iwad_comboBox_currentIndexChanged(int index)
{
    std::string sel = (ui->iwad_comboBox->currentText()).toStdString();
    for (int i = 0; i < int(sel.length()); i++)
        {
            sel[i] = tolower(sel[i]);
        }

    // These are episode/mission based. They need both warp boxes
    if(doom1IWADs.contains(sel.c_str()))
    {
        ui->level_label->show();
        ui->level_lineEdit->show();
        ui->episode_label->setText("Episode");
    }
    else // These are map based. They need 1 warp box
    {
        ui->level_label->hide();
        ui->level_lineEdit->hide();
        ui->episode_label->setText("Level");
    }

    // Reload the DSDA leaderboards
    reloadLeaderboard(true,false);
}

// Show the console
void MainWindow::on_console_pushButton_clicked()
{
    consoleWindow->show();
    consoleWindow->activateWindow();
    consoleWindow->raise();
}

void MainWindow::changeWadLName()
{
    std::string p = ui->wads_listWidget->item(0)->text().toStdString();
    if(p.substr(p.length()-4)==".wad")
    {
        int lastBar=0;
        for( size_t i=0; i<p.length(); i++){
            if(p[i]==QDir::separator())
            {
                lastBar=i+1;
            }
        }
        p = p.substr(lastBar);
        ui->wadDSDA_lineEdit->setText(p.substr(0,p.length()-4).c_str());
    }
}

// Add pwads to be loaded
void MainWindow::on_addWads_toolButton_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Select WAD file"),settings.value("primaryPWADFolder").toString(),tr("WAD files (*.wad *.deh *.bex *.zip)"));
    if(fileNames.length()>0)
    {
        ui->wads_listWidget->addItems(fileNames);
        settings.setValue("primaryPWADFolder", fileNames[0]); // Make the folder you got this pwad to be the primary folder for pwads
    }
}

// Remove a pwad from the list
void MainWindow::on_removeWads_toolButton_clicked()
{
    ui->wads_listWidget->takeItem(ui->wads_listWidget->currentRow());
}

// These are the parameter toggles
void MainWindow::on_fast_checkBox_toggled(bool checked)
{
    isFast = checked;
}
void MainWindow::on_nomo_checkBox_toggled(bool checked)
{
    isNoMo = checked;
}
void MainWindow::on_respawn_checkBox_toggled(bool checked)
{
    isRespawn = checked;
}
void MainWindow::on_solonet_checkBox_toggled(bool checked)
{
    isSoloNet = checked;
}

void MainWindow::on_fullscreen_checkBox_toggled(bool checked)
{
    isFullscreen = checked ? "f" : "w";
}
void MainWindow::on_tooltip_pushButton_clicked()
{
    if(ui->tooltip_textBrowser->isHidden())
        ui->tooltip_textBrowser->show();
    else
        ui->tooltip_textBrowser->hide();
}

void MainWindow::on_record_pushButton_clicked() // Record demo
{
    QString demoName = QFileDialog::getSaveFileName(this, tr("Demo file"),settings.value("demofolder").toString(),tr("lmp files (*.lmp)"));
    settings.setValue("demofolder",demoName);
    ui->record_lineEdit->setText(demoName);
}

void MainWindow::on_playback_pushButton_clicked() // Play demo
{
    QString demoName = QFileDialog::getOpenFileName(this, tr("Demo file"),settings.value("demofolder").toString(),tr("lmp files (*.lmp)"));
    settings.setValue("demofolder",demoName);
    ui->playback_lineEdit->setText(demoName);
}

void MainWindow::on_additionalArguments_pushButton_clicked()
{
    if (!canLaunch)
        return;

    QString path;

#ifdef __APPLE__
        path = execPath+"/../Resources/"+exeName;
#elif __linux__
        path = execPath+"/"+exeName;
#else
        path = execPath+"/"+exeName+".exe";
#endif

    QFile port = QFile(path);
    if(port.exists())
    {
#ifdef __APPLE__
            QProcess *process = new QProcess;
            process->startDetached("sh", {"-c", "echo \""+path+" --help ; rm /tmp/dsda-doom-params.sh\" > /tmp/dsda-doom-params.sh ; chmod +x /tmp/dsda-doom-params.sh ; open -a Terminal /tmp/dsda-doom-params.sh"});
            process->deleteLater();
#elif _WIN32
            system(("start cmd.exe /k \""+ path.toStdString()+"\" --help").c_str());
#else
            // xterm is the most reliable terminal to use, but it seems a few distros do not have it
            system(("xterm -e 'bash -c \""+path.toStdString()+" --help ;bash\"'").c_str());
#endif
    }

    canLaunch=false;
    QTimer::singleShot(2000, this, SLOT(delayLaunch()));
}

QString demoFile;
void MainWindow::get_leaderboards(std::string wad, std::string level, std::string category) // Get the WR for a run from dsdarchive.com
{
    if (!QSslSocket::supportsSsl())
    {
        showSSLDialog();
        return;
    }

    QString player;
    QString time;
    QString engine;
    QString date;

    QNetworkRequest req(QUrl(QString(("https://dsdarchive.com/api/demos/records?wad="+wad+"&level="+level+"&category="+category).c_str())));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("player", "value1");

    QNetworkAccessManager nam;

    QNetworkReply *reply = nam.get(req);

    while (!reply->isFinished())
    {
        qApp->processEvents();
    }

    QByteArray response_data = reply->readAll();

    QJsonDocument jsondoc = QJsonDocument::fromJson(response_data);

    QJsonObject jsonobj = jsondoc.object();
        foreach(const QString& key, jsonobj.keys()) {
            QJsonValue value = jsonobj.value(key);
            if(key=="player")
            {
                player=value.toString();
            }
            else if(key=="time")
            {
                time=value.toString();
            }
            else if(key=="engine")
            {
                engine=value.toString();
            }
            else if(key=="date")
            {
                std::string dateString = value.toString().toStdString();
                dateString=dateString.substr(0,dateString.find("T"));
                date=dateString.c_str();

            }
            else if(key=="file")
            {
                demoFile=value.toString();
            }
        }
    ui->demoTime->setText(("Time: "+time));
    ui->demoPlayer->setText((player));
    ui->demoPort->setText((date));

    reply->deleteLater();
}

void MainWindow::on_dsda_comboBox_currentIndexChanged(int index) // This is the category box (UV speed, UV max, etc)
{
    reloadLeaderboard(false,false);
}

bool reloadingLeaderboards=false;

void MainWindow::reloadLeaderboard(bool changeWad, bool callApi)
{

    reloadingLeaderboards=true;
    std::string arg1 = ui->dsda_comboBox->currentText().toStdString();
    std::string category;

    // We need to change " " with "%20"
    if(ui->iwad_comboBox->currentText()=="heretic")
    {
        if(arg1=="SM Speed")
        {
            category = "SM%20Speed";
        }
        else if(arg1=="SM Max")
        {
            category = "SM%20Max";
        }
        else if(arg1=="BP Speed")
        {
            category = "BP%20Speed";
        }
        else if(arg1=="BP Max")
        {
            category = "BP%20Max";
        }
        else if(arg1=="NM Speed")
        {
            category = "NM%20Speed";
        }
        else if(arg1=="NM 100S")
        {
            category = "NM%20100S";
        }
        else if(arg1=="Tyson")
        {
            category = "Tyson";
        }
        else if(arg1=="Pacifist")
        {
            category = "Pacifist";
        }
        else if(arg1=="Stroller")
        {
            category = "Stroller";
        }
        else if(arg1=="NoMo")
        {
            category = "NoMo";
        }
        else if(arg1=="NoMo 100S")
        {
            category = "NoMo%20100S";
        }
        else if(arg1=="Collector")
        {
            category = "Collector";
        }
    }
    else if(ui->iwad_comboBox->currentText()=="hexen")
    {
        if(arg1=="Sk4 Speed")
        {
            category = "Sk4%20Speed";
        }
        else if(arg1=="Sk4 Max")
        {
            category = "Sk4%20Max";
        }
        else if(arg1=="Sk5 Speed")
        {
            category = "Sk5%20Speed";
        }
        else if(arg1=="Sk5 Max")
        {
            category = "Sk5%20Max";
        }
        else if(arg1=="Tyson")
        {
            category = "Tyson";
        }
        else if(arg1=="Pacifist")
        {
            category = "Pacifist";
        }
        else if(arg1=="Stroller")
        {
            category = "Stroller";
        }
        else if(arg1=="NoMo")
        {
            category = "NoMo";
        }
        else if(arg1=="NoMo 100S")
        {
            category = "NoMo%20100S";
        }
        else if(arg1=="Collector")
        {
            category = "Collector";
        }
    }
    else
    {
        if(arg1=="UV Speed")
        {
            category = "UV%20Speed";
        }
        else if(arg1=="UV Max")
        {
            category = "UV%20Max";
        }
        else if(arg1=="UV Fast")
        {
            category = "UV%20Fast";
        }
        else if(arg1=="UV Respawn")
        {
            category = "UV%20Respawn";
        }
        else if(arg1=="NM Speed")
        {
            category = "NM%20Speed";
        }
        else if(arg1=="NM 100S")
        {
            category = "NM%20100S";
        }
        else if(arg1=="Tyson")
        {
            category = "Tyson";
        }
        else if(arg1=="Pacifist")
        {
            category = "Pacifist";
        }
        else if(arg1=="Stroller")
        {
            category = "Stroller";
        }
        else if(arg1=="NoMo")
        {
            category = "NoMo";
        }
        else if(arg1=="NoMo 100S")
        {
            category = "NoMo%20100S";
        }
        else if(arg1=="Collector")
        {
            category = "Collector";
        }
    }


    std::string wad;
    std::string level;



    if(changeWad)
    {
            wad = lowerCase(ui->iwad_comboBox->currentText().toStdString()).toStdString();
            if(wad=="doomu"||wad=="doom1")
            {
                wad="doom";
            }
    }
    else
    {
        wad=lowerCase(ui->wadDSDA_lineEdit->text().toStdString()).toStdString();
    }


    /*
    if(ui->level_lineEdit->text().toStdString()!= "" && !ui->level_lineEdit->isHidden())
    {
        level = "E"+ui->episode_lineEdit->text().toStdString()+"M"+ui->level_lineEdit->text().toStdString();
    }
    else if(ui->episode_lineEdit->text().toStdString()!= "" && ui->level_lineEdit->isHidden())
    {
        if(ui->episode_lineEdit->text().toStdString().length()==1)
        {
            level = "Map0"+ui->episode_lineEdit->text().toStdString();
        }
        else
        {
            level = "Map"+ui->episode_lineEdit->text().toStdString();
        }

    }
    */
    if(ui->levelDSDA_lineEdit->text()=="" || changeWad)
    {
        if(!ui->level_lineEdit->isHidden())
        {
            level = "E1M1";
        }
        else
        {
            level = "Map01";
        }
        ui->levelDSDA_lineEdit->setText(level.c_str());
    }

    level = ui->levelDSDA_lineEdit->text().toStdString();

    wad.erase(std::remove(wad.begin(), wad.end(), ' '), wad.end());
    level.erase(std::remove(level.begin(), level.end(), ' '), level.end());

    if(lowerCase(level.substr(0,2))=="ep")
    {
        level = "Episode%20"+level.substr(2);
    }
    else if(tolower(level[0])=='e')
    {
        level = "E"+level.substr(1,1)+"M"+level.substr(3);
    }
    else if(lowerCase(level.substr(0,3))=="map")
    {
        if(level.substr(3).length()==1)
            level = "Map%200"+level.substr(3);
        else
            level = "Map%20"+level.substr(3);
    }
    else if(lowerCase(level)=="d2all")
    {
        level = "D2All";
    }

    ui->wadDSDA_lineEdit->setText(wad.c_str());

    if(callApi)
    {
        reloadingLeaderboards=false;
        get_leaderboards(wad,level,category);
    }
    else
    {
        clearLeaderboard();
    }

}

void MainWindow::keyPressEvent(QKeyEvent *event) // ENTER makes the game start
{
    if(event->key()==0x01000005 || event->key()==0x01000004) // Key is either ENTER or RETURN
    {
        on_launchGame_pushButton_clicked(false, false,"");
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *ev) // ENTER does not work on the additional parameters box
{

      if (object == (QObject*)ui->launchGame_pushButton) {
            //if (ev->type() == QEvent::Enter)
            //{
            //    on_launchGame_pushButton_clicked(false, true);
            //    return QWidget::eventFilter(object, ev);
            //}
            if(ev->type() == QEvent::MouseButtonPress)
            {
                on_launchGame_pushButton_clicked(false, false,"");
                return QWidget::eventFilter(object, ev);
            }
      }
      if (ev->type() == QEvent::KeyPress)
      {
           QKeyEvent* keyEvent = (QKeyEvent*)ev;

           if (keyEvent->key() == 0x01000005 || keyEvent->key() == 0x01000004) // Key is either ENTER or RETURN
           {
                on_launchGame_pushButton_clicked(false, false,"");
                return true;
           }
    }
      return false;
}

void MainWindow::closeEvent(QCloseEvent *event) // When closing the launcher, save the settings
{
    if(running)
    {
        gameIsRunning();
        event->ignore();
        return;
    }
    on_launchGame_pushButton_clicked(true, false,"");
    QApplication::quit();
}



void MainWindow::on_showLeaderboard_toolButton_clicked()
{
    std::string str = ui->dsda_comboBox->currentText().toStdString();
    std::replace(str.begin(), str.end(), ' ', '+');
    std::string lvl = ui->levelDSDA_lineEdit->text().toStdString();
    lvl.erase(std::remove(lvl.begin(), lvl.end(), ' '), lvl.end());
    if(tolower(lvl[0])=='e')
    {
        lvl = "E"+lvl.substr(1,1)+"M"+lvl.substr(3);
    }
    else if(lowerCase(lvl.substr(0,3))=="map")
    {
        if(lvl.substr(3).length()==1)
            lvl = "Map%200"+lvl.substr(3);
        else
            lvl = "Map%20"+lvl.substr(3);
    }
    QDesktopServices::openUrl(QUrl("https://dsdarchive.com/wads/"+ui->wadDSDA_lineEdit->text()+"/leaderboard?category="+str.c_str()+"&level="+lvl.c_str()));
}


void MainWindow::clearLeaderboard()
{
    ui->demoTime->setStyleSheet("color: rgb(150, 150, 150);");
    ui->demoPlayer->setStyleSheet("color: rgb(150, 150, 150);");
    ui->demoPort->setStyleSheet("color: rgb(150, 150, 150);");
    ui->reloadLeaderboard_toolButton->show();
}





void MainWindow::on_reloadLeaderboard_toolButton_clicked()
{
    reloadLeaderboard(false, true);
    ui->demoTime->setStyleSheet("");
    ui->demoPlayer->setStyleSheet("");
    ui->demoPort->setStyleSheet("");
    ui->reloadLeaderboard_toolButton->hide();
}


void MainWindow::on_wadDSDA_lineEdit_textChanged(const QString &arg1)
{
    clearLeaderboard();
}

void MainWindow::on_levelDSDA_lineEdit_textChanged(const QString &arg1)
{
    clearLeaderboard();
}

void MainWindow::on_viddump_lineEdit_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->viddump_lineEdit->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->viddump_lineEdit->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
}


void MainWindow::on_playback_comboBox_currentIndexChanged(int index)
{
    if(index!=1)
    {
        ui->viddump_lineEdit->setHidden(true);
        ui->viddump_pushButton->setHidden(true);
    }
    else
    {
        ui->viddump_lineEdit->setHidden(false);
        ui->viddump_pushButton->setHidden(false);
    }
}


void MainWindow::on_viddump_pushButton_clicked()
{
    QString vidName = QFileDialog::getSaveFileName(this, tr("mp4 / mkv"),QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).toStdString().c_str(),tr("video files(*.mp4 *.mkv)"));
    ui->viddump_lineEdit->setText(vidName);
}


void MainWindow::on_showCommandLine_pushButton_clicked()
{
    on_launchGame_pushButton_clicked(false,true,"");
}


void MainWindow::on_episode_lineEdit_textChanged(const QString &arg1)
{
    enable_disable_skill_comboBox();
}

void MainWindow::on_nextPage_pushButton_clicked()
{
   ui->nextPage_pushButton->setText("-");
   nextStackedWidget();
}

void MainWindow::on_previousPage_pushButton_clicked()
{
    ui->previousPage_pushButton->setText("-");
    previousStackedWidget();
}



void MainWindow::nextStackedWidget()
{
    ui->stackedWidget->widget(ui->stackedWidget->currentIndex()+1)->show();

    QPropertyAnimation *anim = new QPropertyAnimation(ui->stackedWidget->currentWidget(), "pos");
    anim->setDuration(350);
    anim->setEasingCurve(QEasingCurve::OutQuart);
    anim->setStartValue(QPoint(0, 0));
    anim->setEndValue(QPoint(-265, 0));

    QPropertyAnimation *animn = new QPropertyAnimation(ui->stackedWidget->widget(ui->stackedWidget->currentIndex()+1), "pos");
    animn->setDuration(350);
    animn->setEasingCurve(QEasingCurve::OutQuart);
    animn->setStartValue(QPoint(265, 0));
    animn->setEndValue(QPoint(0, 0));

    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
    animgroup->addAnimation(anim);
    animgroup->addAnimation(animn);

    animgroup->start(QAbstractAnimation::DeleteWhenStopped);

     connect(animgroup, SIGNAL(finished()),this,SLOT(whenAnimationFinishn()));
}

void MainWindow::previousStackedWidget()
{
    ui->stackedWidget->widget(ui->stackedWidget->currentIndex()-1)->show();

    QPropertyAnimation *anim = new QPropertyAnimation(ui->stackedWidget->currentWidget(), "pos");
    anim->setDuration(350);
    anim->setEasingCurve(QEasingCurve::OutQuart);
    anim->setStartValue(QPoint(0, 0));
    anim->setEndValue(QPoint(265, 0));

    QPropertyAnimation *animn = new QPropertyAnimation(ui->stackedWidget->widget(ui->stackedWidget->currentIndex()-1), "pos");
    animn->setDuration(350);
    animn->setEasingCurve(QEasingCurve::OutQuart);
    animn->setStartValue(QPoint(-265, 0));
    animn->setEndValue(QPoint(0, 0));

    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
    animgroup->addAnimation(anim);
    animgroup->addAnimation(animn);

    animgroup->start(QAbstractAnimation::DeleteWhenStopped);

     connect(animgroup, SIGNAL(finished()),this,SLOT(whenAnimationFinishp()));
}

void MainWindow::whenAnimationFinishn()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    ui->nextPage_pushButton->setText(">");
}

void MainWindow::whenAnimationFinishp()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
    ui->previousPage_pushButton->setText("<");
}



void MainWindow::on_hud_lineEdit_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->hud_lineEdit->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->hud_lineEdit->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
}


void MainWindow::on_config_lineEdit_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->config_lineEdit->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->config_lineEdit->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
}


void MainWindow::on_hud_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("DSDAHUD.lmp"),settings.value("hudfolder").toString(),tr("DSDAHUD file (*.lmp *.txt)"));
    if (fileName.size() != 0)
    {
        settings.setValue("hudfolder",fileName);
        ui->hud_lineEdit->setText(fileName);
    }
}


void MainWindow::on_config_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("dsda-doom.cfg"),settings.value("configfolder").toString(),tr("Config file (*.cfg *.txt)"));
    if (fileName.size() != 0)
    {
        settings.setValue("configfolder",fileName);
        ui->config_lineEdit->setText(fileName);
    }
}



void MainWindow::on_playback_lineEdit_textChanged(const QString &arg1)
{
    enable_disable_skill_comboBox();
    enable_disable_complevel_comboBox();
}

void MainWindow::enable_disable_skill_comboBox()
{
    if (ui->episode_lineEdit->text() == "")
    {
        ui->difficulty_comboBox->setEnabled(false);
        ui->difficulty_label->setEnabled(false);
        ui->difficulty_comboBox->setToolTip("Cannot select a skill level without choosing a map number");
    }
    else if (ui->playback_lineEdit->text() != "")
    {
        ui->difficulty_comboBox->setEnabled(false);
        ui->difficulty_label->setEnabled(false);
        ui->difficulty_comboBox->setToolTip("Cannot select a skill level during demo playback");
    }
    else
    {
        ui->difficulty_comboBox->setEnabled(true);
        ui->difficulty_label->setEnabled(true);
        ui->difficulty_comboBox->setToolTip("");
    }
}

void MainWindow::enable_disable_complevel_comboBox()
{
    if (ui->playback_lineEdit->text() != "")
    {
        ui->complevel_comboBox->setEnabled(false);
        ui->complevel_label->setEnabled(false);
        ui->complevel_comboBox->setToolTip("Cannot select a complevel during demo playback");
    }
    else
    {
        ui->complevel_comboBox->setEnabled(true);
        ui->complevel_label->setEnabled(true);
        ui->complevel_comboBox->setToolTip("");
    }
}

QComboBox *MainWindow::iwad_comboBox() {return ui->iwad_comboBox;}
QComboBox *MainWindow::complevel_comboBox() {return ui->complevel_comboBox;}
QLineEdit *MainWindow::episode_lineEdit() {return ui->episode_lineEdit;}
QLineEdit *MainWindow::level_lineEdit() {return ui->level_lineEdit;}
QComboBox *MainWindow::difficulty_comboBox() {return ui->difficulty_comboBox;}
QCheckBox *MainWindow::fast_checkBox() {return ui->fast_checkBox;}
QCheckBox *MainWindow::nomo_checkBox() {return ui->nomo_checkBox;}
QCheckBox *MainWindow::respawn_checkBox() {return ui->respawn_checkBox;}
QCheckBox *MainWindow::solonet_checkBox() {return ui->solonet_checkBox;}
QComboBox *MainWindow::resolution_comboBox() {return ui->resolution_comboBox;}
QCheckBox *MainWindow::fullscreen_checkBox() {return ui->fullscreen_checkBox;}
QLineEdit *MainWindow::hud_lineEdit() {return ui->hud_lineEdit;}
QLineEdit *MainWindow::config_lineEdit() {return ui->config_lineEdit;}
QComboBox *MainWindow::track_comboBox() {return ui->track_comboBox;}
QComboBox *MainWindow::time_comboBox() {return ui->time_comboBox;}
QListWidget *MainWindow::wads_listWidget() {return ui->wads_listWidget;}
QLineEdit *MainWindow::record_lineEdit() {return ui->record_lineEdit;}
QLineEdit *MainWindow::playback_lineEdit() {return ui->playback_lineEdit;}
QLineEdit *MainWindow::viddump_lineEdit() {return ui->viddump_lineEdit;}
QComboBox *MainWindow::playback_comboBox() {return ui->playback_comboBox;}
QTextEdit *MainWindow::additionalArguments_textEdit() {return ui->additionalArguments_textEdit;}

#include "demodialog.h"
#include "mainwindow.h"

QString lowerCased(std::string word)
{
    for(size_t i=0;i<word.length();i++)
    {
        word[i]=tolower(word[i]);
    }
    return word.c_str();
}

demodialog::demodialog(QStringList iwad_list, QWidget *parent)
    : QDialog(parent)
{
    QGridLayout *mainLayout = new QGridLayout;

    QLabel *description = new QLabel("No footer found on the demo.\nPlease select the correct files.\n");
    mainLayout->addWidget(description, 0, 0, 1, 3);

    QLabel *iwad_label = new QLabel("IWAD:");
    mainLayout->addWidget(iwad_label, 1, 0);

    iwad_comboBox = new QComboBox();
    iwad_comboBox->addItems(iwad_list);
    mainLayout->addWidget(iwad_comboBox, 1, 1, 1, 2);

    QLabel *files_label = new QLabel("Files:");
    mainLayout->addWidget(files_label, 2, 0, 1, 3);

    files_listWidget = new QTableWidget();
    int size = settings.beginReadArray("pwadfolders");
    if(size!=0)
    {
        for (int i = 0; i < size; i++)
        {
            settings.setArrayIndex(i);
            QString folder = settings.value("folder").toString();
            if(folder!="")
            {
                QDir path(folder);
                QStringList files0 = path.entryList(QDir::Files);
                foreach(QString file0, files0)
                {
                    int dot_pos = file0.lastIndexOf('.');
                    if (dot_pos == -1) continue;
                    QString tmp = lowerCased(file0.mid(dot_pos+1).toStdString());
                    if (tmp == "wad" || tmp == "deh" || tmp == "bex")
                    {
                        files_paths.push_back({lowerCased(file0.right(file0.lastIndexOf(QDir::separator())).toStdString()), folder + QDir::separator() + file0});
                    }
                }
            }
        }
        settings.endArray();

        QString folder;
#ifdef _WIN32
        folder = execPath;
#else
        folder = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom";
#endif
        QDir path(folder);
        QStringList files0 = path.entryList(QDir::Files);

        QString f = QString(qgetenv("DOOMWADPATH"));
        int prev = 0;
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

        foreach(QString file0, files0)
        {
            int dot_pos = file0.lastIndexOf('.');
            if (dot_pos == -1) continue;
            QString tmp = lowerCased(file0.mid(dot_pos+1).toStdString());
            if (tmp == "wad" || tmp == "deh" || tmp == "bex")
            {
                files_paths.push_back({lowerCased(file0.right(file0.lastIndexOf(QDir::separator())).toStdString()), folder + QDir::separator() + file0});
            }
        }
    }
    std::sort(files_paths.begin(), files_paths.end(), [](QPair<QString, QString> p1, QPair<QString, QString> p2)
    {
        return p1.first < p2.first;
    });
    files_listWidget->setColumnCount(2);
    files_listWidget->setRowCount(files_paths.size()/2+1);
    files_listWidget->horizontalHeader()->setVisible(false);
    files_listWidget->verticalHeader()->setVisible(false);
    files_listWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    files_listWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    files_listWidget->resizeColumnsToContents();
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < files_paths.size()/2+j; i++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem(files_paths[i + j*(files_paths.size()/2)].first);
            newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);
            files_listWidget->setItem(i, j, newItem);
        }
    }
    files_listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    connect(files_listWidget, &QTableWidget::itemSelectionChanged, this, &demodialog::update_selected_count);
    mainLayout->addWidget(files_listWidget, 3, 0, 1, 3);

    selected_count = new QLabel("0 files selected");
    mainLayout->addWidget(selected_count, 4, 0, 1, 3);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox, 5, 0, 1, 3);

    setLayout(mainLayout);
}

void demodialog::update_selected_count()
{
    selected_count->setText(QString::number(files_listWidget->selectedItems().count()) + " files selected");
}

int demodialog::get_iwad_index()
{
    return iwad_comboBox->currentIndex();
}

QStringList demodialog::get_files_list()
{
    QStringList files_list;
    for (int k = 0; k < files_listWidget->selectedItems().size(); k++)
    {
        files_list.push_back(files_paths.at(files_listWidget->selectedItems().at(k)->row() + files_listWidget->selectedItems().at(k)->column()*(files_paths.size()/2)).second);
    }
    return files_list;
}

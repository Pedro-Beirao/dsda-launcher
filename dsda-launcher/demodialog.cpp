#include "demodialog.h"

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
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel *description = new QLabel("No footer found on the demo.\nPlease select the correct files.\n");
    mainLayout->addWidget(description);

    QLabel *iwad_label = new QLabel("IWAD:");
    mainLayout->addWidget(iwad_label);

    iwad_comboBox = new QComboBox();
    iwad_comboBox->addItems(iwad_list);
    mainLayout->addWidget(iwad_comboBox);

    QLabel *files_label = new QLabel("Files:");
    mainLayout->addWidget(files_label);

    files_listWidget = new QListWidget();
    int size = settings.beginReadArray("pwadfolders");
    if(size!=0)
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
                    int dot_pos = file0.lastIndexOf('.');
                    if (dot_pos == -1) continue;
                    QString tmp = lowerCased(file0.mid(dot_pos+1).toStdString());
                    if (tmp == "wad" || tmp == "deh" || tmp == "bex")
                    {
                        files_listWidget->addItem(file0.right(std::max(file0.lastIndexOf("\\"), file0.lastIndexOf("/"))));
                    }
                }
            }
        }
    }
    settings.endArray();
    mainLayout->addWidget(files_listWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

int demodialog::get_iwad_index()
{
    return iwad_comboBox->currentIndex();
}

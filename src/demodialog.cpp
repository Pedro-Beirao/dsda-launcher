#include "demodialog.h"
#include <mainwindow.h>

demodialog::demodialog(QString footer_iwad, QStringList footer_files, QWidget *parent) : QDialog(parent)
{
    QGridLayout *mainLayout = new QGridLayout;

    QLabel *description;
    if (footer_iwad.isEmpty() && footer_files.isEmpty())
    {
        description = new QLabel("No footer found on the demo.\n");
    }
    else
    {
        description = new QLabel("");
        if (!footer_iwad.isEmpty()) description->setText("IWAD: " + footer_iwad + "\n");
        if (!footer_files.isEmpty())
        {
            QString footer_files_string;
            foreach (QString file_string, footer_files)
                footer_files_string += file_string + " ";

            description->setText(description->text() + "Files: " + footer_files_string + "\n");
        }
    }
    mainLayout->addWidget(description, 0, 0, 1, 3);

    QFrame *splitter;
    splitter = new QFrame();
    splitter->setFrameShape(QFrame::HLine);
    splitter->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(splitter, 1, 0, 1, 3);

    QLabel *iwad_label = new QLabel("IWAD:");
    mainLayout->addWidget(iwad_label, 2, 0);

    iwad_comboBox = new QComboBox();
    for (int i = 0; i < MainWindow::pMainWindow->iwad_comboBox()->count(); i++)
    {
        iwad_comboBox->addItem(MainWindow::pMainWindow->iwad_comboBox()->itemText(i));
        iwad_comboBox->setItemData(iwad_comboBox->count() - 1, MainWindow::pMainWindow->iwad_comboBox()->itemData(i, Qt::ToolTipRole), Qt::ToolTipRole);
    }
    iwad_comboBox->setCurrentIndex(iwad_comboBox->findText(removeExtension(footer_iwad).toLower()));
    mainLayout->addWidget(iwad_comboBox, 2, 1, 1, 2);

    QLabel *files_label = new QLabel("Files:");
    mainLayout->addWidget(files_label, 3, 0, 1, 3);

    files_listWidget = new QTableWidget();
    files = getFilePath_possibleFiles();

    for (int i = 0; i < MainWindow::pMainWindow->wads_listWidget()->count(); i++)
    {
        files.append(QFileInfo(MainWindow::pMainWindow->wads_listWidget()->item(i)->data(Qt::ToolTipRole).toString()));
    }
    MainWindow::pMainWindow->wads_listWidget()->clear();

    std::sort(files.begin(), files.end(), [](QFileInfo p1, QFileInfo p2) { return p1.baseName().toLower() < p2.baseName().toLower(); });
    files.erase(std::unique(files.begin(), files.end()), files.end());

    files_listWidget->setColumnCount(2);
    files_listWidget->setRowCount(files.size() / 2 + 1);
    files_listWidget->horizontalHeader()->setVisible(false);
    files_listWidget->verticalHeader()->setVisible(false);
    files_listWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    files_listWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    files_listWidget->resizeColumnsToContents();
    files_listWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    for (int j = 0; j < 2; j++)
    {
        QTableWidgetItem *newItemTemp = new QTableWidgetItem("");
        newItemTemp->setFlags(newItemTemp->flags() & ~Qt::ItemIsEditable);
        files_listWidget->setItem(files.size() / 2, j, newItemTemp);

        for (int i = 0; i < files.size() / 2 + j; i++)
        {
            if (i + j * (files.size() / 2) >= files.size()) continue;

            QTableWidgetItem *newItem = new QTableWidgetItem(files[i + j * (files.size() / 2)].fileName());
            newItem->setToolTip(files[i + j * (files.size() / 2)].absoluteFilePath());
            newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);
            files_listWidget->setItem(i, j, newItem);

            for (int a = 0; a < footer_files.count(); a++)
            {
                if (footer_files[a].toLower() == newItem->text().toLower())
                {
                    newItem->setSelected(true);
                    break;
                }
            }
        }
    }
    mainLayout->addWidget(files_listWidget, 4, 0, 1, 3);

    selected_count = new QLabel("0 files selected");
    mainLayout->addWidget(selected_count, 5, 0, 1, 3);

    update_selected_count();
    connect(files_listWidget, &QTableWidget::itemSelectionChanged, this, &demodialog::update_selected_count);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    mainLayout->addWidget(buttonBox, 6, 0, 1, 3);

    setLayout(mainLayout);

    if (iwad_comboBox->currentIndex() == -1 || files_listWidget->selectedItems().count() != footer_files.count())
    {
        this->open();
    }
    else
    {
        this->accept();
    }
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
        files_list.push_back(files.at(files_listWidget->selectedItems().at(k)->row() + files_listWidget->selectedItems().at(k)->column() * (files.size() / 2)).absoluteFilePath());
    }
    return files_list;
}

void demodialog::accept()
{
    MainWindow::pMainWindow->iwad_comboBox()->setCurrentIndex(get_iwad_index());
    MainWindow::pMainWindow->wads_listWidget()->clear();

    QStringList files_list = get_files_list();
    foreach (QString filePath, files_list)
    {
        MainWindow::pMainWindow->wads_listWidget()->addItem(getFileName(filePath));
        MainWindow::pMainWindow->wads_listWidget()->item(MainWindow::pMainWindow->wads_listWidget()->count() - 1)->setToolTip(filePath);
    }

    this->close();
}

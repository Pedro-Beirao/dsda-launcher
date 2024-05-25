#include "demodialog.h"
#include <mainwindow.h>

demodialog::demodialog(QString missing_iwad, QStringList missing_files, QWidget *parent) : QDialog(parent)
{
    QGridLayout *mainLayout = new QGridLayout;

    QLabel *description;
    if (missing_iwad.isEmpty() && missing_files.isEmpty())
    {
        description = new QLabel("No footer found on the demo.\n");
    }
    else
    {
        description = new QLabel("");
        if (!missing_iwad.isEmpty()) description->setText("Demo IWAD not found.\n");
        if (!missing_files.isEmpty()) description->setText(description->text() + "Demo PWADs/DEHs not found.\n");
    }
    mainLayout->addWidget(description, 0, 0, 1, 3);

    QLabel *iwad_label = new QLabel("IWAD:");
    mainLayout->addWidget(iwad_label, 1, 0);

    iwad_comboBox = new QComboBox();
    for (int i = 0; i < MainWindow::pMainWindow->iwad_comboBox()->count(); i++)
    {
        iwad_comboBox->addItem(MainWindow::pMainWindow->iwad_comboBox()->itemText(i));
        iwad_comboBox->setItemData(iwad_comboBox->count() - 1, MainWindow::pMainWindow->iwad_comboBox()->itemData(i, Qt::ToolTipRole), Qt::ToolTipRole);
    }
    iwad_comboBox->setCurrentIndex(MainWindow::pMainWindow->iwad_comboBox()->currentIndex());
    mainLayout->addWidget(iwad_comboBox, 1, 1, 1, 2);

    QLabel *files_label = new QLabel("Files:");
    mainLayout->addWidget(files_label, 2, 0, 1, 3);

    files_listWidget = new QTableWidget();
    files = getFilePath_possibleFiles();

    std::sort(files.begin(), files.end(), [](QFileInfo p1, QFileInfo p2) { return p1.baseName().toLower() < p2.baseName().toLower(); });

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

            for (int a = 0; a < MainWindow::pMainWindow->wads_listWidget()->count(); a++)
            {
                if (MainWindow::pMainWindow->wads_listWidget()->item(a)->data(Qt::ToolTipRole) == newItem->data(Qt::ToolTipRole))
                {
                    newItem->setSelected(true);
                }
            }
        }
    }
    mainLayout->addWidget(files_listWidget, 3, 0, 1, 3);

    selected_count = new QLabel("0 files selected");
    mainLayout->addWidget(selected_count, 4, 0, 1, 3);

    update_selected_count();
    connect(files_listWidget, &QTableWidget::itemSelectionChanged, this, &demodialog::update_selected_count);

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
        files_list.push_back(files.at(files_listWidget->selectedItems().at(k)->row() + files_listWidget->selectedItems().at(k)->column() * (files.size() / 2)).absoluteFilePath());
    }
    return files_list;
}

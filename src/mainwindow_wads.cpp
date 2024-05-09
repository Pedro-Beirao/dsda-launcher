#include "mainwindow.h"

void MainWindow::addPwads(QStringList files_list) // Click the + button to add a wad
{
    foreach (QString filePath, files_list)
    {
        ui->wads_listWidget->addItem(getFileName(filePath));
        ui->wads_listWidget->item(ui->wads_listWidget->count() - 1)->setToolTip(filePath);
    }
}

// Add pwads to be loaded
void MainWindow::on_addPwads_toolButton_clicked()
{
    QStringList files_list = QFileDialog::getOpenFileNames(this, tr("Select WAD file"), settings->value("primaryPWADFolder").toString(), tr("WAD files (*.wad *.deh *.bex *.zip)"));
    if (!files_list.isEmpty())
    {
        addPwads(files_list);
        settings->setValue("primaryPWADFolder", files_list[0]); // Make the folder you got this pwad to be the primary folder for pwads
    }
}

// Remove a pwad from the list
void MainWindow::on_removeWads_toolButton_clicked() { ui->wads_listWidget->takeItem(ui->wads_listWidget->currentRow()); }

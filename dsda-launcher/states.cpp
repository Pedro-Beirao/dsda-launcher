#include "states.h"
#include "mainwindow.h"

states::states(QObject *parent)
    : QObject{parent}
{

}

void states::LoadState(QString fileName, bool isString)
{
    std::stringstream file;

    MainWindow *ui = MainWindow::pMainWindow;

    if (isString)
    {
        file << fileName.toStdString();
    }
    else
    {
        std::ifstream filef(fileName.toStdString());
        if (!filef.is_open())
        {
            return;
        }

        file << filef.rdbuf();
        filef.close();
    }

    std::string buffer;
    std::getline(file, buffer);
    std::getline(file, buffer);
    std::getline(file, buffer);
    if(buffer.substr(0,5)=="iwad=") // iwad
    {
        for(int i=0; i<ui->iwad_comboBox()->count();i++)
        {
            if(ui->iwad_comboBox()->itemText(i).toStdString()==buffer.substr(5))
            {
                ui->iwad_comboBox()->setCurrentIndex(i);
            }
        }
        std::getline(file, buffer);
    }
    if(buffer.substr(0,10)=="complevel=") // complevel
            {
                if(buffer.substr(10)[0]=='D')
                {
                    ui->complevel_comboBox()->setCurrentIndex(0);
                }
                else
                {
                    for(int i=0; i<ui->complevel_comboBox()->count();i++)
                    {
                        std::string content=ui->complevel_comboBox()->itemText(i).toStdString().substr(0,2);
                        if(content==buffer.substr(10))
                        {
                            ui->complevel_comboBox()->setCurrentIndex(i);
                        }
                    }
                }
                std::getline(file, buffer);
            }
    if(buffer.substr(0,6)=="warp1=") // warp 1
            {
                    ui->episode_lineEdit()->setText(buffer.substr(6).c_str());
                    std::getline(file, buffer);
            }
    if(buffer.substr(0,6)=="warp2=") //warp 2
            {
                    ui->level_lineEdit()->setText(buffer.substr(6).c_str());
                    std::getline(file, buffer);
            }
    if(buffer.substr(0,6)=="skill=") // skill
            {
                  if (buffer.substr(6).length()>0)
                  {
                     ui->difficulty_comboBox()->setCurrentIndex(atoi(buffer.substr(6).c_str()));
                  }
                  else
                  {
                      ui->difficulty_comboBox()->setCurrentIndex(0);
                  }
                  std::getline(file, buffer);
            }
    if(buffer.substr(0,5)=="box1=") // box1
            {
                if(buffer.substr(5,4)=="true")
                     ui->fast_checkBox()->setChecked(true);
                else
                    ui->fast_checkBox()->setChecked(false);
                std::getline(file, buffer);
            }
    if(buffer.substr(0,5)=="box2=") // box2
            {
                if(buffer.substr(5,4)=="true")
                     ui->nomo_checkBox()->setChecked(true);
                else
                    ui->nomo_checkBox()->setChecked(false);
                std::getline(file, buffer);
            }
    if(buffer.substr(0,5)=="box3=") // box3
            {
                if(buffer.substr(5,4)=="true")
                     ui->respawn_checkBox()->setChecked(true);
                else
                    ui->respawn_checkBox()->setChecked(false);
                std::getline(file, buffer);
            }
    if(buffer.substr(0,5)=="box4=") //box4
            {
                if(buffer.substr(5,4)=="true")
                     ui->solonet_checkBox()->setChecked(true);
                else
                    ui->solonet_checkBox()->setChecked(false);
                std::getline(file, buffer);
            }
    if(buffer.substr(0,11)=="resolution=") // resolution
            {
                ui->resolution_comboBox()->setCurrentIndex(ui->resolution_comboBox()->findText(buffer.substr(11).c_str()));
                std::getline(file, buffer);
            }
    if(buffer.substr(0,11)=="fullscreen=") // fullscreen
            {
                if(buffer.substr(11,4)=="true")
                     ui->fullscreen_checkBox()->setChecked(true);
                else
                    ui->fullscreen_checkBox()->setChecked(false);
                std::getline(file, buffer);
            }
    if(buffer.substr(0,4)=="hud=") // hud
            {
                ui->hud_lineEdit()->setText(buffer.substr(4).c_str());
                std::getline(file, buffer);
            }
    if(buffer.substr(0,7)=="config=") // config
            {
                ui->config_lineEdit()->setText(buffer.substr(7).c_str());
                std::getline(file, buffer);
            }
    if(buffer.substr(0,6)=="track=") // track
            {
                if (buffer.substr(6).length()>0)
                {
                    ui->track_comboBox()->setCurrentIndex(atoi(buffer.substr(6).c_str()));
                }
                else
                {
                    ui->track_comboBox()->setCurrentIndex(0);
                }
                std::getline(file, buffer);
            }
     if(buffer.substr(0,5)=="time=") // time
             {
                 if (buffer.substr(5).length()>0)
                 {
                     ui->time_comboBox()->setCurrentIndex(atoi(buffer.substr(5).c_str()));
                 }
                 else
                 {
                     ui->time_comboBox()->setCurrentIndex(0);
                 }
                 std::getline(file, buffer);
             }
    ui->wads_listWidget()->clear();
    if(buffer.substr(0,4)=="pwad")
    {
         while (std::getline(file, buffer))
         {
            if(buffer.substr(0,7)=="endpwad")
                break;
            ui->wads_listWidget()->addItem(buffer.c_str());
         }
         std::getline(file, buffer);
    }
    if(buffer.substr(0,7)=="record=") // record demo
            {
                    ui->record_lineEdit()->setText(buffer.substr(7).c_str());
                    std::getline(file, buffer);
            }
    if(buffer.substr(0,9)=="playback=") // playback demo
            {
                    ui->playback_lineEdit()->setText(buffer.substr(9).c_str());
                    std::getline(file, buffer);
            }
    if(buffer.substr(0,13)=="demodropdown=") // demo drop down
            {
                if (buffer.substr(13).length()>0)
                {
                    ui->playback_comboBox()->setCurrentIndex(atoi(buffer.substr(13).c_str()));
                }
                else
                {
                    ui->playback_comboBox()->setCurrentIndex(0);
                }
                std::getline(file, buffer);
            }
    if(buffer.substr(0,8)=="viddump=") // demo drop down
            {
                ui->viddump_lineEdit()->setText(buffer.substr(8).c_str());
                std::getline(file, buffer);
            }
    if(buffer.substr(0,11)=="additional=") // additional arguments
            {
                ui->additionalArguments_textEdit()->setText((buffer.substr(11)).c_str());
            }

}

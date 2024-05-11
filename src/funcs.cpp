#include "funcs.h"

void openIWADsFolder() // CTRL+O runs this function to open the folder where the IWADs should be placed in
{
#ifdef __APPLE__
    QProcess::startDetached("open", {dotfolder});
#elif __linux__
    QProcess::startDetached("xdg-open", {dotfolder});
#else
    QProcess::startDetached("explorer.exe", {execPath});
#endif
}

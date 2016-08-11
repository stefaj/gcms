/* Copyright 2015 Ruan Luies */
#include "./main.h"
#include "./login.h"

#include "./virtualconcierge.h"
#include <QDebug>
#include <QDir>

bool copyRecursively(const QString &srcFilePath,
                            const QString &tgtFilePath);
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow login_;
  login_.show();

    /*  QDir dir("VirtualConcierge");
    if ( !dir.exists() ){
      dir.mkdir("VirtualConcierge");
      QString dir = QFileDialog::getExistingDirectory(0, "Open Directory",
                                                      "/home",
                                                      QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);
      copyRecursively(dir, "VirtualConcierge");
    }

    VirtualConcierge virtual_concierge;
    if ( VIRTUAL_CONCIERGE )
      virtual_concierge.showFullScreen();*/
  return a.exec();
}

bool copyRecursively(const QString &srcFilePath,
                            const QString &tgtFilePath)
{
    QFileInfo srcFileInfo(srcFilePath);
    if (srcFileInfo.isDir()) {
        QDir targetDir(tgtFilePath);
        targetDir.cdUp();
        if (!targetDir.mkdir(QFileInfo(tgtFilePath).fileName()))
            return false;
        QDir sourceDir(srcFilePath);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
        foreach (const QString &fileName, fileNames) {
            const QString newSrcFilePath
                    = srcFilePath + QLatin1Char('/') + fileName;
            const QString newTgtFilePath
                    = tgtFilePath + QLatin1Char('/') + fileName;
            if (!copyRecursively(newSrcFilePath, newTgtFilePath))
                return false;
        }
    } else {
        if (!QFile::copy(srcFilePath, tgtFilePath))
            return false;
    }
    return true;
}

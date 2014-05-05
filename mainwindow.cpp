#include "mainwindow.h"

#include "patch.h"

#include <QVBoxLayout>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDateTime>

const QString EMAIL_ADDRESS ("riftup@floop.cz");
const QString BACKUP_EXTENSION (".beforeRiftUp");

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
  QWidget *widget = new QWidget;
  QVBoxLayout *layout = new QVBoxLayout;

  QHBoxLayout *fileLayout = new QHBoxLayout;
  filePathEdit = new QLineEdit;
  fileLayout->addWidget(filePathEdit);
  QPushButton *chooseFileButton = new QPushButton(tr("Choose file"));
  connect(chooseFileButton, SIGNAL(clicked()),
          this, SLOT(chooseFileClicked()));
  fileLayout->addWidget(chooseFileButton);
  layout->addLayout(fileLayout);

  QHBoxLayout *patchLayout = new QHBoxLayout;
  QPushButton *patchButton = new QPushButton(tr("Patch file"));
  connect(patchButton, SIGNAL(clicked()),
          this, SLOT(patchClicked()));
  patchLayout->addWidget(patchButton);
  QPushButton *restoreButton = new QPushButton(tr("Restore file"));
  connect(restoreButton, SIGNAL(clicked()),
          this, SLOT(restoreClicked()));
  patchLayout->addWidget(restoreButton);
  layout->addLayout(patchLayout);

  textArea = new QTextEdit;
  textArea->setReadOnly(true);
  layout->addWidget(textArea);

  widget->setLayout(layout);
  this->setCentralWidget(widget);
  this->resize(800, 480);
}

void MainWindow::chooseFileClicked()
{
  QString filePath = QFileDialog::getOpenFileName(
    this,
    tr("Choose oclulus library file"),
    QDir::currentPath(),
    tr("Library files(*.dll *.so);;All files(*.*)"));
  if (filePath != QString::null)
    filePathEdit->setText(filePath);
}

// log debug
void MainWindow::logd(const QString &str)
{
  textArea->setTextColor(Qt::black);
  textArea->append(str);
}

// log info
void MainWindow::logi(const QString &str)
{
  textArea->setTextColor(Qt::darkGreen);
  textArea->append(str);
}

// log warning
void MainWindow::logw(const QString &str)
{
  textArea->setTextColor(Qt::yellow);
  textArea->append(str);
}

// log error
void MainWindow::loge(const QString &str)
{
  textArea->setTextColor(Qt::red);
  textArea->append(str);
}

void MainWindow::patchClicked()
{
  QFile file (filePathEdit->text());

  // %%% CHECK EXISTENCE OF THE LIBRARY %%%
  if (!file.exists()) {
    loge(tr("ERROR: File does not exist."));
    return;
  }

  logi(tr("--- Backing up the file. ---"));
  QFile backupFile (
    file.fileName() +
    QDateTime::currentDateTime().toString(".yyyyMMdd-hhmmss") +
    BACKUP_EXTENSION
  );

  // %%% CREATE A NEW BACKUP FILE %%%
  if (backupFile.exists()) {
      logw(tr("WARNING: Backup file exists. Skipping backup."));
  } else if (!QFile::copy(file.fileName(), backupFile.fileName())) {
    loge(tr("ERROR: Directory is not writable. "
            "Please rerun the application as an administrator."));
    return;
  } else {
    logd(tr("Backup file created."));
  }

  // %%% PATCH FILE %%%

  logi(tr("--- Patching the library. ---"));

  // %%% OPEN THE FILE  FOR READING %%%
  if (!file.open(QIODevice::ReadOnly)) {
    loge(tr("ERROR: File is not readable. "
            "Please rerun the application as an administrator."));
    return;
  }

  // %%% CREATE PATCHED FILE %%%
  QByteArray oldFile = file.readAll();
  QByteArray newFile = patched(oldFile);

  if (oldFile == newFile) {
    loge(tr("ERROR: Unable to find anything to be patched. "
            "If the file is not patched already, "
            "please send it to %1.")
            .arg(EMAIL_ADDRESS));
    return;
  }
  file.close();

  // %%% OPEN THE FILE  FOR WRITING %%%
  if (!file.open(QIODevice::WriteOnly)) {
    loge(tr("ERROR: File is not writable. "
            "Please rerun the application as an administrator."));
    return;
  }

  // %%% REWRITE THE FILE %%%
  file.write(newFile);

  logi(tr("SUCCESSFULLY PATCHED."));
}

void MainWindow::restoreClicked()
{
  QString backupFileName = QFileDialog::getOpenFileName(
    this,
    tr("Choose oclulus library backup file"),
    QFileInfo(filePathEdit->text()).dir().path(),
    tr("Library files(*") + BACKUP_EXTENSION + tr(");;All files(*.*)")
  );
  if (backupFileName == QString::null) {
    logi("No backup file chosen.");
    return;
  }
  QFile file(filePathEdit->text());
  QFile backupFile (backupFileName);

  // %%% CHECK EXISTENCE OF THE BACKUP FILE %%%
  if (!backupFile.exists()) {
    loge(tr("ERROR: Backup file does not exist."));
    return;
  }

  // %%% CHECK EXISTENCE OF THE ORIGINAL FILE %%%
  if (!file.exists()) {
    loge(tr("ERROR: The original file does not exist or has not been chosen."));
    return;
  }

  logi(tr("--- Restoring original file from backup. ---"));

  // %%% REMOVE THE PATCHED FILE %%%
  logd("Removing patched file.");
  if (!file.exists()) {
    logw(tr("WARNING: File does not exist. Skipping removal."));
  } else {
    if (!file.remove()) {
      loge(tr("ERROR: File could not be removed. "
              "Please rerun the application as an administrator."));
      return;
    }
    logd(tr("Patched file removed."));
  }

  // %%% COPY BACKUP TO THE ORIGINAL LOCATION %%%
  logd(tr("Restoring from the backup file."));
  if (!QFile::copy(backupFile.fileName(), file.fileName())) {
   loge(tr("ERROR: Cannot copy backup file to the original location. "
           "Please rerun the application as an administrator."));
    return;
  }

  /*
  logd(tr("Restored from backup file."));

  // %%% REMOVE BACKUP %%%
  logd(tr("Removing backup file."));
  if (!backupFile.remove()) {
    logw(tr("WARNING: Backup file could not be removed. "
            "Please rerun the application as an administrator."));
  } else {
    logd(tr("Backup file removed."));
  }
  */

  logi(tr("SUCCESSFULLY RESTORED."));
}

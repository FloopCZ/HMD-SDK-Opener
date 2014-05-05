#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QFile>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);

private slots:
  void chooseFileClicked();
  void patchClicked();
  void restoreClicked();

private:
  void logd(const QString &);
  void logi(const QString &);
  void logw(const QString &);
  void loge(const QString &);

  QLineEdit *filePathEdit;
  QTextEdit *textArea;

};

#endif // MAINWINDOW_H

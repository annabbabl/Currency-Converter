#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "converter.h"
#include <QMessageBox>
#include <QDateTime>
#include "plotwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_convert_button_clicked();
    void on_from_currency_currentIndexChanged(int index);
    void on_to_currency_currentIndexChanged(int index);
private:
    Date current_date();

    Converter m_conv;
    PlotWidget* m_plot = nullptr;
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H

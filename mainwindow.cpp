#include "mainwindow.h"
#include "./ui_mainwindow.h"

/* MainWindow class
    it is the window where all the GUI controls are located
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QPixmap("icon.png"));

    m_plot = new PlotWidget(ui->centralwidget);
    ui->plot_layout->addWidget(m_plot);

    ui->from_currency->addItem("None");
    ui->to_currency->addItem("None");

    std::vector<QString> currencies = m_conv.get_currencies();
    for(int i = 0; i < currencies.size();i++) {
        ui->from_currency->addItem(currencies[i]);
        ui->to_currency->addItem(currencies[i]);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_plot;
}

void MainWindow::on_from_currency_currentIndexChanged(int index) {
    m_plot->reset();
    ui->result_value->clear();
}

void MainWindow::on_to_currency_currentIndexChanged(int index) {
    m_plot->reset();
    ui->result_value->clear();
}

Date MainWindow::current_date() {
  QDateTime time = QDateTime::currentDateTime();
  std::string date_string = time.toString("yyyy-MM-dd").toStdString();
  return Date(date_string);
}

void MainWindow::on_convert_button_clicked()
{
    QString from =ui->from_currency->currentText(), to = ui->to_currency->currentText();

    if(from == "None" || to == "None") {
        QMessageBox::critical(this,"Oops!","Please, select start and result currencies to convert");
        return;
    }
    float value = ui->from_value->text().toFloat();
    if(value == 0.0f) {
        QMessageBox::critical(this,"Oops!","Please, enter the start value");
        return;
    }
    
    int res;
    if(from == to) {
        res = QMessageBox::information(this,"Confirm","Are you sure you want to do this? You will waste 7 requests",QMessageBox::Yes, QMessageBox::No);
        if(res != QMessageBox::Yes)
            return;
    }

    QString result = QString::number(m_conv.convert(from.toStdString(),to.toStdString(), value));
    ui->result_value->setText(result);
    
    // we should get around five requests to build plot because in the free version of
    // currency.api there are only 300 requests per month. So it just takes data from 6 last months
    std::vector<Date> dates;
    const int amount_of_requests = 5;
    Date last = current_date(), first(last);
    --last; // previous day, because data only creates at 23:59:59
    --first;
    dates.push_back(first);
    int i = 0;
    while(i < amount_of_requests) {
        first.prev_month();
        i++;
        dates.push_back(first);
    }
    std::vector<std::pair<Date,float>> data= m_conv.get_history(from.toStdString(),to.toStdString(),dates);

    m_plot->processData(data);
}


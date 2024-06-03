#include "comptabilite_metiers.h"

#include <QSqlQuery>

#include <QDate>

#include <QSqlQueryModel>

#include <QVariant>

#include <QPropertyAnimation>

#include "ui_mainwindow.h"

#include "mainwindow.h"

#include <QDebug>

#include <QSqlError>

#include <QMessageBox>

#include <QFile>

#include <QTextStream>

#include <QPdfWriter>

#include <QPainter>

#include <QFileDialog>

#include <QDesktopServices>

#include <QUrl>

#include <QtSql/QSqlRecord>

void MainWindow::generatePdfFile(QString table)
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                                   "/home",
                                                                   QFileDialog::ShowDirsOnly
                                                                   | QFileDialog::DontResolveSymlinks);
                       qDebug()<<dir;
                       QPdfWriter pdf(dir+"/PdfList.pdf");
                                              QPainter painter(&pdf);
                                             int i = 4000;
                                             // Load the logo image from a file
                                             QImage logoImage("C:\\Users\\FanTasy CriT\\Desktop\\projet\\images\\logo.jpg");
                                             QPixmap logoPixmap = QPixmap::fromImage(logoImage);
                                             logoPixmap = logoPixmap.scaled(1500, 1500, Qt::KeepAspectRatio, Qt::SmoothTransformation);

                                             // Draw the logo in the top right corner
                                             int logoX = pdf.width() - logoPixmap.width();
                                             int logoY = 50;
                                             painter.drawPixmap(logoX, logoY, logoPixmap);
                                         painter.drawPixmap(QRect(100,100,2000,2000),QPixmap(""));
                                                 painter.drawText(900,650,"generation pdf");

                                                 // painter.drawPixmap(QRect(7600,100,2100,2700),QPixmap("C:/Users/Admin/Desktop/logo.png"));

                                                  painter.setPen(Qt::blue);
                                                  painter.setFont(QFont("Time New Roman", 25));
                                                  painter.drawText(3000,1400,"Liste Des "+table);
                                                  painter.setPen(Qt::black);
                                                  painter.setFont(QFont("Time New Roman", 15));
                                                  painter.drawRect(100,100,9400,2500);
                                                  painter.drawRect(100,3000,9400,500);
                                                  painter.setFont(QFont("Time New Roman", 9));
                                                  QSqlQuery query;
                                                  query.prepare("select * from "+table);
                                                  query.exec();
                                                  int x =300;
                                                  int columnCount = query.record().count();
                                                                           for (int col = 0; col < columnCount; col++) {
                                                                               QString columnName = query.record().fieldName(col);
                                                                               painter.drawText(x, 3300, columnName);
                                                                               x+=2000;
                                                                           }
                                                  painter.drawText(x,3300,"id");

                                               //painter.drawText(8400,3300,"poids ");
                                                //  painter.drawText(9500,3300,"Date Retour");
                                                  //painter.drawText(10500,3300,"Date Naissance");

                                                  painter.drawRect(100,3000,9400,10700);


                                                  QTextDocument previewDoc;
                                                  QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");


                                                  QTextCursor cursor(&previewDoc);


                                                  while (query.next())
                                                  {
                                                      painter.drawText(300,i,query.value(0).toString());
                                                      painter.drawText(2300,i,query.value(1).toString());
                                                      painter.drawText(4300,i,query.value(2).toString());
                                                      painter.drawText(6300,i,query.value(3).toString());
                                                      painter.drawText(8500,i,query.value(4).toString());
                                                     // painter.drawText(9500,i,query.value(6).toString());
                                                     // painter.drawText(10500,i,query.value(7).toString());*/




                                                     i = i +500;
                                                  }
                                                  int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                                      QMessageBox::Yes|QMessageBox::No);
                                                      if (reponse == QMessageBox::Yes)
                                                      {
                                                          QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                                          painter.end();
                                                      }
                                                      else
                                                      {
                                                           painter.end();
             }
}




comptabilite_metiers::comptabilite_metiers()
{

}
QSqlQueryModel * MainWindow::search_table(QString table ,QString search) {
  QSqlQueryModel * model = new QSqlQueryModel();
  if(search=="")model -> setQuery("Select * from HAROUN." + table);
  else if(table=="sdf")model -> setQuery("Select * from HAROUN." + table+" WHERE NOM LIKE '%"+search+"%';");
  else
  model -> setQuery("Select * from HAROUN." + table+" WHERE TYPE LIKE '%"+search+"%';");
  ui -> tableView -> setModel(model);
  return model;
}
QSqlQueryModel * MainWindow::sortbyup(QString table) {
  QSqlQueryModel * model = new QSqlQueryModel();
  model -> setQuery("Select * from HAROUN." + table+" ORDER BY ID ASC");
  ui -> tableView -> setModel(model);
  return model;
}
QSqlQueryModel * MainWindow::sortbydown(QString table) {
  QSqlQueryModel * model = new QSqlQueryModel();
  model -> setQuery("Select * from HAROUN." + table+" ORDER BY ID DESC");
  ui -> tableView -> setModel(model);
  return model;
}


void MainWindow::on_search_compt_clicked()
{
    ui->tableView->setModel(search_table("comptabilite",ui->lineEdit_2->text()));
}

//sort by
void MainWindow::on_pushButton_11_clicked()
{
    ui->tableView->setModel(sortbyup("comptabilite"));
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->tableView->setModel(sortbydown("comptabilite"));
}

void MainWindow::on_PDF_clicked()
{
    generatePdfFile("COMPTABILITE");

}





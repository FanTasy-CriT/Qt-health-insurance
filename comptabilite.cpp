#include "comptabilite.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <QSqlError>
comptabilite::comptabilite()
{

}

QSqlQueryModel* MainWindow::print_table(QString table){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("Select * from fantasy."+table);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("montant"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
    ui->tableView->setModel(model);
    return model;
}


void MainWindow::on_pushButton_7_clicked() // add button
{
    //add query
    QSqlQuery qry;
    qry.prepare("INSERT INTO FANTASY.COMPTABILITE (ID, TYPE, MONTANT) VALUES (:ID, :type, :montant);");
    qry.bindValue(":ID",ui->lineEdit->text());
    qry.bindValue(":montant",ui->lineEdit_2->text());
    if(ui->radioButton_2->isChecked())
    qry.bindValue(":type","dis nuts");
    else
    qry.bindValue(":type","10");
    //qry.bindValue(":date",ui->dateEdit->date().toString("yyyy-MM-dd"));
    (qry.exec())?qDebug()<<"succefully launched adding request":qDebug()<<qry.lastError();
    //add table header
    print_table("comptabilite");
}


void MainWindow::on_pushButton_8_clicked() //delete button
{
    // Get the selection model of the table view
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();

    // Get the currently selected indexes
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    // Extract the primary keys of the selected rows
    QList<int> primaryKeys;
    foreach (const QModelIndex &index, selectedIndexes) {
        if (index.column() == 0) {
            primaryKeys.append(index.data().toInt());
        }
    }

    // Delete the selected rows from the SQL table
    QSqlQuery query;
    foreach (int primaryKey, primaryKeys) {
        query.prepare("DELETE FROM comptabilite WHERE id = :id");
        query.bindValue(":id", primaryKey);
        query.exec();
        print_table("comptabilite");
    }
}
void MainWindow::intialize_comptabilite(){
    print_table("comptabilite");
}


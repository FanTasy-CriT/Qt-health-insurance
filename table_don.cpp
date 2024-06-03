#include "table_don.h"

#include <QSqlQuery>

#include <QSqlQueryModel>

#include "ui_mainwindow.h"

#include "mainwindow.h"

#include <QDebug>

#include <QSqlError>

#include <QMessageBox>

table_don::table_don()
{

}


void MainWindow::on_add_don_clicked()
{
    bool test=true;
    QString error;
    QRegExp re("\\d*");
    if(!re.exactMatch(ui->id_dons->text())){
        test=false;
        error="id chiffres";
    }
    for(int i=0;i<ui->nom_don->text().length();i++){
    if(re.exactMatch(ui->nom_don->text().at(i))){
        test=false;
        error = "nom non chaine";
    }
}
    if(!test) QMessageBox::information(this, "Information", error); else {
    QSqlQuery qry;
    qry.prepare("INSERT INTO HAROUN.dons (type, ETAT,nom,dater)"
   " VALUES (:type,:ETAT,:nom,TO_DATE(:date, 'DD/MM/YYYY'))");
    qry.bindValue(":type",ui->dropdown_type->currentText());
    qry.bindValue(":ETAT",ui->dropdown_etat->currentText());
    qry.bindValue(":date",ui->date_don->text());
    qry.bindValue(":nom",ui->nom_don->text());
    if(!qry.exec()) QMessageBox::information(this, "check input","erreur cle primaire");
    ui->table_don->setModel(print_table("dons"));
}
}
void MainWindow::on_edit_don_clicked()
{
    bool test=true;
    QString error;
    QRegExp re("\\d*");
    if(!re.exactMatch(ui->id_dons->text())){
        test=false;
        error="id chiffres";
    }
    for(int i=0;i<ui->nom_don->text().length();i++){
    if(re.exactMatch(ui->nom_don->text().at(i))){
        test=false;
        error = "nom non chaine";
    }
}
    if(!test) QMessageBox::information(this, "Information", error); else {
    QSqlQuery qry;
    qry.prepare("UPDATE HAROUN.dons SET TYPE=:type,etat=:etat,NOM=:nom,dater=TO_DATE(:date, 'DD/MM/YYYY') WHERE id=:id");
    qry.bindValue(":id",ui->id_dons->text().toInt());
    qry.bindValue(":type",ui->dropdown_type->currentText());
    qry.bindValue(":etat",ui->dropdown_etat->currentText());
    qry.bindValue(":date",ui->date_don->text());
    qry.bindValue(":nom",ui->nom_don->text());
    if(!qry.exec()) qDebug() << "error updating into donations";
    if (qry.numRowsAffected() == 0) QMessageBox::information(this, "Information", "erreur cle primaire"); else  QMessageBox::information(this, "Information", "modifier avec success");
    ui->table_don->setModel(print_table("dons"));
}
}


void MainWindow::on_delte_don_clicked()
{
    // Get the selection model of the table view
    QItemSelectionModel * selectionModel = ui ->table_don -> selectionModel();
    // Get the currently selected indexes
    QModelIndexList selectedIndexes = selectionModel -> selectedIndexes();

    // Extract the primary keys of the selected rows
    QList < int > primaryKeys;
    foreach(const QModelIndex & index, selectedIndexes) {
      if (index.column() == 0) {
        primaryKeys.append(index.data().toInt());
      }
    }

    // Delete the selected rows from the SQL table
    QSqlQuery query;
    foreach(int primaryKey, primaryKeys) {
        qDebug() << "primary key found";
        query.prepare("DELETE FROM HAROUN.dons WHERE ID=?");
        query.addBindValue(primaryKey);
        query.exec();
        ui->table_don->setModel(print_table("dons"));
    }
}



void MainWindow::on_pushButton_13_clicked()
{
    ui->table_don->setModel(sortbyup("dons"));
}

void MainWindow::on_pushButton_12_clicked()
{
    ui->table_don->setModel(sortbydown("dons"));
}

void MainWindow::on_search_compt_2_clicked()
{
    ui->table_don->setModel(search_table("dons",ui->lineEdit_3->text()));
}

void MainWindow::on_table_don_doubleClicked(const QModelIndex &index)
{
        if (index.isValid())
            {
                QVariant data = ui->table_don->model()->data(index);
                QString id = ui->table_don->model()->data(ui->table_don->model()->index(index.row(), 0)).toString();
                QString type = ui->table_don->model()->data(ui->table_don->model()->index(index.row(), 1)).toString();
                QString etat = ui->table_don->model()->data(ui->table_don->model()->index(index.row(), 2)).toString();
                    ui->dropdown_type->setCurrentText(type);
                    ui->dropdown_etat->setCurrentText(etat);
                    ui->id_dons->setText(id);
              }
}

void MainWindow::on_pdf_don_clicked()
{
// Generate the PDF file with the selected row data
generatePdfFile("DONS");
}


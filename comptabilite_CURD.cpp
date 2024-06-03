#include "comptabilite_CURD.h"

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

#include <QSqlQuery>

#include <QVector>

#include <qcustomplot.h>


void MainWindow::displaystatistiques(QGraphicsView* view,QString table,QString collumn){
    // Create a scene and add it to the view
       QGraphicsScene* scene = new QGraphicsScene();
       view->setScene(scene);


       // Query the database to get the data for the chart
       QSqlQuery query("SELECT "+collumn+" FROM "+table);


       // Count the number of occurrences of each type
       QMap<QString, int> typeCounts;
       while (query.next()) {
           QString type = query.value(0).toString();
           if (typeCounts.contains(type)) {
               typeCounts[type]++;
           } else {
               typeCounts.insert(type, 1);
           }
       }

       // Calculate the total count of all types
       int totalCount = 0;
       QMap<QString, int>::const_iterator i;
       for (i = typeCounts.constBegin(); i != typeCounts.constEnd(); ++i) {
           totalCount += i.value();
       }

       // Set up the colors for the chart slices
       QColor colors[] = {
           Qt::red,
           Qt::green,
           Qt::blue,
           Qt::yellow,
           Qt::cyan,
           Qt::magenta,
           Qt::gray,
       };
       int numColors = sizeof(colors) / sizeof(colors[0]);

       // Set up the chart parameters
       QRectF rect(50, 50, 200, 200);
       qreal startAngle = 0;
           QFont font("Arial", 12);
           QFontMetrics fm(font);
           qreal labelRadius = rect.width() * 0.5 + fm.height();
       // Draw the chart slices
       int colorIndex = 0;
       for (i = typeCounts.constBegin(); i != typeCounts.constEnd(); ++i) {
           QString type = i.key();
           int count = i.value();
           qreal angle = 360.0 * count / totalCount;

           // Set up the brush and pen for the slice
           QBrush brush(colors[colorIndex % numColors]);
           QPen pen(colors[colorIndex % numColors]);
           pen.setWidth(2);

           // Draw the slice
           QPainterPath path;
           path.moveTo(rect.center());
           path.arcTo(rect, startAngle, angle);
           path.lineTo(rect.center());
           path.closeSubpath();
           QGraphicsPathItem* item = scene->addPath(path, pen, brush);
           item->setToolTip(type + ": " + QString::number(count));

           // Draw the label for the slice
                   qreal labelAngle = startAngle + angle / 2.0;
                   qreal x = rect.center().x() + labelRadius * qCos(labelAngle * M_PI / 180.0) - fm.width(type) / 2.0;

                   qreal y = rect.center().y() - labelRadius * qSin(labelAngle * M_PI / 180.0) - fm.height() / 2.0;
                   QGraphicsTextItem* label = new QGraphicsTextItem(type);
                   label->setPos(x, y);
                   scene->addItem(label);

           // Update the start angle for the next slice
           startAngle += angle;
           colorIndex++;
       }

       // Set the view's background color
       view->setBackgroundBrush(QColor(240, 240, 240));

       // Set the scene rectangle and view alignment
       scene->setSceneRect(QRectF(0, 0, 300, 300));
       view->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    }


comptabilite::comptabilite() {

}
QString MainWindow::control_saisie() {
  QString montant = ui -> lineEdit_5 -> text();
  int quantity = ui -> spinBox -> text().toInt();
  QString error = "";
  QRegExp re("\\d*");
  if (ui -> lineEdit_5 -> isVisible()) {
    if (!re.exactMatch(montant)) {
      qDebug() << "montant not digits";
      error = "montant not digits";
    }
  }
  int montant1 = montant.toInt();
  if (ui -> lineEdit_5 -> isVisible()) {
    if (!(montant1 > 0)) {
      qDebug() << "motant negative";
      error = "motant negative";
    }
    if (!(quantity > 0)) {
      qDebug() << "quantity negative";
      error = "quantity negative";
    }
  }
  return error;
}

QSqlQueryModel * MainWindow::print_table(QString table) {
  QSqlQueryModel * model = new QSqlQueryModel();
  model -> setQuery("Select * from HAROUN." + table);
  ui -> tableView -> setModel(model);
  return model;
}


void MainWindow::on_delete_2_clicked() //delete button
{
  // Get the selection model of the table view
  QItemSelectionModel * selectionModel = ui -> tableView -> selectionModel();
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
      query.prepare("DELETE FROM DONS WHERE id_compt = :id ;");
    qDebug() << "not working" << primaryKey << query.executedQuery();
    query.bindValue(":id", primaryKey);
    if (!query.exec()) qDebug() << "not working";
    query.prepare("DELETE FROM COMPTABILITE WHERE id = :id ;");
  qDebug() << "not working" << primaryKey << query.executedQuery();
  query.bindValue(":id", primaryKey);
  if (!query.exec()) qDebug() << "not working";

    else qDebug() << "working"; query.prepare("DELETE FROM DONS WHERE id_compt = :id ;");
  addToHistory("haroun", "deleted", "id",QString::fromStdString(std::to_string(primaryKey)) , "deleted");
  saveHistoryToFile("history.txt");
  qDebug() << "not working" << primaryKey << query.executedQuery();
    query.bindValue(":id", primaryKey);
  }

  if (ui -> tableView -> model() -> headerData(2, Qt::Horizontal, Qt::DisplayRole).toString() == "MONTANT") print_table("comptabilite");
  if (ui -> tableView -> model() -> headerData(2, Qt::Horizontal, Qt::DisplayRole).toString() == "FRAIS") print_table("materiel");
  if (ui -> tableView -> model() -> headerData(2, Qt::Horizontal, Qt::DisplayRole).toString() == "ETAT") print_table("dons");
}
//all commands i need to run initially
void MainWindow::intialize_comptabilite() {
  ui -> tableView -> setModel(print_table("COMPTABILITE"));
  ui -> Dropdown -> clear();
  ui -> Dropdown -> addItem("Materiel");
  ui -> Dropdown -> addItem("Donation");
  displaystatistiques(ui->graphicsView,"COMPTABILITE","type");
   ui->pdf_don->hide();
}


void MainWindow::on_Add_clicked() {
  QSqlQuery qry2;
  QSqlQuery tmp;
  QSqlQuery qry;

  if (control_saisie() == "") {
      if (ui -> Dropdown -> currentText() == "Donation") {
        //add donation
          qry2.prepare("SELECT id,frais from haroun.materiel where type=:type");
          qry2.bindValue(":type", ui -> materiel -> currentText());
          if (!qry2.exec())
            qDebug() << "first wrong";
          else {
            qry2.next();
          }
          qry.prepare("INSERT INTO HAROUN.COMPTABILITE (TYPE, MONTANT, DATER) VALUES (:type, :montant, TO_DATE(:date, 'DD/MM/YYYY'))");
          if (ui -> recu -> isChecked()){
          qry.bindValue(":type", "recu");
          addToHistory("haroun", ui -> date -> text(), "recu",ui->lineEdit_5->text() , "added donation");
          }
          else{
          qry.bindValue(":type", "depnser");
          addToHistory("haroun", ui -> date -> text(), "recu",ui->lineEdit_5->text() , "added donation");
          }
          qry.bindValue(":montant", ui->lineEdit_5->text().toInt());
          qry.bindValue(":date", ui -> date -> text());
          if (!qry.exec()) qDebug() <<ui -> date -> text() ;
          qDebug() << "add donation";
      qry.prepare("INSERT INTO HAROUN.DONS (TYPE, ETAT,dater, ID_COMPT) VALUES (:type, :etat,TO_DATE(:date, 'DD/MM/YYYY'), :my_id);");
      tmp.prepare("SELECT * FROM HAROUN.COMPTABILITE WHERE ROWNUM = 1 ORDER BY id DESC;");
      tmp.exec();
      tmp.next();
      qry.bindValue(":my_id", tmp.value(0).toInt());
      if (ui -> recu -> isChecked())
          qry.bindValue(":type", "recu");
      else
          qry.bindValue(":type", "depnser");
      qry.bindValue(":etat", "Done");
      qry.bindValue(":date", ui->date->text());
      if (!qry.exec())qDebug() << tmp.value(0).toInt();
      //add table header
      print_table("comptabilite");
      }else{
        qDebug()<<"add materiel";
        qry2.prepare("SELECT id,frais from haroun.materiel where type=:type");
        qry2.bindValue(":type", ui -> materiel -> currentText());
        if (!qry2.exec())
          qDebug() << "first wrong";
        else {
          qry2.next();
        }
      QSqlQuery qry;
      qry.prepare("INSERT INTO HAROUN.COMPTABILITE (TYPE, MONTANT, DATER,ID_MAT) VALUES (:type, :montant, TO_DATE(:date, 'MM/DD/YYYY'),:id_mat)");
      qry.bindValue(":montant", qry2.value(1).toInt() * ui -> spinBox -> text().toInt());
      qry.bindValue(":date", ui -> date -> text());
      qry.bindValue(":id_mat", qry2.value(0).toInt());
      if (ui -> recu -> isChecked()){
      qry.bindValue(":type", "recu");
      addToHistory("haroun", ui -> date -> text(), "recu",qry2.value(1).toString() , "added materiel");}
      else{
      addToHistory("haroun", ui -> date -> text(), "depenser",qry2.value(1).toString() , "added materiel");
       qry.bindValue(":type", "depenser");}
      saveHistoryToFile("history.txt");
      if (!qry.exec()) qDebug() << "seond wrong";
      //MATERIEL
      if (ui -> recu -> isChecked())
        qry.prepare("UPDATE HAROUN.MATERIEL SET QUANTITE=QUANTITE+:quantity WHERE ID=:id_mat");
      else
        qry.prepare("UPDATE HAROUN.MATERIEL SET QUANTITE=QUANTITE-:quantity WHERE ID=:id_mat");
      qry.bindValue(":quantity", ui -> spinBox -> text().toInt());
      qry.bindValue(":id_mat", qry2.value(0).toInt());
      tmp.prepare("SELECT * FROM HAROUN.COMPTABILITE WHERE ROWNUM = 1 ORDER BY id DESC;");
      tmp.exec();
      tmp.next();
      if (!qry.exec()) qDebug() << "last wrong"  << "id " << ui -> spinBox -> text().toInt();
  }
  } else QMessageBox::information(this, "check input", control_saisie());
ui -> tableView -> setModel(print_table("comptabilite"));
}
void MainWindow::on_Dropdown_currentTextChanged(const QString & arg1) {
  if (arg1 == "Materiel") {
    ui -> label_6 -> hide();
    ui -> lineEdit_5 -> hide();
    ui -> materiel -> show();
    QSqlQuery query;
    query.prepare("SELECT TYPE FROM HAROUN.MATERIEL;");
    if (!query.exec()) {
      qDebug() << "Error executing query: " << query.lastError().text();
      return;
    }
    ui -> materiel -> clear();
    while (query.next()) {
      QString material = query.value(0).toString();
      qDebug() << material;
      ui -> materiel -> addItem(material);
    }
  } else {
    ui -> materiel -> hide();
    ui -> label_6 -> show();
    ui -> lineEdit_5 -> show();
  }
}

void MainWindow::on_pushButton_7_clicked() {
  ui -> tableView -> setModel(print_table("comptabilite"));
}

void MainWindow::on_pushButton_8_clicked() {
  ui -> tableView -> setModel(print_table("materiel"));
}

void MainWindow::on_pushButton_10_clicked() {
  ui -> tableView -> setModel(print_table("dons"));
}
void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.isValid())
        {
            QVariant data = ui->tableView->model()->data(index);
            QString id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();
            QString type = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 1)).toString();
            QString montant = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 2)).toString();
            QString date = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 3)).toString().left(10);
            QString id_mat = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 4)).toString();
            qDebug() << "Double-clicked on row " << index.row() << " with data: " << id << "First Name: " << montant << "Last Name: " << date;
            if(id_mat!="0"){
                //materiel
                if(type=="recu")ui->recu->setChecked(true);else ui->rendu->setChecked(true);
                ui->lineEdit_5->hide();
                ui->materiel->show();
                ui->label_6->hide();
                ui->IDline->setText(id);
                QDateTime dateTime = QDateTime::fromString(date, "yyyy-MM-dd");
                QDate date = dateTime.date();
                ui->date->setDate(date);
                ui->date->setDisplayFormat("yyyy-MM-dd");
                ui->spinBox->setValue(round(montant.toInt()/12));
                ui->materiel->setCurrentIndex(id_mat.toInt());

            }
            else{
                if(type=="recu")ui->recu->setChecked(true);else ui->rendu->setChecked(true);
                ui->lineEdit_5->show();
                ui->materiel->hide();
                ui->label_6->show();
                ui->IDline->setText(id);
                QDateTime dateTime = QDateTime::fromString(date, "yyyy-MM-dd");
                QDate date = dateTime.date();
                ui->date->setDate(date);
                ui->date->setDisplayFormat("yyyy-MM-dd");
                ui->lineEdit_5->setText(montant);
                ui->Dropdown->setCurrentIndex(1);
            }

    }
}

void MainWindow::on_Edit_clicked()
{
    QSqlQuery qry;
    QSqlQuery qry2;
    //SELECT MATERIEL ID FRAIS
         qry2.prepare("SELECT id,frais from haroun.materiel where type=:type");
         qry2.bindValue(":type", ui -> materiel -> currentText());
         if (!qry2.exec())
         qDebug() << "select materiel wrong";
         else
         qry2.next();
         //EDIT DONATION
         if (ui -> Dropdown -> currentText() == "Donation") {
           qDebug() << "edit donation";
           qry.prepare("UPDATE HAROUN.DONS SET TYPE=:type, ETAT=:etat WHERE ID=:id_old;");
           qry.bindValue(":id_old", ui ->IDline -> text().toInt());
           if (ui -> recu -> isChecked())
             qry.bindValue(":type", "recu");
           else
             qry.bindValue(":type", "depnser");
           qry.bindValue(":etat", "Done");
           if (!qry.exec()) qDebug() << "update into donations";
           qry.prepare("UPDATE HAROUN.COMPTABILITE  SET TYPE=:type, MONTANT=:montant,DATER=TO_DATE(:date, 'YYYY/MM/DD') WHERE ID=:id");
           qry.bindValue(":id", ui->IDline->text());
           if (ui -> recu -> isChecked())  {
             qry.bindValue(":type", "recu");
           addToHistory("haroun", ui -> date -> text(), "recu", ui -> lineEdit_5 -> text(), "updated donation");
           saveHistoryToFile("history.txt");}
           else{
             qry.bindValue(":type", "depnser");
             addToHistory("haroun", ui -> date -> text(), "despnser", ui -> lineEdit_5 -> text(), "updated donation");
             saveHistoryToFile("history.txt");}
           qry.bindValue(":montant", ui -> lineEdit_5 -> text().toInt());
           qry.bindValue(":date", ui -> date -> text());
           if (!qry.exec()) qDebug() << "update donation into comptabilite";
           if (qry.numRowsAffected() == 0) QMessageBox::information(this, "Information", "erreur cle primaire");
           qDebug()<< qry2.value(0);
           qDebug() << "edit doantion done";
         } else {
           QSqlQuery qry2;
           qry2.prepare("SELECT id,frais,quantite from haroun.materiel where type=:type");
           qry2.bindValue(":type", ui -> materiel -> currentText());
           if (!qry2.exec())
             qDebug() << "first wrong";
           else {
             qry2.next();
           }
           qDebug() << "edit materiel";
           qry.prepare("UPDATE HAROUN.COMPTABILITE  SET TYPE=:type, MONTANT=:montant,DATER=TO_DATE(:date, 'YYYY/MM/DD') WHERE ID=:id");
           qry.bindValue(":id", ui ->IDline -> text().toInt());
           if (ui -> recu -> isChecked())  {
             qry.bindValue(":type", "recu");
           addToHistory("haroun", ui -> date -> text(), "recu", QString::fromStdString(std::to_string(qry2.value(1).toInt()*ui->spinBox->value())), "updated materiel");
           saveHistoryToFile("history.txt");}
           else{
             qry.bindValue(":type", "depnser");
             addToHistory("haroun", ui -> date -> text(), "despnser", QString::fromStdString(std::to_string(qry2.value(1).toInt()*ui->spinBox->value())), "updated materiel");
             saveHistoryToFile("history.txt");}
           qry.bindValue(":montant", qry2.value(1).toInt()*ui->spinBox->value());
           qry.bindValue(":date", ui -> date -> text());
           if (!qry.exec()) qDebug() << "insert donation into comptabilite";
           if (qry.numRowsAffected() == 0) QMessageBox::information(this, "Information", "erreur cle primaire");
}
ui->tableView->setModel(print_table("COMPTABILITE"));
}


void MainWindow::on_pushButton_6_clicked()
{
    int x=ui->widget->x();
    int y=ui->widget->y();
    int height=ui->widget->height();
    QString output=ui->pushButton->text();
    if(output=="Comptabilité"){
    QPropertyAnimation *animation = new QPropertyAnimation(ui->widget, "geometry");
    animation->setDuration(150);
    animation->setEndValue(QRect(x,y,72,height));
    animation->start();
    ui->pushButton->setText("");
    ui->pushButton_2->setText("");
    ui->pushButton_3->setText("");
    ui->pushButton_4->setText("");
    ui->pushButton_5->setText("");
    ui->pushButton_6->setText("");}
    else{
        QPropertyAnimation *animation2 = new QPropertyAnimation(ui->widget, "geometry");
        ui->pushButton->setText("Comptabilité");
        ui->pushButton_2->setText("Donations");
        ui->pushButton_3->setText("SDF");
        ui->pushButton_4->setText("Services");
        ui->pushButton_5->setText("Materiels");
        ui->pushButton_6->setText("Menu");
        animation2->setDuration(150);
        animation2->setEndValue(QRect(x,y,171,height));
        animation2->start();
    }
    }

#include <QApplication>
#include <QPalette>
#include <QStyleFactory>

#include "gamechooser.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Set the Fusion style
  QApplication::setStyle(QStyleFactory::create("Fusion"));

  // Customize the palette for the title bar color
  QPalette palette = app.palette();
  palette.setColor(QPalette::Window, QColor("#efebe7"));  // Background color
  palette.setColor(QPalette::WindowText, Qt::black);      // Text color

  // Apply the palette to the application
  app.setPalette(palette);

  GameChooser chooser;
  chooser.show();
  return app.exec();
}

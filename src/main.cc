#include <QApplication>

#include "view/view.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  ObjData obj;
  Affine affine;
  CareTaker caretaker(&affine);
  Controller controller(&obj, &affine, &caretaker);
  View w(&controller);
  w.show();
  int error = a.exec();

  return error;
}

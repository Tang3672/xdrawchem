#include "xdc_toolbutton.h"

XDC_ToolButton::XDC_ToolButton(QWidget *parent, QString name) :
  QToolButton(parent, name) {
  fn = name;
}

void XDC_ToolButton::trigger() {
  emit IncludeFile(fn);
}

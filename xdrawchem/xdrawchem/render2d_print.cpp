#include <iostream>
#include <math.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qprinter.h>
#include <qpaintdevicemetrics.h>
#include <qpointarray.h>
#include <qrect.h>
#include <qpixmap.h>

#include "paintable.h"
#include "render2d.h"
#include "chemdata.h"
#include "defs.h"

void Render2D::PrintSetup() {
  printer = new QPrinter;
  // the following statement is needed for Qt 3.0 or higher
#if QT_VERSION >= 300
  printer->setResolution(100);  // for convenient calculation of line length
  printer->setMargins(50,50,50,50);  // apparently works on UNIX only
#endif
  printer->setFullPage(true);
  //printer->setPageSize(QPrinter::Letter);
  //printer->setOrientation(QPrinter::Portrait);
  printer->setColorMode(QPrinter::GrayScale);
  UpdatePageGeometry();
}

void Render2D::UpdatePageGeometry() {
  if (preferences.getPageOrientation() == PAGE_PORTRAIT) {
    printer->setOrientation(QPrinter::Portrait);
    switch (preferences.getPageSize()) {
    case PAGE_LETTER:
      printer->setPageSize(QPrinter::Letter);
      renderHeight = 1000;
      renderWidth = 750;
      break;
    case PAGE_LEGAL:
      printer->setPageSize(QPrinter::Legal);
      renderHeight = 1300;
      renderWidth = 750;
      break;
    case PAGE_A4:
      printer->setPageSize(QPrinter::A4);
      renderHeight = 1070;
      renderWidth = 776;
      break;
    case PAGE_640:
      renderWidth = 640;
      renderWidth = 480;
      break;
    case PAGE_800:
      renderWidth = 800;
      renderWidth = 600;
      break;
    case PAGE_1024:
      renderWidth = 1024;
      renderWidth = 768;
      break;
    default:
      break;
    }
  } else { // page_orientation == PAGE_LANDSCAPE
    printer->setOrientation(QPrinter::Landscape);
    switch (preferences.getPageSize()) {
    case PAGE_LETTER:
      printer->setPageSize(QPrinter::Letter);
      renderHeight = 750;
      renderWidth = 1000;
      break;
    case PAGE_LEGAL:
      printer->setPageSize(QPrinter::Legal);
      renderHeight = 750;
      renderWidth = 1300;
      break;
    case PAGE_A4:
      printer->setPageSize(QPrinter::A4);
      renderHeight = 776;
      renderWidth = 1070;
      break;
    case PAGE_640:
      renderWidth = 640;
      renderWidth = 480;
      break;
    case PAGE_800:
      renderWidth = 800;
      renderWidth = 600;
      break;
    case PAGE_1024:
      renderWidth = 1024;
      renderWidth = 768;
      break;
    default:
      break;
    }
  }
  resize(renderWidth, renderHeight);
}

void Render2D::Print(QString epsname) {
  if (epsname.length() > 4) {
    // setup printer...
    printer->setOutputToFile(true);
    printer->setColorMode( QPrinter::Color );
    printer->setOutputFileName(epsname);
  } else {  // print from File/Print or Ctrl+P
    if (!printer->setup(this)) {
      emit SignalSetStatusBar( QString("Printing canceled.") );
      return;
    }
  }

  //QPaintDeviceMetrics pm(printer);

  c->DeselectAll();
  // set output device
  outputDevice = OUTPUT_PRINTER;
  // render all objects
  paintqueue.clear();
  repaint();

  // set output to screen
  outputDevice = OUTPUT_SCREEN;
  repaint(false);
  return;
}

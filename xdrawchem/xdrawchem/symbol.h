// symbol.h -- subclass of Drawable for symbols

#ifndef SYMBOL_H
#define SYMBOL_H

#include <qobject.h>
#include <qpixmap.h>
#include "render2d.h"
#include "drawable.h"
#include "dpoint.h"

class Symbol : public Drawable {
  Q_OBJECT
    public:
  Symbol(Render2D *, QObject *parent = 0, const char *name = 0);
  void Render();  // draw this object
  void Edit();
  int Type();  // return type of object
  bool Find(DPoint *); // does this ymbol contain this DPoint?
  DPoint * FindNearestPoint(DPoint *, double &);
  Drawable * FindNearestObject(DPoint *, double &);
  Drawable * DeepCopy();
  void setPoint(DPoint *);
  QRect BoundingBox();
  bool WithinRect(QRect, bool);
  bool WithinBounds(DPoint *);
  QString ToXML(QString);
  void FromXML(QString);
  void SetSymbol(QString);
  QString GetSymbol() { return which; }
  void SetOffset(QPoint d) {
    if ( (d.x() == 0) && (d.y() == 0) ) { 
      need_offset = false; offset = d;
    } else {
      need_offset = true; offset = d;
    }
  }
  QPoint GetOffset() { return offset; }
  void SetRotate(double);
  double GetRotate() { return rotation; }
 private:
  // Renderer
  Render2D *r;
  // Pixmap of original and rotated, regular and highlighted symbol
  QPixmap originalRegular;
  QPixmap originalHighlighted;
  QPixmap rotateRegular;
  QPixmap rotateHighlighted;
  // Offset (if needed -- to avoid label or bond)
  bool need_offset;
  QPoint offset;
  // Rotation (if needed -- if not below or on point)
  double rotation;
  // scale (if needed)
  double scale;
};

#endif

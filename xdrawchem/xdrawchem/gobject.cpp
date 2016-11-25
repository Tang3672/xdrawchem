// gobject.cpp - GraphicObject's implementation of functions

#include <qobject.h>
#include <iostream>
#include <math.h>

using std::cout;
using std::endl;

#include "render2d.h"
#include "drawable.h"
#include "gobject.h"
#include "bondedit.h"
#include "defs.h"

GraphicObject::GraphicObject(Render2D *r1, QObject *parent, const char *name)
  : Drawable(parent, name)
{
  r = r1;
  highlighted = false;
  style = 0;
  ot = 0;
}

QString GraphicObject::ToXML(QString xml_id) {
  QString s, n1;

  // begin graphic object
  s.append("<graphicobject id=\"");
  s.append(xml_id);
  s.append("\">\n");

  // write object type (ot)
  s.append("<objecttype>");
  n1.setNum(ot);
  s.append(n1);
  s.append("</objecttype>\n");

  // write Style
  s.append("<style>");
  n1.setNum(style);
  s.append(n1);
  s.append("</style>\n");

  // write points
  if (ot == TYPE_BEZIER) {
    int ci, xi, yi;
    for (ci = 0; ci < 4; ci++) {
      s.append("<point>");
      pa1.point(ci,&xi,&yi);
      n1.setNum(xi);
      s.append(n1);
      s.append(" ");
      n1.setNum(yi);
      s.append(n1);
      s.append("</point>\n");
    }
  }

  // write color
  s.append("<color>");
  n1.setNum(color.red());
  s.append(n1);
  s.append(" ");
  n1.setNum(color.green());
  s.append(n1);
  s.append(" ");
  n1.setNum(color.blue());
  s.append(n1);
  s.append("</color>\n");

  // end bracket
  s.append("</graphicobject>\n");

  return s;
}

QString GraphicObject::ToCDXML(QString xml_id) {
  QString s, n1;

  return s;  // until I learn how to do these objects in CDXML

  // begin arrow
  s.append("<graphic id=\"");
  s.append(xml_id);
  s.append("\" BoundingBox=\"");
  n1.setNum(end->x);
  s.append(n1);
  s.append(" ");
  n1.setNum(end->y);
  s.append(n1);
  s.append(" ");
  n1.setNum(start->x);
  s.append(n1);
  s.append(" ");
  n1.setNum(start->y);
  s.append(n1);
  s.append("\" ");
  if (style == BRACKET_SQUARE)
    s.append("GraphicType=\"Bracket\" BracketType=\"SquarePair\"");
  if (style == BRACKET_CURVE)
    s.append("GraphicType=\"Bracket\" BracketType=\"RoundPair\"");
  if (style == BRACKET_BRACE)
    s.append("GraphicType=\"Bracket\" BracketType=\"CurlyPair\"");
  s.append("/>\n");

  return s;
}

// set GraphicObject from XDrawChem-format XML
void GraphicObject::FromXML(QString xml_tag) {
  int i1, i2;

  i1 = xml_tag.find("<Start>");
  if (i1 >= 0) {
    i2 = xml_tag.find("</Start>") + 8;
    SetStartFromXML(xml_tag.mid(i1, i2 - i1));
  }
  i1 = xml_tag.find("<End>");
  if (i1 >= 0) {
    i2 = xml_tag.find("</End>") + 6;
    SetEndFromXML(xml_tag.mid(i1, i2 - i1));
  }
  i1 = xml_tag.find("<objecttype>");
  if (i1 >= 0) {
    i2 = xml_tag.find("</objecttype>") + 13;
    ot = xml_tag.mid(i1 + 12, 2).toInt();
  }
  i1 = xml_tag.find("<style>");
  if (i1 >= 0) {
    i2 = xml_tag.find("</style>") + 8;
    style = xml_tag.mid(i1 + 7, i2 - i1 - 15).toInt();
  }
  i1 = xml_tag.find("<color>");
  if (i1 >= 0) {
    i2 = xml_tag.find("</color>") + 8;
    SetColorFromXML(xml_tag.mid(i1, i2 - i1));
  }
  if (ot == TYPE_BEZIER) {
    pa1.resize(4);
    int ci,xi,yi,i3=0;
    QString xml_subtag;
    for (ci = 0; ci < 4; ci++) {
      i1 = xml_tag.find("<point>", i3);
      i2 = xml_tag.find("</point>", i3) + 8;
      i3 = i2 + 1;
      xml_subtag = xml_tag.mid(i1, i2 - i1);
      i1 = xml_subtag.find("<point>");
      i2 = xml_subtag.find("</point>");
      xml_subtag.remove(i2, 999);
      xml_subtag.remove(i1, 7);
      
      QTextStream ts(&xml_subtag, IO_ReadOnly);
      
      ts >> xi >> yi;
      cout << ci << " " << xi << " " << yi << endl;
      pa1.setPoint(ci,xi,yi);
    }
    start = new DPoint(pa1.point(0));
    end = new DPoint(pa1.point(1));
  }
}

void GraphicObject::Render(void)
{
  QColor c1;
  if (highlighted)
    c1 = QColor(255,0,0);
  else
    c1 = color;
  if (ot == TYPE_BEZIER)
    r->drawBezier(pa1, c1, false, style);
  if (ot == TYPE_GRAPHIC_LINE)
    r->drawLine(start->toQPoint(), end->toQPoint(), 1, GetColor(), 1);
  if (ot == TYPE_GRAPHIC_BONDMARK)
    r->drawLine(start->toQPoint(), end->toQPoint(), 1, GetColor(), 1);
}

void GraphicObject::Edit() {
  return;  // it's not practical to edit any graphic objects this way
  /*
  BondEditDialog be(r, "bracket editor", start, end, TYPE_BRACKET, 0, 0, 0, 
		    style, color);
  if ( !be.exec() ) return;
  cout << "change" << endl;
  style = be.Style();
  color = be.Color();
  */
}

int GraphicObject::Type(void)
{
  // real type is stored in style
  return TYPE_GRAPHIC_OBJECT;
}

bool GraphicObject::Find(DPoint *target) {
  if (start == target) return true;
  if (end == target) return true;
  return false;
}

// Do not allow connections to this object.
// Simplest way to do this, I think, is to disallow this function
DPoint * GraphicObject::FindNearestPoint(DPoint *target, double &dist) {
  dist = 99999.0;
  return 0;
}

Drawable * GraphicObject::FindNearestObject(DPoint *target, double &dist) {
  DPoint *tl = new DPoint;
  DPoint *tr = new DPoint;
  DPoint *bl = new DPoint;
  DPoint *br = new DPoint;
  double tl_x, tl_y, br_x, br_y, swp, dist1, dist2;
  tl_x = start->x; tl_y = start->y;
  br_x = end->x; br_y = end->y;
  if (tl_x < br_x) { swp = tl_x; tl_x = br_x; br_x = swp; }
  if (tl_y < br_y) { swp = tl_y; tl_y = br_y; br_y = swp; }
  tl->x = tl_x; tl->y = tl_y;
  bl->x = tl_x; bl->y = br_y;
  tr->x = br_x; tr->y = tl_y;
  br->x = br_x; br->y = br_y;
  dist1 = DistanceToLine(tl, bl, target);
  dist2 = DistanceToLine(tr, br, target);
  if (dist1 < dist2)
    dist = dist1;
  else
    dist = dist2;
  delete tl, tr, bl, br;
  return this;
}

void GraphicObject::setPoints(DPoint *s, DPoint *e) {
  start = s;
  end = e;
}

bool GraphicObject::WithinRect(QRect n, bool shiftdown) {
  if ( DPointInRect(start, n) && DPointInRect(end, n) )
    highlighted = true;
  else
    highlighted = false;
  return highlighted;
}

QRect GraphicObject::BoundingBox() {
  if (highlighted == false)
    return QRect( QPoint(999,999), QPoint(0,0) ); 
  int top, bottom, left, right, swp;
  top = (int)start->y;
  left = (int)start->x;
  bottom = (int)end->y;
  right = (int)end->x;
  if (bottom < top) { swp = top; top = bottom; bottom = swp; }
  if (right < left) { swp = left; left = right; right = swp; }
  return QRect( QPoint(left,top), QPoint(right,bottom) );
}

Drawable * GraphicObject::DeepCopy() {
  GraphicObject *np = new GraphicObject(r);
  DPoint *s1 = new DPoint(start);
  DPoint *e1 = new DPoint(end);
  np->setPoints(s1, e1);
  np->SetColor(color);
  np->setObjectType(ot);
  np->SetStyle(style);
  np->setPointArray(pa1);
  if (highlighted) np->Highlight(true);
  return np;
}

void GraphicObject::setPointArray(QPointArray inp1) {
  pa1 = inp1;
  // kludge around lack opf Start and End in this object type/style
  start = new DPoint(pa1.point(0));
  end = new DPoint(pa1.point(1));
}

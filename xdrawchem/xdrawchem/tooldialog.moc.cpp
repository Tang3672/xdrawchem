/****************************************************************************
** ToolDialog meta object code from reading C++ file 'tooldialog.h'
**
** Created: Wed Nov 23 20:29:56 2016
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "tooldialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ToolDialog::className() const
{
    return "ToolDialog";
}

QMetaObject *ToolDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ToolDialog( "ToolDialog", &ToolDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ToolDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ToolDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ToolDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ToolDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ToolDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"SendHelp", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "SendHelp()", &slot_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ToolDialog", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ToolDialog.setMetaObject( metaObj );
    return metaObj;
}

void* ToolDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ToolDialog" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool ToolDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: SendHelp(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ToolDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool ToolDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool ToolDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES

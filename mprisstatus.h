#include "/usr/include/qt4/Qt/qdbusargument.h"
 #include <qdbusmetatype.h>
 
 #ifndef MPRIS_STATUS_H
 #define MPRIS_STATUS_H
 
 struct MprisStatus
 {
     int i1;
     int i2;
	 int i3;
	 int i4;
 };
 Q_DECLARE_METATYPE(MprisStatus)
/*
 
 // Marshall the MprisStatus data into a D-Bus argument
 QDBusArgument &operator<<(QDBusArgument &argument, const MprisStatus &mystruct);
 // Retrieve the MprisStatus data from the D-Bus argument
 const QDBusArgument &operator>>(const QDBusArgument &argument, MprisStatus &mystruct);
 
 */
 /*
  struct MprisStatus
 {
     int count;
     QString name;
 };
 Q_DECLARE_METATYPE(MprisStatus)
*/
 // Marshall the MprisStatus data into a D-Bus argument
QDBusArgument &operator<<(QDBusArgument &argument, const MprisStatus &mystruct);

 // Retrieve the MprisStatus data from the D-Bus argument
 const QDBusArgument &operator>>(const QDBusArgument &argument, MprisStatus &mystruct);

 #endif
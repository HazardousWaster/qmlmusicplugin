#include "mprisstatus.h"

// Marshall the MyStructure data into a D-Bus argument
QDBusArgument &operator<<(QDBusArgument &argument, const MprisStatus &mystruct)
{
	argument.beginStructure();
	argument << mystruct.i1 << mystruct.i2 << mystruct.i3 << mystruct.i4;
	argument.endStructure();
	return argument;
}

// Retrieve the MyStructure data from the D-Bus argument
const QDBusArgument &operator>>(const QDBusArgument &argument, MprisStatus &mystruct)
{
	argument.beginStructure();
	argument >> mystruct.i1 >> mystruct.i2 >> mystruct.i3 >> mystruct.i4;
	argument.endStructure();
	return argument;
}
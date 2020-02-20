#include "ccompacket.h"

/**
 * @brief	Method serializes the members from the caller class and returns
 *			the serialized data as array of bytes.
 * @return	Serialized array of bytes;
 */
QByteArray CComPacket::serialize()
{
	QByteArray ba;
	QDataStream ds(&ba, QIODevice::WriteOnly);

	ds << *this;
	return ba;
}

/**
 * @brief	The function deserializes the \p ba array of bytes into a
 *			\ref CComPacket object and returns it.
 * @param	ba: serialized array of bytes.
 * @return	The given class object after deserialization.
 */
CComPacket CComPacket::deserialize(QByteArray& ba)
{
	QDataStream ds(&ba, QIODevice::ReadOnly);
	CComPacket cp;

	ds >> cp;
	return cp;
}

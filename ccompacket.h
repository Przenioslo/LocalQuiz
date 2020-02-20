#ifndef CCOMPACKET_H
#define CCOMPACKET_H

#include <QObject>
#include <QDataStream>
#include <QVariant>
#include <QByteArray>

/**
 * @brief	The type used to store the \ref CComPacket::Cmd enum
 */
using CmdType = quint8;

/**
 * @brief	A smart container for the TCP packets
 */
class CComPacket
{

public:

	/**
	 * @brief	Provides the command information for the packet (tells how
	 *			the data is supposed to be parsed).
	 */
	enum class Cmd: CmdType
	{
		Invalid,
		ReadName,
		GiveName,
	};

	/**
	 * @brief	The ostream (<<) overloading
	 * @param	out: The data stream to which the \p cpp class is going to
	 *			be serialized.
	 * @param	ccp: the class to be serialized into the \p out.
	 * @return	reference to \p out.
	 */
	friend QDataStream& operator<<(QDataStream& out, const CComPacket& ccp)
	{
		out << static_cast<CmdType>(ccp.m_cmd) << ccp.m_data;
		return out;
	}

	/**
	 * @brief	The istream (>>) overloading
	 * @param	in: The serialized data that will be deserialized to the \p cpp
	 * @param	ccp: deserialized data goes here.
	 * @return	The \p in reference.
	 */
	friend QDataStream& operator>>(QDataStream& in, CComPacket& ccp)
	{
		CmdType tmp;
		in >> tmp >> ccp.m_data;
		ccp.m_cmd = static_cast<Cmd>(tmp);

		return in;
	}

	QByteArray serialize();
	static CComPacket deserialize(QByteArray& ba);

	/**
	 * @brief	The parsing command
	 */
	Cmd m_cmd = Cmd::Invalid;

	/**
	 * @brief	The data to be parsed
	 */
	QVariant m_data;

};

#endif // CCOMPACKET_H

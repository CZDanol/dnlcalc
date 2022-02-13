#pragma once

#include <type_traits>

#include <QHash>
#include <QMetaEnum>
#include <QDebug>
#include <QVarLengthArray>
#include <QReadWriteLock>

#include "stringutils.h"

#define ID(str) ([] { static const Identifier result = Identifier::fromString(QStringLiteral(str)); return result; } ())
#define IDFUNC(str) ([] { return Identifier::fromString(QStringLiteral(str)); })

/// Define an enum of IDs
/// This type of enum is basically just a wrapper over Identifier. Because of that, it supports custom values outside the defined scope. This allows easy defining of custom values by mods.
#define IDENUM(name) using name = Identifier; struct name ## Predef final

/// Define an "IDENUM" item
#define ENUMID(item) static inline const Identifier item = Identifier::fromString(QStringLiteral(#item))

/// Define a prefix for the enum identifier values
#define PIDENUM_PREFIX(prefix) static inline const QString enumPrefix = QStringLiteral(prefix)

/// Define an "IDENUM" item with prefix defined by PIDENUM_PREFIX
#define PENUMID(item) static inline const Identifier item = Identifier::fromString(enumPrefix + QStringLiteral(#item))

/**
 * Identifiers are basically string literals but stored as integer indexes to a string literal array (thread-safe).
 * It is intended to be used for string constants, provides faster comparison and hashability.
 */
struct Identifier final {

public:
	using Handle = uint32_t;
	using IDFUNCT = Identifier (*)();

public:
	constexpr inline Identifier() = default;

	constexpr inline Identifier(const Identifier &other) = default;

	static Identifier fromString(const QString &str);

	constexpr inline static Identifier fromHandle(Handle handle) {
		Identifier r;
		r.data_ = handle;
		return r;
	}

	/// Prints debug output of identifiers that are currently registered
	static void debugPrintList();

public:
	QString str() const;

	/// Returns an identifier with a given suffix added
	inline Identifier withSuffix(const QString &suffix) const {
		return fromString(str() + suffix);
	}

	constexpr inline Handle val() const {
		return data_;
	}

public:
	template<typename ...Args>
	constexpr inline bool isOneOf(Args ...args) const {
		return ((*this == args) || ...);
	}

public:
	constexpr inline bool operator ==(const Identifier &other) const {
		return data_ == other.data_;
	}

	template<typename E, typename = std::enable_if_t<std::is_enum_v<E>>>
	inline bool operator ==(E e) const {
		return operator ==(fromEnum(e));
	}

	constexpr inline bool operator !=(const Identifier &other) const {
		return data_ != other.data_;
	}

	constexpr inline auto operator <=>(Identifier o) const {
		return data_ <=> o.data_;
	}

	template<typename E, typename = std::enable_if_t<std::is_enum_v<E>>>
	inline bool operator !=(E e) const {
		return operator !=(fromEnum(e));
	}

	constexpr inline Identifier &operator =(const Identifier &other) = default;

	template<typename E, typename = std::enable_if_t<std::is_enum_v<E>>>
	Identifier &operator =(E e) {
		*this = fromEnum(e);
		return *this;
	}

	explicit constexpr inline operator bool() const {
		return data_;
	}

private:
	constexpr inline explicit Identifier(uint data) : data_(data) {

	}

private:
	Handle data_ = 0;

};

static_assert(sizeof(Identifier) == sizeof(int));

Q_DECLARE_METATYPE(Identifier);

using ShortIdentifierList = QVarLengthArray<Identifier, 4>;

inline size_t qHash(Identifier i, size_t seed = 0) {
	return qHash(i.val(), seed);
}

inline QDebug operator <<(QDebug debug, const Identifier &id) {
	QDebugStateSaver _s(debug);
	debug.nospace() << "ID#" << id.val() << ":" << id.str();
	return debug;
}

template<StaticString str>
inline Identifier operator ""_ID() {
	static const Identifier r = Identifier::fromString(str.toString());
	return r;
}
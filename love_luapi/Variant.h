/**
 * Copyright (c) 2006-2021 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#ifndef LOVE_VARIANT_H
#define LOVE_VARIANT_H

#include "config.h"
#include "Object.h"
#include "int.h"

#include <cstring>
#include <string>
#include <vector>

namespace love
{

class LOVE_EXPORT Variant
{
public:

	static const int MAX_SMALL_STRING_LENGTH = 15;

	enum Type
	{
		UNKNOWN = 0,
		BOOLEAN,
		NUMBER,
		STRING,
		SMALLSTRING,
		LUSERDATA,
		LOVEOBJECT,
		NIL,
		TABLE
	};

	class SharedString : public love::Object
	{
	public:

		SharedString(const char *string, size_t len)
			: len(len)
		{
			str = new char[len+1];
			str[len] = '\0';
			memcpy(str, string, len);
		}
		virtual ~SharedString() { delete[] str; }

		char *str;
		size_t len;
	};

	class SharedTable : public love::Object
	{
	public:

		SharedTable() {}
		virtual ~SharedTable() {}

		std::vector<std::pair<Variant, Variant>> pairs;
	};

	union Data
	{
		bool boolean;
		double number;
		SharedString *string;
		void *userdata;
		Proxy objectproxy;
		SharedTable *table;
		struct
		{
			char str[MAX_SMALL_STRING_LENGTH];
			uint8 len;
		} smallstring;
	};

	Variant();
	Variant(bool boolean);
	Variant(double number);
	Variant(const char *str, size_t len);
	Variant(const std::string &str);
	Variant(void *lightuserdata);
	Variant(love::Type *type, love::Object *object);
	Variant(SharedTable *table);
	Variant(const Variant &v);
	Variant(Variant &&v);
	~Variant();

	Variant &operator = (const Variant &v);

	Type getType() const { return type; }
	const Data &getData() const { return data; }

	static Variant unknown() { return Variant(UNKNOWN); }

private:

	Variant(Type vtype);

	Type type;
	Data data;

}; // Variant
} // love

#endif // LOVE_VARIANT_H

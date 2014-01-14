#ifndef __MoonSugar__TypeConver__
#define __MoonSugar__TypeConver__

#include <string>

namespace moonSugar {
	class TypeConver
	{
	public:
		static char * ConstCharToChar(const char * constChar);
		static char * StringToChar(std::string * str);
		static std::string * CharToString(char * charStr);

		static char * combinationChar(char * char1, char * char2);
	};
}

#endif // !__MoonSugar__TypeConver__

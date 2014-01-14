#ifndef __MoonSugar__XmlUtils__
#define __MoonSugar__XmlUtils__

#include "MoonSugar.h"
#include "support/tinyxml2/tinyxml2.h"
#include <string>
#include <vector>

NS_MS_BEGAN
class XmlUtils
{
public:
    /**直接打印xml**/
	static void printfXml(tinyxml2::XMLDocument * root);
    /**解析节点下所有元素**/
	static std::string parseAttribute(tinyxml2::XMLElement * element);
    /**解析节点**/
	static std::string parseElement(tinyxml2::XMLElement * element);
    /**返回下一子级的节点列表**/
	static std::vector<tinyxml2::XMLElement*> getChildren(tinyxml2::XMLElement * node);
    /**传入节点下一子级节点列表**/
	static void printfChildren(tinyxml2::XMLElement * node);
protected:
	static void roundPrintfXml(tinyxml2::XMLElement * parent, int level);
	static std::string createSpaceByLevel(int level);
private:
};
NS_MS_END

#endif // !__MoonSugar__XmlUtils__


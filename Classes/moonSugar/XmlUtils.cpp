#include "XmlUtils.h"
#include "TypeConver.h"
#include "cocos2d.h"
USING_NS_CC;

NS_MS_BEGAN
void XmlUtils::printfXml(tinyxml2::XMLDocument * root)
{
	tinyxml2::XMLElement * element = root->FirstChildElement();
	if (element)
	{
		char * nameCharStr = TypeConver::ConstCharToChar(element->Name());
		std::string nameStr(nameCharStr);
		std::string attributeStr = parseAttribute(element);
		std::string title;
		title = "<" + nameStr + attributeStr;
		if (false == element->NoChildren())
		{
			title += ">";
			CCLog("%s", title.c_str());
			roundPrintfXml(element, 1);
			title = "</" + nameStr + ">";
			CCLog("%s", title.c_str());
		}
		else
		{
			title += "/>";
			CCLog("%s", title.c_str());
		}
		delete nameCharStr;
	}
}

void XmlUtils::roundPrintfXml(tinyxml2::XMLElement * parent, int level)
{
	tinyxml2::XMLElement * element = parent->FirstChildElement();
	while (element)
	{
		std::string space = createSpaceByLevel(level);
		std::string title;
		char * nameCharStr = TypeConver::ConstCharToChar(element->Name());
		std::string nameStr(nameCharStr);
		std::string attributeStr = parseAttribute(element);
		title = space + "<" + nameStr + attributeStr;
		parseAttribute(element);
		if (false == element->NoChildren())
		{
			title += ">";
			CCLog("%s", title.c_str());
			roundPrintfXml(element, level + 1);
			title = space + "</" + nameStr + ">";
			CCLog("%s", title.c_str());
		}
		else
		{
			title += "/>";
			CCLog("%s", title.c_str());
		}
		element = element->NextSiblingElement();
		delete  nameCharStr;
	}
}

std::string XmlUtils::createSpaceByLevel(int level)
{
	std::string title(" ");
	for (int i = level; i > 0; i --)
	{
		title += title;
	}
	return title;
}

std::string XmlUtils::parseAttribute(tinyxml2::XMLElement * element)
{
	const tinyxml2::XMLAttribute * attribute = element->FirstAttribute();
	std::string title(" ");
	std::string comp;
	while(attribute)
	{
		std::string nameStr(attribute->Name());
		std::string valueStr(attribute->Value());
		comp += title;
		comp += nameStr;
		comp += "=";
        comp += "'";
		comp += valueStr;
        comp += "'";
		attribute = attribute->Next();
	}
	return comp;
}

std::string XmlUtils::parseElement(tinyxml2::XMLElement * element)
{
	char * nameCharStr = TypeConver::ConstCharToChar(element->Name());
	std::string nameStr(nameCharStr);
	std::string attributeStr = parseAttribute(element);
	std::string title;
	title = "<" + nameStr + attributeStr + "/>";
    return title;
}

std::vector<tinyxml2::XMLElement*> XmlUtils::getChildren(tinyxml2::XMLNode * node)
{
	std::vector<tinyxml2::XMLElement*> children;
	tinyxml2::XMLElement * element = node->FirstChildElement();
	while(element)
	{
		children.push_back(element);
		element = element->NextSiblingElement();
	}
	return children;
}

void XmlUtils::printfChildren(tinyxml2::XMLNode * node)
{
	std::vector<tinyxml2::XMLElement*> children = getChildren(node);
    tinyxml2::XMLElement * element;
    int n = children.size();
    for (int i = 0; i < n; i ++) {
        element = children.at(i);
        std::string elementStr = parseElement(element);
        CCLOG("%s", elementStr.c_str());
    }
}
NS_MS_END
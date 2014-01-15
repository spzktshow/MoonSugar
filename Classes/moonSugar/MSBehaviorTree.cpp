#include "MSBehaviorTree.h"
#include "XmlUtils.h"
#include "TypeConver.h"
#include "cocos2d.h"

using namespace std;
USING_NS_CC;
namespace moonSugar {

const std::string MSBehaviorTreeParser::SELECTOR_NODE("selector");
const std::string MSBehaviorTreeParser::SEQUENCE_NODE("sequence");
const std::string MSBehaviorTreeParser::CONDITION_NODE("condition");
const std::string MSBehaviorTreeParser::ACTION_NODE("action");

const std::string MSBehaviorTreeParser::PARSE_NAME("name");
const std::string MSBehaviorTreeParser::PARSE_ID("id");
const std::string MSBehaviorTreeParser::PARSE_TYPE("type");
const std::string MSBehaviorTreeParser::PARSE_CONDITION_TYPE("conditionType");
const std::string MSBehaviorTreeParser::PARSE_ACTION_TYPE("actionType");

/**************MSBehaviorTreeParser***************/
ActionAssemble * MSBehaviorTreeParser::parser(tinyxml2::XMLDocument * document)
{
	//actions
	std::vector<MSBehaviorNode*> list;
	tinyxml2::XMLElement * element= document->RootElement();
	std::vector<tinyxml2::XMLElement*> children = moonSugar::XmlUtils::getChildren(element);
	int n = children.size();
	ActionAssemble * actionAssemble;
	for (int i = 0; i < n; i ++)
	{
		element = children.at(i);
		actionAssemble = parserActionAssemble(element);
	}
	return actionAssemble;
}

MSBehaviorNode* MSBehaviorTreeParser::parserElement(tinyxml2::XMLElement * element)
{
	MSCompositeNode * compositeNode;
	std::string typeStr = element->Attribute(MSBehaviorTreeParser::PARSE_TYPE.c_str());
	if (typeStr == MSBehaviorTreeParser::SELECTOR_NODE)
	{
		compositeNode = new MSSelectorNode;
		compositeNode->name = element->Attribute(MSBehaviorTreeParser::PARSE_NAME.c_str());
		round(element, compositeNode);
		return compositeNode;
	}
	else if (typeStr == MSBehaviorTreeParser::SEQUENCE_NODE)
	{
		compositeNode = new MSSequenceNode;
		compositeNode->name = element->Attribute(MSBehaviorTreeParser::PARSE_NAME.c_str());
		round(element, compositeNode);
		return compositeNode;
	}
	else if (typeStr == MSBehaviorTreeParser::CONDITION_NODE)
	{
		MSConditionNode * conditionNode = MSBehaviorTreeParser::createConditionNode(element);
		compositeNode->name = element->Attribute(MSBehaviorTreeParser::PARSE_NAME.c_str());
		return conditionNode;
	}
	else if (typeStr == MSBehaviorTreeParser::ACTION_NODE)
	{
		MSActionNode * actionNode = MSBehaviorTreeParser::createActionNode(element);
		compositeNode->name = element->Attribute(MSBehaviorTreeParser::PARSE_NAME.c_str());
		return actionNode;
	}
	return NULL;
}

ActionAssemble * MSBehaviorTreeParser::parserActionAssemble(tinyxml2::XMLElement * element)
{
	ActionAssemble * actionAssemble = new ActionAssemble();
	CCLog("%s", MSBehaviorTreeParser::PARSE_ID.c_str());
	CCLog("%s", moonSugar::XmlUtils::parseAttribute(element).c_str());
	CCLog("%s", element->Attribute(MSBehaviorTreeParser::PARSE_ID.c_str()));
	actionAssemble->id = moonSugar::TypeConver::CharToInt(element->Attribute(MSBehaviorTreeParser::PARSE_ID.c_str()));
	actionAssemble->name = element->Attribute(MSBehaviorTreeParser::PARSE_NAME.c_str());
	actionAssemble->root = parserElement(element->FirstChildElement());//root
	return actionAssemble;
}

void MSBehaviorTreeParser::round(tinyxml2::XMLElement * parent, MSCompositeNode * parentCompositeNode)
{
	std::vector<tinyxml2::XMLElement*> children = moonSugar::XmlUtils::getChildren(parent);
	std::vector<moonSugar::MSBehaviorNode*> nodeChildren;
	int n = children.size();
	tinyxml2::XMLElement * element;
	moonSugar::MSBehaviorNode * node;
	for (int i = 0; i < n; i ++)
	{
		element = children.at(i);
		node = parserElement(element);
		nodeChildren.push_back(node);
	}
	parentCompositeNode->children = nodeChildren;
}

moonSugar::MSConditionNode * MSBehaviorTreeParser::createConditionNode(tinyxml2::XMLElement * element)
{
	return NULL;
}

moonSugar::MSActionNode * MSBehaviorTreeParser::createActionNode(tinyxml2::XMLElement * element)
{
	return NULL;
}

/****************MSBehaviorNodeContext****************/
MSBehaviorNodeContext::MSBehaviorNodeContext(string typeValue)
{
	type = typeValue;
}

MSBehaviorNodeContext::~MSBehaviorNodeContext()
{

}

/****************MSBehaviorNode*****************/
MSBehaviorNode::MSBehaviorNode()
{

}

MSBehaviorNode::~MSBehaviorNode()
{

}

bool MSBehaviorNode::excute(MSBehaviorNodeContext *context)
{
	return false;
}

/****************MSCompositeNode*********************/
MSCompositeNode::MSCompositeNode()
{
}

MSCompositeNode::~MSCompositeNode()
{
}

bool MSCompositeNode::excute(MSBehaviorNodeContext *context)
{
	return roundChildren(context);
}

bool MSCompositeNode::roundChildren(MSBehaviorNodeContext * context)
{
	return false;
}

/****************MSDecoratorNode***********************/
MSDecoratorNode::MSDecoratorNode()
{

}

MSDecoratorNode::~MSDecoratorNode()
{

}

bool MSDecoratorNode::excute(MSBehaviorNodeContext *context)
{
	return false;
}

/****************MSConditionNode***********************/
MSConditionNode::MSConditionNode()
{

}

MSConditionNode::~MSConditionNode()
{

}

bool MSConditionNode::excute(MSBehaviorNodeContext *context)
{
	return false;
}

/*****************MSActionNode************************/
MSActionNode::MSActionNode()
{

}

MSActionNode::~MSActionNode()
{
	
}

bool MSActionNode::excute(MSBehaviorNodeContext *context)
{
	return false;
}

/********************MSSelectorNode************************/
MSSelectorNode::MSSelectorNode()
{

}

MSSelectorNode::~MSSelectorNode()
{
	
}

bool MSSelectorNode::roundChildren(MSBehaviorNodeContext * context)
{
	int n = children.size();
	for (int i = 0; i < n; i ++)
	{
		moonSugar::MSBehaviorNode * tempNode = children.at(i);
		bool result = tempNode->excute(context);
		if (result) return result;
	}
	return false;
}

/******************MSSequenceNode*************************/
MSSequenceNode::MSSequenceNode()
{

}

MSSequenceNode::~MSSequenceNode()
{

}

bool MSSequenceNode::roundChildren(MSBehaviorNodeContext * context)
{
	int n = children.size();
	for (int i = 0; i < n; i ++)
	{
        moonSugar::MSBehaviorNode * tempNode = children.at(i);
		bool result = tempNode->excute(context);
		if (false == result) return false;
	}
	return true;
}

};
#ifndef  __HelloCpp_MSBehaviorTree__
#define  __HelloCpp_MSBeahviorTree__

#include "MoonSugar.h"
#include <vector>
#include <string>
#include "support/tinyxml2/tinyxml2.h"

NS_MS_BEGAN

/********************abstract node! cant be construct***********************/
class MSBehaviorNodeContext
{
public:
	MSBehaviorNodeContext(std::string typeValue);
	~MSBehaviorNodeContext();
    //current type
	std::string type;
};

class MSBehaviorNode
{
public:
	MSBehaviorNode();
	~MSBehaviorNode();

	std::string name;
	virtual bool excute(MSBehaviorNodeContext *context);
};

/********************type of node****************************/
class MSCompositeNode : public MSBehaviorNode
{
public:
	MSCompositeNode();
	~MSCompositeNode();

	std::vector<MSBehaviorNode*> children;

	virtual bool excute(MSBehaviorNodeContext *context);

protected:
	virtual bool roundChildren(MSBehaviorNodeContext * context);
};

class MSDecoratorNode : public MSBehaviorNode
{
public:
	MSDecoratorNode();
	~MSDecoratorNode();

	virtual bool excute(MSBehaviorNodeContext *context);
};

class MSConditionNode : public MSBehaviorNode
{
public:
	MSConditionNode();
	~MSConditionNode();

	virtual bool excute(MSBehaviorNodeContext *context);

	std::string conditionType;
};

class MSActionNode : public MSBehaviorNode
{
public:
	MSActionNode();
	~MSActionNode();

	virtual bool excute(MSBehaviorNodeContext *context);

	std::string actionType;
};

/**selector**/
class MSSelectorNode : public MSCompositeNode
{
public:
	MSSelectorNode();
	~MSSelectorNode();

	virtual bool roundChildren(MSBehaviorNodeContext * context);
};

/**sequence**/
class MSSequenceNode : public MSCompositeNode
{
public:
	MSSequenceNode();
	~MSSequenceNode();

	virtual bool roundChildren(MSBehaviorNodeContext * context);
};

/******node assemble*****************/
class ActionAssemble
{
public:
	unsigned int id;
	std::string name;

	MSBehaviorNode * root;
private:

};

/********************parser****************/
class MSBehaviorTreeParser
{
public:
	//enum
	static const std::string SELECTOR_NODE;
	static const std::string SEQUENCE_NODE;
	static const std::string CONDITION_NODE;
	static const std::string ACTION_NODE;
	//
	static const std::string PARSE_NAME;
	static const std::string PARSE_ID;
	static const std::string PARSE_TYPE;
	static const std::string PARSE_CONDITION_TYPE;
	static const std::string PARSE_ACTION_TYPE;

	virtual ActionAssemble* parser(tinyxml2::XMLDocument * document);

	virtual MSConditionNode * createConditionNode(tinyxml2::XMLElement * element);

	virtual MSActionNode * createActionNode(tinyxml2::XMLElement * element);
protected:
	virtual void round(tinyxml2::XMLElement * parent, MSCompositeNode * parentCompositeNode);

	virtual MSBehaviorNode* parserElement(tinyxml2::XMLElement * element);

	virtual ActionAssemble* parserActionAssemble(tinyxml2::XMLElement * element);
};
NS_MS_END;
#endif // ! __HelloCpp_MSBehaviorTree__
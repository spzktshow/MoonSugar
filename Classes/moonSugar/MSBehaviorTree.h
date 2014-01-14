#ifndef  __HelloCpp_MSBehaviorTree__
#define  __HelloCpp_MSBeahviorTree__

#include "MoonSugar.h"
#include <vector>
#include <string>

NS_MS_BEGAN

/********************abstract node! cant be construct***********************/
class MSBehaviorNodeContext
{
public:
	MSBehaviorNodeContext(std::string * typeValue);
	~MSBehaviorNodeContext();
    //current recive type
	std::string * type;
};

class MSBehaviorNode
{
public:
	MSBehaviorNode();
	~MSBehaviorNode();
	virtual bool excute(MSBehaviorNodeContext *context);
};

/********************type of node****************************/
class MSCompositeNode : public MSBehaviorNode
{
public:
	MSCompositeNode();
	~MSCompositeNode();

	std::vector<MSBehaviorNode> *children;

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
};

class MSActionNode : public MSBehaviorNode
{
public:
	MSActionNode();
	~MSActionNode();

	virtual bool excute(MSBehaviorNodeContext *context);
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

NS_MS_END;
#endif // ! __HelloCpp_MSBehaviorTree__
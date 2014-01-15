#include "LightOfHope.h"
#include "moonSugar/MSBehaviorTree.h"

NS_LOH_BEGAN

class ActionsBehaviorEventConditionNode : public moonSugar::MSConditionNode
{
public:
	std::string checkEventName;

	virtual bool ActionsBehaviorEventConditionNode::excute(moonSugar::MSBehaviorNodeContext *context);
};

class ActionsBehaviortreeParser : public moonSugar::MSBehaviorTreeParser
{
public:
	//condition type
	static const std::string CONDITION_TYPE_EVENT;//value
	static const std::string CONDITION_TYPE_STATE;//value
	//condition eventName
	static const std::string PARSE_CONDITION_EVENT_NAME;//event parse
	static const std::string PARSE_CONDITION_STATE_NAME;//state parse
	//event**********
	static const std::string CONDITION_EVENT_DIRECT;//directEvent value
	static const std::string CONDITION_EVENT_CANCEL_DIRECT;//cancelDirectEvent value;
	//state**********
	static const std::string CONDITION_STATE_IDLE;//idle state value;
	static const std::string CONDITION_STATE_RUN;//run state value;

	virtual moonSugar::MSConditionNode * createConditionNode(tinyxml2::XMLElement * element);
	virtual moonSugar::MSActionNode * createActionNode(tinyxml2::XMLElement * element);
};
NS_LOH_END;

#include "ActionsBehaviorTree.h"

NS_LOH_BEGAN
const std::string ActionsBehaviortreeParser::CONDITION_TYPE_EVENT("event");
const std::string ActionsBehaviortreeParser::CONDITION_TYPE_STATE("state");

const std::string ActionsBehaviortreeParser::PARSE_CONDITION_EVENT_NAME("eventName");
const std::string ActionsBehaviortreeParser::PARSE_CONDITION_STATE_NAME("stateName");

const std::string ActionsBehaviortreeParser::CONDITION_EVENT_DIRECT("directEvent");
const std::string ActionsBehaviortreeParser::CONDITION_EVENT_CANCEL_DIRECT("cancelDirectEvent");
const std::string ActionsBehaviortreeParser::CONDITION_STATE_IDLE("idle");
const std::string ActionsBehaviortreeParser::CONDITION_STATE_RUN("run");

moonSugar::MSConditionNode * ActionsBehaviortreeParser::createConditionNode(tinyxml2::XMLElement * element)
{
	//
	std::string conditionType = element->Attribute(moonSugar::MSBehaviorTreeParser::PARSE_CONDITION_TYPE.c_str());
	if (conditionType == CONDITION_TYPE_EVENT)//event
	{
		std::string eventName = element->Attribute(lightOfHope::ActionsBehaviortreeParser::PARSE_CONDITION_EVENT_NAME.c_str());
		if (eventName == CONDITION_EVENT_DIRECT)
		{

		}
		else if(eventName == CONDITION_EVENT_CANCEL_DIRECT)
		{

		}
		else
		{
			return NULL;
		}
	}
	else if (conditionType == CONDITION_TYPE_STATE)//state
	{
		std::string stateName = element->Attribute(lightOfHope::ActionsBehaviortreeParser::PARSE_CONDITION_STATE_NAME.c_str());
		if (stateName == CONDITION_STATE_IDLE)
		{

		}
		else if (stateName == CONDITION_STATE_RUN)
		{


		}
		else
		{
			return NULL;
		}
	}
	return NULL;
}

NS_LOH_END;
#include "MSBehaviorTree.h"

using namespace std;
namespace moonSugar {
/****************MSBehaviorNodeContext****************/
MSBehaviorNodeContext::MSBehaviorNodeContext(string *typeValue)
{
	type = typeValue;
}

MSBehaviorNodeContext::~MSBehaviorNodeContext()
{
	type = NULL;
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
	children = new vector<MSBehaviorNode>;
}

MSCompositeNode::~MSCompositeNode()
{
	delete children;
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
	int n = children->size();
	for (int i = 0; i < n; i ++)
	{
		moonSugar::MSBehaviorNode &tempNode = children->at(i);
		bool result = tempNode.excute(context);
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
	int n = children->size();
	for (int i = 0; i < n; i ++)
	{
        moonSugar::MSBehaviorNode &tempNode = children->at(i);
		bool result = tempNode.excute(context);
		if (false == result) return false;
	}
	return true;
}

};
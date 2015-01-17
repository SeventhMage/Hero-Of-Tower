#include "SceneNode.h"
#include <string.h>

namespace xeng
{


	SceneNode::SceneNode()
		:m_pParentNode(NULL)
	{
		memset(m_name, 0, sizeof(m_name));
	}

	SceneNode::~SceneNode()
	{

	}

	void SceneNode::AddNode(SceneNode *pNode)
	{
		if (pNode)
		{
			m_vecNode.push_back(pNode);
		}
	}

	void SceneNode::RemoveNode(SceneNode *pNode)
	{
		std::vector<SceneNode *>::iterator it = m_vecNode.begin();
		for (; it != m_vecNode.end(); ++it)
		{
			if (*it == pNode)
			{
				m_vecNode.erase(it);
				delete *it;
				*it = NULL;
				break;
			}
		}
	}


}
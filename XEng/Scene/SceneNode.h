#ifndef SCENE_NODE_H_
#define SCENE_NODE_H_

#include <vector>

namespace xeng
{
	class SceneNode
	{
	public:
		SceneNode();
		virtual ~SceneNode();

		void AddNode(SceneNode *pNode);
		void RemoveNode(SceneNode *pNode);

	private:
		static const int MAX_NODE_NAME = 256;
		char *m_name[MAX_NODE_NAME];

		std::vector<SceneNode *>m_vecNode;
		SceneNode *m_pParentNode;


	};
}

#endif
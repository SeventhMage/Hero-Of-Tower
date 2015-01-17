#ifndef SCENE_MGR_H_
#define SCENE_MGR_H_

#include "SceneNode.h"

namespace xeng
{
	class SceneMgr
	{
	public:
		SceneMgr();
		virtual ~SceneMgr();

		SceneNode *GetRootNode(){ return m_pRootNode; }
		
	private:
		SceneNode *m_pRootNode;
	};
}

#endif
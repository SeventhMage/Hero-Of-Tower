#include "SceneMgr.h"
#include <assert.h>


xeng::SceneMgr::SceneMgr()
{
	m_pRootNode = new SceneNode;
	assert(m_pRootNode);
}

xeng::SceneMgr::~SceneMgr()
{
	delete m_pRootNode;
	m_pRootNode = NULL;
}

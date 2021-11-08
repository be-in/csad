/*
 *  renderer.cpp
 *
 *  Created on: 15.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#include "glextension.h"

#include <platform.h>
#include <bt.h>
#include <core/graph.h>
#include <scene/transform.h>
#include <scene/scene.h>
#include <scene/camera.h>
#include <scene/meshfilter.h>
#include <scene/mesh.h>
#include "csad/core/csadcore.h"

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

void _sortZUpNodes(Transform** list,int begin,int end);
void _sortZDownNodes(Transform** list,int begin,int end);
int _sortTreeNodes(Transform** list,int begin,int end);

Renderer::Renderer(int order,char * name)
{
	_init(order);
	Graph::graph().p_renderer->addObject(this,name);
}

Renderer::Renderer(int order,const char * name)
{
	_init(order);
	Graph::graph().p_renderer->addObject(this,name);
}

Renderer::~Renderer()
{
	if (p_tempfilter) extFunctions.DeleteMem(p_tempfilter,0);
}

void Renderer::setActive(bool val)
{
	if (val!=((fmode & NOT_ACTIVE)==0)) fmode^=NOT_ACTIVE;
}

void Renderer::setCamera(Camera *camera)
{
	if (p_camera!=camera) p_needUpdate=true;
	p_camera=camera;
}

void Renderer::setCamera(char *cameraPath)
{
	Camera *camera=Camera::finder(cameraPath);
	if (camera) {
		if (p_camera!=camera) p_needUpdate=true;
		p_camera=camera;
	}
}

void Renderer::setContext(GlContext *context)
{
	if (p_context!=context) p_needUpdate=true;
	p_context=context;
}

void Renderer::setContext(char *contextPath)
{
	GlContext *context=GlContext::finder(contextPath);
	if (context) {
		if (p_context!=context) p_needUpdate=true;
		p_context=context;
	}
}

void Renderer::setSort(unsigned int mode)
{
	fmode=(fmode&0xFFFFFFF0) | mode;
}

void Renderer::setSort(char *mode)
{
	int size=extFunctions.FindCMem(mode,0,255);
	if (size==2 && extFunctions.CmpMem(mode,(void*)"NO",2)==-1) setSort(NO);
	if (size==6 && extFunctions.CmpMem(mode,(void*)"NOSORT",6)==-1) setSort(NOSORT);
	if (size==3 && extFunctions.CmpMem(mode,(void*)"ZUP",3)==-1) setSort(ZUP);
	if (size==5 && extFunctions.CmpMem(mode,(void*)"ZDOWN",5)==-1) setSort(ZDOWN);
	if (size==4 && extFunctions.CmpMem(mode,(void*)"TREE",4)==-1) setSort(TREE);
}

unsigned int Renderer::getSort()
{
	return fmode&0x0000000F;
}

Camera* Renderer::getCamera()
{
	return p_camera;
}

GlContext* Renderer::getContext()
{
	return p_context;
}

void Renderer::setSelectInput(char*path)
{
	p_input=Input::input().finder(path);
}

void Renderer::setSelectInput(csad::BaseObject*val)
{
	p_input=val;
}

bool Renderer::draw()
{
	if (core->graph()->isDisplayLocked()) return true;
	if (!p_context || !p_camera) return false;
	Transform *transform=(Transform *)p_camera->getContainer();
	if (!transform) {
#ifdef LOG_CSAD
		Log::console("camera not have target");
#endif
		return false;
	}

	Scene *scene = p_camera->getScene();
	if (!scene) {
#ifdef LOG_CSAD
		Log::console("can not use null scene.");
#endif
		return false;
	}

	if (!p_context->makeCurrent()) return false;
	if (!p_camera->makeCurrent()) return false;
	_bindCamera();

//	_int64 sr1=extFunctions.TSC();

	scene->_setDefault();

	scene->_prepare();
	_validateUpdate(scene,p_camera);
	if (p_needUpdate) {
		//_int64 sr2=extFunctions.TSC();
		_prepareNodes(p_camera);
		//sr2=(extFunctions.TSC()-sr2);
		//if (sr2<0) sr2=cikles_nodes;
		//cikles_nodes=(cikles_nodes+sr2)*0.5;
		_fillFilter(scene);
		//_int64 sr3=extFunctions.TSC();
		if (p_count>0) {
			if ((fmode & 0xf)==ZUP) _sortZUpNodes(p_tempfilter,0,p_count-1);
			if ((fmode & 0xf)==ZDOWN) _sortZDownNodes(p_tempfilter,0,p_count-1);
		}
		//sr3=(extFunctions.TSC()-sr3);
		//if (sr3<0) sr3=cikles_sort;
		//cikles_sort=(cikles_sort+sr3)*0.5;
		p_needUpdate=false;
	}

/*
	sr1=(extFunctions.TSC()-sr1);
	if (sr1<0) sr1=cikles_prepare;
	cikles_prepare=(cikles_prepare+sr1)*0.5;
*/

	//Render::PushAttrib();

	//_int64 sr2=extFunctions.TSC();
	_draw();
	//sr2=(extFunctions.TSC()-sr2);
	//if (sr2<0) sr2=cikles_prepare;
	//cikles_prepare=(cikles_prepare+sr2)*0.5;

	//Render::PopAttrib();
	Render::Finish();

	//Log::console("%i %i %i %i %i",(int)cikles_prepare,(int)cikles_nodes,(int)cikles_sort,(int)cikles_inititem,(int)cikles_fullitem);
	//Log::console("-- %i",(int)cikles_prepare);
	return true;
}

struct buffSelectMesh4f {
	vector4f v;
	unsigned int flag;
};

struct buffSelectMesh4d {
	vector4d v;
	unsigned int flag;
};

void *Renderer::selectSoft(vector4i _rect)
{
	sFunctionsGLContext &functions=p_context->functions();

	if (!p_context || !p_camera) return 0;
	Transform *transform=p_camera->getContainer();
	if (!transform) {
#ifdef LOG_CSAD
		Log::console("camera not have target");
#endif
		return 0;
	}

	Scene *scene = p_camera->getScene();
	if (!scene) {
#ifdef LOG_CSAD
		Log::console("can not use null scene.");
#endif
		return 0;
	}

	if (!p_context->makeCurrent()) return 0;
	p_camera->makeCurrent(_rect);

	scene->_setDefault();
	p_selected.clear();

	_validateUpdate(scene,p_camera);
	if (p_needUpdate) {
		_prepareNodes(p_camera);
		_fillFilter(scene);
		if (p_count>0) {
			if ((fmode & 0xf)==ZUP) _sortZUpNodes(p_tempfilter,0,p_count-1);
			if ((fmode & 0xf)==ZDOWN) _sortZDownNodes(p_tempfilter,0,p_count-1);
		}
		p_needUpdate=false;
	}

	p_context->makeCurrent();
	p_camera->makeCurrent(_rect);

	matrix4f projMatrix;
	vector4i viewport=p_camera->getViewPort(p_context);
	functions.GetFloatv(GL_PROJECTION_MATRIX,(float*)&projMatrix);

	float vportScale[3]={(float)(0.5f*viewport.z),(float)(0.5f*viewport.w),(float)((p_camera->getMaxRange()-p_camera->getMinRange())*0.5f)};
	float vportAdd[3]={(float)(viewport.x+viewport.z*0.5f),(float)(viewport.y+viewport.w*0.5f),(float)p_camera->getMinRange()};
	double vportScaled[3];
	double vportAddd[3];
	vecFunctions.V3FAdd(vportAdd,vportScale,vportAdd);
	vecFunctions.V3FTo3D(vportScale,vportScaled);
	vecFunctions.V3FTo3D(vportAdd,vportAddd);

	char *buff=(char*)extFunctions.CreateMem(65536*(sizeof(buffSelectMesh4d)),0);
	buffSelectMesh4f *buffMesh4f=(buffSelectMesh4f *)buff;
	buffSelectMesh4d *buffMesh4d=(buffSelectMesh4d *)buff;

	Transform *mtransform;
	MeshFilter *geom;
	unsigned int i;
	vector4b *t;
	t=(vector4b*)&i;
	matrix4f mMatrix;
	matrix4d mMatrixd;
	for (i=0;i<p_count;i++)
	{
		mtransform=p_tempfilter[i];
		if (!mtransform->isSelected()) continue;
		geom=mtransform->getComponent<MeshFilter>();
		if (geom) {
			matrix4f mMatrix;
			vector3f mpos(mtransform->realPosition());
			quaternionf mrot(mtransform->realRotate());
			vecFunctions.M4FTRS(&mMatrix,&mpos,&mrot,mtransform->realScale());
			mMatrix=projMatrix*mMatrix;

			Mesh *mesh=geom->getMesh();
			unsigned int type=mesh->getVectorType();

			if (type==Mesh::_TGL_V2D || type==Mesh::_TGL_V3D || type==Mesh::_TGL_V4D) {
				vecFunctions.M4FToM4D(mMatrix.m,mMatrixd.m);
			}

			int count=mesh->elementsCount();
			bt::LinkArray<int>::iterator vectors=mesh->vector<int>().begin();
			if (count>65536) count=65536;
			if (type==Mesh::_TGL_V2F) {
				if (count>0) arvFunctions.A2FProj(&vectors.value(),&mMatrix,vportScale,vportAdd,buffMesh4f,vectors.step(),sizeof(buffSelectMesh4f),(_voidint)&buffMesh4f->flag-(_voidint)buffMesh4f,count);
			}
			if (type==Mesh::_TGL_V3F) {
				if (count>0) arvFunctions.A3FProj(&vectors.value(),&mMatrix,vportScale,vportAdd,buffMesh4f,vectors.step(),sizeof(buffSelectMesh4f),(_voidint)&buffMesh4f->flag-(_voidint)buffMesh4f,count);
			}
			if (type==Mesh::_TGL_V4F) {
				if (count>0) arvFunctions.A4FProj(&vectors.value(),&mMatrix,vportScale,vportAdd,buffMesh4f,vectors.step(),sizeof(buffSelectMesh4f),(_voidint)&buffMesh4f->flag-(_voidint)buffMesh4f,count);
			}
			if (type==Mesh::_TGL_V2D) {
				if (count>0) arvFunctions.A2DProj(&vectors.value(),&mMatrixd,vportScaled,vportAddd,buffMesh4d,vectors.step(),sizeof(buffSelectMesh4d),(_voidint)&buffMesh4d->flag-(_voidint)buffMesh4d,count);
			}
			if (type==Mesh::_TGL_V3D) {
				if (count>0) arvFunctions.A3DProj(&vectors.value(),&mMatrixd,vportScaled,vportAddd,buffMesh4d,vectors.step(),sizeof(buffSelectMesh4d),(_voidint)&buffMesh4d->flag-(_voidint)buffMesh4d,count);
			}
			if (type==Mesh::_TGL_V4D) {
				if (count>0) arvFunctions.A4DProj(&vectors.value(),&mMatrixd,vportScaled,vportAddd,buffMesh4d,vectors.step(),sizeof(buffSelectMesh4d),(_voidint)&buffMesh4d->flag-(_voidint)buffMesh4d,count);
			}
			bool isselected=false;
			bt::LinkArray<GlIndex> index=mesh->index<GlIndex>();
			if (type==Mesh::_TGL_V2F || type==Mesh::_TGL_V3F || type==Mesh::_TGL_V4F) {
				for (unsigned int e=0;e<index.count();e+=3) {
					int i1=index[e];
					int i2=index[e+1];
					int i3=index[e+2];
					if ((buffMesh4f[i1].flag & buffMesh4f[i2].flag & buffMesh4f[i3].flag & 0x33)==0) isselected=true;
				}
			}
			if (type==Mesh::_TGL_V2D || type==Mesh::_TGL_V3D || type==Mesh::_TGL_V4D) {
				for (unsigned int e=0;e<index.count();e+=3) {
					int i1=index[e];
					int i2=index[e+1];
					int i3=index[e+2];
					if ((buffMesh4d[i1].flag & buffMesh4d[i2].flag & buffMesh4d[i3].flag & 0x33)==0) isselected=true;
				}
			}
			if (isselected) p_selected.assign(mtransform);
		}
	}
	extFunctions.DeleteMem(buff,0);

	//if (i<p_count) p_selected.assign(p_tempfilter[i]);
	//Render::UnBindModel();

	return &p_selected;
}

void *Renderer::set(unsigned _int32 id,void *param)
{
	if (id==BaseObject::EVENT && active()) {
		BaseInterfaceEventSystem::Event *msg=(BaseInterfaceEventSystem::Event *)param;
		if (!msg) {
			if (p_input) input(); // ??? need set scene prepare before
			draw();
		}
//		if ((msg) && (msg->message==BaseInterfaceEventSystem::Intersection)) return (void*)getIntersection((vector2i*)&msg->lparam);
		return 0;
	}
	if (id==BaseObject::TYPE) return Renderer::t();
	if (id==BaseObject::WRITE) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		if ((p=list.find("camera"))!=0) setCamera(p->getString());
		if ((p=list.find("context"))!=0) setContext(p->getString());
		if ((p=list.find("input"))!=0) setSelectInput(p->getString());
		if ((p=list.find("sort"))!=0) setSort(p->getString());
		//
	}
	if (id==BaseObject::READ) {
		Variant *p;
		ParametersList &list=*(ParametersList *)param;
		p=&list["camera"];
		if (p_camera)
			p->setString(""); //Camera::finder path()
		p=&list["context"];
		if (p_context)
			p->setString(""); //GlContext::path()
	}
	return 0;
}

void Renderer::_init(int order)
{
	p_camera=0;
	p_context=0;
	p_input=0;
	p_needUpdate=true;
	p_count=0;
	p_size=0;
	fmode=ZUP;
	p_clear=GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	System::system().getIRS().registerTarget(order,this);

	p_tempfilter=0;
	cikles_inititem=0;
	cikles_prepare=0;
	cikles_fullitem=0;
	cikles_nodes=0;
	cikles_sort=0;
}

void Renderer::_prepareNodes(Camera *camera)
{
	Transform *transform=camera->getContainer();
	transform->setChildReal(transform);
	transform->setParentReal(transform);
}

void Renderer::_fillFilter(Scene *scene)
{
	ObjectsList &mapTransforms=scene->getMapObjects();
	ListSceneTransforms &transforms=scene->getObjects();
	p_count=0;

	unsigned int newSize=mapTransforms.count()+transforms.count();
	if (p_size!=newSize) {
		p_size=newSize;
		if (p_tempfilter) extFunctions.DeleteMem(p_tempfilter,0);
		p_tempfilter=(Transform **)extFunctions.CreateMem(sizeof(void*)*p_size,0);
	}
	if ((fmode & 0xf)!=TREE) {
		ObjectsList::iterator mit=mapTransforms.begin();
		ObjectsList::iterator end=mapTransforms.end();
		while (mit!=end){
			Transform *transform=(Transform *)mit.value();
			if (transform->isVisible()) {
				p_tempfilter[p_count]=transform;
				p_count++;
			}
			mit++;
		}
		for (unsigned int i=0;i<transforms.count();i++) {
			Transform *transform=transforms.at(i);
			if (transform->isVisible()) {
				p_tempfilter[p_count]=transform;
				p_count++;
			}
		}
	} else {
		Transform *transform=scene->getRoot();
		if (transform->isVisible()) {
			p_tempfilter[p_count]=transform;
			p_count++;
			p_count=_sortTreeNodes(p_tempfilter,0,p_count-1)+1;
		}
	}
}

void Renderer::_validateUpdate(Scene *scene,Camera *)
{
	if (!p_needUpdate) {
		p_needUpdate=scene->changes()!=p_sceneChanges;
		p_sceneChanges=scene->changes();
	}
}

void _sortZUpNodes(Transform** list,int begin,int end)
{
	int b=begin;
	int e=end;
	int s=(e+b)>>1;
	Transform *tr=list[s];
	double z=tr->realPosition()->z;
	double zz;

	bool wend=true;
	do {
		wend=true;
		do {
			tr=list[b];
			zz=tr->realPosition()->z;
			wend=(zz<z);
			if (wend) b++;
			wend&=(b<end);
		} while (wend);

		wend=true;
		do {
			tr=list[e];
			zz=tr->realPosition()->z;
			wend=(zz>z);
			if (wend) e--;
			wend&=(e>begin);
		} while (wend);
		wend=(b<e);
		if (wend) {
			tr=list[b];
			list[b]=list[e];
			list[e]=tr;
		}
		if (b<=e) {
			b+=(b<=end);
			e-=(e>0);
		}
	} while (wend);

	if (begin<e) _sortZUpNodes(list,begin,e);
	if (end>b) _sortZUpNodes(list,b,end);
}

void _sortZDownNodes(Transform** list,int begin,int end)
{
	int b=begin;
	int e=end;
	int s=(e+b)>>1;
	Transform *tr=list[s];
	double z=tr->realPosition()->z;
	double zz;

	bool wend=true;
	do {
		wend=true;
		do {
			tr=list[b];
			zz=tr->realPosition()->z;
			wend=(zz>z);
			if (wend) b++;
			wend&=(b<end);
		} while (wend);

		wend=true;
		do {
			tr=list[e];
			zz=tr->realPosition()->z;
			wend=(zz<z);
			if (wend) e--;
			wend&=(e>begin);
		} while (wend);
		wend=(b<e);
		if (wend) {
			tr=list[b];
			list[b]=list[e];
			list[e]=tr;
		}
		if (b<=e) {
			b+=(b<=end);
			e-=(e>0);
		}
	} while (wend);

	if (begin<e) _sortZDownNodes(list,begin,e);
	if (end>b) _sortZDownNodes(list,b,end);
}

int _sortTreeNodes(Transform** list,int begin,int end)
{
	while (begin<=end) {
		TransformList &listt=list[begin]->children();
		TransformList::iterator it=listt.begin();
		TransformList::iterator endd=listt.end();
		while (it!=endd) {
			Transform *transform=it.value();
			if (transform->isVisible()) {
				end++;
				list[end]=transform;
			}
			it++;
		}
		begin++;
	}
	return end;
}

TYPEINFO(Renderer)

}

OPTIMIZE_OFF;
WARNING_ENABLE;


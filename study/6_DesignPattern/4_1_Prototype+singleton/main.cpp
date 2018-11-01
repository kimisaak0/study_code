#include <iostream>
#include <list>
#include <map>

using namespace std;

//싱글톤 템플릿
template <class T> class singleton
{
public:
	static T& GetInstance()	
	{
		static T inst;
		return inst;
	}
};

//점
class Position
{
public:
	int m_ix;
	int m_iy;

public:
	Position() {}

	Position(int ix, int iy)
	{
		m_ix = ix;
		m_iy = iy;
	}
};

//그래픽 클래스들
class Graphic
{
public:
	virtual Graphic* Clone() = 0;
	virtual void Draw(Position pos)
	{
		cout << pos.m_ix << pos.m_iy;
	}
};

class Triangle : public Graphic
{
public:
	Graphic * Clone()
	{
		//복사 생성자 호출
		return new Triangle(*this);
	}
};

class Rectangle : public Graphic
{
public:
	Graphic * Clone()
	{
		//복사 생성자 호출
		return new Rectangle(*this);
	}
};

class GraphicComposite : public Graphic
{
public:
	list<Graphic*> m_Components;

public:
	Graphic * Clone()
	{
		//복사 생성자 호출
		GraphicComposite* pGC = new GraphicComposite(*this);

		list<Graphic*>::iterator iterSrc;
		for (iterSrc = m_Components.begin(); iterSrc != m_Components.end(); iterSrc++) {
			Graphic* pNewGraphic = (*iterSrc)->Clone();
			pGC->m_Components.push_back(pNewGraphic);
		}

		return pGC;
	}
};

//그외
class TMouse
{
public:
	Position m_pos;
	bool     m_bButton[3];

public:
	bool IsLeftButtonPushed()
	{
		return m_bButton[0];
	}

	Position GetPt()
	{
		return m_pos;
	}
};

TMouse g_Mouse;

class Document
{
public:
	list<Graphic*> m_docList;

public:
	void Add(Graphic* pObj)
	{
		m_docList.push_back(pObj);
	}
};

class GraphicEditor
{
public:
	Document   m_doc;

public:
	void AddNewGraphics(Graphic* pSeleted)
	{
		Graphic* pObj = pSeleted->Clone();
		while (g_Mouse.IsLeftButtonPushed()) {
			pObj->Draw(g_Mouse.GetPt());
		}

		m_doc.Add(pObj);
	}
};

class Palatte : public singleton<Palatte>
{
	friend class singleton<Palatte>;

private:
	map<int, Graphic*> m_items;



public:
	void Draw() {}

	void RegisterNewGraphic(Graphic* pGraphic) 
	{
		m_items[m_items.size() + 1] = pGraphic;
	}

	int GetItemOrder()
	{
		int iItem = 0;
		return iItem;
	}

	Graphic* GetSelectObj()
	{
		return m_items[GetItemOrder()];
	}

protected:
	Palatte()
	{
		Graphic* pGpA = new Triangle;
		m_items[0] = pGpA;
		Graphic* pGpB = new Rectangle;
		m_items[1] = pGpB;
	}
};
#define I_Palette Palatte::GetInstance()

int main()
{
	Palatte pallete = I_Palette;
	pallete.Draw();

	GraphicEditor editor;
	editor.AddNewGraphics(pallete.GetSelectObj());

	GraphicComposite etc;
	list<Graphic*>::iterator iter;
	for (iter = editor.m_doc.m_docList.begin();
		iter != editor.m_doc.m_docList.end();
		iter++) {
		Graphic* pData = (*iter);
		etc.m_Components.push_back(pData);
	}
	pallete.RegisterNewGraphic(&etc);
}
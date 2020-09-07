#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Visitor;
class Element
{
    string name;
public:
    Element(string name) : name(name) {}
    string GetName()const
    {
        return name;
    }
    virtual void Accept(Visitor* visitor) = 0;
};

class Picture;
class Diary;

class Visitor
{
public:
    virtual void VisitPicture(Picture* picture) = 0;
    virtual void VisitDiary(Diary* diary) = 0;
};

class Diary : public Element
{
    string content;
public:
    Diary(string name, string content) :Element(name)
    {
        SetContent(content);
    }

    void ViewContent()
    {
        cout << content << endl;
    }

    void SetContent(string content)
    {
        this->content = content;
    }

    virtual void Accept(Visitor* visitor)
    {
        visitor->VisitDiary(this);
    }
};

class Picture : public Element
{
    int tone;
    int brightness;
    int saturation;
public:
    Picture(string name, int tone, int brightness, int saturation) :Element(name)
    {
        SetInfo(tone, brightness, saturation);
    }

    void ViewInfo()
    {
        cout << "색조:" << tone << " 명도:" << brightness << " 채도:" << saturation << endl;
    }

    void SetInfo(int tone, int brightness, int saturation)
    {
        this->tone = tone;
        this->brightness = brightness;
        this->saturation = saturation;
    }

    virtual void Accept(Visitor* visitor)
    {
        visitor->VisitPicture(this);
    }
};

class Initializer : public Visitor
{
public:
    virtual void VisitPicture(Picture* picture)
    {
        picture->SetInfo(0, 0, 0);
    }

    virtual void VisitDiary(Diary* diary)
    {
        diary->SetContent("내용없음");
    }
};

class Viewer : public Visitor
{
public:
    virtual void VisitPicture(Picture* picture)
    {
        cout << "사진 제목:" << picture->GetName() << endl;
        picture->ViewInfo();
    }

    virtual void VisitDiary(Diary* diary)
    {
        cout << diary->GetName() << endl;
        diary->ViewContent();
    }
};

typedef vector<Element*> Collection;
typedef vector<Element*>::iterator CIter;
class MyTour
{
    Collection collection;
    Visitor* visitors[2];
public:
    MyTour()
    {
        visitors[0] = new Viewer();
        visitors[1] = new Initializer();
    }

    void AddElement(Element* element)
    {
        collection.push_back(element);
    }

    void ViewAll()
    {
        CIter seek = collection.begin();
        CIter end = collection.end();
        Element* element = 0;
        for (; seek != end; ++seek)
        {
            element = *seek;
            element->Accept(visitors[0]);
        }
    }
    void Reset()
    {
        CIter seek = collection.begin();
        CIter end = collection.end();
        Element* element = 0;
        for (; seek != end; ++seek)
        {
            element = *seek;
            element->Accept(visitors[1]);
        }
        cout << "모든 정보를 초기 상태로 바꾸었습니다." << endl;
    }
};

int main(void)
{
    MyTour* mt = new MyTour();
    Picture* e = new Picture("A", 1, 1, 1);

    Diary* d = new Diary("2016.2.26", "언제나 휴일");
    mt->AddElement(e);
    mt->AddElement(d);
    mt->ViewAll();
    mt->Reset();
    mt->ViewAll();

    delete e;
    delete d;
    delete mt;

    return 0;

}

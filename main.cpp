#include <iostream>
#include <set>

using namespace std;

class Action
{
public:
    Action(const int priority, void * owner) : priority(priority), owner(owner) {}
    virtual ~Action() {}
    
    virtual void execute() = 0;
    
    struct PrioritySorter
    {
        bool operator()(Action* a, Action* b)
        {
            return a->priority < b->priority;
        }
    };
    
    bool ownerIs(void * owner) const { return this->owner == owner; }

private:
    const int priority;
    void * owner;
};

class DrawBackgroundAction : public Action
{
public:
    DrawBackgroundAction(const int priority, void * owner) : Action(priority, owner) {}
    
    void execute()
    {
        cout << "drawing background" << endl;
    }
};

class DrawForegroundAction : public Action
{
public:
    DrawForegroundAction(const int priority, void * owner) : Action(priority, owner) {}
    
    void execute()
    {
        cout << "drawing foreground!!!" << endl;
    }
};

class DrawSomethingElseAction : public Action
{
public:
    DrawSomethingElseAction(const int priority, void * owner) : Action(priority, owner) {}

    void execute()
    {
        cout << "drawing something else" << endl;
    }
};

class DrawManager
{
public:
    DrawManager() {}
    ~DrawManager()
    {
        for ( ActionList::iterator i = actions.begin(), e = actions.end(); i != e; i++ )
        {
            delete *i;
        }
        actions.clear();
    }
    
    void draw()
    {
        for ( ActionList::iterator i = actions.begin(), e = actions.end(); i != e; i++ )
        {
            (*i)->execute();
        }
    }
    
    void addAction(Action* action)
    {
        actions.insert(action);
    }
    
    void removeOwnedActions(void * owner)
    {
        for ( ActionList::iterator i = actions.begin(), e = actions.end(); i != e; i++)
        {
            if ( (*i)->ownerIs(owner) )
            {
                delete *i;
                actions.erase(i);
            }
        }
    }
    
private:
    typedef std::set<Action*,Action::PrioritySorter> ActionList;
    ActionList actions;
};

class Example
{
public:
    Example()
    {
        manager.addAction(new DrawForegroundAction(100,this));
        manager.addAction(new DrawBackgroundAction(0,this));
        manager.addAction(new DrawSomethingElseAction(50,this));
    }
    
    void drawAll()
    {
        manager.draw();
    }

    void removeTheActionsIfYouWant()
    {
        manager.removeOwnedActions(this);
    }

private:
    DrawManager manager;
};

int main()
{
    Example ex;

    cout << "Drawing all" << endl;
    
    ex.drawAll();
    
    ex.removeTheActionsIfYouWant();
    
    cout << "Drawing again" << endl;
    
    ex.drawAll();
    
    return 0;
}
